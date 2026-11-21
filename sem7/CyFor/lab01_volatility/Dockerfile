# Volatility 3 analysis workstation (native arm64, nothing installed on the Mac)
FROM python:3.12-slim

ARG VOL_VERSION=2.28.2
RUN apt-get update \
 && apt-get install -y --no-install-recommends build-essential unzip file less jq \
 # Not using the [full] extra: it pulls leechcorepyc (PCILeech hardware acquisition), which
 # doesn't build on arm64 and isn't needed. These are the extras the analysis plugins use:
 # pefile (PE parsing, verinfo), yara-python (yarascan/vadyarascan), capstone (malfind disasm),
 # pycryptodome (hashdump/lsadump/cachedump).
 && pip install --no-cache-dir "volatility3==${VOL_VERSION}" pefile yara-python capstone pycryptodome \
 && apt-get purge -y build-essential && apt-get autoremove -y \
 && rm -rf /var/lib/apt/lists/*

# Windows symbol tables (PDB -> ISF) are downloaded on first use and cached here
VOLUME ["/root/.cache/volatility3"]

COPY scripts/ /opt/lab/
RUN chmod +x /opt/lab/*.sh
WORKDIR /output
ENTRYPOINT ["vol"]
CMD ["-h"]
