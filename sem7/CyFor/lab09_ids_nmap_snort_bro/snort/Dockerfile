# Snort 3 built from source (Ubuntu only packages Snort 2.9, which is end-of-life).
# Multi-stage: the compiler toolchain stays in the "build" stage; the final image only has
# the runtime libraries + /usr/local (libdaq + snort). Tarballs are pinned by SHA-256.
#
#   docker build -t cyfor/lab09-snort:3.12.4.0 .
FROM ubuntu:24.04 AS build
ARG LIBDAQ_VER=3.0.28
ARG LIBDAQ_SHA256=a72bc8882abdcfaf475b18d547b5a08785d574005584ce258e533d247bc62771
ARG SNORT_VER=3.12.4.0
ARG SNORT_SHA256=5bab33f703ca09b74bc2de72d16d8be59c67ebb98dbd45e50c30989b5cdd510f
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
      build-essential cmake pkg-config autoconf automake libtool ca-certificates curl \
      libdumbnet-dev libhwloc-dev libluajit-5.1-dev libssl-dev libpcap-dev libpcre2-dev \
      zlib1g-dev liblzma-dev uuid-dev libunwind-dev libmnl-dev flex libfl-dev bison \
 && rm -rf /var/lib/apt/lists/*
WORKDIR /src
# libdaq = Data AcQuisition library: the layer that hands packets to Snort (pcap file, AF_PACKET, ...)
RUN curl -fsSLo daq.tgz https://github.com/snort3/libdaq/archive/refs/tags/v${LIBDAQ_VER}.tar.gz \
 && echo "${LIBDAQ_SHA256}  daq.tgz" | sha256sum -c - \
 && tar xzf daq.tgz && cd libdaq-${LIBDAQ_VER} \
 && ./bootstrap && ./configure --prefix=/usr/local && make -j"$(nproc)" && make install
RUN curl -fsSLo snort.tgz https://github.com/snort3/snort3/archive/refs/tags/${SNORT_VER}.tar.gz \
 && echo "${SNORT_SHA256}  snort.tgz" | sha256sum -c - \
 && tar xzf snort.tgz && cd snort3-${SNORT_VER} \
 && ./configure_cmake.sh --prefix=/usr/local --disable-docs \
 && cd build && make -j"$(nproc)" && make install

FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
      libdumbnet1 libhwloc15 libluajit-5.1-2 libssl3t64 libpcap0.8t64 libpcre2-8-0 zlib1g \
      liblzma5 libuuid1 libunwind8 libmnl0 libnuma1 \
      tcpdump tshark jq iproute2 ca-certificates \
 && rm -rf /var/lib/apt/lists/*
COPY --from=build /usr/local /usr/local
RUN ldconfig && ! ldd /usr/local/bin/snort | grep "not found" && snort -V
WORKDIR /lab
