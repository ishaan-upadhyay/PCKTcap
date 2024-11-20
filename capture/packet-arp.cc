#include <iostream>
#include <stdexcept>

#include "packet-arp.h"
#include "../utils/pcktcap_util.h"
#include "../dependencies/json.hpp"

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

void ARPFrame::print()
{
    std::cout << "ARP frame\n";
    std::cout << "Hardware type: " << hardwareType << "\n";
    std::cout << "Protocol type: " << protocolType << "\n";
    std::cout << "Hardware address length: " << hardwareAddressLength << "\n";
    std::cout << "Protocol address length: " << protocolAddressLength << "\n";
    std::cout << "Operation: " << operation << "\n";
    std::cout << "Sender hardware address: ";
    print_byte_stream(senderHardwareAddress, 6);
    std::cout << "\n";
    std::cout << "Sender protocol address: ";
    print_byte_stream(senderProtocolAddress, 4);
    std::cout << "\n";
    std::cout << "Target hardware address: ";
    print_byte_stream(targetHardwareAddress, 6);
    std::cout << "\n";
    std::cout << "Target protocol address: ";
    print_byte_stream(targetProtocolAddress, 4);
    std::cout << "\n";
}

nlohmann::json ARPFrame::toJson() {
    nlohmann::json j;
    j["type"] = "ARP";
    j["hardwareType"] = hardwareType;
    j["protocolType"] = protocolType;
    j["hardwareAddressLength"] = hardwareAddressLength;
    j["protocolAddressLength"] = protocolAddressLength;
    j["operation"] = operation;
    j["senderHardwareAddress"] = byte_stream_to_mac_string(senderHardwareAddress, 6);
    j["senderProtocolAddress"] = senderProtocolAddress;
    j["targetHardwareAddress"] = byte_stream_to_mac_string(targetHardwareAddress, 6);
    j["targetProtocolAddress"] = targetProtocolAddress;

    return j;
}