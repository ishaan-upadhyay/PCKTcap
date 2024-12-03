
#ifndef PACKET_UDP_H
#define PACKET_UDP_H

#include "layer.h"

/*
 * UDPFrame is a class that represents the UDP header in a network packet.
 * 
 * RFC: https://datatracker.ietf.org/doc/html/rfc768
 */
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
        std::unique_ptr<Layer> next_layer_parse(const unsigned char *packet, int length, uint16_t sport, uint16_t dport);
};

#endif // PACKET_UDP_H