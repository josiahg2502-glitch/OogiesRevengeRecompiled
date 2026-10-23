"""Find every function in an XBE by recursive descent.

usage: python -I analyze.py <default.xbe> [functions.tsv]
"""
import collections
import os
import struct
import sys

import capstone
from capstone import x86

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from xbe import Xbe  # noqa: E402

md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True

JCC = {x86.X86_INS_JA, x86.X86_INS_JAE, x86.X86_INS_JB, x86.X86_INS_JBE, x86.X86_INS_JE,
       x86.X86_INS_JNE, x86.X86_INS_JG, x86.X86_INS_JGE, x86.X86_INS_JL, x86.X86_INS_JLE,
       x86.X86_INS_JO, x86.X86_INS_JNO, x86.X86_INS_JS, x86.X86_INS_JNS, x86.X86_INS_JP,
       x86.X86_INS_JNP, x86.X86_INS_JCXZ, x86.X86_INS_JECXZ, x86.X86_INS_LOOP,
       x86.X86_INS_LOOPE, x86.X86_INS_LOOPNE}
# never emitted by the game's compilers; seeing one means we are decoding data
BOGUS = {"aaa", "aas", "daa", "das", "aam", "aad", "arpl", "bound", "into", "les", "lds",
         "lcall", "ljmp", "retf", "insb", "insd", "insw", "outsb", "outsd", "outsw", "salc", "int1", "sysret", "iretd", "hlt", "clts", "str", "sldt", "sgdt",
         "verw", "lsl", "ud1", "pushal", "popal", "enter",
         "wrmsr", "invd", "into", "fstpnce", "prefetchwt1", "vpcmpeqw", "ltr", "fxtract"}
NORETURN_INS = {x86.X86_INS_RET, x86.X86_INS_RETF, x86.X86_INS_JMP, x86.X86_INS_INT3,
                x86.X86_INS_HLT, x86.X86_INS_UD2}


