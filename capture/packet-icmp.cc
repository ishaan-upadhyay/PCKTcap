#include "packet-icmp.h"
#include "utils/pcktcap_util.h"

ICMPFrame::ICMPFrame(const unsigned char *buf, int length)
{
    if (length < 4)
    {
        throw std::runtime_error("Packet length is less than ICMP minimum header length");
    }

    type = buf[0];
    code = buf[1];
    checksum = (buf[2] << 8) | buf[3];
}

bsoncxx::builder::basic::document ICMPFrame::toBson()
{
    bsoncxx::builder::basic::document doc;
    doc.append(bsoncxx::builder::basic::kvp("layerType", "ICMP"));
    doc.append(bsoncxx::builder::basic::kvp("type", type));
    doc.append(bsoncxx::builder::basic::kvp("code", code));
    doc.append(bsoncxx::builder::basic::kvp("checksum", checksum));
    return doc;
}