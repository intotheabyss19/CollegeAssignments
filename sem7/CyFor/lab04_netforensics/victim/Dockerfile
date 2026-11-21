# A "production web server" that has been compromised. plant_iocs.sh seeds the evidence at start-up.
FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
 && apt-get install -y --no-install-recommends nginx openssh-server rsyslog cron sudo git ca-certificates \
      python3 sqlite3 tcpdump iproute2 procps psmisc lsof curl debsums file kmod \
 && rm -rf /var/lib/apt/lists/*

# Live-Forensicator, pinned to the commit this lab was tested with
ARG LF_COMMIT=663a87d8de8a016a1cd7710451d4dc6b5abec34c
RUN git clone https://github.com/Johnng007/Live-Forensicator.git /opt/Live-Forensicator \
 && git -C /opt/Live-Forensicator checkout -q "$LF_COMMIT" \
 && chmod +x /opt/Live-Forensicator/Linux/Forensicator.sh

COPY plant_iocs.sh /opt/plant_iocs.sh
RUN chmod +x /opt/plant_iocs.sh
CMD ["/opt/plant_iocs.sh"]