class Program:
    def __init__(self, path):
        self.xbe = Xbe(path)
        self.code = [s for s in self.xbe.sections if s.executable]
        self.thunks = self.xbe.kernel_thunks()
        self.insns = {}             # va -> capstone insn
        self.funcs = {}             # start va -> Function
        self.jump_tables = {}       # jmp va -> [targets]
        self.unresolved = []        # indirect jmps with no table
        self.table_bytes = set()    # jump table storage inside code sections

    def in_code(self, va):
        return any(va in s for s in self.code)

    def decode(self, va):
        i = self.insns.get(va)
        if i is None:
            s = self.xbe.section(va)
            buf = self.xbe.read(va, min(16, s.va + s.vsize - va))
            i = next(md.disasm(buf, va, 1), None)
            self.insns[va] = i
        return i

    def jump_table(self, jmp, prev, start):
        """Targets of `jmp [reg*4 + table]`, sized by the `cmp reg, n` guarding it.

        Without a visible bound, MSVC's layout is used: the table follows its
        function, so entries run while they point between the function start and the table.
        """
        op = jmp.operands[0]
        if op.type != x86.X86_OP_MEM or op.mem.scale != 4 or op.mem.base != 0:
            return None
        table, index, count = op.mem.disp & 0xFFFFFFFF, op.mem.index, None
        byte_table = None
        for p in reversed(prev[-8:]):
            if p.id == x86.X86_INS_MOVZX and p.operands[0].reg == index \
                    and p.operands[1].type == x86.X86_OP_MEM and p.operands[1].size == 1:
                m = p.operands[1].mem
                byte_table, index = m.disp & 0xFFFFFFFF, m.index or m.base
            elif p.id == x86.X86_INS_AND and p.operands[0].type == x86.X86_OP_REG \
                    and p.operands[1].type == x86.X86_OP_IMM and same_reg(p.operands[0].reg, index) \
                    and 0 <= p.operands[1].imm < 256:
                count = p.operands[1].imm + 1  # `and edx, 3`: hand-written memcpy style
                break
            elif p.id == x86.X86_INS_CMP and p.operands[0].type == x86.X86_OP_REG \
                    and p.operands[1].type == x86.X86_OP_IMM \
                    and same_reg(p.operands[0].reg, index):
                count = p.operands[1].imm + 1
                break
        if count is None:
            targets = []
            if byte_table is None:
                while start <= (t := self.xbe.u32(table + 4 * len(targets))) < table:
                    targets.append(t)
            if not targets:
                # no recognizable bound (or a negative index): take the run of nearby code
                # pointers around the table; extra targets only cost unused labels
                near = lambda t: abs(t - jmp.address) < 0x10000 and self.in_code(t)
                lo = table
                while table - lo < 1024 and near(self.xbe.u32(lo - 4)):
                    lo -= 4
                hi = table
                while hi - table < 1024 and near(self.xbe.u32(hi)):
                    hi += 4
                targets = [self.xbe.u32(a) for a in range(lo, hi, 4)]
                self.table_bytes.update(range(lo, hi))
            if not targets:
                return None
        else:
            if byte_table is not None:
                self.table_bytes.update(range(byte_table, byte_table + count))
                count = max(self.xbe.read(byte_table, count)) + 1
            targets = [self.xbe.u32(table + 4 * k) for k in range(count)]
            if not all(self.in_code(t) for t in targets):
                return None
        self.table_bytes.update(range(table, table + 4 * len(targets)))
        return targets

    def explore(self, start):
        """Blocks reachable from start without crossing a call; returns (insn vas, callees)."""
        seen, callees, work = set(), set(), [start]
        while work:
            va = work.pop()
            prev = []
            while va not in seen and self.in_code(va):
                if va != start and va in self.funcs:
                    break  # fell into another function: treat as tail call
                i = self.decode(va)
                if i is None:
                    self.bad = True
                    break
                if i.mnemonic in BOGUS or bogus_operands(i):
                    self.bad = True
                seen.add(va)
                prev.append(i)
                nxt = va + i.size
                if i.id == x86.X86_INS_CALL:
                    t = self.direct_target(i)
                    if t is not None:
                        callees.add(t)
                elif i.id in JCC:
                    work.append(self.direct_target(i))
                elif i.id == x86.X86_INS_JMP:
                    t = self.direct_target(i)
                    if t is not None:
                        if t in self.funcs:
                            callees.add(t)  # tail call
                        else:
                            work.append(t)
                    else:
                        tbl = self.jump_table(i, prev, start)
                        if tbl is None:
                            self.unresolved.append(va)
                        else:
                            self.jump_tables[va] = tbl
                            work.extend(tbl)
                if i.id in NORETURN_INS:
                    break
                va = nxt
        return seen, callees

    @staticmethod
    def direct_target(i):
        op = i.operands[0]
        return op.imm & 0xFFFFFFFF if op.type == x86.X86_OP_IMM else None

    def code_immediates(self, owner):
        out = set()
        for v in owner:
            for op in self.insns[v].operands:
                if op.type == x86.X86_OP_IMM and self.in_code(op.imm & 0xFFFFFFFF):
                    out.add(op.imm & 0xFFFFFFFF)
        return out

    def data_pointers(self):
        """Aligned words in data sections that point at code (vtables, callbacks)."""
        out = set()
        for s in self.xbe.sections:
            if s.executable:
                continue
            raw = self.xbe.read(s.va, s.raw_size)
            for o in range(0, len(raw) - 3, 4):
                v, = struct.unpack_from("<I", raw, o)
                if self.in_code(v):
                    out.add(v)
        return out

    def run(self, known=()):
        """known: function starts named by XbSymbolDatabase, trusted like the entry point."""
        owner = {}
        self.rejected = []

        def add(seeds, trusted, inside=None):
            # (address, called): a call target is a function even inside another one's body
            # (MSVC __finally helpers are called 3 bytes into their block)
            queue = [(s, trusted if inside is None else inside) for s in seeds]
            while queue:
                f, called = queue.pop()
                if f in self.funcs or (f in owner and not called) or not self.in_code(f):
                    continue
                self.funcs[f] = None
                self.bad = False
                nj = len(self.jump_tables)
                body, callees = self.explore(f)
                if not body or (self.bad and not trusted):
                    del self.funcs[f]
                    for k in list(self.jump_tables)[nj:]:
                        del self.jump_tables[k]
                    self.rejected.append(f)
                    continue
                if self.bad:
                    self.suspect.append(f)
                self.funcs[f] = body
                for v in body:
                    owner.setdefault(v, f)
                queue.extend((t, True) for t in callees)

        self.suspect = []
        add([self.xbe.entry, *known], True)
        # data pointers and code immediates (callbacks, thread routines) start new functions
        add(sorted(self.data_pointers(), reverse=True), False, inside=True)  # switch tables live in .text, not here
        add(sorted(self.code_immediates(owner), reverse=True), False, inside=True)
        # code that follows padding but nothing points at (reached via computed calls)
        while True:
            n = len(self.funcs)
            add(self.gap_seeds(owner), False)
            if len(self.funcs) == n:
                return owner

    def gap_seeds(self, owner):
        covered = set(self.table_bytes)
        for v in owner:
            covered.update(range(v, v + self.insns[v].size))
        tried = getattr(self, "_tried", set())
        self._tried = tried
        seeds = []
        for s in self.code:
            va, end = s.va, s.va + s.raw_size
            while va < end:
                if va in covered or self.xbe.read(va, 1)[0] in (0x00, 0x90, 0xCC):
                    va += 1
                    continue
                if va not in tried:
                    tried.add(va)
                    seeds.append(va)
                while va < end and va not in covered:
                    va += 1
        return reversed(seeds)


