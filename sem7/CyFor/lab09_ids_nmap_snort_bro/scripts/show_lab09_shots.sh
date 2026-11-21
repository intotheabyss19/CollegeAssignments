#!/usr/bin/env bash
# Lab 09 - produces all screenshot material in one run: starts the lab network, runs the
# live Nmap scans, then prints the saved Snort + Zeek results from the recorded attack.
# Usage:  cd lab09_ids_nmap_snort_bro && ./scripts/show_lab09_shots.sh
set -e
cd "$(dirname "$0")/.."

echo "============================================================"
echo " [01] START THE 8-CONTAINER LAB NETWORK"
echo "============================================================"
docker compose up -d >/dev/null 2>&1
sleep 6
docker compose ps --format 'table {{.Service}}\t{{.Status}}'

echo
echo "============================================================"
echo " [02] NMAP  SYN scan   (attacker 203.0.113.66 -> web01 10.10.90.20)"
echo "============================================================"
docker compose exec -T attacker nmap -sS -Pn --top-ports 100 10.10.90.20

echo
echo "============================================================"
echo " [03] NMAP  service / version scan"
echo "============================================================"
docker compose exec -T attacker nmap -sV -p 21,22,80 10.10.90.20

echo
echo "============================================================"
echo " [04/05] SNORT  packets, alerts, and top rules (recorded attack)"
echo "============================================================"
sed -n '1,41p' output/scenario/SUMMARY.txt

echo
echo "============================================================"
echo " [06] ZEEK  notices + log line counts (recorded attack)"
echo "============================================================"
sed -n '/Zeek: notices/,$p' output/scenario/SUMMARY.txt

echo
echo "============================================================"
echo " [07] ZEEK  ftp.log - cleartext credentials captured off the wire"
echo "============================================================"
docker compose exec -T zeek zeek-cut id.orig_h id.resp_h user password \
  < output/scenario/zeek/ftp.log 2>/dev/null || cat output/scenario/zeek/ftp.log

echo
echo "Done. To shut the lab down when finished:  docker compose --profile '*' down -v"
