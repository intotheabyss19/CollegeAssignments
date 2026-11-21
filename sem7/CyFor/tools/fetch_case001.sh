#!/usr/bin/env bash
# Download artifacts from the public DFIR Madness "Case 001 - The Stolen Szechuan Sauce"
# training case, verify them against the MD5s published on the case page, and record
# every acquisition in evidence/CHAIN_OF_CUSTODY.md.
#
#   tools/fetch_case001.sh                 # default set: DC01 memory + pcap (~710 MB)
#   tools/fetch_case001.sh DC01-E01.zip    # anything listed in expected_md5 (E01s are 5-7 GB)
#
# Source: https://dfirmadness.com/the-stolen-szechuan-sauce/
# Written for macOS's stock bash 3.2 (no associative arrays).
set -euo pipefail

BASE_URL="https://dfirmadness.com/case001"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
DEST="$ROOT/evidence/case001"
COC="$ROOT/evidence/CHAIN_OF_CUSTODY.md"
ANALYST="${ANALYST:-Yash Gupta}"

# Published MD5s (copied from the case page on 2026-10-31)
expected_md5() {
  case "$1" in
    case001-pcap.zip)              echo 422046b753cf8a4df49d2c4ce892db16 ;;
    DC01-memory.zip)               echo 64a4e2cb47138084a5c2878066b2d7b1 ;;
    DC01-E01.zip)                  echo e57fc636e833c5f1ab58dface873bbde ;;
    DC01-pagefile.zip)             echo 964eeaf0009d08cc101de4a83a4e5d23 ;;
    DC01-autorunsc.zip)            echo 964f2d710687d170c77c94947da29e66 ;;
    DC01-ProtectedFiles.zip)       echo ad29830a583efe49c8c1c35faffd264f ;;
    DESKTOP-SDN1RPT-memory.zip)    echo cf31e2635c77811aaa1bb04a92a721e2 ;;
    DESKTOP-E01.zip)               echo 71c5c3509331f472abcdf81eb6efff07 ;;
    Desktop-SDN1RPT-pagefile.zip)  echo 45c096f2688a0b5de0346fb72391b245 ;;
    *) return 1 ;;
  esac
}

md5_of() { if command -v md5 >/dev/null; then md5 -q "$1"; else md5sum "$1" | cut -d' ' -f1; fi; }

[[ $# -eq 0 ]] && set -- DC01-memory.zip case001-pcap.zip

mkdir -p "$DEST"
if [[ ! -f "$COC" ]]; then
  cat >"$COC" <<'EOF'
# Chain of Custody - CS17239 Cyber Forensics Lab

Every evidence item is hashed on acquisition and checked against the publisher's MD5.
Extracted copies are made read-only; all analysis runs on read-only mounts.

| # | Acquired (UTC) | Item | Source | Expected MD5 | Computed MD5 | SHA-256 | Size (bytes) | Handled by | Verified |
|---|---|---|---|---|---|---|---|---|---|
EOF
fi

for f in "$@"; do
  if ! expected="$(expected_md5 "$f")"; then
    echo "Unknown artifact: $f" >&2; exit 1
  fi
  out="$DEST/$f"
  url="$BASE_URL/$f"

  if [[ -f "$out" && "$(md5_of "$out")" == "$expected" ]]; then
    echo "[=] $f already present and verified"
  else
    echo "[+] Downloading $url"
    curl -fL --retry 3 -C - -o "$out" "$url"

    echo "[+] Hashing $f"
    got_md5="$(md5_of "$out")"
    got_sha="$(shasum -a 256 "$out" | cut -d' ' -f1)"
    size="$(wc -c <"$out" | tr -d ' ')"
    ok="NO"; [[ "$got_md5" == "$expected" ]] && ok="YES"
    n=$(( $(grep -c '^| [0-9]' "$COC" || true) + 1 ))
    echo "| $n | $(date -u '+%Y-%m-%d %H:%M:%S') | $f | $url | $expected | $got_md5 | $got_sha | $size | $ANALYST | $ok |" >>"$COC"
    if [[ "$ok" != "YES" ]]; then
      echo "[!] MD5 MISMATCH for $f - do not use it as evidence" >&2
      exit 2
    fi
    echo "[ok] $f verified (md5 $got_md5)"
  fi

  # Unpack next to the zip and make the copy read-only so the original stays pristine
  dir="$DEST/${f%.zip}"
  if [[ ! -d "$dir" ]]; then
    mkdir -p "$dir"
    unzip -n -q "$out" -d "$dir"
    chmod -R a-w "$dir"
    echo "[ok] extracted to evidence/case001/${f%.zip}/"
  fi
done
