"""Build-time generator for the lab's files (runs inside the image, nothing touches the Mac).

Creates real file formats so the analysis tools have something to identify and carve:
  /srv/www/img/logo.png        PNG image        -> NetworkMiner "Images" tab, Zeek files.log (image/png)
  /srv/www/files/report.pdf    PDF document     -> NetworkMiner "Files", Zeek files.log (application/pdf)
  /srv/www/.htpasswd           Basic-auth user for /admin/
  /opt/lab/customers.csv       "sensitive" data the attacker steals over FTP
  /srv/c2/payload.exe          harmless file with a Windows PE ("MZ") header -> "malware download"
  /srv/c2/beacon               what the C2 answers to a beacon
  /srv/c2/update.txt           EICAR anti-virus test string (built from two halves so the
                               source file on the Mac never contains the full string)
"""
import os, struct, zlib

def write(path, data, mode="wb"):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, mode) as f:
        f.write(data)

def png(w, h):
    rows = b""
    for y in range(h):
        rows += b"\x00" + b"".join(bytes((20 + x % 200, 60 + y * 2 % 150, 160)) for x in range(w))
    def chunk(t, d):
        return struct.pack(">I", len(d)) + t + d + struct.pack(">I", zlib.crc32(t + d) & 0xFFFFFFFF)
    return (b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 2, 0, 0, 0))
            + chunk(b"IDAT", zlib.compress(rows)) + chunk(b"IEND", b""))

def pdf(text):
    objs = [b"<< /Type /Catalog /Pages 2 0 R >>",
            b"<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
            b"<< /Type /Page /Parent 2 0 R /MediaBox [0 0 595 842] /Contents 4 0 R "
            b"/Resources << /Font << /F1 5 0 R >> >> >>",
            None,
            b"<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>"]
    stream = ("BT /F1 18 Tf 72 760 Td (%s) Tj ET" % text).encode()
    objs[3] = b"<< /Length %d >>\nstream\n" % len(stream) + stream + b"\nendstream"
    out, offs = b"%PDF-1.4\n", []
    for i, o in enumerate(objs, 1):
        offs.append(len(out))
        out += b"%d 0 obj\n" % i + o + b"\nendobj\n"
    xref = len(out)
    out += b"xref\n0 %d\n0000000000 65535 f \n" % (len(objs) + 1)
    out += b"".join(b"%010d 00000 n \n" % o for o in offs)
    out += b"trailer\n<< /Size %d /Root 1 0 R >>\nstartxref\n%d\n%%%%EOF\n" % (len(objs) + 1, xref)
    return out

write("/srv/www/img/logo.png", png(240, 80))
write("/srv/www/files/report.pdf", pdf("Corp Q3 2026 financial report - INTERNAL"))
write("/srv/www/.htpasswd", "staff:{PLAIN}letmein\n", "w")
write("/opt/lab/customers.csv",
      "id,name,email,card_last4\n" + "".join(
          f"{i},Customer {i},customer{i}@example.com,{1000 + i * 37 % 9000}\n" for i in range(1, 51)), "w")

# PE-looking payload: DOS header "MZ", e_lfanew -> "PE\0\0", the classic DOS stub text. Not runnable.
stub = b"This program cannot be run in DOS mode.\r\r\n$"
pe = bytearray(512)
pe[0:2] = b"MZ"
pe[0x3C:0x40] = struct.pack("<I", 0x80)
pe[0x4E:0x4E + len(stub)] = stub
pe[0x80:0x84] = b"PE\x00\x00"
pe[0x100:0x100 + 40] = b"CYFOR LAB09 harmless training payload\x00\x00\x00"
write("/srv/c2/payload.exe", bytes(pe))
write("/srv/c2/beacon", "sleep 5\n", "w")
write("/srv/c2/update.txt", "X5O!P%@AP[4\\PZX54(P^)7CC)7}$" + "EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*", "w")