SEGMENT_REGS = {x86.X86_REG_CS, x86.X86_REG_DS, x86.X86_REG_ES, x86.X86_REG_SS,
                x86.X86_REG_FS, x86.X86_REG_GS}
ADDR16 = {x86.X86_REG_BX, x86.X86_REG_BP, x86.X86_REG_SI, x86.X86_REG_DI}


def bogus_operands(i):
    """Segment register moves, 16-bit addressing or odd segment overrides: data, not code."""
    for op in i.operands:
        if op.type == x86.X86_OP_REG and op.reg in SEGMENT_REGS:
            return True
        if op.type == x86.X86_OP_MEM and (op.mem.base in ADDR16 or op.mem.index in ADDR16
                                          or op.mem.segment in (x86.X86_REG_CS, x86.X86_REG_GS)):
            return True
    return False


def same_reg(a, b):
    groups = [(x86.X86_REG_EAX, x86.X86_REG_AX, x86.X86_REG_AL),
              (x86.X86_REG_ECX, x86.X86_REG_CX, x86.X86_REG_CL),
              (x86.X86_REG_EDX, x86.X86_REG_DX, x86.X86_REG_DL),
              (x86.X86_REG_EBX, x86.X86_REG_BX, x86.X86_REG_BL),
              (x86.X86_REG_ESI, x86.X86_REG_SI), (x86.X86_REG_EDI, x86.X86_REG_DI),
              (x86.X86_REG_EBP, x86.X86_REG_BP)]
    return a == b or any(a in g and b in g for g in groups)


def main(path, out=None):
    p = Program(path)
    owner = p.run()
    hist = collections.Counter(p.insns[v].mnemonic for v in owner)
    code_bytes = sum(s.vsize for s in p.code)
    covered = sum(p.insns[v].size for v in owner)
    print(f"entry {p.xbe.entry:#x}, kernel imports {len(p.thunks)}")
    print(f"functions {len(p.funcs)}, instructions {len(owner)}, "
          f"coverage {covered}/{code_bytes} bytes ({100 * covered / code_bytes:.1f}%)")
    print(f"jump tables {len(p.jump_tables)}, unresolved indirect jmps {len(p.unresolved)}")
    print(f"pointer seeds rejected {len(p.rejected)}, suspect functions {len(p.suspect)}: "
          + " ".join(f"{f:#x}" for f in p.suspect[:20]))
    print("mnemonics:", len(hist))
    for m, n in hist.most_common():
        print(f"  {m:12} {n}")
    if out:
        with open(out, "w") as f:
            for s in sorted(p.funcs):
                body = p.funcs[s]
                f.write(f"{s:08x}\t{len(body)}\n")


if __name__ == "__main__":
    main(*sys.argv[1:])
