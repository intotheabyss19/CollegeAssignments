#!/usr/bin/env bash
# "Normal day" traffic for steps 6-7 - DNS, HTTP, FTP, Telnet, SSH, Redis - including the
# cleartext logins and file transfers that Lab 04 (BruteShark) will recover from the pcap.
set -uo pipefail
source /lab/scripts/lib.sh

generate() {
  echo "[dns ] lookups";        for h in web ftp ssh telnet cache nonexistent; do dig +short "$h.lab"; done
  dig +short TXT lab; dig +short example.com

  echo "[http] browse + download files"
  curl -s -o /dev/null -w "  GET / -> %{http_code}\n" http://web.lab/
  curl -s -o /dev/null -w "  GET /files/brochure.pdf -> %{http_code}\n" http://web.lab/files/brochure.pdf
  curl -s -o /dev/null -w "  GET /files/logo.png -> %{http_code}\n" http://web.lab/files/logo.png
  echo "[http] basic-auth login (cleartext, base64 only)"
  curl -s -o /dev/null -w "  wrong password -> %{http_code}\n" -u "$LAB_USER:letmein" http://web.lab/admin/
  curl -s -o /dev/null -w "  right password -> %{http_code}\n" -u "$LAB_USER:$LAB_PASS" http://web.lab/admin/
  echo "[http] form POST login"
  curl -s -o /dev/null -w "  POST /login -> %{http_code}\n" -d "username=$LAB_USER&password=$LAB_PASS" http://web.lab/login

  echo "[ftp ] login, list, download two files, upload one"
  printf 'quote USER %s\nquote PASS %s\nbinary\nls\nget q3_financials.pdf /tmp/q3.pdf\nget site_diagram.png /tmp/diag.png\nput /etc/hostname uploaded_by_attacker.txt\nbye\n' \
    "$LAB_USER" "$LAB_PASS" | ftp -n -p ftp.lab >/dev/null 2>&1
  printf 'quote USER anonymous\nquote PASS guest@\nls pub\nbye\n' | ftp -n -p ftp.lab >/dev/null 2>&1
  ls -la /tmp/q3.pdf /tmp/diag.png 2>/dev/null | sed 's/^/  /'

  echo "[tel ] interactive telnet session"
  python3 - "$LAB_USER" "$LAB_PASS" <<'PY'
import socket, sys, time
user, pw = sys.argv[1], sys.argv[2]
s = socket.create_connection(("telnet.lab", 23), timeout=10)
def drain(t=1.0):
    s.settimeout(t); buf = b""
    try:
        while True:
            d = s.recv(4096)
            if not d: break
            # refuse every telnet option the server proposes (IAC DO/WILL x -> IAC WONT/DONT x)
            i = 0
            while i < len(d):
                if d[i] == 255 and i + 2 < len(d) and d[i+1] in (251, 252, 253, 254):
                    s.sendall(bytes([255, 252 if d[i+1] in (253, 254) else 254, d[i+2]])); i += 3
                else:
                    buf += d[i:i+1]; i += 1
    except socket.timeout:
        pass
    return buf
drain(); s.sendall(user.encode() + b"\r\n"); drain()
s.sendall(pw.encode() + b"\r\n"); drain(1.5)
for cmd in (b"id", b"uname -a", b"cat notes.txt", b"ls -la", b"exit"):
    s.sendall(cmd + b"\r\n"); time.sleep(0.3)
print("  telnet session done, last output:", drain().decode(errors="replace").strip().splitlines()[-1:] )
PY

  echo "[ssh ] encrypted login (compare with telnet in Wireshark)"
  sshpass -p "$LAB_PASS" ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null \
    "$LAB_USER@ssh.lab" 'id; hostname' 2>/dev/null | sed 's/^/  /'

  echo "[redis] unauthenticated access"
  redis-cli -h cache.lab SET session:42 "user=$LAB_USER;role=admin" >/dev/null
  redis-cli -h cache.lab GET session:42 | sed 's/^/  /'
}

banner "Generating baseline + credential traffic"
capture 06_normal_traffic generate
