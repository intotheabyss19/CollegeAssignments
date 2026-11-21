#!/bin/bash
# Authoritative-ish DNS for the *.lab zone (and an open resolver, which nmap will flag).
cat >/etc/dnsmasq.conf <<'EOF'
no-resolv
server=1.1.1.1
domain=lab
local=/lab/
address=/web.lab/10.10.30.20
address=/ftp.lab/10.10.30.21
address=/telnet.lab/10.10.30.22
address=/ssh.lab/10.10.30.23
address=/cache.lab/10.10.30.24
address=/dns.lab/10.10.30.53
address=/attacker.lab/10.10.30.10
txt-record=lab,"CS17239 CyFor lab range"
log-queries
log-facility=-
EOF
exec dnsmasq -k
