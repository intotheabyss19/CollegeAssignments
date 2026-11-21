#!/usr/bin/env bash
# Build a 64 MiB "seized USB stick" image (MBR + FAT32) for WinHex / ExifTool / Autopsy.
#
# Scenario: an employee is suspected of leaking a confidential design. Their USB stick holds
# holiday photos, some documents, and traces of files they tried to delete or disguise.
#
# What's planted (ground truth - don't put it in the report until you've found it with the tools):
#   DCIM/IMG_0412.JPG .. IMG_0415.JPG  photos with camera make/model, timestamps and GPS
#   DCIM/IMG_0416.JPG                  metadata edited afterwards (Software=Photoshop, ModifyDate
#                                      before DateTimeOriginal, GPS stripped) -> tampering
#   Documents/meeting_notes.txt        normal file
#   Documents/budget_2026.xlsx         actually a JPEG of the "prototype" (extension mismatch)
#   Documents/prototype_design.pdf     DELETED  (recoverable from the FAT directory entry)
#   Documents/handover.txt             DELETED  (mentions the buyer)
#   DCIM/IMG_0417.JPG                  DELETED and its directory entry overwritten -> only carving
#                                      from unallocated space gets it back
set -euo pipefail
EV=/lab/evidence; WORK=/tmp/stage; IMG="$EV/usb_evidence.img"
rm -rf "$WORK"; mkdir -p "$WORK/DCIM" "$WORK/Documents" "$EV"

photo() {  # photo <file> <label> <colour>
  convert -size 1280x960 "gradient:$3-white" -font DejaVu-Sans -gravity center -pointsize 64 -fill black \
    -annotate 0 "$2" -quality 88 "$1"
}

echo "[+] creating photos"
photo "$WORK/DCIM/IMG_0412.JPG" "Beach - Puri"        skyblue
photo "$WORK/DCIM/IMG_0413.JPG" "Temple - Bhubaneswar" orange
photo "$WORK/DCIM/IMG_0414.JPG" "Office whiteboard"    lightgray
photo "$WORK/DCIM/IMG_0415.JPG" "Cafe meeting"         tan
photo "$WORK/DCIM/IMG_0416.JPG" "Edited photo"         pink
photo "$WORK/DCIM/IMG_0417.JPG" "PROTOTYPE v2 - CONFIDENTIAL" red
photo "$WORK/disguised.jpg" "PROTOTYPE v2 - schematic" yellow   # renamed to .xlsx below

exif() { exiftool -q -overwrite_original "$@"; }
exif -Make=Apple -Model="iPhone 14" -Software="17.5.1" -DateTimeOriginal="2026:09:12 07:41:03" \
     -GPSLatitude=19.7983 -GPSLatitudeRef=N -GPSLongitude=85.8249 -GPSLongitudeRef=E "$WORK/DCIM/IMG_0412.JPG"
exif -Make=Apple -Model="iPhone 14" -Software="17.5.1" -DateTimeOriginal="2026:09:13 16:20:44" \
     -GPSLatitude=20.2382 -GPSLatitudeRef=N -GPSLongitude=85.8338 -GPSLongitudeRef=E "$WORK/DCIM/IMG_0413.JPG"
exif -Make=Samsung -Model="SM-S918B" -Software="S918BXXU3" -DateTimeOriginal="2026:10:21 18:05:10" \
     -GPSLatitude=12.9719 -GPSLatitudeRef=N -GPSLongitude=77.5937 -GPSLongitudeRef=E "$WORK/DCIM/IMG_0414.JPG"
exif -Make=Samsung -Model="SM-S918B" -Software="S918BXXU3" -DateTimeOriginal="2026:10:22 13:47:29" \
     -GPSLatitude=12.9352 -GPSLatitudeRef=N -GPSLongitude=77.6245 -GPSLongitudeRef=E \
     -ImageDescription="with R. - final handover" "$WORK/DCIM/IMG_0415.JPG"
exif -Make=Samsung -Model="SM-S918B" -DateTimeOriginal="2026:10:22 14:02:11" \
     -ModifyDate="2026:10:20 09:00:00" -Software="Adobe Photoshop 25.1 (Windows)" "$WORK/DCIM/IMG_0416.JPG"
