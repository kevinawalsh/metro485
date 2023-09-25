/*
 * Listens to laptop over USB, sends to conductor over RS485. Also listens to
 * conductor over RS485, sends to laptop over USB.
 * 
 * Created:
 *   K. Walsh (kwalsh@holycross.edu) 16 September 2023
 * 
 */
#include <SoftwareSerial.h>
#include "util.h"

#define IDENTIFICATION   "+metro remote v1.1 ready\n"

// Pins
#define LED_G                   (2)
#define LED_R                   (3)
#define LED_B                   (4)
#define LED_Y                   (5)
// UNUSED                       (6)
#define RS485_ISOLATED_TX_DATA  (7) /* working for this device */
#define RS485_ISOLATED_RX_DATA  (8)
#define LED_N                   LED_BUILTIN // D13

// Variables
SoftwareSerial rs485(RS485_ISOLATED_RX_DATA, RS485_ISOLATED_TX_DATA); // RX, TX
LineBuffer local_input(&Serial); // for commands from laptop connected over USB
bool debug_metro = false;

// A player can mute their ticks locally by setting enabled to false. This
// also turns off all LEDs.
bool enabled = true;

// A player can dim their lights locally by setting illuminated to false. This
// only affects the LEDs.
bool illuminated = true;

// These variables are used internally.
byte last_color = 0; // last received color value, or 0 if none available
byte last_seqno = 0; // last received seqno value, or 0 if none available
byte start_at = 0; // start when we next arrive at this seqno
byte stop_at = 0; // stop when we next arrive at this seqno
byte illuminate_at; // illuminate lights when we next arrive at this seqno
byte dim_at; // dim lights when we next arrive at this seqno


void setup() {
  Serial.flush(); // attempt to avoid garbage output on startup
  Serial.begin(57600);
  while (!Serial) { } // wait for native USB serial

  rs485.begin(14400); // 4800 seemed to work fine
  while (!rs485) { } // wait for RS 485

  pinMode(LED_N, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  digitalWrite(LED_N, HIGH);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_Y, HIGH);

  Serial.write("\n\n\n\n");
  Serial.write(IDENTIFICATION);
}

void setLights(byte color) {
  int map = color_map[color];
  digitalWrite(LED_G, (map & 1) ? LOW : HIGH);
  digitalWrite(LED_R, (map & 2) ? LOW : HIGH);
  digitalWrite(LED_B, (map & 4) ? LOW : HIGH);
  digitalWrite(LED_Y, (map & 8) ? LOW : HIGH);
}

void process_command(const char *buf) {
  int n = -1;
  if (match(&buf, "debug", &n)) {
    // takes effect immediately
    debug_metro = (n != 0);
  } else if (match(&buf, "start", &n)) {
    // takes effect when given seqno arrives (or immediately if seqno not given or zero),
    // ignored if already enabled
    if (enabled)
      return;
    if (n <= 0) {
      enabled = true;
      start_at = 0;
      stop_at = 0;
      if (illuminated)
        setLights(last_color);
      if (debug_metro)
        Serial.write("* metro player enabled\n");
    } else {
      start_at = n;
      if (debug_metro) {
        Serial.write("* metro player will enable at seqno ");
        Serial.print(n, DEC);
        Serial.write("\n");
      }
    }
  } else if (match(&buf, "stop", &n)) {
    // takes effect when given seqno arrives (or immediately if seqno not given or zero),
    // ignored if already enabled
    if (!enabled)
      return;
    if (n <= 0) {
      enabled = false;
      start_at = 0;
      stop_at = 0;
      setLights(0);
      if (debug_metro) {
        Serial.write("* metro player disabled\n");
      }
    } else {
      start_at = 0;
      stop_at = n;
      if (debug_metro) {
        Serial.write("* metro player will disable at seqno ");
        Serial.print(n, DEC);
        Serial.write("\n");
      }
    }
  } else if (match(&buf, "illuminate", &n)) {
    // takes effect on given seqno (or immediately if seqno not given or 0),
    // ignored if already illuminated
    dim_at = 0;
    if (illuminated)
      return;
    if (n <= 0) {
      illuminated = true;
    } else {
      illuminate_at = n;
      if (debug_metro) {
        Serial.write("* will illuminate on seqno ");
        Serial.print(n, DEC);
        Serial.write("\n");
      }
    }
  } else if (match(&buf, "dim", &n)) {
    // takes effect on given seqno (or immediately if seqno not given or 0),
    // ignored if already dimmed
    illuminate_at = 0;
    if (!illuminated)
      return;
    if (n <= 0) {
      illuminated = false;
    } else {
      dim_at = n;
      if (debug_metro) {
        Serial.write("* will dim on seqno ");
        Serial.print(n, DEC);
        Serial.write("\n");
      }
    }
  } else if (match(buf, "identification")) {
    Serial.write("\n\n\n\n");
    Serial.write(IDENTIFICATION);
  } else {
    if (debug_metro) {
      Serial.write("* unrecognized command\n");
    }
  }
}

