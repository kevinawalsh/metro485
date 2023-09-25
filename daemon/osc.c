#include "main.h"

// Open Sound Control (osc) conversion routines.
//
// OSC messages sent to/from MaxMSP carry:
//  - a tag string
//  - a parameter descriptor string, like ",iiifss" 
//  - zero or more corresponding int32, float32, or string parameters.
// All parts align to 4-byte boundaries.
// Integer and float parameters are encoded in 4-byte, big-endian format.
// Strings are 8-bit ascii, nul-terminated ascii, and padded with extra nul
// bytes to align to a 4-byte boundary.
//
// Examples:
// "start"
//    73 74 61 72 74 00 00 00 2c 00 00 00
//    s  t  a  r  t  _  _  _  ,  _  _  _
//
// "debug 1"
//   64 65 62 75 67 00 00 00 2c 69 00 00 00 00 00 01
//   d  e  b  u  g  _  _  _  ,  i  _  _  _  _  _  _
//
// "send twinkle twinkle 42 teapots 3.14 cupcakes"
//   73 65 6e 64 00 00 00 00 2c 73 73 69 73 66 73 00 74 77 69 6e 6b 6c 65 00 74
//    s  e  n  d  _  _  _  _  ,  s  s  i  s  f  s  _  t  w  i  n  k  l  e  _  t
//   77 69 6e 6b 6c 65 00 00 00 00 2a 74 65 61 70 6f 74 73 00 40 48 f5 c3 63 75
//    w  i  n  k  l  e  _  _  _  _  *  t  e  a  p  o  t  s  _  @  H  _  _  c  u
//   70 63 61 6b 65 73 00 00 00 00
//    p  c  a  k  e  s  _  _  _  _
//
// Messages to arduinos use plain ascii, where each message is one line with a
// tag string, then zero or more integer, float, or string parameters. 
// The tag and string parameters are escaped so they contain only printable
// 7-bit clean ascii with no spaces, newlines, etc. String parameters are
// prefixed with "s:" if they are empty or start with +, -, ., or a digit, or if
// they start with "s:" or "f:". Integer parameters are formatted in decimal,
// with no prefix. Float parameters are formatted as hex, prefixed with "f:",
// unless they can be represented exactly using "%g" formatting, in which case
// that's used instead with no prefix.
//
// Examples:
// "start\n"
// "debug 1\n"
// "set 168 1 2 3 4\n"
// "pi is about 3.14\n"
// "pi is more like f:4048f5c3\n"
// "send twinkle_twinkle 42 tea_pots f:4048f5c3 cupcakes\n".
//
// Messages from arduinos use tagged ascii with checksums, where each message
// is one line and starts with either:
// - '*', followed by a debug message
// - '+' followed by a plain ascii message as described above
// - '#', a hex checksum, a space, and a plain ascii message as described above
// The checksum is probably overkill and should be removed. It was intended to
// protect against garbage messages at the start of a connection, but that can
// be avoided by waiting until a valid identification message arrives before
// accepting other messages.

// 8-bit nul terminated string
size_t osc_convert_s(str osc, size_t *pos, str ascii) {
    if (*pos + 4 > osc->len) {
        printf_locked("Error: OSC packet truncated, expecting string at position %d\n", *pos);
        return 0;
    }
    if (ascii->len > 0)
        str_append1(ascii, ' ');
    uchar *start = osc->buf + *pos;
    uchar *end = memchr(start, '\0', osc->len - *pos);
    if (!end) {
        printf_locked("Error: OSC packet truncated, expecting zero byte after position %d\n", *pos);
        return 0;
    }
    if (!*start || start[0] == '+' || start[0] == '-' || start[0] == '.' ||
            ('0' <= start[0] && start[0] <= '9') ||
            ((start[0] == 's' || start[0] == 'f') && start[1] == ':')) {
        str_append(ascii, "s:");
    }
    ascii_escape2(ascii, start, end - start, 0);
    size_t n = (end - start) + 1;
    while ((n % 4) != 0) {
        if (*end != '\0') {
            printf_locked("Warning: misaligned OSC data\n");
        }
        n++;
        end++;
    }
    *pos += n;
    return n;
}

// 32-bit integer
size_t osc_convert_i(str osc, size_t *pos, str ascii) {
    if (*pos + 4 > osc->len) {
        printf_locked("Error: OSC packet truncated, expecting 4-byte integer at position %d\n", *pos);
        return 0;
    }
    int32_t v;
    v  = osc->buf[(*pos)+0] << 24;
    v |= osc->buf[(*pos)+1] << 16;
    v |= osc->buf[(*pos)+2] << 8;
    v |= osc->buf[(*pos)+3] << 0;
    str_printf(ascii, " %d", v);
    *pos += 4;
    return 4;
}

