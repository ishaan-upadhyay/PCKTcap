
#ifndef PACKET_ICMP_H
#define PACKET_ICMP_H

#include "layer.h"

/*
 * ICMPFrame is a class that represents an ICMP frame in a network packet.
 * There is no nextLayer from here.
 * 
 * RFC: https://datatracker.ietf.org/doc/html/rfc792
 */
class ICMPFrame : public Layer
{
public:
    uint8_t type; /* Type of ICMP message */
    uint8_t code; /* Code of ICMP message */
    uint16_t checksum;
    ICMPFrame(const unsigned char *buf, int length);
    bsoncxx::builder::basic::document toBson() override;
};

#endif // PACKET_ICMP_H