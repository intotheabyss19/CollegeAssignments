#!/usr/bin/env bash
# Lab 03 steps 8-9: generate anomalous traffic INSIDE the isolated range so it can be detected.
# (Only ever point these at the lab containers - flooding real hosts is illegal.)
set -uo pipefail
source /lab/scripts/lib.sh

anomalies() {
  echo "[scan ] aggressive full-range SYN scan (port-scan signature: many SYNs, many RSTs)"
  nmap -sS -p- -T5 --min-rate 5000 10.10.30.20 -oN captures/nmap/09_fullrange.nmap >/dev/null
  echo "[scan ] stealth scan types: NULL, FIN, Xmas"
  nmap -sN -p 1-200 10.10.30.23 >/dev/null; nmap -sF -p 1-200 10.10.30.23 >/dev/null; nmap -sX -p 1-200 10.10.30.23 >/dev/null
  echo "[dos  ] 5-second SYN flood at web:80 (spoofed random sources)"
  timeout 5 hping3 -S -p 80 --flood --rand-source 10.10.30.20 >/dev/null 2>&1
  echo "[dos  ] 3-second ICMP flood at web"
  timeout 3 hping3 --icmp --flood 10.10.30.20 >/dev/null 2>&1
  echo "[brute] 15 rapid failed HTTP basic-auth logins"
  for i in $(seq 1 15); do curl -s -o /dev/null -u "admin:guess$i" http://web.lab/admin/; done
  echo "[dns  ] 50 random-subdomain lookups (tunnelling / DGA-like pattern)"
  for i in $(seq 1 50); do dig +short "$(head -c 12 /dev/urandom | od -An -tx1 | tr -d ' \n').exfil.lab" >/dev/null; done
}

banner "Generating anomalous traffic"
capture 09_anomalies anomalies
