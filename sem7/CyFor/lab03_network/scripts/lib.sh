#!/usr/bin/env bash
# Shared helpers: run a command while tcpdump records everything the attacker box sends/receives.
CAP_DIR=/lab/captures
IFACE="$(ip -o -4 addr show | awk '/10\.10\.30\./ {print $2; exit}')"
mkdir -p "$CAP_DIR" "$CAP_DIR/nmap"

banner() { printf '\n==================== %s ====================\n' "$*"; }

# capture <name> <command...>   -> captures/<name>.pcap
capture() {
  local name="$1"; shift
  local pcap="$CAP_DIR/$name.pcap"
  tcpdump -i "$IFACE" -U -s 0 -w "$pcap" 'not port 2375' >/dev/null 2>&1 &
  local tp=$!
  sleep 1
  "$@"
  sleep 1
  kill -INT "$tp" 2>/dev/null; wait "$tp" 2>/dev/null
  echo "[pcap] $pcap  ($(capinfos -c -M "$pcap" 2>/dev/null | awk '/Number of packets/ {print $NF}') packets, $(du -h "$pcap" | cut -f1))"
}
