#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <glob.h>
#include <signal.h>
#include <pthread.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <termios.h>

typedef unsigned char uchar;

// usage.c
extern char *av0; // program path, from argv[0]
extern int verbose;
void help(void); // print help then exit
void usage(char *errmsg, char *detail); // print errors and optional detail then fail
void parse_args(int ac, char **av); // parse command-line arguments

// debug.c
void close_handles(void);
void exit_fail(char *msg, ...);
void exit_perror(char *syscall, char *msg, ...);

// helpers.c
extern pthread_mutex_t print_lock;
void printf_locked(char *msg, ...); // printf, but multi-threaded
int file_exists(char *path);

// str.c
typedef struct str_buf {
  size_t cap; // capacity of buffer, not including nul terminator
  size_t len; // length of buffer, not including nul terminator
  uchar *buf; // size is cap+1, zero-filled except for initial len bytes
} *str;
str str_new(size_t cap);
str str_empty(void);
str str_from(char *cstr);
void str_free(str *s);
void str_clear(str s);
void str_ensure(str s, size_t space);
void str_append1(str s, char c);
void str_append(str s, char *m);
void str_appendN(str s, char *m, size_t n);
str str_tail(str s, size_t i);
str str_mid(str s, size_t i, size_t n);
void str_discard_prefix(str s, size_t n);
str str_split(str s, size_t n);
str str_splitline_after(str s, size_t n);
void str_skip_spaces(str ascii, size_t *pos);
str str_next_word(str ascii, size_t *pos);
ssize_t str_printf(str s, char *fmt, ...); // returns negative on error
void str_dump_bytes(str s, char *title);
void str_show_ascii(str s, char *title);

// osc.c
str osc_to_ascii(str osc); // caller must free result
str ascii_to_osc(str ascii, size_t initialPos); // caller must free result
void ascii_unescape2(str result, char *s, int allowSpace);
void ascii_escape2(str result, void *s, size_t n, int allowSpace);

// usb.c
extern volatile struct termios saveoptions;
extern volatile int serialfd;
int open_serial(char *name);
void serial_wait_for_ready(void);
str serial_readline(unsigned int *timeout_us);
void serial_write(str line);

// udp.c
extern volatile int sockfd;
void open_udp_socket(void);

// main.c
extern volatile int ready;
extern volatile int exiting;
extern str board_mode;
extern str board_version;
extern int maxport; // dest port to send UDP messages to MaxMSP
extern int rcvport; // recv port to receive UDP messages from MaxMSP
extern char *serial; // name of serial port
extern socklen_t maddr_len, raddr_len; // maxmsp and daemon UDP addresses
extern struct sockaddr *maddr, *raddr;


#endif // _MAIN_H_
