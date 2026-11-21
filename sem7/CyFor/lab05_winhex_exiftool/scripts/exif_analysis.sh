#!/usr/bin/env bash
# ExifTool steps 4, 5 and 9: extract metadata, turn it into evidence, look for tampering.
# Works on the files you export from the image with WinHex (put them in evidence/exported/),
# or straight from the image via mtools if you haven't done the WinHex part yet.
set -euo pipefail
EV=/lab/evidence; OUT=/lab/output; SRC="$EV/exported"
mkdir -p "$OUT"
if [[ ! -d "$SRC" || -z "$(ls -A "$SRC" 2>/dev/null)" ]]; then
  echo "[i] evidence/exported/ is empty - pulling allocated files out of the image with mtools"
  SRC=/tmp/exported; rm -rf "$SRC"; mkdir -p "$SRC"
  mcopy -i "$EV/usb_evidence.img@@1M" -s -n ::/DCIM ::/Documents "$SRC/"
fi
echo "[i] analysing $(find "$SRC" -type f | wc -l) files from $SRC"

echo; echo "== Step 4: full metadata dump (output/exif_full.txt, output/exif_full.json)"
exiftool -r -a -G1 -s "$SRC" >"$OUT/exif_full.txt"
exiftool -r -j -G1 "$SRC" >"$OUT/exif_full.json"
wc -l "$OUT/exif_full.txt"

echo; echo "== Step 4/5: evidence table (output/exif_summary.csv)"
exiftool -r -csv -n -FileName -FileType -FileTypeExtension -MIMEType -Make -Model -Software \
  -DateTimeOriginal -ModifyDate -FileModifyDate -GPSLatitude -GPSLongitude -Author -Creator \
  -ImageDescription "$SRC" >"$OUT/exif_summary.csv"
column -s, -t <"$OUT/exif_summary.csv" | cut -c1-200

echo; echo "== Step 5: where were the photos taken? (output/gps_locations.md)"
{
  echo "| File | Taken | Device | Lat, Lon | Map |"
  echo "|---|---|---|---|---|"
  exiftool -r -n -p '| $FileName | $DateTimeOriginal | $Make $Model | $GPSLatitude, $GPSLongitude | https://www.openstreetmap.org/?mlat=$GPSLatitude&mlon=${GPSLongitude}#map=16/${GPSLatitude}/${GPSLongitude} |' \
    -if '$GPSLatitude' "$SRC" 2>/dev/null
} | tee "$OUT/gps_locations.md"

echo; echo "== Step 9a: extension vs real file type (signature mismatch)"
exiftool -r -q -p '$FileName|$FileType|$FileTypeExtension' "$SRC" | while IFS='|' read -r name type ext; do
  actual="${name##*.}"
  if [[ "${actual,,}" != "${ext,,}" && ! ( "${actual,,}" == "jpg" && "${ext,,}" == "jpg" ) ]]; then
    echo "MISMATCH: $name claims .$actual but its header says $type"
  fi
done | tee "$OUT/signature_mismatches.txt"

echo; echo "== Step 9b: signs of editing / tampering"
# -f prints '-' for missing tags (without it exiftool silently skips the whole line)
exiftool -r -q -f -p '$FileName|$Software|$DateTimeOriginal|$ModifyDate|$GPSLatitude' -n "$SRC" 2>/dev/null |
while IFS='|' read -r name sw orig mod gps; do
  [[ "$sw" =~ Photoshop|GIMP|Lightroom|Snapseed ]] && echo "EDITED   : $name - Software tag '$sw'"
  [[ "$orig" != "-" && "$mod" != "-" && "$mod" < "$orig" ]] && echo "TIMESTAMP: $name - ModifyDate $mod is BEFORE DateTimeOriginal $orig"
  [[ "$name" =~ \.(JPG|jpg)$ && "$orig" != "-" && "$gps" == "-" ]] && echo "NO GPS   : $name - location removed or never recorded"
done | tee "$OUT/tamper_indicators.txt"

echo; echo "== Step 8/9: integrity - hash every analysed file (output/file_hashes.sha256)"
( cd "$SRC" && find . -type f -exec sha256sum {} + | sort -k2 ) | tee "$OUT/file_hashes.sha256"
