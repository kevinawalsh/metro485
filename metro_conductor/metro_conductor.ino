/*
 * Listens to laptop over USB and over special dedicated RS485 connection, sends
& * messages to multiple players over multiple RS485 serial connections.
 * 
 * Created:
 *   K. Walsh (kwalsh@holycross.edu) 24 August 2023
 * 
 */
#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <SoftwareSerial.h>
#include <NoDelay.h>
#include "util.h"

#define IDENTIFICATION   "+metro conductor v1.1 ready\n"

// Pins
#define RS485_TX_DATA  (2)
#define RS485_RX_DATA  (3)
#define LED_Y          (5)
#define LED_B          (6)
#define LED_R          (7)
#define LED_G          (8)
#define LED_N          LED_BUILTIN // D13

// Variables
SSD1306AsciiWire oled;
SoftwareSerial rs485(RS485_RX_DATA, RS485_TX_DATA); // RX, TX
LineBuffer local_input(&Serial); // for commands from laptop connected over USB
LineBuffer remote_input(&rs485); // for commands from laptop connected over rs485
bool debug_metro = false;

// Fonts used for OLED screen
#define SMALLFONT ZevvPeep8x16
#define LARGEFONT CalBlk36

// When ticking is true, we are sending out periodic messages to all players.
bool ticking = false;

// When illuminated is true, arduinos will used LEDs to show data in messages.
bool illuminated = true;

// The value of tick_ms controls how often messages are sent, in milliseconds.
// Very small values (below 50ms?) are probably not as accurate, because we
// don't currently make any attempt to account for processing and transmission
// delays. The meximum value 9999 (this is an arbitrary choice, but waiting 10
// seconds or more between beats seems unlikely in practice).
int tick_ms = 500;

// The patterns of values sent out in messages is called the meter. A meter with
// length 12 would send out messages numbered 1, 2, 3, ... 12, then repeat the
// same sequence again starting from 1. These are called sequence numbers, they
// always start at 1, count up to some maximum value, then go back to 1. Each
// message also contains a color number, which can be used to subdivide the
// meter. For example, a meter with length 12 could be subdivided into a color
// pattern [1 2 3 4 1 2 3 4 1 2 1 2], for example, to get a 4-4-2-2 repeating
// pattern. Or it could be divided into [ 1 2 3 1 2 3 1 2 3 1 2 3] to get a
// 3-3-3-3 repeating pattern, or [ 1 2 3 4 5 6 1 2 3 4 5 6] to get a 6-6
// pattern. 
//
// There are no constraints on the pattern of colors for subdividing a meter. A
// meter could be [ 1 1 2 2 3 3 4 4 ] if desired, so colors are repated twice.
// Or, [ 4 3 2 1 1 2 3 4 ] would make the colors go down then back up, etc.
//
// The Arduino normally displays the color value using the LEDs (1 = Green, 2 =
// Red, etc.), but this can be "muted". Also, color 16 is invisible, so if this
// is included in the meter, it will effectively mute only the corresponding
// messages. Color 0 is synonymous with color 16.
//
// Because of the way messages are currently encoded, there are limitations:
//   The maximum length of a meter is 64.
//   The color values must be between 1 and 16. Color 0 is a synonym for 16.
//   There are only a few LEDs on the arduino, so combinations are sometimes
//   used. For example, color numbrer 6 might be shown as Red+Green.

byte meter_len; // length of meter, maximum is 64
byte meter[64]; // pattern of colors that make up the meter, each between 1 and 16

// seqno tracks the current sequence number, counting from 1.
byte seqno, prevSeqno = 0;

// These variables are used internally.
noDelay tickDelay(tick_ms, false);
int next_tick_ms = 0;  // after current meter finishes, used to update tick_ms
byte next_meter_len = 0; // after current meter finishes, used to update meter
byte next_meter[64]; // after current meter finishes, used to update meter
byte stop_at; // stop when we next arrive at this seqno
byte illuminate_at; // illuminate lights when we next arrive at this seqno
byte dim_at; // dim lights when we next arrive at this seqno

void update_settings();