byte rs_read_blocking() {
  int c = rs485.read();
  while (c < 0) {
    c = rs485.read();
  }
  if (debug_metro) {
    Serial.write("* ");
    Serial.print(c >> 4, HEX);
    Serial.print(c & 4, HEX);
    Serial.write('\n');
  }
  return (byte)c;
}

int rs_read_nonblocking() {
  int c = rs485.read();
  if (c >= 0 && debug_metro) {
    Serial.write("* ");
    Serial.print(c >> 4, HEX);
    Serial.print(c & 4, HEX);
    Serial.write('\n');
  }
  return c;
}

void update_settings(byte seqno) {
  if (illuminate_at == seqno) {
    illuminated = true;
    illuminate_at = 0;
  }
  if (dim_at == seqno) {
    illuminated = false;
    dim_at = 0;
  }
  if (start_at == seqno) {
    enabled = true;
    start_at = 0;
  }
  if (stop_at == seqno) {
    enabled = false;
    stop_at = 0;
  }
}

void remote_command(const char *buf) {
  if (debug_metro) {
    int n = strlen(buf);
    Serial.write("* metro remote sending ");
    Serial.print(n+1, DEC);
    Serial.write(" bytes: '");
    Serial.write(buf);
    Serial.write("\\n'\n");
  }
  rs485.write("\x02\n"); // STX, newline... clear out any garbage in buffer
  rs485.write(buf);
  rs485.write("\n");
}

char tick_msg[64]; // "tick cc ss"

void process_tick(byte b0, byte b1) {
  byte tag = b0 & 0xfc; // top 6 bits
  byte seqno = (((int)(b0 & 0x3)) << 4) | ((b1>>4)&0xf);
  byte color = b1 & 0xf;
  if (seqno == 0)
    seqno = 64;
  if (color == 0)
    color = 16;

  last_color = (tag == 0xB4) ? color : 0;
  update_settings(seqno);

  if (tag == 0xB4 && illuminated && enabled)
    setLights(color);
  else
    setLights(0);

  if (enabled) {
    sprintf(tick_msg, "+tick %d %d\n", color, seqno);
    Serial.write(tick_msg);
  } 
}

char payload[261]; // 256 payload, 1 terminator, 4 for "msg "

void loop() {
  // process commands, if needed
  if (char *line = local_input.nextLine()) {
    if (match(line, "identify")) {
      Serial.write("\n\n\n\n");
      Serial.write(IDENTIFICATION);
    } else if (match_prefix(&line, "local ")) {
      process_command(line);
    } else if (match_prefix(&line, "all ")) {
      remote_command(line);
    } else {
      remote_command(line);
    }
  }

  // Process rs485 data, if available
  int s = rs_read_nonblocking();
  if (s < 0) {
    return;
  }
  if ((s & 0xfc) == 0xB4 || (s & 0xfc) == 0x68) {
    byte b = rs_read_blocking();
    process_tick(s, b);
  } else if (s == 0xD6) {
    // dim lights immediately
    illuminated = false;
    illuminate_at = 0;
    dim_at = 0;
    setLights(0);
  } else if (s == 0xD7) {
    // illuminate lights immediately
    illuminated = true;
    illuminate_at = 0;
    dim_at = 0;
    setLights(last_color);
  } else if (s = 0xAA) {
    byte nn = rs_read_blocking();
    // byte h0 = rs_read_blocking();
    // byte h1 = rs_read_blocking();
    // unsigned int rchk = (((int)h0) & 0xff << 8) | (((int)h1) & 0xff);
    unsigned int n = ((int)nn) & 0xff;
    unsigned int got = rs485.readBytes(payload, n);
    if (got != n) {
      if (debug_metro)
        Serial.write("* ERR truncated message or timeout");
    } else {
      payload[n] = '\0';
      // unsigned int lchk = compute_checksum(payload);
      // if (lchk != rchk) {
      //   if (debug_metro)
      //     Serial.write("* ERR bad checksum");
      // } else {
        Serial.write("+msg ");
        Serial.write(payload);
        Serial.write('\n');
      // }
    }
  } else {
    if (debug_metro) {
      Serial.write("* ERR unrecognized serial data\n");
    }
  }
}
