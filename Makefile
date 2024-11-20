CC = g++
CFLAGS = -Wall -g
LIBS = -lpcap -I./dependencies
HDRS = capture/layer.h capture/packet-eth.h capture/packet-arp.h 
SRCS = capture/main.cc capture/packet-eth.cc capture/packet-arp.cc

all: main

main: capture/main.cc
	$(CC) $(CFLAGS) -o PCKTcap $(SRCS) $(HDRS) $(LIBS)

clean:
	rm -f capture/*.out capture/*.o PCKTcap