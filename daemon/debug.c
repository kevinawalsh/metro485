#include "main.h"

pthread_mutex_t print_lock = PTHREAD_MUTEX_INITIALIZER;

void printf_locked(char *msg, ...) {
    pthread_mutex_lock(&print_lock);
    va_list ap;
    va_start(ap, msg);
    vprintf(msg, ap);
    va_end(ap);
    fflush(stdout);
    pthread_mutex_unlock(&print_lock);
}

void close_handles(void) {
    exiting = 1;
    if (sockfd >= 0) {
        close(sockfd);
        sockfd = -1;
    }
    if (serialfd >= 0) {
        struct termios options = saveoptions;
        tcsetattr(serialfd, TCSANOW, &options);
        close(serialfd);
        serialfd = -1;
    }
}


void exit_fail(char *msg, ...) {
    if (exiting)
        pthread_exit(NULL); // msleep(1000); // give other thread a chance to close, print, and exit
    close_handles();
    if (msg) {
        va_list ap;
        va_start(ap, msg);
        vfprintf(stderr, msg, ap);
        va_end(ap);
    }
    exit(EXIT_FAILURE);
}

void exit_perror(char *syscall, char *msg, ...) {
    if (exiting)
        pthread_exit(NULL); // msleep(1000); // give other thread a chance to close, print, and exit
    exiting = 1;
    perror(syscall);
    close_handles();
    if (msg) {
        va_list ap;
        va_start(ap, msg);
        vfprintf(stderr, msg, ap);
        va_end(ap);
    }
    exit(EXIT_FAILURE);
}
