#include "main.h"

char *av0 = NULL;
int verbose = 1;

void help() {
    printf("%s [OPTIONS]\n"
            "\n"
            "Starts a daemon to synchronize MaxMSP instances using a retro arduino serial protocol.\n"
            "This program listens for incoming serial data, packages it into OSC messages, and\n"
            "sends it to MaxMSP via UDP. It simultaneously listens for incoming UDP packets from\n"
            "MaxMSP containing OSC messages, and sends those along to the arduino over serial protocol.\n"
            "\n"
            "Options:\n"
            "  -v, --verbose       Be more verbose.\n"
            "  -q, --quiet         Be more quiet.\n"
            "  -p N, --port N      Send to UDP port N (default: 5556).\n"
            "  -l N, --listen N    Listen to UDP port N (default: 5557).\n"
            "  -s S, --serial S    Send to serial port S (default: first matching 'usbserial-*').\n"
            "  -?, --help          Show this help message, then exit immediately.\n"
            "\n"
            "Examples:\n"
            "  %s                                     # Start daemon with default options.\n"
            "  %s --serial usbserial-10 --port 6000   # Use specific serial port, and UDP port 6000.\n"
            "\n",
        av0, av0, av0);
    exit(0);
}

void usage(char *errmsg, char *detail) {
    if (detail)
        fprintf(stderr, "%s: %s: %s\n", av0, errmsg, detail);
    else
        fprintf(stderr, "%s: %s\n", av0, errmsg);
    fprintf(stderr, "Try --help to get a list of valid options.\n");
    exit(EXIT_FAILURE);
}

// Acceptable variations:
//  -x ARG
//  -xARG
//  --xxx ARG
//  --xxx=ARG
char *opt_with_arg(int *pac, char ***pav) {
    int ac = *pac;
    char **av = *pav;
    char *ret;

    if (av[0][1] != '-' && !av[0][2]) {
        // Variation: -x ARG
        if (ac < 2)
            usage("expected argument after option", *av);
        av++; ac--;
        ret = strdup(*av);
    } else if (av[0][1] != '-') {
        // Variation: -xARG
        ret = strdup(&av[0][2]);
    } else if ((ret = strchr(*av, '='))) {
        // Variation: --xxx=ARG
        if (!ret[1])
            usage("missing argument for option", *av);
        ret = strdup(ret+1);
    } else {
        // Variation: --xxx ARG
        if (ac < 2)
            usage("expected argument after option", *av);
        av++; ac--;
        ret = strdup(*av);
    }

    *pac = ac;
    *pav = av;
    return ret;
}

void parse_args(int ac, char **av) {
    av0 = *av;
    av++; ac--;
    while (ac) {
        if (!strcmp(*av, "-v") || !strcmp(*av, "--verbose")) {
            verbose++;
        } else if (!strcmp(*av, "-q") || !strcmp(*av, "--quiet")) {
            verbose--;
        } else if (!strncmp(*av, "-p", 2) || !strcmp(*av, "--port") || !strncmp(*av, "--port=", 7)) {
            char *p = opt_with_arg(&ac, &av);
            char *end = NULL;
            maxport = strtoul(p, &end, 10);
            if (!end || *end || maxport <= 0 || maxport > 0xfffe)
                usage("invalid UDP port number", p);
        } else if (!strncmp(*av, "-l", 2) || !strcmp(*av, "--listen") || !strncmp(*av, "--listen=", 9)) {
            char *p = opt_with_arg(&ac, &av);
            char *end = NULL;
            rcvport = strtoul(p, &end, 10);
            if (!end || *end || rcvport <= 0 || rcvport > 0xfffe)
                usage("invalid UDP port number", p);
        } else if (!strncmp(*av, "-s", 2) || !strcmp(*av, "--serial") || !strncmp(*av, "--serial=", 9)) {
            serial = opt_with_arg(&ac, &av);
        } else if (!strcmp(*av, "-?") || !strcmp(*av, "--help")) {
            help();
        } else if (!strcmp(*av, "-")) {
            usage("unrecognized option", *av);
        } else if ((*av)[0] == '-' && ((*av)[1] != '-')) {
            for (char *p = &(*av)[1]; *p; p++) {
                if (*p == 'q')
                    verbose--;
                else if (*p == 'v')
                    verbose++;
                else if (*p == '?')
                    help();
                else if (*p == 's')
                    usage("option 's' can't be combined with other options", *av);
                else if (*p == 'p')
                    usage("option 'p' can't be combined with other options", *av);
                else
                    usage("unrecognized option", *av);
            }
        } else {
            usage("unrecognized option", *av);
        }
        av++; ac--;
    }
    
    if (maxport == rcvport) {
        usage("Can't use same port for both sending and receiving UDP packets", NULL);
    }

    if (verbose < 0)
        verbose = 0;

}
