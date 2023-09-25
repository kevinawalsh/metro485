#include "main.h"

// Protocol:
//
//   Arduino              Arduino               Laptop            Laptop
//  Coordinator            Player               Daemon            MaxMSP
//      |  <---------------> |  <-------------->  |  <----------> :5556
//      |    rs485 serial    |      USB-serial    |       UDP       |
//      |                    |                    |                 |
//      |  -- binary msg-->  |                    |                 |
//      |                    |  -- ascii msg -->  |                 |
//      |                    |                    |  -- osc msg --> |
//
// Arduino Player Message        Deaemon Message
// (ascii line)                  (osc packet)           Comments
// metro player vX.Y ready       n/a                    validates, prints to console
// * error/status message        n/a                    prints to console
// tick color seqno              {tick color seqno}     color is 1..16, seqno=1..64
// msg ...                       {msg ... }             payload is a list of (int, float, string) data

_Static_assert(sizeof(int) == 4, "sizeof(int) expected to be 4 bytes");
_Static_assert(sizeof(float) == 4, "sizeof(float) expected to be 4 bytes");

int baud = 57600;
char *serial = NULL;
int maxport = 5556; // dest port to send UDP messages to MaxMSP
int rcvport = 5557; // recv port to receive UDP messages from MaxMSP

volatile int ready = 0;
volatile int exiting = 0;

str board_mode = NULL; // player, conductor, remote, etc.
str board_version = NULL; // v1.0, v1.1, etc.

socklen_t maddr_len, raddr_len;
struct sockaddr *maddr, *raddr;

void *xfer_maxmsp_to_arduino(void *arg) {
    str udp = str_new(4096);
    for (;;) {
        // Wait for UDP message from MaxMSP
        ssize_t udp_len = recv(sockfd, udp->buf, udp->cap, 0);
        if (udp_len < 0)
            exit_perror("recv", "Could not receive UDP message");
        udp->len = (size_t)udp_len;
        if (verbose >= 2)
            str_dump_bytes(udp, "UDP packet");
        // Convert to equivalent ascii message
        str ascii = osc_to_ascii(udp);
        if (ascii) {
            // Send to arduino over USB serial
            if (verbose >= 2) {
                printf_locked("Sending ascii message to arduino on port %s\n", serial);
                str_show_ascii(ascii, "ascii message");
            }
            serial_write(ascii);
            str_free(&ascii);
        }
        // Prepare for next message
        str_clear(udp);
    }
}

void *xfer_arduino_to_maxmsp(void *arg) {
    for (;;) {
        // Wait for ascii message from arduino over USB serial
        str line = serial_readline(NULL);
        if (!line) {
            return NULL; // serial port closed or failed
        } else if (line->buf[0] == '\0') {
            // do nothing, arduino sent blank line
        } else if (line->buf[0] == '*') {
            // Arduino sent a debug message
            str_show_ascii(line, "Arduino debug");
        } else if (line->buf[0] == '+') {
            // Arduino sent a regular message
            if (verbose >= 2)
                str_show_ascii(line, "Arduino message");
            // Convert to equivalent OSC message
            str osc = ascii_to_osc(line, 1);
            if (osc) {
                // Send to MaxMSP over UDP
                if (verbose >= 2) {
                    printf_locked("Sending OSC message to MaxMSP on port %d\n", maxport);
                    str_dump_bytes(osc, "OSC message");
                }
                ssize_t n = sendto(sockfd, osc->buf, osc->len, 0, maddr, maddr_len);
                if (n < 0 || (size_t)n != osc->len)
                    fprintf(stderr, "Error: failed to send OSC message to MaxMSP.\n");
                str_free(&osc);
            }
        } else {
            // Arduino sent garbage
            if (verbose >= 1)
                str_show_ascii(line, "Arduino unexpected data");
        }
        // Parepare for next message
        str_free(&line);
    }
}

void intr_handler(int ignore) {
    close_handles();
    fprintf(stderr, "\nKilled by user, exiting.\n");
    exit(0);
}

int main(int ac, char **av) {

    parse_args(ac, av);

    serialfd = open_serial(serial);

    signal(SIGINT, intr_handler);
    signal(SIGPIPE, SIG_IGN);

    serial_wait_for_ready();

    open_udp_socket();

    pthread_t tid;
    pthread_create(&tid, NULL, xfer_maxmsp_to_arduino, NULL);

    xfer_arduino_to_maxmsp(NULL);

    if (verbose >= 1)
        printf_locked("Exiting.\n");

    close_handles();
    pthread_join(tid, NULL);
    exit(0);
}
