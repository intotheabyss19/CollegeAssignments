#!/bin/bash
# Live response on the victim with Live-Forensicator (Linux), then copy + hash the results.
#   docker compose exec victim /lab/collect.sh          # standard triage + web logs
#   docker compose exec victim /lab/collect.sh -p       # ...plus a 60-second packet capture
#
# With -p: wait for the ">>> CAPTURE RUNNING" line (Live-Forensicator does ~1 min of other
# collection first), then run `docker compose exec c2 /lab/attack.sh` in a second terminal.
set -uo pipefail
LF=/opt/Live-Forensicator/Linux
HOST="$(hostname)"
STAMP="$(date -u +%Y%m%dT%H%M%SZ)"

# Live-Forensicator records with `tcpdump -G 60 -W 1`, which only exits when a packet arrives
# after the 60 s mark - on a quiet host it waits forever. This watcher announces the capture
# and sends one harmless packet every 5 s so the capture always ends.
watcher() {
  local announced=0
  while sleep 2; do
    if pgrep -x tcpdump >/dev/null; then
      if [[ $announced -eq 0 ]]; then
        echo; echo ">>> CAPTURE RUNNING (60 s) - run the attack now: docker compose exec c2 /lab/attack.sh"; echo
        announced=1
      fi
      (exec 3<>/dev/tcp/10.10.40.66/9) 2>/dev/null
      sleep 3
    fi
  done
}
if [[ " $* " == *" -p "* || " $* " == *" --pcap "* ]]; then
  watcher & WATCHER=$!
  trap 'kill $WATCHER 2>/dev/null' EXIT
fi

cd "$LF"
rm -rf "./$HOST"
./Forensicator.sh -w "$@" \
  -name "Yash Gupta" -case "CS17239-LAB04" -title "Compromised web server triage" \
  -loc "Docker lab (cyfor-lab04)" -device "$HOST"

DEST="/output/live_forensicator/${HOST}_${STAMP}"
mkdir -p "$DEST"
cp -a "./$HOST/." "$DEST/"
(cd "$DEST" && find . -type f ! -name SHA256SUMS -exec sha256sum {} + | sort -k2 >SHA256SUMS)
echo
echo "[ok] results: lab04_netforensics/output/live_forensicator/${HOST}_${STAMP}/"
echo "     report: reports/index.html   detections: DETECTIONS/findings.csv   hashes: SHA256SUMS"
find "$DEST" -maxdepth 2 -name '*.pcap' -exec echo "     pcap for BruteShark/Wireshark: {}" \;
