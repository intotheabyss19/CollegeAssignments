#!/usr/bin/env python3
"""Rewrite a classic pcap captured with `tcpdump -i any` (Linux cooked capture, SLL / SLL2)
into Ethernet framing, because BruteShark's packet parser only understands Ethernet-style
link layers. Ethernet captures are copied unchanged.

    sll2eth.py in.pcap out.pcap
"""
import struct
import sys

LINKTYPE_ETHERNET, LINKTYPE_SLL, LINKTYPE_SLL2 = 1, 113, 276


def main(src: str, dst: str) -> None:
    with open(src, "rb") as f:
        data = f.read()
    magic = data[:4]
    endian = {b"\xd4\xc3\xb2\xa1": "<", b"\xa1\xb2\xc3\xd4": ">",
              b"\x4d\x3c\xb2\xa1": "<", b"\xa1\xb2\x3c\x4d": ">"}.get(magic)
    if endian is None:
        sys.exit(f"{src}: not a classic pcap file")
    ghdr = list(struct.unpack(endian + "IHHiIII", data[:24]))
    linktype = ghdr[6]
    if linktype not in (LINKTYPE_SLL, LINKTYPE_SLL2):
        with open(dst, "wb") as f:
            f.write(data)
        return

    ghdr[6] = LINKTYPE_ETHERNET
    out = [struct.pack(endian + "IHHiIII", *ghdr)]
    off, n = 24, 0
    while off + 16 <= len(data):
        ts_s, ts_frac, incl, orig = struct.unpack(endian + "IIII", data[off:off + 16])
        pkt = data[off + 16: off + 16 + incl]
        off += 16 + incl
        if linktype == LINKTYPE_SLL:      # 16-byte header, protocol in last 2 bytes
            proto, addr, payload = pkt[14:16], pkt[6:12], pkt[16:]
        else:                              # SLL2: 20-byte header, protocol in first 2 bytes
            proto, addr, payload = pkt[0:2], pkt[12:18], pkt[20:]
        frame = b"\x00" * 6 + addr.ljust(6, b"\x00")[:6] + proto + payload
        out.append(struct.pack(endian + "IIII", ts_s, ts_frac, len(frame), orig - (len(pkt) - len(frame))))
        out.append(frame)
        n += 1
    with open(dst, "wb") as f:
        f.write(b"".join(out))
    print(f"[sll2eth] {src}: converted {n} cooked-capture packets to Ethernet framing")


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
