CC = g++
CFLAGS = -Wall -Wextra -g -std=c++17
LIBS = -lpcap $(shell pkg-config --cflags --libs libmongocxx)
HDRS = capture/layer.h capture/packet-eth.h capture/packet-arp.h capture/packet-ipv4.h
SRCS = capture/main.cc capture/packet-eth.cc capture/packet-arp.cc capture/packet-ipv4.cc

all: main

main: capture/main.cc
	$(CC) $(CFLAGS) -o PCKTcap $(SRCS) $(HDRS) $(LIBS)

clean:
	rm -f capture/*.out capture/*.o PCKTcap