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

/* Helper function to convert a byte stream to a MAC address string. */
inline std::string byte_stream_to_mac_string(unsigned char *packet, int length) {
    std::stringstream mac;
    for (int i = 0; i < length; ++i) {
        if (i != 0) {
            mac << ":";
        }
        mac << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(packet[i]);
    }
    return mac.str();
}

#endif // PCKTCAP_UTIL_H