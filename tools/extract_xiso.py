"""Extract the game partition (XDVDFS) of a Redump-style Xbox disc image.

usage: python extract_xiso.py <image.iso> <out_dir>
"""
import os
import struct
import sys

SECTOR = 2048
MAGIC = b"MICROSOFT*XBOX*MEDIA"
# game partition offsets: XGD1, XGD2, XGD3, plain xiso
PARTITIONS = (0x18300000, 0xFD90000, 0x2080000, 0)


def find_partition(f):
    for base in PARTITIONS:
        f.seek(base + 32 * SECTOR)
        if f.read(20) == MAGIC:
            return base
    sys.exit("no XDVDFS volume found")


def walk(f, base, sector, size, out, seen):
    f.seek(base + sector * SECTOR)
    table = f.read(size)
    stack = [0]
    while stack:
        off = stack.pop()
        if off + 14 > len(table) or table[off:off + 2] == b"\xff\xff":
            continue
        left, right, start, length, attr, nlen = struct.unpack_from("<HHIIBB", table, off)
        name = table[off + 14:off + 14 + nlen].decode("latin-1")
        if os.sep in name or "/" in name or name in ("", ".", ".."):
            sys.exit(f"unsafe name in image: {name!r}")  # trust boundary: image is untrusted
        if left:
            stack.append(left * 4)
        if right:
            stack.append(right * 4)
        path = os.path.join(out, name)
        if attr & 0x10:
            os.makedirs(path, exist_ok=True)
            if length and (start, length) not in seen:
                seen.add((start, length))
                walk(f, base, start, length, path, seen)
        else:
            f.seek(base + start * SECTOR)
            with open(path, "wb") as o:
                left_bytes = length
                while left_bytes:
                    chunk = f.read(min(left_bytes, 1 << 22))
                    if not chunk:
                        sys.exit(f"truncated image at {path}")
                    o.write(chunk)
                    left_bytes -= len(chunk)


def main(iso, out):
    with open(iso, "rb") as f:
        base = find_partition(f)
        f.seek(base + 32 * SECTOR + 20)
        root_sector, root_size = struct.unpack("<II", f.read(8))
        os.makedirs(out, exist_ok=True)
        walk(f, base, root_sector, root_size, out, set())
    print(f"partition at {base:#x}, extracted to {out}")


if __name__ == "__main__":
    main(*sys.argv[1:3])
