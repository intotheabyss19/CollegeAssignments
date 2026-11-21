#!/usr/bin/env bash
# Quick tshark triage of a capture - the numbers for your "Results and Analysis" section.
# The same views exist in the Wireshark GUI under Statistics (named in brackets below).
#   analyze_pcap.sh captures/09_anomalies.pcap  [> captures/09_anomalies.report.txt]
set -uo pipefail
P="${1:?usage: analyze_pcap.sh <file.pcap>}"
h() { printf '\n### %s\n' "$*"; }

h "Capture summary  [Statistics > Capture File Properties]"
capinfos -c -d -u -y -i "$P" 2>/dev/null || tshark -n -r "$P" -q -z io,stat,0 2>/dev/null

h "Protocol hierarchy  [Statistics > Protocol Hierarchy]"
tshark -n -r "$P" -q -z io,phs 2>/dev/null | sed -n '1,40p'

h "Top IPv4 conversations  [Statistics > Conversations]"
tshark -n -r "$P" -q -z conv,ip 2>/dev/null | sed -n '1,20p'

h "Packets per second  [Statistics > I/O Graphs] - spikes = floods"
tshark -n -r "$P" -q -z io,stat,1 2>/dev/null | awk '/<>/ {print}' | sort -t'|' -k3 -nr | head -8

h "Port-scan indicator: SYNs without ACK per source  [filter: tcp.flags.syn==1 && tcp.flags.ack==0]"
tshark -n -r "$P" -Y 'tcp.flags.syn==1 && tcp.flags.ack==0' -T fields -e ip.src 2>/dev/null | sort | uniq -c | sort -nr | head
h "Distinct destination ports probed per source"
tshark -n -r "$P" -Y 'tcp.flags.syn==1 && tcp.flags.ack==0' -T fields -e ip.src -e tcp.dstport 2>/dev/null | sort -u | cut -f1 | uniq -c | sort -nr | head

h "Stealth scans (NULL / FIN / Xmas)  [tcp.flags==0x000 | 0x001 | 0x029]"
for f in 0x000 0x001 0x029; do printf '%s: %s packets\n' "$f" "$(tshark -n -r "$P" -Y "tcp.flags==$f" 2>/dev/null | wc -l)"; done

h "ICMP volume by type"
tshark -n -r "$P" -Y icmp -T fields -e icmp.type 2>/dev/null | sort | uniq -c | sort -nr

h "DNS queries (top)  [dns.flags.response==0]"
tshark -n -r "$P" -Y 'dns.flags.response==0' -T fields -e dns.qry.name 2>/dev/null | sort | uniq -c | sort -nr | head -15

h "HTTP requests  [http.request]"
tshark -n -r "$P" -Y http.request -T fields -e ip.src -e http.request.method -e http.host -e http.request.uri -e http.authorization 2>/dev/null | head -25

h "HTTP status codes (401 bursts = brute force)"
tshark -n -r "$P" -Y http.response -T fields -e http.response.code 2>/dev/null | sort | uniq -c

h "Cleartext credentials on the wire  [ftp.request.command==\"PASS\" || telnet || http.authbasic]"
tshark -n -r "$P" -Y 'ftp.request.command=="USER" || ftp.request.command=="PASS"' -T fields -e ip.src -e ftp.request.command -e ftp.request.arg 2>/dev/null
tshark -n -r "$P" -Y 'http.authbasic' -T fields -e ip.src -e http.authbasic 2>/dev/null | sort -u

h "Expert info (warnings and errors)  [Analyze > Expert Information]"
tshark -n -r "$P" -q -z expert,warn 2>/dev/null | sed -n '1,25p'
