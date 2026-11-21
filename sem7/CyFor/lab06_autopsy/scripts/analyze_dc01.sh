#!/usr/bin/env bash
# Lab 06 fallback analysis: The Sleuth Kit (the engine Autopsy wraps) on the DC01 E01 image,
# run natively on the Mac in Docker because Autopsy's x64 build hangs under Windows-on-ARM emulation.
#
# Usage:  ./scripts/analyze_dc01.sh
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
E01DIR="$ROOT/../evidence/case001/DC01-E01/E01-DC01"
OUT="$ROOT/output"; mkdir -p "$OUT/recovered"
IMG=/ev/20200918_0347_CDrive.E01
OFF=718848   # C: partition (from mmls)

docker run --rm -v "$E01DIR:/ev:ro" -v "$OUT:/out" cyfor/lab05-tools:latest bash -c '
set -e; IMG='"$IMG"'; OFF='"$OFF"'
echo "############ 1. PARTITION TABLE (mmls) ############"
mmls "$IMG"
echo; echo "############ 2. C: FILE SYSTEM (fsstat) ############"
fsstat -o $OFF "$IMG" | sed -n "1,16p"
echo; echo "############ 3. TIMELINE BODY FILE (fls -r) ############"
if [ ! -s /out/bodyfile.txt ]; then fls -r -m C: -o $OFF "$IMG" > /out/bodyfile.txt 2>/dev/null; fi
echo "files inventoried: $(wc -l < /out/bodyfile.txt)"
echo; echo "############ 4. KEYWORD SEARCH (szechuan / secret / coreupdater) ############"
grep -iE "szechuan|FileShare/Secret|coreupdater" /out/bodyfile.txt | grep -ivE "FILE_NAME" \
  | awk -F"|" "{print \$2}" | sort -u
echo; echo "############ 5. INTRUSION TIMELINE (2020-09-18..19) ############"
mactime -b /out/bodyfile.txt 2020-09-18..2020-09-19 2>/dev/null \
  | grep -iE "FileShare/Secret|/Recent/.*lnk|coreupdater" | grep -ivE "FILE_NAME" | sed -n "1,20p"
echo; echo "############ 6. RECOVER + HASH THE MALWARE AND THE STOLEN FILE ############"
icat -o $OFF "$IMG" 87137 > /out/recovered/coreupdater.exe 2>/dev/null
icat -o $OFF "$IMG" 87059 > /out/recovered/SzechuanSauce.txt 2>/dev/null
echo "coreupdater.exe  $(wc -c < /out/recovered/coreupdater.exe) bytes"
sha256sum /out/recovered/coreupdater.exe
echo "-- plaintext strings in coreupdater.exe (packed -> no C2 on disk):"
cat /out/recovered/coreupdater.exe | tr -c "[:print:]" "\n" | grep -E "^.{4,}$" | sort -u | grep -iE "dll|http|[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+" | head
echo "-- stolen file content (Szechuan Sauce.txt):"; sed -n "1,4p" /out/recovered/SzechuanSauce.txt
echo; echo "############ 7. PREFETCH (executed programs) ############"
echo "Prefetch .pf files: $(grep -icE "C:/Windows/Prefetch/.*\.pf" /out/bodyfile.txt)  (0 = prefetch off, server default; matches Lab 01)"
echo; echo "[done] recovered artifacts in output/recovered/, timeline body in output/bodyfile.txt"
'
