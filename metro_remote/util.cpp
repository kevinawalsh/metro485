#include "util.h"

// GREEN=1 RED=2 BLUE=4 YELLOW=8
byte color_map[] = {
  0,             // color #0, aka color #16, no LEDs
  1,             // color #1
  2,             // color #2
  4,             // color #3
  8,             // color #4
  8+4,           // color #5
  8+2,           // color #6
  8+1,           // color #7
  4+1,           // color #8
  2+1,           // color #9
  1+2+4,         // color #10
  2+4+8,         // color #11
  1+2+8,         // color #12
  1+4+8,         // color #13
  2+4,           // color #14
  1+2+4+8,       // color #15
};

bool match(const char **buf, const char *cmd, int *param) {
  int cmdlen = strlen(cmd);
  if (!strcasecmp(*buf, cmd)) {
    *buf += cmdlen;
    *param = -1;
    return true;
  }
  if (!strncasecmp(*buf, cmd, cmdlen) && (*buf)[cmdlen] == ' ') {
    const char *p = (*buf) + cmdlen + 1;
    const char *e;
    int n = (int)strtol(p, &e, 10);
    if (e == p || n < 0) {
      if (debug_metro)
        Serial.write("* ERR bad parameter\n");
        return false;
    }
    *buf = e;
    *param = n;
    return true;
  }
  return false;
}

bool match_prefix(const char **buf, const char *cmd) {
  int cmdlen = strlen(cmd);
  if (!strncasecmp(*buf, cmd, cmdlen)) {
    *buf += cmdlen;
    return true;
  }
  return false;
}

bool match(const char *buf, const char *cmd) {
  return !strcasecmp(buf, cmd);
}

LineBuffer::LineBuffer(Stream *base) : base(base), len(0), eol(-1) { }

char *LineBuffer::nextLine() {
  // discard current line, if present
  if (eol >= 0) {
    eol = -1;
    len = 0;
  }
  // read more data, if available
  int b = base->read();
  // process data
  while (b >= 0) {
    if (len < LINE_BUFFER_LEN) {
      // append to buffer
      if (b == '\n') {
        buf[len] = '\0';
        eol = len;
        return buf;
      } else {
        buf[len] = b;
        len++;
      }
    } else if (b == '\n') {
      // buffer had overflowed, reset to prepare for more data
      len = 0;
    } else if (len == LINE_BUFFER_LEN && debug_metro) {
      // buffer just overflowed, print error, but only once
      Serial.print("* ERR buffer overflow\n");
      len++; // ensures further overflow bytes won't print errors
    }
    // get more data, if available
    b = base->read();
  }
  // next line is not yet avilable
  return nullptr;
}

LineBuffer::linelen() {
  return eol;
}

