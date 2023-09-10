/*
 * Listens laptop over USB, sends to conductor hub over RS485.
 * 
 * The circuit:
 *  * Pins D2, D3, D4, D5 connected to red/green/blue/yellow LEDs (active low)
 *  * Pin D7 is connected to RS485 module pin DI, via magneto-isolator, used to transmit.
 *  * Pin D8 is connected to RS485 module pin RO, via magneto-isolator, used to receive data (not enabled for this board).
 *  * Pin D13 is built-in LED.
 * 
 * Created:
 *   K. Walsh (kwalsh@holycross.edu) 24 August 2023
 * 
 */
#include <SoftwareSerial.h>

// Pins
#define LED_G                   (2)
#define LED_R                   (3)
#define LED_B                   (4)
#define LED_Y                   (5)
// UNUSED                       (6)
#define RS485_ISOLATED_TX_DATA  (7)
#define RS485_ISOLATED_RX_DATA  (8)
#define LED_N                   LED_BUILTIN // D13

SoftwareSerial rs485(RS485_ISOLATED_RX_DATA, RS485_ISOLATED_TX_DATA); // RX, TX

bool debug_metro = true;

// BEGIN USB CMD

void process_usb(int len, const char *buf);
int usb_idx = 0;
char usb_buf[256];

void usb_pump() {
    int b = Serial.read();
    while (b >= 0) {
        if (usb_idx < 256) {
            if (b == '\n') {
                usb_buf[usb_idx] = '\0';
                process_usb(usb_idx, usb_buf);
                usb_idx = 0;
            } else {
                usb_buf[usb_idx] = b;
                usb_idx++;
            }
        } else if (b == '\n') {
            usb_idx = 0;
        } else {
            if (usb_idx == 256 && debug_metro) {
                Serial.print("* ERR USB overflow\n");
                usb_idx++;
            }
        }
        b = Serial.read();
    }
}

void serial_write_chk(char *line) {
  unsigned int chk = 0;
  for (char *p = line; *p; p++) {
    chk = chk * 31 + (((unsigned int)*p) & 0xff);
  }
  Serial.write("#");
  Serial.print(chk, HEX);
  Serial.write(" ");
  Serial.write(line);
  Serial.write("\n");
}

void rs_write_chk(char *line) {
  unsigned int chk = 0;
  for (char *p = line; *p; p++) {
    chk = chk * 31 + (((unsigned int)*p) & 0xff);
  }
  rs485.write("#");
  rs485.print(chk, HEX);
  rs485.write(" ");
  rs485.write(line);
  rs485.write("\n");
  Serial.write("Sent: ");
  serial_write_chk(line);
}

// END USB CMD

void setup() {
    Serial.flush(); // attempt to avoid garbage output on startup
    Serial.begin(57600);
    while (!Serial) { } // wait for native USB serial

    rs485.begin(4800);
    while (!rs485) { } // wait for RS 485

    pinMode(LED_N, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_Y, OUTPUT);
    digitalWrite(LED_N, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_Y, HIGH);

    serial_write_chk("metro remote v1.0 ready");
}

void process_usb(int len, const char *buf) {
  digitalWrite(LED_G, LOW);
  rs_write_chk(buf);
  digitalWrite(LED_G, HIGH);
}

void loop() {
    usb_pump();
}
