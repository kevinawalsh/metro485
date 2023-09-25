#include "main.h"

volatile int sockfd = -1;

struct sockaddr *get_addr(char *node, int port, socklen_t *addrlen) {
    struct addrinfo hints, *ai;
    bzero(&hints, sizeof(hints));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family = AF_INET;
    hints.ai_protocol = 0;
    hints.ai_flags = /* AI_NUMERICHOST | */ AI_NUMERICSERV;

    char portstr[20];
    snprintf(portstr, sizeof(portstr), "%d", port);
    if (getaddrinfo(node, portstr, &hints, &ai))
        exit_perror("getaddrinfo", "Could not get UDP address information for %s:%d.\n", node, port);
    if (!ai)
        exit_fail("No UDP address information available for %s:%d\n", node, port);

    *addrlen = ai->ai_addrlen;
    struct sockaddr *addr = malloc(ai->ai_addrlen);
    memcpy(addr, ai->ai_addr, ai->ai_addrlen);
    freeaddrinfo(ai);
    return addr;
}

void open_udp_socket(void) {
    maddr = get_addr("127.0.0.1", maxport, &maddr_len);
    raddr = get_addr("127.0.0.1", rcvport, &raddr_len);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        close_handles();
        exit(EXIT_FAILURE);
    }

    int enable = 1;
    int rc = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    if (rc) {
        perror("setsockopt");
        close_handles();
        exit(EXIT_FAILURE);
    }

    if (bind(sockfd, raddr, raddr_len)) {
        perror("UDP bind");
        close_handles();
        fprintf(stderr, "Could not bind to UDP port %d\n", rcvport);
        exit(EXIT_FAILURE);
    }
    printf_locked("  Sending OSC to UDP port: %d\n", maxport);
    printf_locked("  Receiving OSC on UDP port: %d\n", rcvport);
}

