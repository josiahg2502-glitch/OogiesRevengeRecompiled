"""Minimal reader for retail Xbox executables (.xbe)."""
import struct

ENTRY_KEY_RETAIL = 0xA8FC57AB
THUNK_KEY_RETAIL = 0x5B6D40B6
SEC_EXECUTABLE = 0x4
# linkers set the executable flag on data too; DOLBY is audio DSP microcode
DATA_SECTIONS = {".rdata", ".data", "DOLBY", "BINKDATA"}


class Section:
    def __init__(self, name, flags, va, vsize, raw_off, raw_size):
        self.name, self.flags, self.va, self.vsize = name, flags, va, vsize
        self.raw_off, self.raw_size = raw_off, raw_size

    @property
    def executable(self):
        return bool(self.flags & SEC_EXECUTABLE) and self.name not in DATA_SECTIONS

    def __contains__(self, va):
        return self.va <= va < self.va + self.vsize


class Xbe:
    def __init__(self, path):
        d = self.data = open(path, "rb").read()
        if d[:4] != b"XBEH":
            raise ValueError("not an XBE")
        self.base, = struct.unpack_from("<I", d, 0x104)
        nsec, sec_va = struct.unpack_from("<II", d, 0x11C)
        self.entry = struct.unpack_from("<I", d, 0x128)[0] ^ ENTRY_KEY_RETAIL
        self.thunk_va = struct.unpack_from("<I", d, 0x158)[0] ^ THUNK_KEY_RETAIL
        self.sections = []
        for i in range(nsec):
            o = self.hdr_off(sec_va) + i * 56
            flags, va, vsize, raw_off, raw_size, name_va = struct.unpack_from("<6I", d, o)
            n = self.hdr_off(name_va)
            name = d[n:d.index(b"\0", n)].decode("latin-1")
            self.sections.append(Section(name, flags, va, vsize, raw_off, raw_size))
        if not any(self.entry in s for s in self.sections if s.executable):
            raise ValueError(f"entry {self.entry:#x} not in code; debug XBE?")

    def hdr_off(self, va):
        return va - self.base

    def section(self, va):
        for s in self.sections:
            if va in s:
                return s
        return None

    def read(self, va, n):
        """Bytes at a virtual address; zero fill past the raw data (bss)."""
        s = self.section(va)
        if s is None:
            if self.base <= va and va + n <= self.base + len(self.data):
                o = va - self.base
                return self.data[o:o + n]  # header area is mapped too
            raise KeyError(f"{va:#x} unmapped")
        o = va - s.va
        raw = self.data[s.raw_off + o:s.raw_off + min(o + n, s.raw_size)] if o < s.raw_size else b""
        return raw + b"\0" * (n - len(raw))

    def u32(self, va):
        return struct.unpack("<I", self.read(va, 4))[0]

    def kernel_thunks(self):
        """{thunk slot va: kernel export ordinal}"""
        out, va = {}, self.thunk_va
        while (v := self.u32(va)) != 0:
            out[va] = v & 0x7FFFFFFF
            va += 4
        return out
