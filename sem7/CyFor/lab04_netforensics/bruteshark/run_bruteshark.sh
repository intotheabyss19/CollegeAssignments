#!/usr/bin/env bash
# Run BruteSharkCli over each pcap group and export credentials, hashes, network map, DNS, files.
#   docker compose run --rm bruteshark                 # every group found under /pcaps
#   docker compose run --rm bruteshark /pcaps/lab03     # one directory
#   docker compose run --rm bruteshark --help          # raw BruteSharkCli usage
set -uo pipefail
[[ "${1:-}" == -* ]] && exec BruteSharkCli "$@"

MODULES="Credentials,NetworkMap,FileExtracting,DNS"
targets=("$@")
[[ ${#targets[@]} -eq 0 ]] && targets=(/pcaps/*/)

echo "BruteSharkCli $(cut -c1-16 /opt/bruteshark/SHA256SUM)... (sha256 prefix)"
for dir in "${targets[@]}"; do
  dir="${dir%/}"; name="$(basename "$dir")"
  # BruteShark needs classic pcap with Ethernet framing: pcapng -> pcap, then cooked (-i any) -> Ethernet
  work="/tmp/in/$name"; mkdir -p "$work"
  while IFS= read -r f; do
    rel="${f#$dir/}"; base="$(echo "${rel%.*}" | tr '/' '_')"
    editcap -F pcap "$f" "/tmp/$base.tmp" 2>/dev/null || cp "$f" "/tmp/$base.tmp"
    python3 /opt/sll2eth.py "/tmp/$base.tmp" "$work/$base.pcap" && rm -f "/tmp/$base.tmp"
  done < <(find "$dir" -type f \( -name '*.pcap' -o -name '*.pcapng' \))
  n=$(ls "$work"/*.pcap 2>/dev/null | wc -l)
  [[ $n -eq 0 ]] && { echo "[skip] $dir has no pcaps"; continue; }

  out="/output/bruteshark/$name"; mkdir -p "$out"
  echo; echo "==== $name: $n pcap(s) -> output/bruteshark/$name ===="
  BruteSharkCli -m "$MODULES" -d "$work" -o "$out" 2>&1 | tee "$out/run.log" | grep -vE '^\s*$' | tail -25
done
