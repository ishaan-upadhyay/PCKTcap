from scapy.all import *

# Send UDP packet to loopback interface
packet = IP(dst="127.0.0.1")/UDP(dport=12345, sport=54321)/"Hello, World!"
send(packet)

# Send out a DNS query
packet = IP(dst="8.8.8.8")/UDP(dport=53)/DNS(rd=1,qd=DNSQR(qname="www.google.com"))
send(packet)