int float_is_unambiguous(char *buf, int32_t floatbits) {
    float f2;
    sscanf(buf, "%f", &f2);
    int32_t b;
    memcpy(&b, &f2, 4);
    float f1;
    memcpy(&f1, &floatbits, 4);
    return (b == floatbits);
}

// 32-bit float
int osc_convert_f(str osc, size_t *pos, str ascii) {
    if (*pos + 4 > osc->len) {
        printf_locked("Error: OSC packet truncated, expecting 4-byte integer at position %d\n", *pos);
        return 0;
    }
    int v;
    v  = osc->buf[(*pos)+0] << 24;
    v |= osc->buf[(*pos)+1] << 16;
    v |= osc->buf[(*pos)+2] << 8;
    v |= osc->buf[(*pos)+3] << 0;
    float f;
    memcpy(&f, &v, 4);
    char buf[32];
    sprintf(buf, "%g", f);
    if (!strchr(buf, '.') && !strchr(buf, 'e') && !strchr(buf, 'E'))
        strcat(buf, ".");
    if (float_is_unambiguous(buf, v)) {
        str_printf(ascii, " %s", buf);
    } else {
        str_printf(ascii, " f:%x", v);
    }
    *pos += 4;
    return 4;
}

str osc_to_ascii(str osc) {
    if (osc->len < 8 || (osc->len % 4) != 0) {
        printf_locked("Error: invalid OSC packet size\n");
        return NULL;
    }

    size_t pos = 0;
    str result = str_new(osc->len + 100);

    // parse the tag string, append to result
    size_t taglen = osc_convert_s(osc, &pos, result);
    if (taglen == 0)  {
        printf_locked("Error: OSC packet has missing or empty tag\n");
        str_free(&result);
        return NULL;
    }

    // parse the descriptor string, save for later
    str args = str_new(4);
    osc_convert_s(osc, &pos, args);
    if (args->buf[0] != ',') {
        printf_locked("Warning: OSC packet has missing or invalid descriptor string\n");
        str_free(&args);
        str_append1(result, '\n');
        return result;
    }

    size_t ok = 1;
    for (size_t i = 1; i < args->len && ok != 0; i++) {
        uchar desc = args->buf[i];
        if (desc == 'i') {
            ok = osc_convert_i(osc, &pos, result);
        } else if (desc == 'f') {
            ok = osc_convert_f(osc, &pos, result);
        } else if (desc == 's') {
            ok = osc_convert_s(osc, &pos, result);
        } else {
            ok = 0;
            printf_locked("Error: unsupported OSC parameter descriptor: %c\n", desc);
        }
    }
    if (ok && pos != osc->len) {
        printf_locked("Error: OSC packet has trailing data\n");
    }
    str_free(&args);
    str_append1(result, '\n');
    return result;
}

void unescape2_and_align(str osc, char *ascii) {
    ascii_unescape2(osc, ascii, 0);
    str_append1(osc, '\0');
    while ((osc->len % 4) != 0)
        str_append1(osc, '\0');
}

