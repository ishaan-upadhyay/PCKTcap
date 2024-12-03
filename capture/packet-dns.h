#ifndef PACKET_DNS_H
#define PACKET_DNS_H

#include "layer.h"

/*
 * DNSFrame is a class that represents the DNS header in a network packet.
 * This has no nextLayer.
 * 
 * RFC: https://datatracker.ietf.org/doc/html/rfc1035
 */
class DNSFrame : public Layer
{
    public:
        DNSFrame(const unsigned char *buf, int length);
        bsoncxx::builder::basic::document toBson() override;
    private:
        uint16_t identifier;
        bool qr;
        uint8_t opcode;
        bool aa;
        bool tc;
        bool rd;
        bool ra;
        uint8_t rcode;
        uint16_t qdcount;
        uint16_t ancount;
        uint16_t nscount;
        uint16_t arcount;
};

#endif // PACKET_DNS_H