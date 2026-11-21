#!/bin/bash
# Zeek wrapper.
#   run.sh live                               sniff the firewall's DMZ interface -> /output/live/zeek/
#   run.sh pcap <file.pcap> <outdir> [zeek code]   read a capture             -> <outdir>/
# Zeek writes its logs into the CURRENT directory, hence the cd.
#   -C : ignore bad checksums (Docker offload, see snort/run.sh)
#   -e : extra Zeek code, e.g. 'redef Site::local_nets += { 10.42.85.0/24 };'
set -euo pipefail
export PATH=/usr/local/zeek/bin:$PATH
mode=${1:-live}
case "$mode" in
  live)
    out=/output/live/zeek; mkdir -p "$out"; cd "$out"
    echo "[zeek] live on dmz0, logs -> $out"
    exec zeek -C -i dmz0 /lab/zeek/lab.zeek ;;
  pcap)
    pcap=$2 out=$3 extra=${4:-}
    mkdir -p "$out"; cd "$out"; rm -f ./*.log; rm -rf extract_files
    zeek -C -r "$pcap" /lab/zeek/lab.zeek ${extra:+-e "$extra"}
    ls -1 *.log ;;
  *) echo "usage: $0 live | pcap <file> <outdir> [zeek code]"; exit 1 ;;
esac
