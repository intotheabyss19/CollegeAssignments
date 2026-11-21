# Central syslog collector: one file per sending container under /var/log/remote/
FROM alpine:3.20
RUN apk add --no-cache rsyslog
RUN cat >/etc/rsyslog.conf <<'EOF'
module(load="imtcp")
input(type="imtcp" port="514")
template(name="PerTag" type="string" string="/var/log/remote/%programname%.log")
*.* action(type="omfile" dynaFile="PerTag")
EOF
CMD ["rsyslogd", "-n", "-f", "/etc/rsyslog.conf"]