exif -Make=Samsung -Model="SM-S918B" -DateTimeOriginal="2026:10:21 18:06:55" \
     -GPSLatitude=12.9719 -GPSLatitudeRef=N -GPSLongitude=77.5937 -GPSLongitudeRef=E "$WORK/DCIM/IMG_0417.JPG"
exif -Make=Samsung -Model="SM-S918B" -DateTimeOriginal="2026:10:21 18:07:30" "$WORK/disguised.jpg"
mv "$WORK/disguised.jpg" "$WORK/Documents/budget_2026.xlsx"     # the disguise: JPEG with an Excel name

echo "[+] creating documents"
printf 'Team sync 2026-10-20\n- Q4 roadmap\n- prototype v2 freeze on 25 Oct\n' >"$WORK/Documents/meeting_notes.txt"
printf 'Handover to R. at the cafe, 22 Oct 1:45 PM. Price agreed. Delete this file.\n' >"$WORK/Documents/handover.txt"
python3 - "$WORK/Documents/prototype_design.pdf" <<'PY'
import sys
text = "PROTOTYPE v2 - CONFIDENTIAL - internal design specification"
objs = ["<< /Type /Catalog /Pages 2 0 R >>", "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>"]
s = f"BT /F1 16 Tf 72 720 Td ({text}) Tj ET"
objs += [f"<< /Length {len(s)} >>\nstream\n{s}\nendstream", "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>"]
out = b"%PDF-1.4\n"; offs = []
for i, o in enumerate(objs, 1):
    offs.append(len(out)); out += f"{i} 0 obj\n{o}\nendobj\n".encode()
x = len(out)
out += f"xref\n0 {len(objs)+1}\n0000000000 65535 f \n".encode() + b"".join(f"{o:010d} 00000 n \n".encode() for o in offs)
out += f"trailer\n<< /Size {len(objs)+1} /Root 1 0 R >>\nstartxref\n{x}\n%%EOF\n".encode()
open(sys.argv[1], "wb").write(out)
PY
exif -Author="Rohan Mehta" -Creator="Microsoft Word for Microsoft 365" -Title="Prototype v2 design" \
     -CreateDate="2026:10:19 11:30:00+05:30" "$WORK/Documents/prototype_design.pdf"

echo "[+] building disk image (MBR, one FAT32 partition at 1 MiB)"
rm -f "$IMG"
truncate -s 64M "$IMG"
echo 'label: dos
start=2048, type=c' | sfdisk -q "$IMG"
P="$IMG@@1M"
mformat -i "$P" -F -v USB_16GB -N 2c9a1f07 ::
mmd -i "$P" ::/DCIM ::/Documents
for f in "$WORK"/DCIM/*.JPG; do mcopy -i "$P" -m "$f" ::/DCIM/; done
for f in "$WORK"/Documents/*; do mcopy -i "$P" -m "$f" ::/Documents/; done

echo "[+] simulating the suspect's clean-up"
mdel -i "$P" ::/Documents/prototype_design.pdf ::/Documents/handover.txt ::/DCIM/IMG_0417.JPG
# overwrite IMG_0417's (deleted) directory entry by filling the slot with new files
for i in 1 2 3 4; do printf 'cache %s\n' "$i" >"$WORK/c$i.tmp"; mcopy -i "$P" "$WORK/c$i.tmp" "::/DCIM/THUMB$i.DAT"; done

chmod a-w "$IMG"
echo "[+] hashing"
( cd "$EV" && md5sum usb_evidence.img >usb_evidence.img.md5 && sha256sum usb_evidence.img >usb_evidence.img.sha256 )
cat "$EV"/usb_evidence.img.md5 "$EV"/usb_evidence.img.sha256
{
  echo "# Lab 05 evidence item"
  echo "Item: usb_evidence.img (64 MiB raw image, MBR, FAT32 'USB_16GB')"
  echo "Created (UTC): $(date -u '+%F %T') on $(hostname) by make_evidence_image.sh"
  echo "MD5:    $(cut -d' ' -f1 "$EV/usb_evidence.img.md5")"
  echo "SHA256: $(cut -d' ' -f1 "$EV/usb_evidence.img.sha256")"
  echo "Handling: image is read-only on disk; verify hashes before and after every analysis."
} >"$EV/ACQUISITION.md"
echo "[ok] evidence/usb_evidence.img ready (copy it into the Windows VM for WinHex/Autopsy)"
