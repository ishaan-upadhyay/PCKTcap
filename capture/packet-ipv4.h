#ifndef PACKET_IPV4_H
#define PACKET_IPV4_H

#include "layer.h"

/*
 Class representing the IPv4 layer of a captured packet.

 As a network-layer protocol, this class can contain further layers, such as TCP, UDP, etc.
 This makes an explicit destructor necessary to ensure that all layers are properly deallocated.
 
 RFC: https://datatracker.ietf.org/doc/html/rfc791
 */
class IPV4Frame : public Layer
{
    public:
        uint8_t version;
        uint8_t ihl;
        uint8_t dscp;
        uint16_t totalLength;
        uint16_t identification;
        uint8_t flags;
        uint16_t offset;
        uint8_t ttl;
        uint8_t protocol;
        uint16_t checksum;
        unsigned char source[4];
        unsigned char destination[4];
        IPV4Frame(const unsigned char *buf, int length);
        ~IPV4Frame();
        bsoncxx::builder::basic::document toBson() override;
    private:
        std::unique_ptr<Layer> next_layer_parse(const unsigned char *packet, int length, int protocol);
};

#endif // PACKET_ETH_H