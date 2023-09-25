
.PHONY: all
all: metro485


metro485: main.h main.c usage.c str.c debug.c osc.c udp.c usb.c
	clang -o metro485 -g -Wall -Werror main.c usage.c str.c debug.c osc.c udp.c usb.c


.PHONY: clean
clean:
	rm -f metro485
	rm -rf *.dSYM
