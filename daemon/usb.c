#include "main.h"

static str recvd;
volatile struct termios saveoptions;
volatile int serialfd = -1;

int file_exists(char *path) {
  struct stat st;   
  return stat(path, &st) == 0;
}

void subtract_elapsed_since(unsigned int *timeout_us, struct timespec start)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    int64_t elapsed =
        ((int64_t)now.tv_sec - (int64_t)start.tv_sec) * (int64_t)1000000 +
        ((int64_t)now.tv_nsec - (int64_t)start.tv_nsec) / 1000;
    if (elapsed <= 0)
        return;
    else if (elapsed > *timeout_us)
        *timeout_us = 0;
    else
        *timeout_us -= (int)elapsed;
}

str serial_readline(unsigned int *timeout_us) {
    str line = str_splitline_after(recvd, 0);
    if (line) {
        if (verbose >= 2)
            str_dump_bytes(line, "recv from arduino");
        return line;
    }

    struct timespec start = { 0 };
    unsigned int time_remaining = 0;
    if (timeout_us && *timeout_us > 0) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        time_remaining = *timeout_us;
    }

    size_t pos = recvd->len;
    for (;;) {
        if (timeout_us) {
            fd_set read_fds;
            FD_ZERO(&read_fds);
            FD_SET(serialfd, &read_fds);
            struct timeval timeout;
            timeout.tv_sec = time_remaining/1000000;
            timeout.tv_usec = time_remaining%1000000;
            int avail = select(serialfd + 1, &read_fds, NULL, NULL, &timeout);
            if (avail != 1) { // timeout with no data available
                subtract_elapsed_since(timeout_us, start);
                if (verbose >= 2) {
                    printf("Timeout waiting for data from %s\n", serial);
                }
                return NULL;
            }
        }
        str_ensure(recvd, 256);
        size_t left = recvd->cap - recvd->len;
        ssize_t n = read(serialfd, recvd->buf + recvd->len, left);
        if (n < 0)
            exit_perror("read", "Could not read from serial port.\n");
        if ((size_t)n > left)
            exit_fail("Unexpected overflow reading from serial port (%d > %d).\n", n, left);
        if (n == 0)
            exit_fail("Serial port closed unexpectedly.\n");
        recvd->len += (size_t)n;
        line = str_splitline_after(recvd, pos);
        if (line) {
            if (verbose >= 2)
                str_dump_bytes(line, "recv from arduino");
            return line;
        }
        pos = recvd->len;
        if (timeout_us && *timeout_us <= 0)
            return NULL;
        if (timeout_us && *timeout_us > 0) {
            time_remaining = *timeout_us;
            subtract_elapsed_since(&time_remaining, start);
        }
    }
}

void serial_write(str line) {
    size_t sent = write(serialfd, line->buf, line->len);
    if (sent != line->len)
        exit_perror("write", "Could not write to serial port.");
}

void try_ready(void) {
    unsigned int timeout_us = 5000000;
    while (!ready) {
        str line = serial_readline(&timeout_us);
        if (!line) { // timeout
            printf_locked("Arduino on %s not yet identified.\n", serial);
            return;
        }
        str_show_ascii(line, serial);
        size_t pos = 0;
        str title = str_next_word(line, &pos);
        str mode = str_next_word(line, &pos);
        str version = str_next_word(line, &pos);
        str status = str_next_word(line, &pos);
        if (!title || strcmp((char*)title->buf, "+metro")) {
            // ignore this line
        } else if (!mode && !version && !status) {
            printf_locked("Warning: malformed identification string.\n");
        } else if (strcmp((char*)status->buf, "ready")) {
            printf("Warning: unexpected status.\n");
        } else {
            board_mode = mode;
            board_version = version;
            mode = version = NULL;
            ready = 1;
        }
        str_free(&mode);
        str_free(&version);
        str_free(&status);
        str_free(&title);
        str_free(&line);
    }
}

void serial_wait_for_ready(void) {
    str query = str_from("identify\n");
    try_ready();
    for (int i = 0; i < 4 && !ready; i++) { // up to 4 more tries
        serial_write(query);
        try_ready();
    }
    if (!ready)
        exit_fail("Arduino on %s is not responding.\n", serial);

    printf("===========================================\n");
    printf("Connected to global-metro arduino hardware.\n");
    printf("  Port: %s\n", serial);
    printf("  Mode: %s\n", board_mode->buf); // todo: ascii-escape this?
    printf("  Version: %s\n", board_version->buf); // todo: ascii-escape this?
    printf("  Status: ready\n");
}

int open_serial(char *name) {
    recvd = str_new(2048);
    // todo: Maybe try to turn off DTR so Arduino doesn't reset on open?
    char *path = NULL;
    if (!name) { // open any /dev/cu.usbserial*
        glob_t g;
        int rc = glob("/dev/cu.usbserial*", 0, NULL, &g);
        if (rc == GLOB_NOMATCH)
            usage("no matching serial ports found", "/dev/cu.usbserial*");
        if (rc)
            usage("can't enumerate serial ports", "/dev/cu.usbserial*");
        path = strdup(g.gl_pathv[0]);
        globfree(&g);
    } else if (file_exists(name)) { // try name
        path = name;
    } else if (!strchr(name, '/')) {  // try /dev/cu.name
        size_t n = strlen("/dev/cu.") + strlen(name) + 1;
        char *s = malloc(n);
        snprintf(s, n, "/dev/cu.%s", name);
        if (file_exists(s)) {
            path = s;
        } else {
            fprintf(stderr, "No such serial port '%s' or '/dev/cu.%s\n", name, name);
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "No such serial port '%s'\n", name);
        exit(EXIT_FAILURE);
    }

    serial = path;
    if (verbose >= 2)
        printf("Opening serial port '%s'\n", path);
    int fd = open(path, O_RDWR);
    if (fd < 0)
        exit_perror("open", "Could not open serial port '%s'\n", path);

    struct termios options;
    int rc = tcgetattr(fd, &options);
    if (rc < 0)
        exit_perror("tcgetattr", "Could not query serial port '%s'\n", path);
    saveoptions = options;

    cfsetispeed(&options, B57600);
    cfsetospeed(&options, B57600);
    cfmakeraw(&options);
    options.c_cc[VMIN] = 1;  // read minimum is 1 byte
    options.c_cc[VTIME] = 10; // read timeout is 10 deciseconds
    options.c_cflag &= ~CSTOPB; // don't use 2 stop bits
    options.c_cflag &= ~CRTSCTS; // no hardware RTS/CTS flow control
    options.c_cflag |= CLOCAL | CREAD; // ignore control signals, enable reading
    options.c_cflag |= CS8 | B57600;
    rc = tcsetattr(fd, TCSANOW, &options);
    if (rc < 0)
        exit_perror("tcgetattr", "Could not configure serial port '%s'\n", path);

    return fd;
}

