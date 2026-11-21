# Linux box for system-call tracing. strace needs ptrace, which compose.yaml grants.
FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
 && apt-get install -y --no-install-recommends strace ltrace gcc libc6-dev make python3 \
      netcat-openbsd procps file less coreutils util-linux ca-certificates \
 && rm -rf /var/lib/apt/lists/* \
 && useradd -m -s /bin/bash analyst
WORKDIR /lab
CMD ["bash"]
