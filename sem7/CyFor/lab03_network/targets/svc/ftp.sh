#!/bin/bash
# Plain FTP (no TLS) with anonymous login enabled - two classic findings for nmap NSE.
source /opt/svc/common.sh
mkdir -p /var/ftp/pub /var/run/vsftpd/empty
echo "public readme - anonymous access is enabled on this server" >/var/ftp/pub/README.txt
cat >/etc/vsftpd/vsftpd.conf <<'EOF'
listen=YES
anonymous_enable=YES
anon_root=/var/ftp
local_enable=YES
write_enable=YES
chroot_local_user=YES
allow_writeable_chroot=YES
pasv_enable=YES
pasv_min_port=21100
pasv_max_port=21110
seccomp_sandbox=NO
ftpd_banner=Welcome to CyFor Lab FTP (vsFTPd)
secure_chroot_dir=/var/run/vsftpd/empty
EOF
exec vsftpd /etc/vsftpd/vsftpd.conf
