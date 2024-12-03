
#ifndef PACKET_ICMP_H
#define PACKET_ICMP_H

#include "layer.h"

class ICMPFrame : public Layer
{
    public:
        uint8_t type;
        uint8_t code;
        uint16_t checksum;
        ICMPFrame(const unsigned char *buf, int length);
        bsoncxx::builder::basic::document toBson() override;
};

#endif // PACKET_ICMP_H