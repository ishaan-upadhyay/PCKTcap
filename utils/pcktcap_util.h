#ifndef PCKTCAP_UTIL_H
#define PCKTCAP_UTIL_H

#include <iostream>

/* Print a byte stream, given the stream and its length. */
inline void print_byte_stream(unsigned char *packet, int length) {
    for (int i = 0; i < length; ++i) {
        printf("%02x ", packet[i]);
    }
    std::cout << std::endl;
}

#endif // PCKTCAP_UTIL_H