// Update the OLED screen with new information. Currently the display shows the
// meter (or part of it, if the meter is very long), the tick_ms value, and a
// notice about whether debug messages are enabled.
//    +=================+
//    | 1 2 3 1 2 3     |
//    |                 |
//    |  125 ms         |
//    |                 |
//    | debug enabled   |
//    +=================+
bool cleared = false;
void oled_update() {
  if (!debug_metro) {
    if (!cleared) {
      oled.clear();
      oled.setFont(LARGEFONT);
      oled.setCursor(0, 0);
      oled.print("metro");
      oled.setCursor(0, 4);
      oled.print("485");
      cleared = true;
    }
    return; // too slow for normal use
  }
  cleared = false;
  oled.clear();

  char buf[30];

  int v = tick_ms;
  buf[0] = (tick_ms >= 1000 ? '0' + v / 1000 : ' '); v %= 1000;
  buf[1] = (tick_ms >= 100 ? '0' + v / 100 : ' '); v %= 100;
  buf[2] = (tick_ms >= 10 ? '0' + v / 10 : ' '); v %= 10;
  buf[3] = '0' + v;
  buf[4] = '\0';
  oled.setFont(LARGEFONT);
  oled.setCursor(17, 2);
  oled.print(buf);
  if (ticking) {
    oled.setCursor(2, 3);
    oled.print("*");
  }

  int idx = 0;
  buf[idx++] = meter[0] <= 9 ? ('0' + meter[0]) : ('A' + (meter[0] - 10));
  for (int i = 1; i < meter_len && idx < 26; i++) {
    if (meter_len <= 8)
      buf[idx++] = ' ';
    buf[idx++] = meter[i] <= 9 ? ('0' + meter[i]) : ('A' + (meter[i] - 10));
  }
  buf[idx] = '\0';
  oled.setFont(SMALLFONT);
  oled.setCursor(0, 0); oled.print(buf);
  oled.setCursor(110, 4); oled.print("ms");
  if (debug_metro) {
    oled.setCursor(0, 6); oled.print("debug enabled");
  } else {
    // oled.setCursor(0, 6); oled.print("debug disabled");
  }
}

void setLights(int cccc) {
  int map = color_map[cccc & 0xf];
  digitalWrite(LED_G, (map & 1) ? LOW : HIGH);
  digitalWrite(LED_R, (map & 2) ? LOW : HIGH);
  digitalWrite(LED_B, (map & 4) ? LOW : HIGH);
  digitalWrite(LED_Y, (map & 8) ? LOW : HIGH);
}

// Ticks are encoded in 16 bits:
//      1011 01ss ssss cccc  (when illuminated)
//  or: 0110 10ss ssss cccc  (when not illuminated)
//  where ssssss is the sequence number (modulo 64)
//    and cccc is the color number (modulo 16)
// Illuminate/dim messages are encoded in 8 bits:
//      1101 011i
// where i is either 1 or 0 to illuminate or dim the lights.
// Arbitrary ascii string, up to 256 bytes, is sent as 4+N bytes:
//    0xAA nn xx xx ... character payload ...
// where nn is the payload length
//   and xxxx is a hash of the payload
char tick_msg[16];
void tick() {
  byte color = meter[seqno-1];

  // send message to all players
  byte ssssss = seqno & 0x3f; // 6 bits
  byte cccc = color & 0xf; // 4 bits
  byte tag = illuminated ? 0xB4 : 0x68; // 6 bits, upper end
  byte b0 = tag | (ssssss)>>4;  // tag, plus top 2 bits of ssssss
  byte b1 = (ssssss<<4) | cccc;  // rest of ssssss, plus cccc
  rs485.write(b0);
  rs485.write(b1);

  // send message to remote control laptop over special rs485 connection
  sprintf(tick_msg, "+tick %d %d\n", (int)color, (int)seqno);
  Serial.write(tick_msg);

  // update our LEDs
  if (illuminated) {
    setLights(cccc);
  }
  prevSeqno = seqno;
  seqno = seqno + 1;
  if (seqno > meter_len)
    seqno = 1;
}

