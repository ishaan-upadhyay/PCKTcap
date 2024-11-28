#ifndef PACKET_ETH_H
#define PACKET_ETH_H

#include "layer.h"

/*
 Class representing the Ethernet layer of a captured packet.

 As a link-layer protocol, this class can contain further layers, such as ARP, IP, etc.
 This makes an explicit destructor necessary to ensure that all layers are properly deallocated.
 */
class EthernetFrame : public Layer
{
    public:
        unsigned char destination[6]; /* 48-bit destination MAC address */
        unsigned char source[6]; /* 48-bit source MAC address */
        uint16_t type; /* 16-bit protocol type identifier. */
        EthernetFrame(const unsigned char *buf, const struct pcap_pkthdr *header);
        ~EthernetFrame();
        bsoncxx::builder::basic::document toBson() override;
    private:
        std::unique_ptr<Layer> next_layer_parse(const unsigned char *packet, int length, int type);
};

#endif // PACKET_ETH_H