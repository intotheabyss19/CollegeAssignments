# One small image that can play several weak services (chosen by the compose `command`)
FROM alpine:3.20
RUN apk add --no-cache vsftpd busybox-extras openssh-server dnsmasq shadow bash
COPY svc/ /opt/svc/
COPY files/ /srv/files/
RUN chmod +x /opt/svc/*.sh
