#include <iostream>
#include <stdexcept>

#include "packet-arp.h"
#include "../utils/pcktcap_util.h"
#include <bsoncxx/json.hpp>

ARPFrame::ARPFrame(const unsigned char *buf, int length)
{
    if (length < 28)
    {
        throw std::runtime_error("Packet length is less than ARP frame length");
    };

    hardwareType = (buf[0] << 8) | buf[1];
    protocolType = (buf[2] << 8) | buf[3];
    hardwareAddressLength = buf[4];
    protocolAddressLength = buf[5];
    operation = (buf[6] << 8) | buf[7];
    std::copy(buf + 8, buf + 14, senderHardwareAddress);
    std::copy(buf + 14, buf + 18, senderProtocolAddress);
    std::copy(buf + 18, buf + 24, targetHardwareAddress);
    std::copy(buf + 24, buf + 28, targetProtocolAddress);
    nextLayer = nullptr;
};

bsoncxx::builder::basic::document ARPFrame::toBson()
{
    bsoncxx::builder::basic::document doc;
    doc.append(bsoncxx::builder::basic::kvp("layerType", "ARP"));
    doc.append(bsoncxx::builder::basic::kvp("hardwareType", hardwareType));
    doc.append(bsoncxx::builder::basic::kvp("protocolType", protocolType));
    doc.append(bsoncxx::builder::basic::kvp("hardwareAddressLength", hardwareAddressLength));
    doc.append(bsoncxx::builder::basic::kvp("protocolAddressLength", protocolAddressLength));
    doc.append(bsoncxx::builder::basic::kvp("operation", operation));
    doc.append(bsoncxx::builder::basic::kvp("senderHardwareAddress", byte_stream_to_mac_string(senderHardwareAddress, 6)));
    doc.append(bsoncxx::builder::basic::kvp("senderProtocolAddress", byte_stream_to_ip_string(senderProtocolAddress, 4)));
    doc.append(bsoncxx::builder::basic::kvp("targetHardwareAddress", byte_stream_to_mac_string(targetHardwareAddress, 6)));
    doc.append(bsoncxx::builder::basic::kvp("targetProtocolAddress", byte_stream_to_ip_string(targetProtocolAddress, 4)));

    return doc;
}