
#ifndef PACKET_UDP_H
#define PACKET_UDP_H

#include "layer.h"

class UDPFrame : public Layer
{
    public:
        uint16_t sourcePort;
        uint16_t destinationPort;
        uint16_t length;
        uint16_t checksum;
        UDPFrame(const unsigned char *buf, int length);
        ~UDPFrame();
        bsoncxx::builder::basic::document toBson() override;
    private:
        std::unique_ptr<Layer> next_layer_parse(const unsigned char *packet, int length, int protocol);
};

#endif // PACKET_UDP_H