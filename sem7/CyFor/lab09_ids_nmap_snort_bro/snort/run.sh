#!/bin/bash
# Snort 3 wrapper.
#   run.sh live                         IDS on the firewall's DMZ interface  -> /output/live/snort/
#   run.sh pcap <file.pcap> <outdir>    read a capture (passive IDS)          -> <outdir>/
#   run.sh ips  <file.pcap> <outdir>    simulated inline IPS: packets that survive go to passed.pcap
# Env: HOME_NET (default 10.10.90.0/24), ET=1 to add Emerging Threats Open rules.
#
# -k none : don't verify checksums. Docker's virtual NICs offload checksumming, so captured packets
#           often carry WRONG checksums; Snort would silently ignore those packets otherwise.
set -euo pipefail
CONF=/lab/snort/lab.lua
mode=${1:-live}

case "$mode" in
  live)
    out=/output/live/snort; mkdir -p "$out"
    echo "[snort] live IDS on dmz0, HOME_NET=${HOME_NET:-10.10.90.0/24}, alerts -> $out"
    exec snort -c "$CONF" -i dmz0 -k none -l "$out" ;;
  pcap)
    pcap=$2 out=$3; mkdir -p "$out"; rm -f "$out"/alert_*.txt "$out"/file.log
    snort -c "$CONF" -r "$pcap" -k none -l "$out" 2>&1 | tee "$out/snort_stats.txt" ;;
  ips)
    pcap=$2 out=$3; mkdir -p "$out"; rm -f "$out"/alert_*.txt "$out"/file.log
    # -Q = inline mode; the "dump" DAQ wraps the pcap reader and writes every packet Snort lets
    # through to passed.pcap. A block/drop rule removes the offending packets (and flow) from it.
    snort -c "$CONF" -r "$pcap" -k none -l "$out" -Q --daq dump --daq-var "file=$out/passed.pcap" \
      2>&1 | tee "$out/snort_stats.txt" ;;
  *) echo "usage: $0 live | pcap <file> <outdir> | ips <file> <outdir>"; exit 1 ;;
esac
