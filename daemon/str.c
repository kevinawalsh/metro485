#include "main.h"

str str_new(int cap) {
    if (cap <= 100)
        cap = 100;
    str s = calloc(sizeof(struct str_buf), 1);
    s->buf = calloc(cap+1, 1);
    s->cap = cap;
    return s;
}

str str_empty() {
    return str_new(0);
}

str str_from(char *cstr) {
    int n = strlen(cstr);
    str s = calloc(sizeof(struct str_buf), 1);
    s->buf = calloc(n+1, 1);
    s->cap = n;
    memcpy(s->buf, cstr, n);
    s->len = n;
    return s;
}

void str_free(str *s) {
    if (!*s)
        return;
    str_clear(*s);
    free((*s)->buf);
    (*s)->buf = NULL;
    free((*s));
    *s = NULL;
}

void str_clear(str s) {
    memset(s->buf, 0, s->len);
    s->len = 0;
}

void str_ensure(str s, int space) {
    if (space < 0)
        space = 0;
    if (s->len + space <= s->cap)
        return;
    int n = s->len + space + 10; // a little extra
    uchar *newbuf = realloc(s->buf, n+1);
    memset(newbuf + s->cap, 0, n + 1 - s->cap);
    s->buf = newbuf;
    s->cap = n;
}

void str_append1(str s, char c) {
    str_ensure(s, 1);
    s->buf[s->len++] = c;
}

void str_append(str s, char *m) {
    int n = strlen(m);
    str_ensure(s, n);
    memcpy(s->buf+s->len, m, n);
    s->len += n;
}

void str_appendN(str s, char *m, int n) {
    str_ensure(s, n);
    memcpy(s->buf+s->len, m, n);
    s->len += n;
}

str str_tail(str s, int i) {
    int n = s->len - i;
    if (n < 0) {
        printf_locked("Error: invalid substring\n");
        return str_empty();
    }
    if (n == 0) {
        return str_empty();
    }
    str result = str_new(n);
    memcpy(result->buf, s->buf + i, n);
    result->len = n;
    return result;
}

str str_mid(str s, int i, int n) {
    if (n < 0 || i < 0 || i + n > s->len) {
        printf_locked("Error: invalid substring\n");
        return str_empty();
    }
    str result = str_new(n);
    memcpy(result->buf, s->buf + i, n);
    result->len = n;
    return result;
}

void str_discard_prefix(str s, int n) {
    if (n < 0) {
        printf_locked("Error: invalid prefix length\n");
    } else if (n > s->len) {
        printf_locked("Error: invalid prefix length\n");
        str_clear(s);
    } else if (n > 0) {
        memmove(s->buf, s->buf + n, s->len - n);
        memset(s->buf + (s->len - n), 0, n);
        s->len -= n;
    }
}

str str_split(str s, int n) {
    if (n < 0) {
        printf_locked("Error: invalid prefix length\n");
        return str_empty();
    }
    if (n > s->len) {
        printf_locked("Error: invalid prefix length\n");
        n = s->len;
    }
    str result = str_new(n);
    str_appendN(result, (char*)s->buf, n);
    str_discard_prefix(s, n);
    return result;
}

str str_splitline_after(str s, int n) {
    if (n < 0)
        n = 0;
    else if (n > s->len)
        return NULL;
    uchar *e = memchr(s->buf+n, '\n', s->len - n);
    if (!e)
        return NULL;
    str line = str_split(s, e - s->buf + 1);
    line->buf[line->len] = '\0';
    line->len--;
    return line;
}

void str_skip_spaces(str ascii, int *pos) {
    while (*pos < ascii->len && ascii->buf[*pos] == ' ')
        (*pos)++;
}

str str_next_word(str ascii, int *pos) {
    str_skip_spaces(ascii, pos);
    if (*pos == ascii->len)
        return NULL;
    uchar *start = ascii->buf + *pos;
    uchar *end = memchr(start, ' ', ascii->len - *pos);
    str result;
    if (!end) {
        result = str_tail(ascii, *pos);
        *pos = ascii->len;
    } else {
        int n = (end - start);
        result = str_mid(ascii, *pos, n);
        *pos += n;
    }
    return result;
}


int str_printf(str s, char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf((char*)s->buf + s->len, s->cap - s->len, fmt, ap);
    va_end(ap);
    if (n < 0) {
        memset(s->buf + s->len, 0, s->cap - s->len);
        return n;
    }
    if (s->len + n < s->cap) {
        s->len += n;
        return n;
    }
    str_ensure(s, n);
    va_start(ap, fmt);
    vsnprintf((char *)s->buf + s->len, s->cap - s->len, fmt, ap);
    va_end(ap);
    s->len += n;
    return n;
}

void str_dump_bytes(str s, char *title) {
    pthread_mutex_lock(&print_lock);
    int n;
    if (title)
        n = printf("%s, %d bytes:", title, s->len);
    else
        n = printf("%d bytes:", s->len);
    for (int i = 0; i < s->len; i++)
        printf(" %02x", s->buf[i]);
    if (s->len > 0) {
        printf("\n%*s:", n-1, ""); // indent
        for (int i = 0; i < s->len; i++) {
            if (' ' <= s->buf[i] && s->buf[i] <= '~')
                printf("  %c", s->buf[i]);
            else
                printf("  _");
        }
    }
    printf("\n");
    pthread_mutex_unlock(&print_lock);
}

void str_show_ascii(str s, char *title) {
    str safe = str_new(200);
    ascii_escape2(safe, s->buf, s->len, 1);
    if (title)
        printf_locked("%s: %s\n", title, safe->buf);
    else
        printf_locked("%s\n", safe->buf);
    str_free(&safe);
}
