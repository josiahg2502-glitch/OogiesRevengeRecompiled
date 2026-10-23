"""Oogie's Revenge .lz archives: the game's own decompressor (sub_31120 in the XBE), rewritten.

A file is a type byte (1 or 2), the unpacked size (u32 LE), then a bit stream read least significant bit first from
32-bit little-endian words. Bit 1: a literal byte (8 bits). Bit 0: a copy of earlier output. The offset has 10 bits
(type 1) or a unary-coded count of bits from BITS (type 2); the length always has a unary-coded count from BITS. The
copy goes from pos - offset - 1, a dword at a time as the game's `rep movsd` does (overlapping copies included).

usage: python oogie_lz.py <file.lz> <out>
"""
import struct
import sys

BITS = (2, 4, 6, 10)  # the XBE's table at 0x260A00


def decompress(data: bytes, start: int = 5) -> bytes:
    kind, size = data[0], struct.unpack_from('<I', data, 1)[0]
    out = bytearray(size + 8)
    words = data[start:] + b'\0' * 8
    word_at = start
    bit = 0
    word = struct.unpack_from('<I', words, 0)[0]
    wi = 0

    def get():
        nonlocal bit, word, wi
        b = (word >> bit) & 1
        bit = (bit + 1) & 31
        if bit == 0:
            wi += 4
            word = struct.unpack_from('<I', words, wi)[0] if wi + 4 <= len(words) else 0
        return b

    def read(n):
        v = 0
        for i in range(n):
            v |= get() << i
        return v

    pos = 0
    while pos < size:
        if get():
            out[pos] = read(8)
            pos += 1
            continue
        if kind == 1:
            offset = read(10)
        else:
            k = 0
            while not get():
                k += 1
            offset = read(BITS[k])
        k = 0
        while not get():
            k += 1
        length = read(BITS[k])
        src, dst = pos - offset - 1, pos
        for _ in range(length // 4):  # rep movsd: each dword read before it is written
            out[dst:dst + 4] = bytes(out[src:src + 4])
            src, dst = src + 4, dst + 4
        for _ in range(length & 3):
            out[dst] = out[src]
            src, dst = src + 1, dst + 1
        pos += length
    return bytes(out[:size])


if __name__ == '__main__':
    raw = open(sys.argv[1], 'rb').read()
    open(sys.argv[2], 'wb').write(decompress(raw))
