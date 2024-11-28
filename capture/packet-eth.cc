#include <iostream>
#include <stdexcept>
#include <pcap/pcap.h>

#include "packet-ipv4.h"
#include "packet-arp.h"
#include "packet-eth.h"
#include "../utils/pcktcap_util.h"
#include <bsoncxx/builder/basic/kvp.hpp>   

EthernetFrame::EthernetFrame(const unsigned char *buf, const struct pcap_pkthdr *header)
{
    if (header->len < 14)
    {
        throw std::runtime_error("Packet length is less than Ethernet frame length");
    }

    std::copy(buf, buf + 6, destination);
    std::copy(buf + 6, buf + 12, source);
    type = (buf[12] << 8) | buf[13];
    nextLayer = next_layer_parse(buf + 14, header->len - 14, type);
}

EthernetFrame::~EthernetFrame()
{
    if (nextLayer)
    {
        nextLayer.reset();
    }
}

bsoncxx::builder::basic::document EthernetFrame::toBson()
{
    bsoncxx::builder::basic::document doc;
    doc.append(bsoncxx::builder::basic::kvp("layerType", "Ethernet"));
    doc.append(bsoncxx::builder::basic::kvp("destination", byte_stream_to_mac_string(destination, 6)));
    doc.append(bsoncxx::builder::basic::kvp("source", byte_stream_to_mac_string(source, 6)));
    doc.append(bsoncxx::builder::basic::kvp("type", type));

    if (nextLayer)
    {
        doc.append(bsoncxx::builder::basic::kvp("nextLayer", nextLayer->toBson().extract()));
    }
    return doc;
}

std::unique_ptr<Layer> EthernetFrame::next_layer_parse(const unsigned char *packet, int length, int type)
{
    switch (type)
    {
    case 0x0800:
        return std::make_unique<IPV4Frame>(packet, length);
    case 0x0806:
        return std::make_unique<ARPFrame>(packet, length);
    default:
        return nullptr;
    }
}
