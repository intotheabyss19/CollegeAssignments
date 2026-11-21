#!/usr/bin/env bash
# Run the Lab 01 analysis (steps 2-7 of the lab sheet) against a Windows memory image and
# save every plugin's output to /output/<NN>_<plugin>.txt plus a run log with timings.
#
#   docker compose run --rm --entrypoint /opt/lab/analyze.sh vol [image]
#
# Default image: the first *.mem/*.raw/*.vmem/*.dmp found under /evidence/case001/DC01-memory
set -uo pipefail

IMG="${1:-${MEMIMG:-}}"
if [[ -z "$IMG" ]]; then
  IMG="$(find /evidence/case001/DC01-memory -maxdepth 2 -type f \( -iname '*.mem' -o -iname '*.raw' -o -iname '*.vmem' -o -iname '*.dmp' \) | head -1)"
fi
[[ -f "$IMG" ]] || { echo "Memory image not found. Run tools/fetch_case001.sh first, or pass a path." >&2; exit 1; }

OUT=/output
LOG="$OUT/00_run_log.txt"
mkdir -p "$OUT"
# `vol -h` lists e.g. "windows.pslist.PsList"; plugins are invoked without the class suffix
PLUGINS="$(vol -h 2>/dev/null | grep -oE '^\s+windows\.[A-Za-z_.]+' | tr -d ' ' | sed -E 's/\.[A-Za-z_]+$//')"

# pick the first plugin name this Volatility build actually has (names moved between releases)
pick() { for p in "$@"; do grep -qx "$p" <<<"$PLUGINS" && { echo "$p"; return 0; }; done; return 1; }

n=0
run() {               # run <label> <plugin-candidates...> -- [plugin args]
  local label="$1"; shift
  local cands=(); while [[ $# -gt 0 && "$1" != "--" ]]; do cands+=("$1"); shift; done
  [[ "${1:-}" == "--" ]] && shift
  local plugin; plugin="$(pick "${cands[@]}")" || { echo "[skip] $label: none of ${cands[*]} available" | tee -a "$LOG"; return; }
  n=$((n+1)); local f; f="$(printf '%s/%02d_%s.txt' "$OUT" "$n" "$label")"
  local t0=$SECONDS
  echo "[run ] vol -f $IMG $plugin $*" | tee -a "$LOG"
  vol -q -r pretty -f "$IMG" "$plugin" "$@" >"$f" 2>>"$LOG"
  echo "[done] $label -> $(basename "$f") ($(wc -l <"$f") lines, $((SECONDS-t0))s)" | tee -a "$LOG"
}

{
  echo "Lab 01 Volatility run  $(date -u '+%F %T') UTC  host=$(hostname)"
  echo "Image: $IMG"
  echo "Image SHA-256: $(sha256sum "$IMG" | cut -d' ' -f1)"
  echo "Volatility: $(vol --version 2>&1 | tail -1)"
  echo
} | tee "$LOG"

# Step 2: identify the image / OS (first run downloads the kernel's PDB symbols - needs internet)
run info            windows.info

# Step 3: process analysis
run pslist          windows.pslist
run pstree          windows.pstree
run psscan          windows.psscan          # finds unlinked/terminated processes pslist misses
run cmdline         windows.cmdline
run getsids         windows.getsids
run privileges      windows.privileges

# Step 4: network analysis
run netscan         windows.netscan
run netstat         windows.netstat

# Step 5: file analysis
run filescan        windows.filescan

# Step 6: registry analysis
run hivelist        windows.registry.hivelist
run run_keys_hklm   windows.registry.printkey -- --key 'Microsoft\Windows\CurrentVersion\Run'
run userassist      windows.registry.userassist
run services        windows.svcscan
run hashdump        windows.registry.hashdump windows.hashdump

# Step 7: malware detection
run malfind         windows.malware.malfind windows.malfind
run psxview         windows.malware.psxview windows.psxview
run ldrmodules      windows.malware.ldrmodules windows.ldrmodules
run hollowprocesses windows.malware.hollowprocesses windows.hollowprocesses
run dlllist         windows.dlllist

echo | tee -a "$LOG"
echo "Finished: $n plugins, outputs in lab01_volatility/output/" | tee -a "$LOG"
