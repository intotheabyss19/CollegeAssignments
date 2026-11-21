#!/bin/bash
# Offline analysis of a capture with Snort 3 and Zeek, in containers with NO network and the
# evidence mounted read-only. Results -> output/<name>/{snort,zeek}/ + output/<name>/SUMMARY.txt
#
#   scripts/analyze.sh scenario                 # pcaps/lab09_scenario.pcap   (HOME_NET 10.10.90.0/24)
#   scripts/analyze.sh case001                  # Stolen Szechuan Sauce pcap  (HOME_NET 10.42.85.0/24)
#   scripts/analyze.sh lab03 09_anomalies.pcap  # a Lab 03 capture            (HOME_NET 10.10.30.0/24)
# Options (env):  ET=1   also load Emerging Threats Open rules (output name gets "-et")
#                 IPS=1  run Snort as a simulated inline IPS (writes snort/passed.pcap)
set -euo pipefail
cd "$(dirname "$0")/.."
target=${1:?usage: analyze.sh scenario|case001|lab03 <file>}

case "$target" in
  scenario) pcap=/pcaps/lab09_scenario.pcap;           net=10.10.90.0/24; name=scenario ;;
  case001)  pcap=/evidence/case001/case001.pcap;       net=10.42.85.0/24; name=case001 ;;
  lab03)    f=${2:?file name in lab03_network/captures}; pcap=/evidence/lab03/$f; net=10.10.30.0/24; name=lab03_${f%.pcap} ;;
  *) echo "unknown target $target"; exit 1 ;;
esac
[ "${ET:-0}" = 1 ] && name=$name-et
[ "${IPS:-0}" = 1 ] && name=$name-ips
out=output/$name
mkdir -p "$out"
DC="docker compose --profile offline"

# Real malware lives in case001 (coreupdater.exe) - hash it, don't carve it onto the Mac.
extract=T; [ "$target" = case001 ] && extract=F

echo "== Snort: $pcap (HOME_NET=$net, ET=${ET:-0}, IPS=${IPS:-0})"
$DC run --rm -T -e HOME_NET=$net -e ET=${ET:-0} snort-offline \
    "$([ "${IPS:-0}" = 1 ] && echo ips || echo pcap)" "$pcap" "/$out/snort" > /dev/null
echo "== Zeek: $pcap"
$DC run --rm -T zeek-offline pcap "$pcap" "/$out/zeek" \
    "redef Site::local_nets += { $net }; redef LabC2::extract_executables = $extract;" 2>&1 | grep -v -i 'warning\|zeekygen' || true

# ---- summary ---------------------------------------------------------------------------------------
{
  echo "# $name  ($pcap)   generated $(date -u +%FT%TZ)"
  echo
  echo "## Snort: alerts by rule (count, gid:sid, message)"
  $DC run --rm -T --entrypoint sh snort-offline -c \
    "jq -r '\"\(.rule)  \(.msg)\"' /$out/snort/alert_json.txt 2>/dev/null | sort | uniq -c | sort -rn"
  echo
  echo "## Snort: packets / alerts"
  grep -E '^\s+(received|analyzed|alerts|logged|total_alerts|blocked|would_block|block|allow|pass):' "$out/snort/snort_stats.txt" | head -12 || true
  echo
  echo "## Zeek: notices (count, type, first message)"
  $DC run --rm -T --entrypoint bash zeek-offline -c \
    "cd /$out/zeek && [ -f notice.log ] && /usr/local/zeek/bin/zeek-cut note msg < notice.log | awk -F'\t' '{c[\$1]++; if(!(\$1 in m)) m[\$1]=\$2} END {for(k in c) printf \"%5d  %-36s %s\n\", c[k], k, m[k]}' | sort -rn || echo '  (no notice.log)'"
  echo
  echo "## Zeek: logs written (lines)"
  (cd "$out/zeek" && for l in *.log; do printf '%7d  %s\n' "$(grep -vc '^#' "$l")" "$l"; done)
} > "$out/SUMMARY.txt"
cat "$out/SUMMARY.txt"
