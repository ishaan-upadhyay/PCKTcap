#ifndef PACKET_ARP_H
#define PACKET_ARP_H
#include "layer.h"

class ARPFrame : public Layer
{
public:
    uint16_t hardwareType;
    uint16_t protocolType;
    uint8_t hardwareAddressLength;
    uint8_t protocolAddressLength;
    uint16_t operation;
    unsigned char senderHardwareAddress[6];
    unsigned char senderProtocolAddress[4];
    unsigned char targetHardwareAddress[6];
    unsigned char targetProtocolAddress[4];
    ARPFrame(const unsigned char *buf, int length);
    void print() override;
    bsoncxx::builder::basic::document toBson() override;
};

#endif // PACKET_ARP_H