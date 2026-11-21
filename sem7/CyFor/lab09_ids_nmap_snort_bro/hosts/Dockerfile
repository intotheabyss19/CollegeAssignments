# One small Alpine image for every scenario host. The ROLE argument to `role` decides what it runs:
#   web01    - DMZ server: nginx (HTTP + Basic-auth /admin), vsftpd (FTP), OpenSSH
#   customer - legitimate internet user
#   attacker - nmap, hydra, curl, lftp
#   c2       - attacker's "update server": serves payload.exe and answers beacons
#   resolver - DNS (dnsmasq) for the lab, incl. the attacker's domain evil-cdn.lab
FROM alpine:3.20
RUN apk add --no-cache nginx vsftpd openssh dnsmasq curl bind-tools python3 nmap nmap-scripts \
      hydra lftp sshpass iproute2 tcpdump coreutils
COPY gen_assets.py nginx.conf vsftpd.conf /opt/lab/
COPY www/ /srv/www/
RUN python3 /opt/lab/gen_assets.py && mkdir -p /srv/ftp \
 # deliberately weak accounts on web01 (the attacker will guess two of them)
 && adduser -D -h /srv/ftp/alice  alice    && echo 'alice:Summer2026!'  | chpasswd \
 && adduser -D -h /srv/ftp/backup backup   && echo 'backup:backup123'   | chpasswd \
 && adduser -D -s /bin/sh webadmin         && echo 'webadmin:sunshine'  | chpasswd \
 && mv /opt/lab/customers.csv /srv/ftp/backup/ && cp /srv/www/files/report.pdf /srv/ftp/alice/ \
 && chown -R alice:alice /srv/ftp/alice && chown -R backup:backup /srv/ftp/backup \
 && cp /opt/lab/nginx.conf /etc/nginx/http.d/default.conf && cp /opt/lab/vsftpd.conf /etc/vsftpd/vsftpd.conf \
 && sed -i 's/^#\?PasswordAuthentication.*/PasswordAuthentication yes/; s/^#\?MaxStartups.*/MaxStartups 64:30:128/' /etc/ssh/sshd_config \
 && ssh-keygen -A
COPY role.sh /usr/local/bin/role
COPY wordlists/ /opt/lab/wordlists/
