#include "packet-udp.h"
#include "packet-dns.h"
#include "utils/pcktcap_util.h"

UDPFrame::UDPFrame(const unsigned char *buf, int length)
{
    if (length < 8)
    {
        throw std::runtime_error("Packet length is less than UDP minimum header length");
    }

    sourcePort = (buf[0] << 8) | buf[1];
    destinationPort = (buf[2] << 8) | buf[3];
    this->length = (buf[4] << 8) | buf[5];
    checksum = (buf[6] << 8) | buf[7];
    nextLayer = next_layer_parse(buf + 8, length - 8, sourcePort, destinationPort);
}

UDPFrame::~UDPFrame()
{
    if (nextLayer)
    {
        nextLayer.reset();
    }
}

bsoncxx::builder::basic::document UDPFrame::toBson()
{
    bsoncxx::builder::basic::document doc;
    doc.append(bsoncxx::builder::basic::kvp("layerType", "UDP"));
    doc.append(bsoncxx::builder::basic::kvp("sourcePort", sourcePort));
    doc.append(bsoncxx::builder::basic::kvp("destinationPort", destinationPort));
    doc.append(bsoncxx::builder::basic::kvp("length", length));
    doc.append(bsoncxx::builder::basic::kvp("checksum", checksum));

    if (nextLayer)
    {
        doc.append(bsoncxx::builder::basic::kvp("nextLayer", nextLayer->toBson().extract()));
    }
    return doc;
}

std::unique_ptr<Layer> UDPFrame::next_layer_parse(const unsigned char *packet, int length, uint16_t sport, uint16_t dport)
{
    if (sport == 53 || dport == 53)
    {
        return std::make_unique<DNSFrame>(packet, length);
    }
    else
    {
        return nullptr;
    }
}