
.PHONY: all
all: global-metro


global-metro: main.h main.c usage.c str.c debug.c osc.c udp.c usb.c
	gcc -o global-metro -g -Wall -Werror main.c usage.c str.c debug.c osc.c udp.c usb.c


.PHONY: clean
clean:
	rm -rf global-metro *.dSYM
