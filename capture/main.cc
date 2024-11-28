#include <pcap.h>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <signal.h>
#include <stdexcept>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include "packet-eth.h"

pcap_t *handle;

/* Set up MongoDB connection */
const std::string DB_URL = "mongodb://localhost:27017";

mongocxx::instance instance;
mongocxx::uri uri(DB_URL);
mongocxx::client client(uri);

auto database = client["PCKTcap"];

/* Set up new collection based on timestamp */
time_t now = time(NULL);
auto collection = database["cap_" + std::to_string(now)];

/* Structure to pass around required metadata for the packet handler */
struct handler_metadata
{
    pcap_dumper_t *dumper;
    int link_type; /* Used to determine initial parsing strategy. */
};

/* Capture exit signal, to gracefully end the pcap_loop. */
void signal_handler(int signum)
{
    std::cout << "Signal " << signum << " received. Exiting..." << std::endl;
    if (handle)
    {
        pcap_breakloop(handle);
    }
}

void packet_handler(unsigned char *user_data, const struct pcap_pkthdr *pkthdr, const unsigned char *packet)
{
    /* Sanity checks */
    if (pkthdr->len < pkthdr->caplen)
    {
        std::cerr << "Packet length is less than packet capture length" << std::endl;
        return;
    }

    struct handler_metadata *meta = reinterpret_cast<struct handler_metadata *>(user_data);

    if (meta->dumper)
    {
        pcap_dump(reinterpret_cast<u_char *>(meta->dumper), pkthdr, packet);
    };

    std::unique_ptr<Layer> base = nullptr;
    try
    {
        switch (meta->link_type)
        {
        case DLT_EN10MB:
            base = std::make_unique<EthernetFrame>(packet, pkthdr);
        default:
            break;
        }

        if (base)
        {
            bsoncxx::builder::basic::document doc = base->toBson();
            /* Get full microsecond level granularity. */
            doc.append(bsoncxx::builder::basic::kvp("timestamp", pkthdr->ts.tv_sec * 1000000 + pkthdr->ts.tv_usec));

            std::cout << bsoncxx::to_json(doc.view()) << std::endl;

            collection.insert_one(doc.view());
        }
    } catch (std::runtime_error &e)
    {
        std::cerr << "Error parsing packet: " << e.what() << std::endl;
    }
}

void print_usage()
{
    std::cout << "Usage: capture [-i <interface>] [-l <log_file>] [-h]\n";
    std::cout << "Options:\n";
    std::cout << "  -i <interface>  Interface to capture packets from (default: first available interface)\n";
    std::cout << "  -l <log_file>   Log file to write captured packets to (default: no logging)\n";
    std::cout << "  -h              Display this help message" << std::endl;
}

int main(int argc, char *argv[])
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs;
    std::string interface;
    std::string log_file = "";
    int opt;

    while ((opt = getopt(argc, argv, "i:l:h")) != -1)
    {
        switch (opt)
        {
        case 'i':
            interface = optarg;
            break;
        case 'l':
            log_file = optarg;
            break;
        case 'h':
            print_usage();
            return 0;
        default:
            print_usage();
            return 1;
        }
    }

    if (interface.empty())
    {
        if (pcap_findalldevs(&alldevs, errbuf) == -1)
        {
            std::cerr << "Error finding devices: " << errbuf << std::endl;
            return 1;
        }
        interface = alldevs->name;
    }

    handle = pcap_open_live(interface.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr)
    {
        std::cerr << "Couldn't open device " << interface << ": " << errbuf << std::endl;
        return 1;
    }

    int link_type = pcap_datalink(handle);
    std::cout << "Link type: " << pcap_datalink_val_to_name(link_type) << std::endl;

    pcap_dumper_t *dumper = nullptr;
    if (!log_file.empty())
    {
        dumper = pcap_dump_open(handle, log_file.c_str());
        if (dumper == nullptr)
        {
            std::cerr << "Couldn't open dump file " << log_file << ": " << pcap_geterr(handle) << std::endl;
            return 1;
        }
    }

    struct handler_metadata metadata = {dumper, link_type};

    signal(SIGINT, signal_handler);
    pcap_loop(handle, 0, packet_handler, reinterpret_cast<unsigned char *>(&metadata));

    if (dumper)
    {
        pcap_dump_close(dumper);
    }
    pcap_close(handle);

    return 0;
}