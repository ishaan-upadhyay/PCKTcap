#ifndef PACKET_ARP_H
#define PACKET_ARP_H
#include "layer.h"

/*
 * ARPFrame is a class that represents an ARP frame in a network packet.
 * There is no nextLayer from here.
 * We assume IPv4 protocol addresses and Ethernet hardware addresses.
 * 
 * RFC: https://datatracker.ietf.org/doc/html/rfc826
 */
class ARPFrame : public Layer
{
public:
    uint16_t hardwareType; /* Type corresponding to hardware address. */
    uint16_t protocolType; /* Type corresponding to protocol address. */
    uint8_t hardwareAddressLength; 
    uint8_t protocolAddressLength;
    uint16_t operation; /* ARP operation code, e.g. request or reply. */
    unsigned char senderHardwareAddress[6]; 
    unsigned char senderProtocolAddress[4];
    unsigned char targetHardwareAddress[6];
    unsigned char targetProtocolAddress[4];
    ARPFrame(const unsigned char *buf, int length);
    bsoncxx::builder::basic::document toBson() override;
};

#endif // PACKET_ARP_H