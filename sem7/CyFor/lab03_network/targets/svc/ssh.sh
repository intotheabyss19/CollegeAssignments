#!/bin/bash
# SSH with password auth - encrypted, so a good contrast to telnet/FTP in Wireshark.
source /opt/svc/common.sh
ssh-keygen -A >/dev/null
sed -i 's/^#\?PasswordAuthentication.*/PasswordAuthentication yes/' /etc/ssh/sshd_config
exec /usr/sbin/sshd -D -e