str ascii_to_osc(str ascii, size_t initialPos) {
    size_t pos = initialPos;
  
    str tag = str_next_word(ascii, &pos);
    if (!tag) {
        printf_locked("Error: line is missing leading tag word\n");
        return NULL;
    }

    str args = str_new(100);
    str desc = str_new(4);
    str_append1(desc, ',');

    str param = str_next_word(ascii, &pos);
    while (param) {
        if (param->buf[0] == 's' && param->buf[1] == ':') {
            // string using prefix
            str_append1(desc, 's');
            unescape2_and_align(args, (char *)param->buf+2);
        } else if (param->buf[0] == 'f' && param->buf[1] == ':') {
            // float32 using prefix
            str_append1(desc, 'f');
            uchar *e;
            unsigned int v = (unsigned int)strtoul((char*)param->buf+2, (char**)&e, 16);
            if (e != param->buf + param->len) {
                printf_locked("Error: invalid hex-encoded float32\n");
            }
            str_append1(args, 0xff & (v >> 24));
            str_append1(args, 0xff & (v >> 16));
            str_append1(args, 0xff & (v >> 8));
            str_append1(args, 0xff & (v >> 0));
        } else if (param->buf[0] == '+' || param->buf[0] == '-' || param->buf[0] == '.' ||
                ('0' <= param->buf[0] && param->buf[0] <= '9')) {
            if (!strchr((char*)param->buf, '.') && !strchr((char*)param->buf, 'e') && !strchr((char*)param->buf, 'E')) {
                // int32
                str_append1(desc, 'i');
                char *e;
                int v = (int)strtol((char*)param->buf, &e, 10);
                if (e != (char*)param->buf + param->len) {
                    printf_locked("Error: invalid int32\n");
                }
                str_append1(args, 0xff & (v >> 24));
                str_append1(args, 0xff & (v >> 16));
                str_append1(args, 0xff & (v >> 8));
                str_append1(args, 0xff & (v >> 0));
            } else {
                // float32 using "%g" format
                str_append1(desc, 'f');
                char *e;
                float f = strtof((char*)param->buf, &e);
                if (e != (char*)param->buf + param->len) {
                    printf_locked("Error: invalid int32\n");
                }
                int v;
                memcpy(&v, &f, 4);
                str_append1(args, 0xff & (v >> 24));
                str_append1(args, 0xff & (v >> 16));
                str_append1(args, 0xff & (v >> 8));
                str_append1(args, 0xff & (v >> 0));
            }
        } else {
            // string without prefix
            str_append1(desc, 's');
            ascii_unescape2(args, (char*)param->buf, 0);
            str_append1(args, '\0');
            while ((args->len % 4) != 0)
                str_append1(args, '\0');
        } 
        str_free(&param);
        param = str_next_word(ascii, &pos);
    }

    // put it all together now
    str osc = str_new(200);
    unescape2_and_align(osc, (char*)tag->buf);
    unescape2_and_align(osc, (char*)desc->buf);
    str_appendN(osc, (char*)args->buf, args->len);
   
    str_free(&tag);
    str_free(&desc);
    str_free(&args);
    return osc;
}

void ascii_escape2(str result, void *buf, size_t n, int allowSpaces) {
    uchar *s = buf;
    for (size_t i = 0; i < n; i++) {
        uchar c = s[i];
        if (' ' < c && c <= '~' && c != '_') {
            str_append1(result, c);
        } else if (c == ' ') {
            str_append1(result, allowSpaces ? ' ' : '_');
        } else if (c == '_') {
            str_append(result, allowSpaces ? "_" : "\\_");
        } else if (c == '\n') {
            str_append(result, "\\n");
        } else if (c == '\r') {
            str_append(result, "\\r");
        } else if (c == '\t') {
            str_append(result, "\\t");
        } else if (c == '\\') {
            str_append(result, "\\\\");
        } else {
            str_printf(result, "\\x%02x", c);
        }
    }
}

// str ascii_escape(str s, int allowSpaces) {
//     str result = str_new(100);
//     ascii_escape2(result, s->buf, allowSpaces);
//     return rsult;
// }

void ascii_unescape2(str result, char *s, int allowSpaces) {
    for (uchar c = *s; c; c = *(++s)) { 
        uchar c1 = s[1];
        if (c == '\\' && c1 == '\\') {
            str_append1(result, '\\');
            s++;
        } else if (c == '\\' && c1 == '_') {
            str_append1(result, '_');
            s++;
        } else if (c == '_') {
            str_append1(result, allowSpaces ? '_' : ' ');
        } else if (c == '\\' && c1 == 'n') {
            str_append1(result, '\n');
            s++;
        } else if (c == '\\' && c1 == 'r') {
            str_append1(result, '\r');
            s++;
        } else if (c == '\\' && c1 == 't') {
            str_append1(result, '\t');
            s++;
        } else if (c == '\\' && c1 == 'x') {
            if (!s[2] || !s[3]) {
                printf_locked("warning: truncated hex escape sequence\n");
                break;
            }
            char num[3];
            num[0] = s[2];
            num[1] = s[3];
            num[2] = '\0';
            char *e;
            char v = (char)strtoul(num, &e, 16);
            size_t n = (e - num);
            if (n != 2) {
                printf_locked("warning: invalid hex escape sequence\n");
                s++; // skip the 'x'
                continue;
            }
            str_append1(result, v);
            s += 1 + n;
        } else if (c == '\\' && c1 == '\0') {
            printf_locked("warning: truncated hex escape sequence\n");
            break;
        } else if (c == '\\') {
            // for \", \', etc., ignore slash, just take whatever comes next
        } else {
            str_append1(result, c);
        }
    }
}

