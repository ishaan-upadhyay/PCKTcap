#include "packet-tcp.h"
#include <iostream>

TCPFrame::TCPFrame(const unsigned char *buf, int length)
{
    if (length < 20)
    {
        throw std::runtime_error("Packet length is less than TCP minimum header length");
    }

    sourcePort = (buf[0] << 8) | buf[1];
    destinationPort = (buf[2] << 8) | buf[3];
    sequenceNumber = (buf[4] << 24) | (buf[5] << 16) | (buf[6] << 8) | buf[7];
    acknowledgmentNumber = (buf[8] << 24) | (buf[9] << 16) | (buf[10] << 8) | buf[11];
    dataOffset = (buf[12] & 0xF0) >> 4;
    flags = buf[13];
    windowSize = (buf[14] << 8) | buf[15];
    checksum = (buf[16] << 8) | buf[17];
    urgentPointer = (buf[18] << 8) | buf[19];
    /* nextLayer = next_layer_parse(buf + dataOffset * 4, length - dataOffset * 4, sourcePort, destinationPort); */
}

TCPFrame::~TCPFrame()
{
    if (nextLayer)
    {
        nextLayer.reset();
    }
}

bsoncxx::builder::basic::document TCPFrame::toBson()
{
    bsoncxx::builder::basic::document doc;
    doc.append(bsoncxx::builder::basic::kvp("layerType", "TCP"));
    doc.append(bsoncxx::builder::basic::kvp("sourcePort", sourcePort));
    doc.append(bsoncxx::builder::basic::kvp("destinationPort", destinationPort));
    doc.append(bsoncxx::builder::basic::kvp("sequenceNumber", static_cast<int64_t>(sequenceNumber)));
    doc.append(bsoncxx::builder::basic::kvp("acknowledgmentNumber", static_cast<int64_t>(acknowledgmentNumber)));
    doc.append(bsoncxx::builder::basic::kvp("dataOffset", dataOffset));
    doc.append(bsoncxx::builder::basic::kvp("flags", flags));
    doc.append(bsoncxx::builder::basic::kvp("windowSize", windowSize));
    doc.append(bsoncxx::builder::basic::kvp("checksum", checksum));
    doc.append(bsoncxx::builder::basic::kvp("urgentPointer", urgentPointer));

    if (nextLayer)
    {
        doc.append(bsoncxx::builder::basic::kvp("nextLayer", nextLayer->toBson().extract()));
    }
    return doc;
}

/* TCP reassembly is currently beyond project scope. */
/* std::unique_ptr<Layer> TCPFrame::next_layer_parse(const unsigned char *packet, int length, uint16_t sport, uint16_t dport)
{
    return nullptr;
} */