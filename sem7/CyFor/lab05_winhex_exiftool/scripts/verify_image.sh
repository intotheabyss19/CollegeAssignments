#!/usr/bin/env bash
# Step 8: integrity check of the evidence image + an independent Sleuth Kit view of it
# (useful to cross-check what WinHex shows you, and to compare against Autopsy in Lab 06).
set -uo pipefail
EV=/lab/evidence; IMG="$EV/usb_evidence.img"; OUT=/lab/output
mkdir -p "$OUT"
cd "$EV"
echo "== hash verification"
md5sum -c usb_evidence.img.md5 && sha256sum -c usb_evidence.img.sha256

{
echo "== partition table (mmls)";               mmls "$IMG"
echo; echo "== file system (fsstat)";            fsstat -o 2048 "$IMG" | sed -n '1,25p'
echo; echo "== all files incl. deleted (fls -r; * = deleted)"; fls -r -p -o 2048 "$IMG"
echo; echo "== unallocated space size (blkls)";  echo "$(blkls -o 2048 "$IMG" | wc -c) bytes"
echo; echo "== JPEG / PDF signatures inside unallocated space (carving candidates)"
blkls -o 2048 "$IMG" >/tmp/unalloc.bin
LC_ALL=C grep -obUaP '\xFF\xD8\xFF[\xE0-\xEF]' /tmp/unalloc.bin | cut -d: -f1 | sed 's/^/  JPEG header at unallocated offset /'
grep -obUa '%PDF-' /tmp/unalloc.bin | cut -d: -f1 | sed 's/^/  PDF header at unallocated offset /'
} | tee "$OUT/sleuthkit_view.txt"
