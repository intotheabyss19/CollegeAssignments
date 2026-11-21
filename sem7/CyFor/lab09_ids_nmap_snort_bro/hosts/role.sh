#!/bin/sh
# role <web01|customer|attacker|c2|resolver>
# 1. Route the "other side" through the firewall/sensor box (10.10.90.254 / 203.0.113.254),
#    so DMZ <-> internet traffic crosses the point where Snort and Zeek are listening.
# 2. Start the services for that role.
set -e
ROLE="$1"
DMZ=10.10.90.0/24  WAN=203.0.113.0/24
case "$ROLE" in
  web01) ip route replace $WAN via 10.10.90.254
         echo "nameserver 203.0.113.53" > /etc/resolv.conf ;;
  *)     ip route replace $DMZ via 203.0.113.254
         echo "nameserver 203.0.113.53" > /etc/resolv.conf ;;
esac

case "$ROLE" in
  web01)
    /usr/sbin/sshd
    vsftpd /etc/vsftpd/vsftpd.conf &
    exec nginx -g 'daemon off;' ;;
  c2)
    # plain python web server = typical cheap attacker infrastructure
    cd /srv/c2 && exec python3 -m http.server 80 ;;
  resolver)
    # authoritative for the lab names, wildcard for the attacker's domain (so DNS-exfil labels resolve)
    # --listen-address: without it dnsmasq answers only its own subnet ("local-service" default).
    # No upstream server: AAAA (IPv6) lookups get REFUSED, so the scenario uses IPv4-only clients.
    exec dnsmasq --no-daemon --no-resolv --log-queries --log-facility=- --listen-address=203.0.113.53 \
      --host-record=www.corp.lab,10.10.90.20 --host-record=ftp.corp.lab,10.10.90.20 \
      --address=/evil-cdn.lab/203.0.113.99 ;;
  *) exec sleep infinity ;;
esac
