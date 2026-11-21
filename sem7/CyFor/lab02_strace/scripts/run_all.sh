#!/usr/bin/env bash
# Lab 02 - every step of the lab sheet, in order. Traces land in /lab/output (= ./output).
#   docker compose run --rm lab02 ./scripts/run_all.sh
set -uo pipefail
OUT=/lab/output; BIN=/opt/bin
mkdir -p "$OUT" "$BIN"
banner() { printf '\n==================== %s ====================\n' "$*"; }

banner "Step 1: strace installed"
strace -V | head -1 | tee "$OUT/01_version.txt"
strace -o "$OUT/01_ls.trace" ls /lab >/dev/null
echo "simplest trace: $(wc -l <"$OUT/01_ls.trace") syscalls made by 'ls /lab' -> 01_ls.trace"

banner "Compiling samples"
for c in /lab/samples/*.c; do
  gcc -O0 -g -o "$BIN/$(basename "${c%.c}")" "$c" && echo "built $(basename "${c%.c}")"
done
chmod 755 "$BIN"/*

banner "Step 2: tracing system calls (timestamps -tt, durations -T, long strings -s)"
strace -tt -T -s 128 -o "$OUT/02_file_ops.trace" "$BIN/file_ops"
grep -E 'openat|write|read|lseek|fstat|rename|unlink' "$OUT/02_file_ops.trace" | grep -v '\.so' | tail -12

banner "Step 3: program flow - fork/execve/wait4/exit (-f follows children)"
strace -f -tt -e trace=process -o "$OUT/03_fork_exec.trace" "$BIN/fork_exec"
cat "$OUT/03_fork_exec.trace"

banner "Step 4: filtering"
strace -e trace=%file    -o "$OUT/04a_filter_file.trace"    "$BIN/file_ops" >/dev/null
strace -e trace=%network -o "$OUT/04b_filter_network.trace" "$BIN/errors"   >/dev/null
strace -e trace=openat,read,write -e signal=none -o "$OUT/04c_filter_named.trace" "$BIN/file_ops" >/dev/null
strace -c -S calls -o "$OUT/04d_summary_counts.txt" "$BIN/fork_exec" >/dev/null
echo "--- syscall summary (-c) for fork_exec:"; head -15 "$OUT/04d_summary_counts.txt"

# attach to an already-running process by PID (-p), like you would on a live suspect process
( while true; do date >/tmp/heartbeat; sleep 0.5; done ) &
TARGET=$!
timeout 3 strace -tt -p "$TARGET" -f -o "$OUT/04e_attach_pid_$TARGET.trace" || true
kill "$TARGET" 2>/dev/null
echo "--- attached to PID $TARGET for 3s: $(wc -l <"$OUT/04e_attach_pid_$TARGET.trace") syscalls captured -> 04e_attach_pid_$TARGET.trace"

banner "Step 5: error handling - run as unprivileged user, show only failed calls (-Z)"
runuser -u analyst -- strace -Z -o "$OUT/05a_failed_only.trace" "$BIN/errors"
echo "--- failed syscalls:"; cat "$OUT/05a_failed_only.trace"
runuser -u analyst -- strace -c -o "$OUT/05b_error_summary.txt" "$BIN/errors" >/dev/null
echo "--- error column of the summary:"; awk 'NR<=2 || $5 ~ /^[0-9]+$/' "$OUT/05b_error_summary.txt"

banner "Step 6: spotting insecure behaviour"
strace -f -s 256 -e trace=openat,chmod,fchmodat,execve,write,unlink -o "$OUT/06_insecure_app.trace" "$BIN/insecure_app" '/var/log; id' >/dev/null
echo "--- the evidence:"
grep -E 'rotate.tmp|chmod|execve\(.*sh|app.secret|DB_PASSWORD' "$OUT/06_insecure_app.trace"

banner "Step 7: forensic trace of a (simulated) dropper"
nc -l -p 4444 >"$OUT/07_exfil_received_by_listener.txt" &
LISTENER=$!; sleep 0.5
cp "$BIN/dropper_sim" /tmp/update-helper            # the "malware" runs from a writable path
strace -f -tt -s 256 -yy -o "$OUT/07_incident.trace" /tmp/update-helper
sleep 0.5; kill "$LISTENER" 2>/dev/null
{
  echo "# Reconstructed timeline from 07_incident.trace"
  echo "## Process identity changes";  grep -E 'execve|prctl' "$OUT/07_incident.trace"
  echo "## Credential access";        grep -E 'openat.*(passwd|shadow)' "$OUT/07_incident.trace"
  echo "## Staging / persistence";    grep -E 'mkdir|X11-cache' "$OUT/07_incident.trace" | grep -E 'mkdir|openat'
  echo "## Network (C2 / exfil)";     grep -E 'socket|connect|sendto' "$OUT/07_incident.trace" | cut -c1-200
  echo "## Anti-forensics";           grep -E 'unlink|rmdir' "$OUT/07_incident.trace"
} | tee "$OUT/07_timeline.md"
echo "binary still on disk? $(ls /tmp/update-helper 2>/dev/null || echo 'no - it deleted itself')"
echo "listener received $(wc -c <"$OUT/07_exfil_received_by_listener.txt") bytes"

banner "Done"
ls -1 "$OUT"
