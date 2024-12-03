#ifndef PCKTCAP_UTIL_H
#define PCKTCAP_UTIL_H

#include <iostream>
#include <iomanip>

/* Convert a stream of bytes to a string (hexadecimal representation). */
inline std::string byte_stream_to_byte_string(const unsigned char *packet, int length) {
    std::stringstream rep;
    for (int i = 0; i < length; ++i) {
        if (i != 0) {
            rep << " ";
        }
        rep << "0x";
        rep << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(packet[i]);
    }

    return rep.str();
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

/* Helper function to convert a byte stream to an IPv4 address string. */
inline std::string byte_stream_to_ip_string(unsigned char *packet, int length) {
    std::stringstream ip;
    
    for (int i = 0; i < length; ++i) {
        if (i != 0) {
            ip << ".";
        }

        ip << std::dec << static_cast<int>(packet[i]);
    }
    
    return ip.str();
}

#endif // PCKTCAP_UTIL_H