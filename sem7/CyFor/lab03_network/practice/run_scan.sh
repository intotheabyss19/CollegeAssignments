#!/bin/bash
# Lab 03 - scan the stock nginx target and capture the traffic.
# Runs inside a throwaway ubuntu container (see the docker command in the README/chat).
set -e

# 1. install the tools (stock ubuntu has neither)
apt-get update -qq
apt-get install -y -qq nmap tcpdump

# 2. start capturing the scan traffic in the background
tcpdump -i any -w /work/captures/nmap_scan.pcap -U "host lab03-web" >/dev/null 2>&1 &
sleep 1

# 3. run the scan: SYN/half-open (-sS) + service-version detection (-sV)
nmap -sS -sV lab03-web

# 4. stop the capture
sleep 1
pkill tcpdump
echo ">>> capture saved to practice/captures/nmap_scan.pcap"
