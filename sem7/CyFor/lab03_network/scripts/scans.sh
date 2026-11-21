#!/usr/bin/env bash
# Lab 03 steps 3-5: discovery, the main scan types, OS detection, versions and NSE scripts.
# Each scan is saved in all nmap formats (captures/nmap/<name>.{nmap,gnmap,xml}) AND as a pcap,
# so you can show in Wireshark what each scan type looks like on the wire.
set -uo pipefail
source /lab/scripts/lib.sh
NET=10.10.30.0/24
N="captures/nmap"

banner "nmap version"; nmap --version | head -1

banner "Step 3a: host discovery (ping sweep, no port scan)"
capture 03a_host_discovery nmap -sn "$NET" -oA "$N/03a_host_discovery"

banner "Step 3b: TCP SYN (half-open) scan - needs raw sockets"
capture 03b_syn_scan nmap -sS -p 1-1024 -T4 10.10.30.20-24 -oA "$N/03b_syn_scan"

banner "Step 3c: TCP connect scan - full 3-way handshake, what an unprivileged user gets"
capture 03c_connect_scan nmap -sT -p 21,22,23,80,6379 10.10.30.20-24 -oA "$N/03c_connect_scan"

banner "Step 3d: UDP scan (slow - top 20 ports on the DNS server)"
capture 03d_udp_scan nmap -sU --top-ports 20 10.10.30.53 -oA "$N/03d_udp_scan"

banner "Step 3e: OS detection"
capture 03e_os_detect nmap -O --osscan-guess 10.10.30.20 10.10.30.23 -oA "$N/03e_os_detect"

banner "Step 4: service/version enumeration"
capture 04_version nmap -sV -p 21,22,23,53,80,6379 10.10.30.20-24,53 -oA "$N/04_version"

banner "Step 5a: NSE default scripts (-sC)"
capture 05a_nse_default nmap -sC -sV -p 21,22,80,6379 10.10.30.20,21,23,24 -oA "$N/05a_nse_default"

banner "Step 5b: targeted NSE scripts for service discovery"
capture 05b_nse_targeted nmap -p 21,22,53,80,6379 \
  --script "ftp-anon,ftp-syst,ssh2-enum-algos,ssh-hostkey,http-title,http-headers,http-enum,http-auth,http-methods,redis-info,dns-recursion,banner" \
  10.10.30.20-24,53 -oA "$N/05b_nse_targeted"

banner "Step 5c: NSE vuln category against the web server"
capture 05c_nse_vuln nmap -sV --script vuln -p 80 10.10.30.20 -oA "$N/05c_nse_vuln"

banner "Done - results in captures/nmap/, pcaps in captures/"
grep -h "open" "$N"/04_version.nmap | sort -u
