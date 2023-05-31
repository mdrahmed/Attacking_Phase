from netfilterqueue import NetfilterQueue
from scapy.all import *

def packet_handler(packet):
    ip_packet = IP(packet.get_payload())
    if ip_packet.haslayer(TCP) and ip_packet[TCP].dport == 1883:
        # Packet is a TCP packet with destination port 1883 (MQTT)
        # Process the packet or extract the desired information
        print("Received MQTT packet:")
        ip_packet.show()

    packet.accept()  # Accept the packet and forward it

try:
    nfqueue = NetfilterQueue()
    nfqueue.bind(1, packet_handler)  # Bind to queue number 1 and set the packet_handler as the callback
    nfqueue.run()
except KeyboardInterrupt:
    nfqueue.unbind()

