#!/bin/bash
# Lab 03 - analyse the captured scan with tshark (Wireshark's CLI engine).
set -e
apt-get update -qq
apt-get install -y -qq tshark
PCAP=/work/captures/nmap_scan.pcap

echo "== Total packets in the capture =="
tshark -r "$PCAP" 2>/dev/null | wc -l

echo "== SYN probes sent by nmap (SYN set, ACK not) =="
tshark -r "$PCAP" -Y "tcp.flags.syn==1 && tcp.flags.ack==0" 2>/dev/null | wc -l

echo "== RST replies from the 999 closed ports =="
tshark -r "$PCAP" -Y "tcp.flags.reset==1" 2>/dev/null | wc -l

echo "== SYN/ACK from the one OPEN port (80) =="
tshark -r "$PCAP" -Y "tcp.flags.syn==1 && tcp.flags.ack==1" 2>/dev/null