void process_command(const char *buf) {
  int n = -1;
  if (match(buf, "start")) {
    // takes effect immediately
    if (!ticking) {
      ticking = true;
      stop_at = 0;
      // digitalWrite(LED_N, HIGH);
      oled_update();
      update_settings();
      tickDelay.start();
      tick();
    }
  } else if (match(&buf, "stop", &n)) {
    // takes effect when given seqno arrives (or immediately if seqno not given or zero),
    // ignored if not ticking
    if (!ticking)
      return;
    if (n <= 0) {
      ticking = false;
      tickDelay.stop();
      stop_at = 0;
      // digitalWrite(LED_N, LOW); // to indicate standby
      oled_update();
    } else {
      stop_at = n;
      if (debug_metro) {
        Serial.write("* will stop on seqno ");
        Serial.print(n, DEC);
        Serial.write("\n");
      }
    }
  } else if (match(buf, "reset")) {
    // takes effect on next tick
    seqno = 1;
    if (debug_metro) {
      Serial.write("* reset to start of meter\n");
    }
  } else if (match(buf, "set")) {
    // takes effect when seqno = 1
    next_tick_ms = 500;
    next_meter_len = 4;
    next_meter[0] = 1;
    next_meter[1] = 2;
    next_meter[2] = 3;
    next_meter[3] = 4;
      if (debug_metro) {
        Serial.write("* will set ms to 500 ms per tick with meter len 4\n");
      }
  } else if (match(&buf, "set", &n)) {
    // takes effect when seqno is 1
    if (n > 9999) {
      if (debug_metro)
        Serial.write("* ERR bad parameter\n");
      return;
    }
    if (n > 0) {
      next_tick_ms = n;
      if (debug_metro) {
        Serial.write("* will set ms to ");
        Serial.print(next_tick_ms, DEC);
        Serial.write(" ms per tick\n");
      }
    }
    next_meter_len = 0;
    const char *p = buf;
    const char *e;
    while (*p != '\0') {
      int led = (int)strtol(p, &e, 10);
      if (p == e) {
        if (debug_metro)
          Serial.write("* ERR bad meter\n");
        break;
      }
      if (next_meter_len >= 64) {
        if (debug_metro)
          Serial.write("* ERR meter overflow\n");
        break;
      }
      if (led < 0 || led > 16) {
        if (debug_metro)
          Serial.write("* ERR bad color\n");
        led &= 0x4; // coerce into range 0 to 15
      }
      if (led == 0)
        led = 16;
      next_meter[next_meter_len] = led;
      next_meter_len++;
      p = e;
    }
  } else if (match(&buf, "illuminate", &n)) {
    // takes effect on given seqno (or immediately if seqno not given or 0),
    // mostly ignored if already illuminated
    dim_at = 0;
    if (illuminated)
      return;
    if (n <= 0) {
      illuminated = true;
      rs485.write(0xD7);
      setLights(prevSeqno > 0 ? meter[prevSeqno-1] : 0);
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
    // mostly ignored if already dimmed
    illuminate_at = 0;
    if (!illuminated)
      return;
    if (n <= 0) {
      illuminated = false;
      rs485.write(0xD6);
      setLights(0);
    } else {
      dim_at = n;
      if (debug_metro) {
        Serial.write("* will dim on seqno ");
        Serial.print(n, DEC);
        Serial.write("\n");
      }
    }
  } else if (match_prefix(&buf, "send ")) {
    char *payload = buf;
    int nn = strlen(payload);
    // unsigned int chk = compute_checksum(payload);
    rs485.write(0xAA);
    rs485.write((byte)nn);
    // rs485.write((chk >> 8) & 0xff);
    // rs485.write((chk >> 0) & 0xff);
    rs485.write(payload);
    Serial.write("+msg ");
    Serial.write(payload);
    Serial.write('\n');
  } else if (match(&buf, "debug", &n)) {
    // takes effect immediately
    debug_metro = (n != 0);
    oled_update();
  } else if (match(buf, "identify")) {
    Serial.write("\n\n\n\n");
    Serial.write(IDENTIFICATION);
  } else {
    if (debug_metro) {
      Serial.write("* ERR unrecognized command\n");
      Serial.write("* CMD: ");
      Serial.write(buf);
      Serial.write("\n");
    }
  }
}

void process_remote_command(const char *buf) {
  int n = strlen(buf);
  if (buf < 2)
    return;
  if (buf[n-1] == '\x02') // STX, ignore garbage in buffer
    return;
  // buf = validate_checksum(buf);
  // if (buf)
  process_command(buf);
}

// Initialize arduino.
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

  meter_len = 4;
  meter[0] = 1;
  meter[1] = 2;
  meter[2] = 3;
  meter[3] = 4;
  seqno = 1;

  Wire.begin();
  oled.begin(&Adafruit128x64, 0x3C);
  oled.clear();

  oled_update();

  Serial.write("\n\n\n\n");
  Serial.write(IDENTIFICATION);
}

void update_settings() {
  bool updated = false;
  if (seqno == 1 && next_tick_ms) { // question: better to not wait until end of meter?
    tick_ms = next_tick_ms;
    tickDelay.setdelay(tick_ms);
    next_tick_ms = 0;
    updated = true;
  }
  if (seqno == 1 && next_meter_len) {
    meter_len = next_meter_len;
    memcpy(meter, next_meter, meter_len);
    next_meter_len = 0;
    updated = true;
  }
  if (seqno == stop_at) {
    ticking = false;
    tickDelay.stop();
    stop_at = 0;
    // digitalWrite(LED_N, LOW); // to indicate standby
    updated = true;
  }
  if (seqno == illuminate_at) {
    illuminated = true;
    illuminate_at = 0;
    rs485.write(0xD7);
    if (!ticking)
      setLights(prevSeqno > 0 ? meter[prevSeqno-1] : 0);
  }
  if (seqno == dim_at) {
    illuminated = false;
    dim_at = 0;
    rs485.write(0xD6);
    setLights(0);
  }
  if (updated)
    oled_update();
}

void loop() {
  // update settings and send out message, if needed
  if (!ticking || tickDelay.update()) {
    update_settings();
    if (ticking)
      tick();
  }

  // process commands, if needed
  if (char *line = local_input.nextLine())
    process_command(line);
  if (char *line = remote_input.nextLine())
    process_remote_command(line);
}
