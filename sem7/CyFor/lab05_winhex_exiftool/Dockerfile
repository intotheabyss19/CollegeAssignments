# Evidence factory + ExifTool/Sleuth Kit workstation for Lab 05 (and a cross-check for Lab 06)
FROM debian:bookworm-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
 && apt-get install -y --no-install-recommends libimage-exiftool-perl imagemagick fonts-dejavu-core mtools dosfstools \
      fdisk sleuthkit python3 xxd file bsdextrautils coreutils \
 && rm -rf /var/lib/apt/lists/*
WORKDIR /lab
