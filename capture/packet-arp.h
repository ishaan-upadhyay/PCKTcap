#ifndef PACKET_ARP_H
#define PACKET_ARP_H
#include "layer.h"

class ARPFrame : public Layer
{
public:
    short hardwareType;
    short protocolType;
    char hardwareAddressLength;
    char protocolAddressLength;
    short operation;
    unsigned char senderHardwareAddress[6];
    unsigned char senderProtocolAddress[4];
    unsigned char targetHardwareAddress[6];
    unsigned char targetProtocolAddress[4];
    ARPFrame(const unsigned char *buf, int length);
    void print() override;
    nlohmann::json toJson() override;
};

#endif // PACKET_ARP_H