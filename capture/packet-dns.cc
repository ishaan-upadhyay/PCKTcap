#include "packet-dns.h"

DNSFrame::DNSFrame(const unsigned char *buf, int length)
{
    if (length < 12)
    {
        throw std::runtime_error("Packet length is less than DNS minimum header length");
    }

    identifier = (buf[0] << 8) | buf[1];
    qr = (buf[2] & 0x80) >> 7;
    opcode = (buf[2] & 0x78) >> 3;
    aa = (buf[2] & 0x04) >> 2;
    tc = (buf[2] & 0x02) >> 1;
    rd = buf[2] & 0x01;
    ra = (buf[3] & 0x80) >> 7;
    /* We ignore z as it is reserved and intended to be 0. */
    rcode = buf[3] & 0x0F;
    qdcount = (buf[4] << 8) | buf[5];
    ancount = (buf[6] << 8) | buf[7];
    nscount = (buf[8] << 8) | buf[9];
    arcount = (buf[10] << 8) | buf[11];
}

bsoncxx::builder::basic::document DNSFrame::toBson()
{
    bsoncxx::builder::basic::document doc;
    doc.append(bsoncxx::builder::basic::kvp("layerType", "DNS"));
    doc.append(bsoncxx::builder::basic::kvp("identifier", identifier));
    doc.append(bsoncxx::builder::basic::kvp("isQuery", !qr));
    doc.append(bsoncxx::builder::basic::kvp("operationCode", opcode));
    doc.append(bsoncxx::builder::basic::kvp("authoritativeAnswer", aa));
    doc.append(bsoncxx::builder::basic::kvp("truncated", tc));
    doc.append(bsoncxx::builder::basic::kvp("recursionDesired", rd));
    doc.append(bsoncxx::builder::basic::kvp("recursionAvailable", ra));
    doc.append(bsoncxx::builder::basic::kvp("responseCode", rcode));
    doc.append(bsoncxx::builder::basic::kvp("questionCount", qdcount));
    doc.append(bsoncxx::builder::basic::kvp("answerCount", ancount));
    doc.append(bsoncxx::builder::basic::kvp("authorityCount", nscount));
    doc.append(bsoncxx::builder::basic::kvp("additionalCount", arcount));
    return doc;
}