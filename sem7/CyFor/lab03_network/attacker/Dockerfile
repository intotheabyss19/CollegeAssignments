# Attacker / analyst workstation for the scanning range
FROM debian:bookworm-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN echo "wireshark-common wireshark-common/install-setuid boolean false" | debconf-set-selections \
 && apt-get update \
 && apt-get install -y --no-install-recommends \
      nmap ndiff tcpdump tshark hping3 curl dnsutils iproute2 iputils-ping netcat-openbsd \
      inetutils-ftp sshpass openssh-client redis-tools python3 procps less jq ca-certificates \
 && rm -rf /var/lib/apt/lists/*
WORKDIR /lab
