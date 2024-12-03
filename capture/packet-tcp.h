
#ifndef PACKET_TCP_H
#define PACKET_TCP_H

#include "layer.h"

class TCPFrame : public Layer
{
    public:
        TCPFrame(const unsigned char *buf, int length);
        ~TCPFrame();
        uint16_t sourcePort;
        uint16_t destinationPort;
        uint32_t sequenceNumber;
        uint32_t acknowledgmentNumber;
        uint8_t dataOffset;
        uint8_t flags;
        uint16_t windowSize;
        uint16_t checksum;
        uint16_t urgentPointer;
        bsoncxx::builder::basic::document toBson() override;
    private:
        std::unique_ptr<Layer> next_layer_parse(const unsigned char *packet, int length, int protocol);
};

#endif // PACKET_TCP_H