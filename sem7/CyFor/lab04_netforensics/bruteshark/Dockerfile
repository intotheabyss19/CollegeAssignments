# BruteSharkCli v1.2.5 - the official Linux build (self-contained .NET, x86-64 only,
# so compose runs it with platform linux/amd64 under emulation).
FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive \
    DOTNET_SYSTEM_GLOBALIZATION_INVARIANT=1
RUN apt-get update \
 && apt-get install -y --no-install-recommends libpcap0.8 libpcap-dev ca-certificates curl tshark python3-minimal \
 && rm -rf /var/lib/apt/lists/*

# Download and verify against the hash recorded when this lab was built (2026-10-31).
# (curl instead of ADD: the 87 MB GitHub asset is slow and BuildKit's ADD times out.)
ARG BS_URL=https://github.com/odedshimon/BruteShark/releases/download/v1.2.5/BruteSharkCli
ARG BS_SHA256=ec969ecd2198727c041a0827640b821f8df2c4e90bfa7581a45d5eab5e2cd1f0
RUN mkdir -p /opt/bruteshark \
 && curl -fL --retry 5 --retry-delay 3 -o /opt/bruteshark/BruteSharkCli "$BS_URL" \
 && echo "$BS_SHA256  /opt/bruteshark/BruteSharkCli" | sha256sum -c - \
 && echo "$BS_SHA256  /opt/bruteshark/BruteSharkCli" > /opt/bruteshark/SHA256SUM \
 && chmod +x /opt/bruteshark/BruteSharkCli \
 && ln -s /opt/bruteshark/BruteSharkCli /usr/local/bin/BruteSharkCli \
 # SharpPcap dlopen()s the unversioned "libdl.so"; glibc >= 2.34 only ships libdl.so.2
 && ln -sf /lib/x86_64-linux-gnu/libdl.so.2 /usr/lib/x86_64-linux-gnu/libdl.so

COPY run_bruteshark.sh sll2eth.py /opt/
RUN chmod +x /opt/run_bruteshark.sh /opt/sll2eth.py
WORKDIR /output
