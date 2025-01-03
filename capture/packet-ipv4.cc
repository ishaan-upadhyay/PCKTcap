#include "packet-ipv4.h"
#include "utils/pcktcap_util.h"
#include "packet-tcp.h"
#include "packet-udp.h"
#include "packet-icmp.h"

IPV4Frame::IPV4Frame(const unsigned char *buf, int length)
{
    if (length < 20)
    {
        throw std::runtime_error("Packet length is less than IP minimum header length");
    }

    version = (buf[0] & 0xF0) >> 4;

    if (version != 4)
    {
        throw std::runtime_error("Non IPv-4 packet; not currently supported.");
    }

    ihl = buf[0] & 0x0F;
    dscp = (buf[1] & 0xFC) >> 2;
    totalLength = (buf[2] << 8) | buf[3];
    identification = (buf[4] << 8) | buf[5];
    flags = (buf[6] & 0xE0) >> 5;
    offset = ((buf[6] & 0x1F) << 8) | buf[7];
    ttl = buf[8];
    protocol = buf[9];
    checksum = (buf[10] << 8) | buf[11];
    std::copy(buf + 12, buf + 16, source);
    std::copy(buf + 16, buf + 20, destination);
    nextLayer = next_layer_parse(buf + ihl * 4, length - ihl * 4, protocol);
};

IPV4Frame::~IPV4Frame()
{
    if (nextLayer)
    {
        nextLayer.reset();
    }
}

bsoncxx::builder::basic::document IPV4Frame::toBson()
{
    bsoncxx::builder::basic::document doc;
    doc.append(bsoncxx::builder::basic::kvp("layerType", "IPv4"));
    doc.append(bsoncxx::builder::basic::kvp("version", version));
    doc.append(bsoncxx::builder::basic::kvp("ipHeaderLength", ihl));
    doc.append(bsoncxx::builder::basic::kvp("differentiatedServices", dscp));
    doc.append(bsoncxx::builder::basic::kvp("totalLength", totalLength));
    doc.append(bsoncxx::builder::basic::kvp("identification", identification));
    doc.append(bsoncxx::builder::basic::kvp("flags", flags));
    doc.append(bsoncxx::builder::basic::kvp("offset", offset));
    doc.append(bsoncxx::builder::basic::kvp("ttl", ttl));
    doc.append(bsoncxx::builder::basic::kvp("protocol", protocol));
    doc.append(bsoncxx::builder::basic::kvp("checksum", checksum));
    doc.append(bsoncxx::builder::basic::kvp("source", byte_stream_to_ip_string(source, 4)));
    doc.append(bsoncxx::builder::basic::kvp("destination", byte_stream_to_ip_string(destination, 4)));

    if (nextLayer)
    {
        doc.append(bsoncxx::builder::basic::kvp("nextLayer", nextLayer->toBson().extract()));
    }
    return doc;
}

std::unique_ptr<Layer> IPV4Frame::next_layer_parse(const unsigned char *packet, int length, int protocol)
{
    /* If this is not the first fragment, we should not expect the next layer header. */
    if (offset != 0)
    {
        return nullptr;
    }

    switch (protocol)
    {
    case 1:
        return std::make_unique<ICMPFrame>(packet, length);
    case 6:
        return std::make_unique<TCPFrame>(packet, length);
    case 17:
        return std::make_unique<UDPFrame>(packet, length);
    default:
        return nullptr;
    }
}