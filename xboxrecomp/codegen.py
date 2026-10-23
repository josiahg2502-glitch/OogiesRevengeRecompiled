"""Translate every discovered XBE function to C++.

usage: python codegen.py <default.xbe> <out_dir> [shards]
"""
import collections
import os
import sys

from capstone import x86

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze  # noqa: E402

OP_REG, OP_IMM, OP_MEM = x86.X86_OP_REG, x86.X86_OP_IMM, x86.X86_OP_MEM
T = {1: "u8", 2: "u16", 4: "u32", 8: "u64"}
S = {1: "s8", 2: "s16", 4: "s32", 8: "s64"}
REG32 = ["eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"]
REG16 = {"ax": "eax", "cx": "ecx", "dx": "edx", "bx": "ebx", "sp": "esp", "bp": "ebp",
         "si": "esi", "di": "edi"}
REG8L = {"al": "eax", "cl": "ecx", "dl": "edx", "bl": "ebx"}
REG8H = {"ah": "eax", "ch": "ecx", "dh": "edx", "bh": "ebx"}
COND = {
    "o": "f.of", "no": "!f.of", "b": "f.cf", "c": "f.cf", "nae": "f.cf", "ae": "!f.cf",
    "nb": "!f.cf", "nc": "!f.cf", "e": "f.zf", "z": "f.zf", "ne": "!f.zf", "nz": "!f.zf",
    "be": "(f.cf | f.zf)", "na": "(f.cf | f.zf)", "a": "!(f.cf | f.zf)", "nbe": "!(f.cf | f.zf)",
    "s": "f.sf", "ns": "!f.sf", "p": "f.pf", "pe": "f.pf", "np": "!f.pf", "po": "!f.pf",
    "l": "(f.sf != f.of)", "nge": "(f.sf != f.of)", "ge": "f.sf == f.of", "nl": "f.sf == f.of",
    "le": "(f.zf | (f.sf != f.of))", "ng": "(f.zf | (f.sf != f.of))",
    "g": "(!f.zf && f.sf == f.of)", "nle": "(!f.zf && f.sf == f.of)",
    "u": "f.pf", "nu": "!f.pf",
}
NOPS = {"cli", "sti", "nop", "wait", "fnclex", "emms", "femms", "sfence", "prefetchnta", "prefetchw",
        "prefetcht0", "prefetcht1", "prefetcht2", "wbinvd", "invd", "ffree", "fwait"}
FCONST = {"fld1": "1.0", "fldz": "0.0", "fldpi": "3.14159265358979323846",
          "fldl2e": "1.44269504088896340736", "fldln2": "0.693147180559945309417",
          "fldlg2": "0.301029995663981195214", "fldl2t": "3.32192809488736234787"}
FARITH = {"fadd": "{a} + {b}", "fsub": "{a} - {b}", "fsubr": "{b} - {a}", "fmul": "{a} * {b}",
          "fdiv": "{a} / {b}", "fdivr": "{b} / {a}"}
SSE_SCALAR = {"addss": "{a} + {b}", "subss": "{a} - {b}", "mulss": "{a} * {b}", "divss": "{a} / {b}",
              "minss": "({a} < {b} ? {a} : {b})", "maxss": "({a} > {b} ? {a} : {b})",
              "sqrtss": "std::sqrt({b})", "rcpss": "1.0f / {b}", "rsqrtss": "1.0f / std::sqrt({b})"}
SSE_PACKED_F = {"addps": "{a} + {b}", "subps": "{a} - {b}", "mulps": "{a} * {b}", "divps": "{a} / {b}",
                "minps": "({a} < {b} ? {a} : {b})", "maxps": "({a} > {b} ? {a} : {b})",
                "sqrtps": "std::sqrt({b})", "rcpps": "1.0f / {b}", "rsqrtps": "1.0f / std::sqrt({b})"}
SSE_PACKED_U = {"xorps": "{a} ^ {b}", "orps": "{a} | {b}", "andps": "{a} & {b}", "andnps": "~{a} & {b}"}
# MMX lane ops: (lane type, lanes, expression over x, y)
MMX = {
    "paddb": ("u8", 8, "u8(x + y)"), "paddw": ("u16", 4, "u16(x + y)"), "paddd": ("u32", 2, "x + y"),
    "psubb": ("u8", 8, "u8(x - y)"), "psubw": ("u16", 4, "u16(x - y)"), "psubd": ("u32", 2, "x - y"),
    "paddsw": ("s16", 4, "sat<s16>(x + y)"), "psubsw": ("s16", 4, "sat<s16>(x - y)"),
    "paddusw": ("u16", 4, "sat<u16>(s32(x) + y)"), "psubusw": ("u16", 4, "sat<u16>(s32(x) - y)"),
    "paddusb": ("u8", 8, "sat<u8>(s32(x) + y)"), "psubusb": ("u8", 8, "sat<u8>(s32(x) - y)"),
    "paddsb": ("s8", 8, "sat<s8>(x + y)"), "psubsb": ("s8", 8, "sat<s8>(x - y)"),
    "pmullw": ("s16", 4, "s16(s32(x) * y)"), "pmulhw": ("s16", 4, "s16((s32(x) * y) >> 16)"),
    "pcmpeqb": ("u8", 8, "x == y ? 0xFF : 0"), "pcmpeqw": ("u16", 4, "x == y ? 0xFFFF : 0"),
    "pcmpeqd": ("u32", 2, "x == y ? ~0u : 0"), "pcmpgtw": ("s16", 4, "x > y ? -1 : 0"),
    "pcmpgtb": ("s8", 8, "x > y ? -1 : 0"), "pcmpgtd": ("s32", 2, "x > y ? -1 : 0"),
    "pavgb": ("u8", 8, "u8((x + y + 1) >> 1)"), "pavgw": ("u16", 4, "u16((x + y + 1) >> 1)"),
    "pminub": ("u8", 8, "x < y ? x : y"), "pmaxub": ("u8", 8, "x > y ? x : y"),
    "pminsw": ("s16", 4, "x < y ? x : y"), "pmaxsw": ("s16", 4, "x > y ? x : y"),
}
MMX_Q = {"por": "a | b", "pxor": "a ^ b", "pand": "a & b", "pandn": "~a & b"}
MMX_SHIFT = {"psllw": ("u16", 4, "<<"), "psrlw": ("u16", 4, ">>"), "psraw": ("s16", 4, ">>"),
             "pslld": ("u32", 2, "<<"), "psrld": ("u32", 2, ">>"), "psrad": ("s32", 2, ">>"),
             "psllq": ("u64", 1, "<<"), "psrlq": ("u64", 1, ">>")}
UNPACK = {"punpcklbw": ("u8", 8, False), "punpcklwd": ("u16", 4, False), "punpckldq": ("u32", 2, False),
          "punpckhbw": ("u8", 8, True), "punpckhwd": ("u16", 4, True), "punpckhdq": ("u32", 2, True)}


class Unsupported(Exception):
    pass


class FuncGen:
    def __init__(self, prog, start, body):
        self.p, self.start, self.body = prog, start, body
        self.labels = set()
        self.xdk = None  # (hook index, symbol) for functions XbSymbolDatabase named

    # ---- operands ----
    def ea(self, op):
        m = op.mem
        parts = []
        if m.base:
            parts.append("c." + self.reg32(m.base))
        if m.index:
            parts.append(f"c.{self.reg32(m.index)}" + (f" * {m.scale}" if m.scale != 1 else ""))
        if m.disp or not parts:
            parts.append(f"0x{m.disp & 0xFFFFFFFF:X}u")
        e = " + ".join(parts)
        if m.segment == x86.X86_REG_FS:
            e = "c.fs_base + " + e
        elif m.segment not in (0, x86.X86_REG_DS, x86.X86_REG_SS, x86.X86_REG_ES):
            raise Unsupported("segment")
        return f"u32({e})"

    def reg32(self, r):
        n = self.name(r)
        if n not in REG32:
            raise Unsupported("address register " + n)
        return n

    def name(self, r):
        return self.insn.reg_name(r)

    def rd(self, op, size=None):
        size = size or op.size
        if op.type == OP_IMM:
            return f"{T[size]}(0x{op.imm & ((1 << 8 * size) - 1):X}u)"
        if op.type == OP_MEM:
            return f"ld<{T[size]}>({self.ea(op)})"
        n = self.name(op.reg)
        if n in REG32:
            return "c." + n
        if n in REG16:
            return f"u16(c.{REG16[n]})"
        if n in REG8L:
            return f"u8(c.{REG8L[n]})"
        if n in REG8H:
            return f"u8(c.{REG8H[n]} >> 8)"
        if n.startswith("mm"):
            return f"c.mm[{n[2]}].q"
        raise Unsupported("register " + n)

    def wr(self, op, v):
        if op.type == OP_MEM:
            return f"st<{T[op.size]}>({self.ea(op)}, {T[op.size]}({v}));"
        n = self.name(op.reg)
        if n in REG32:
            return f"c.{n} = u32({v});"
        if n in REG16:
            return f"set16(c.{REG16[n]}, u16({v}));"
        if n in REG8L:
            return f"set8l(c.{REG8L[n]}, u8({v}));"
        if n in REG8H:
            return f"set8h(c.{REG8H[n]}, u8({v}));"
        if n.startswith("mm"):
            return f"c.mm[{n[2]}].q = u64({v});"
        raise Unsupported("register " + n)

    def xmm(self, op):
        n = self.name(op.reg)
        if not n.startswith("xmm"):
            raise Unsupported("expected xmm")
        return f"c.xmm[{n[3]}]"

    def xmm_src(self, op):
        """A full 128-bit source as an Xmm value."""
        if op.type == OP_REG:
            return self.xmm(op)
        return f"ld<Xmm>({self.ea(op)})"

    def fscalar(self, op):
        return f"{self.xmm(op)}.f[0]" if op.type == OP_REG else f"ldf({self.ea(op)})"

    def sti(self, op):
        n = self.name(op.reg)
        if not n.startswith("st"):
            raise Unsupported("expected st(i)")
        return int(n[3]) if "(" in n else 0

    def mm_src(self, op):
        if op.type == OP_REG:
            return f"c.mm[{self.name(op.reg)[2]}].q"
        return f"ld<u64>({self.ea(op)})"

    # ---- control flow ----
    def goto(self, t):
        if t in self.body:
            self.labels.add(t)
            if t <= self.insn.address:  # loop back-edge: let other threads in
                return f"{{ SAFEPOINT(0x{self.insn.address:X}u) goto L_{t:X}; }}"
            return f"goto L_{t:X};"
        if t in self.p.funcs:
            return f"{{ sub_{t:X}(c); return; }}"
        return f"{{ dispatch(c, 0x{t:X}u); return; }}"

    def call(self, i):
        nxt = i.address + i.size
        op = i.operands[0]
        if op.type == OP_IMM:
            t = op.imm & 0xFFFFFFFF
            if t == nxt:
                return f"push32(c, 0x{nxt:X}u);"  # call $+5 / pop: reads its own address
            fn = f"sub_{t:X}(c);" if t in self.p.funcs else f"dispatch(c, 0x{t:X}u);"
            return f"push32(c, 0x{nxt:X}u); {fn}"
        return f"{{ u32 t = {self.rd(op, 4)}; push32(c, 0x{nxt:X}u); dispatch(c, t); }}"

    # ---- one instruction ----
    def insn_code(self, i):
        self.insn = i
        m = i.mnemonic
        for pre in ("lock ", "notrack "):
            if m.startswith(pre):
                m = m[len(pre):]
        ops = i.operands
        pc = f"0x{i.address:X}u"

        if m in NOPS:
            return ""
        if m == "mov" or m == "movntq":
            return self.wr(ops[0], self.rd(ops[1], ops[0].size))
        if m == "push":
            return f"{{ u32 v = {self.rd(ops[0], 4) if ops[0].type != OP_IMM else f'0x{ops[0].imm & 0xFFFFFFFF:X}u'}; push32(c, v); }}"
        if m == "pop":
            return f"{{ u32 v = pop32(c); {self.wr(ops[0], 'v')} }}"
        if m == "lea":
            return self.wr(ops[0], self.ea(ops[1]).replace("c.fs_base + ", ""))
        if m in ("add", "sub", "cmp", "and", "or", "xor", "test", "adc", "sbb"):
            sz = ops[0].size
            a, b = self.rd(ops[0]), self.rd(ops[1], sz)
            t = T[sz]
            if m == "add":
                return self.wr(ops[0], f"add_f<{t}>(f, {a}, {b})")
            if m == "adc":
                return f"{{ u8 k = f.cf; {self.wr(ops[0], f'add_f<{t}>(f, {a}, {b}, k)')} }}"
            if m == "sub":
                return self.wr(ops[0], f"sub_f<{t}>(f, {a}, {b})")
            if m == "sbb":
                return f"{{ u8 k = f.cf; {self.wr(ops[0], f'sub_f<{t}>(f, {a}, {b}, k)')} }}"
            if m == "cmp":
                return f"sub_f<{t}>(f, {a}, {b});"
            if m == "test":
                return f"logic_f<{t}>(f, {t}({a} & {b}));"
            sym = {"and": "&", "or": "|", "xor": "^"}[m]
            if m == "xor" and ops[0].type == OP_REG and ops[1].type == OP_REG and ops[0].reg == ops[1].reg:
                return self.wr(ops[0], f"logic_f<{t}>(f, {t}(0))")
            return self.wr(ops[0], f"logic_f<{t}>(f, {t}({a} {sym} {b}))")
        if m in ("inc", "dec", "neg"):
            t = T[ops[0].size]
            return self.wr(ops[0], f"{m}_f<{t}>(f, {self.rd(ops[0])})")
        if m == "not":
            return self.wr(ops[0], f"~{self.rd(ops[0])}")
        if m in ("movzx", "movsx"):
            src = self.rd(ops[1])
            if m == "movsx":
                src = f"{S[ops[1].size]}({src})"
            return self.wr(ops[0], f"{T[ops[0].size]}({src})" if m == "movzx" else f"{S[ops[0].size]}({src})")
        if m in ("shl", "sal", "shr", "sar", "rol", "ror", "rcl", "rcr"):
            t = T[ops[0].size]
            n = "1" if len(ops) == 1 else (self.rd(ops[1], 1) if ops[1].type != OP_IMM else str(ops[1].imm & 0xFF))
            fn = "shl" if m == "sal" else m
            return self.wr(ops[0], f"{fn}_f<{t}>(f, {self.rd(ops[0])}, u8({n}))")
        if m in ("shld", "shrd"):
            if ops[0].size != 4:
                raise Unsupported("16-bit double shift")
            n = self.rd(ops[2], 1) if ops[2].type != OP_IMM else str(ops[2].imm & 0xFF)
            return self.wr(ops[0], f"{m}_f(f, {self.rd(ops[0])}, {self.rd(ops[1])}, u8({n}))")
        if m == "imul" and not (len(ops) == 1 and ops[0].size == 1):
            if len(ops) == 1:
                if ops[0].size != 4:
                    raise Unsupported("narrow one-operand imul")
                return f"imul32(c, f, {self.rd(ops[0])});"
            t = T[ops[0].size]
            a, b = (ops[0], ops[1]) if len(ops) == 2 else (ops[1], ops[2])
            return self.wr(ops[0], f"imul_f<{t}>(f, {self.rd(a, ops[0].size)}, {self.rd(b, ops[0].size)})")
        if m == "imul" and len(ops) == 1 and ops[0].size == 1:
            return f"{{ s16 r = s16(s8(c.eax)) * s8({self.rd(ops[0])}); set16(c.eax, u16(r)); f.cf = f.of = r != s8(r); }}"
        if m == "mul":
            if ops[0].size == 4:
                return f"mul32(c, f, {self.rd(ops[0])});"
            if ops[0].size == 1:
                return f"mul8(c, f, {self.rd(ops[0])});"
            raise Unsupported("mul16")
        if m in ("div", "idiv"):
            sz = ops[0].size
            fn = {("div", 4): "div32", ("idiv", 4): "idiv32", ("div", 2): "div16",
                  ("div", 1): "div8", ("idiv", 1): "idiv8"}.get((m, sz))
            if not fn:
                raise Unsupported(m + str(sz))
            return f"{fn}(c, {self.rd(ops[0])}, {pc});"
        if m == "xlatb":
            return "set8l(c.eax, ld<u8>(u32(c.ebx + u8(c.eax))));"
        if m == "cdq":
            return "c.edx = u32(s32(c.eax) >> 31);"
        if m == "cwde":
            return "c.eax = u32(s32(s16(c.eax)));"
        if m == "cbw":
            return "set16(c.eax, u16(s16(s8(c.eax))));"
        if m == "cwd":
            return "set16(c.edx, u16(s16(c.eax) >> 15));"
        if m == "xchg":
            return f"{{ auto a = {self.rd(ops[0])}; auto b = {self.rd(ops[1])}; {self.wr(ops[0], 'b')} {self.wr(ops[1], 'a')} }}"
        if m == "xadd":
            t = T[ops[0].size]
            return f"{{ auto a = {self.rd(ops[0])}; auto b = {self.rd(ops[1])}; {self.wr(ops[1], 'a')} {self.wr(ops[0], f'add_f<{t}>(f, a, b)')} }}"
        if m == "cmpxchg":
            t = T[ops[0].size]
            acc = {1: "u8(c.eax)", 2: "u16(c.eax)", 4: "c.eax"}[ops[0].size]
            accw = {1: "set8l(c.eax, d);", 2: "set16(c.eax, d);", 4: "c.eax = d;"}[ops[0].size]
            return (f"{{ {t} d = {self.rd(ops[0])}; sub_f<{t}>(f, {acc}, d); "
                    f"if (f.zf) {{ {self.wr(ops[0], self.rd(ops[1]))} }} else {{ {accw} }} }}")
        if m == "bsf":
            return self.wr(ops[0], f"bsf_f(f, {self.rd(ops[1])}, {self.rd(ops[0])})")
        if m == "bsr":
            return self.wr(ops[0], f"({self.rd(ops[1])} ? (f.zf = 0, 31 - __builtin_clz({self.rd(ops[1])})) : (f.zf = 1, {self.rd(ops[0])}))")
        if m in ("bt", "btc", "bts", "btr"):
            bits = ops[0].size * 8
            n = f"({self.rd(ops[1], ops[0].size)} & {bits - 1})"
            code = f"f.cf = ({self.rd(ops[0])} >> {n}) & 1;"
            if m != "bt":
                o = {"btc": "^", "bts": "|", "btr": "& ~"}[m]
                code += " " + self.wr(ops[0], f"{self.rd(ops[0])} {o} ({T[ops[0].size]}(1) << {n})")
            return f"{{ {code} }}"
        if m.startswith("set"):
            return self.wr(ops[0], f"{COND[m[3:]]} ? 1 : 0")
        if m.startswith("cmov"):
            return f"if ({COND[m[4:]]}) {{ {self.wr(ops[0], self.rd(ops[1]))} }}"
        if m == "lahf":
            return "set8h(c.eax, get_flags8(f));"
        if m == "sahf":
            return "set_flags8(f, u8(c.eax >> 8));"
        if m == "pushfd":
            return "push32(c, get_eflags(c, f));"
        if m == "popfd":
            return "set_eflags(c, f, pop32(c));"
        if m in ("clc", "stc", "cmc"):
            return {"clc": "f.cf = 0;", "stc": "f.cf = 1;", "cmc": "f.cf ^= 1;"}[m]
        if m in ("cld", "std"):
            return f"c.df = {int(m == 'std')};"
        if m == "leave":
            return "c.esp = c.ebp; c.ebp = pop32(c);"
        if m == "enter":
            if ops[1].imm != 0:
                raise Unsupported("nested enter")
            return f"push32(c, c.ebp); c.ebp = c.esp; c.esp -= {ops[0].imm}u;"
        if m in ("in", "out"):  # port I/O (the XDK pokes a few hardware registers)
            port, data = (ops[1], ops[0]) if m == "in" else (ops[0], ops[1])
            p = f"0x{port.imm & 0xFFFF:X}u" if port.type == OP_IMM else "u16(c.edx)"
            if m == "out":
                return f"guest_out({p}, {self.rd(data)}, {data.size});"
            return self.wr(data, f"guest_in({p}, {data.size})")
        if m == "cpuid":
            return "guest_cpuid(c);"
        if m == "rdtsc":
            return "guest_rdtsc(c);"
        if m in ("int", "int3"):
            vec = ops[0].imm if ops else 3
            return f"guest_int(c, {vec}, {pc});"

        # string instructions
        sm = m.split()
        if sm[-1][:-1] in ("movs", "stos", "lods", "cmps", "scas") and sm[-1][-1] in "bwd":
            return self.string_op(sm)

        # control flow
        if m == "call":
            return self.call(i)
        if m == "ret":
            n = 4 + (ops[0].imm if ops else 0)
            return f"c.esp += {n}u; return;"
        if m == "jmp":
            op = ops[0]
            if op.type == OP_IMM:
                return self.goto(op.imm & 0xFFFFFFFF)
            tbl = self.p.jump_tables.get(i.address)
            if tbl:
                cases = " ".join(f"case 0x{t:X}u: {self.goto(t)}" for t in sorted(set(tbl)))
                return f"switch (u32 t = {self.rd(op, 4)}) {{ {cases} default: dispatch(c, t); return; }}"
            return f"{{ u32 t = {self.rd(op, 4)}; dispatch(c, t); return; }}"
        if m in ("jecxz", "jcxz"):
            return f"if (c.ecx == 0) {self.goto(ops[0].imm)}"
        if m == "loop":
            return f"if (--c.ecx != 0) {self.goto(ops[0].imm)}"
        if m == "loope":
            return f"if (--c.ecx != 0 && f.zf) {self.goto(ops[0].imm)}"
        if m == "loopne":
            return f"if (--c.ecx != 0 && !f.zf) {self.goto(ops[0].imm)}"
        if m[0] == "j" and m[1:] in COND:
            return f"if ({COND[m[1:]]}) {self.goto(ops[0].imm & 0xFFFFFFFF)}"

        if m[0] == "f":
            return self.x87(m, ops)
        return self.simd(m, ops)

    def string_op(self, sm):
        rep = sm[0] if len(sm) == 2 else None
        op = sm[-1][:-1]
        size = {"b": 1, "w": 2, "d": 4}[sm[-1][-1]]
        t = T[size]
        acc = {1: "u8(c.eax)", 2: "u16(c.eax)", 4: "c.eax"}[size]
        step = f"(c.df ? -{size} : {size})"
        body = {
            "movs": f"st<{t}>(c.edi, ld<{t}>(c.esi)); c.esi += {step}; c.edi += {step};",
            "stos": f"st<{t}>(c.edi, {acc}); c.edi += {step};",
            "lods": {1: "set8l(c.eax, ld<u8>(c.esi));", 2: "set16(c.eax, ld<u16>(c.esi));",
                     4: "c.eax = ld<u32>(c.esi);"}[size] + f" c.esi += {step};",
            "cmps": f"sub_f<{t}>(f, ld<{t}>(c.esi), ld<{t}>(c.edi)); c.esi += {step}; c.edi += {step};",
            "scas": f"sub_f<{t}>(f, {acc}, ld<{t}>(c.edi)); c.edi += {step};",
        }[op]
        if rep is None:
            return f"{{ {body} }}"
        stop = ""
        if op in ("cmps", "scas"):
            stop = " if (!f.zf) break;" if rep in ("repe", "repz") else " if (f.zf) break;"
        elif rep not in ("rep",):
            stop = ""
        return f"while (c.ecx) {{ c.ecx--; {body}{stop} }}"

    def x87(self, m, ops):
        if m in FCONST:
            return f"fpush(c, {FCONST[m]});"
        if m == "fld":
            op = ops[0]
            if op.type == OP_REG:
                return f"{{ double v = ST(c, {self.sti(op)}); fpush(c, v); }}"
            ld = {4: "ldf", 8: "ldd", 10: "ld80"}[op.size]
            return f"fpush(c, {ld}({self.ea(op)}));"
        if m == "fild":
            op = ops[0]
            return f"fpush(c, double(ld<{S[op.size]}>({self.ea(op)})));"
        if m in ("fst", "fstp"):
            op = ops[0]
            pop = " fpop(c);" if m == "fstp" else ""
            if op.type == OP_REG:
                return f"ST(c, {self.sti(op)}) = ST(c, 0);{pop}"
            if op.size == 10:
                return f"st80({self.ea(op)}, ST(c, 0));{pop}"
            ft = {4: "float", 8: "double"}[op.size]
            return f"st<{ft}>({self.ea(op)}, {ft}(ST(c, 0)));{pop}"
        if m in ("fist", "fistp", "fisttp"):
            op = ops[0]
            pop = " fpop(c);" if m != "fist" else ""
            if m == "fisttp":
                return f"st<{T[op.size]}>({self.ea(op)}, {T[op.size]}({S[op.size]}(std::trunc(ST(c, 0)))));{pop}"
            return f"st<{T[op.size]}>({self.ea(op)}, fist<{T[op.size]}>(c, ST(c, 0)));{pop}"
        if m == "fxch":
            k = max(self.sti(op) for op in ops) if ops else 1  # capstone gives "st(0), st(i)" or just "st(i)"
            return f"std::swap(ST(c, 0), ST(c, {k}));"
        base = m[:-1] if m.endswith("p") and m[:-1] in FARITH else m
        if base in FARITH:
            expr = FARITH[base]
            if m.endswith("p"):  # fXXXp st(i), st(0)
                k = self.sti(ops[0]) if ops else 1
                return f"ST(c, {k}) = {expr.format(a=f'ST(c, {k})', b='ST(c, 0)')}; fpop(c);"
            if len(ops) == 1 and ops[0].type == OP_REG:  # fmul st(i): st(0) *= st(i)
                k = self.sti(ops[0])
                return f"ST(c, 0) = {expr.format(a='ST(c, 0)', b=f'ST(c, {k})')};"
            if len(ops) == 1:
                op = ops[0]
                src = {4: f"double(ldf({self.ea(op)}))", 8: f"ldd({self.ea(op)})"}[op.size]
                return f"ST(c, 0) = {expr.format(a='ST(c, 0)', b=src)};"
            d, s = self.sti(ops[0]), self.sti(ops[1])
            return f"ST(c, {d}) = {expr.format(a=f'ST(c, {d})', b=f'ST(c, {s})')};"
        if m in ("fiadd", "fisub", "fisubr", "fimul", "fidiv", "fidivr"):
            op = ops[0]
            src = f"double(ld<{S[op.size]}>({self.ea(op)}))"
            return f"ST(c, 0) = {FARITH['f' + m[2:]].format(a='ST(c, 0)', b=src)};"
        if m in ("fcom", "fcomp", "fucom", "fucomp", "fcompp", "fucompp", "ficom", "ficomp", "ftst"):
            if m == "ftst":
                b = "0.0"
            elif m.startswith("fi"):
                b = f"double(ld<{S[ops[0].size]}>({self.ea(ops[0])}))"
            elif not ops:
                b = "ST(c, 1)"
            elif ops[0].type == OP_REG:
                b = f"ST(c, {self.sti(ops[-1])})"
            else:
                b = {4: f"double(ldf({self.ea(ops[0])}))", 8: f"ldd({self.ea(ops[0])})"}[ops[0].size]
            pops = 2 if m.endswith("pp") else 1 if m.endswith("p") else 0
            return f"fcom(c, ST(c, 0), {b});" + " fpop(c);" * pops
        if m in ("fcomi", "fcompi", "fucomi", "fucompi", "fcomip", "fucomip"):
            k = self.sti(ops[-1]) if ops else 1
            pop = " fpop(c);" if "p" in m[4:] or m.endswith("pi") else ""
            return f"fcomi(f, ST(c, 0), ST(c, {k}));{pop}"
        if m == "fnstsw":
            op = ops[0]
            if op.type == OP_REG:
                return "set16(c.eax, fsw(c));"
            return f"st<u16>({self.ea(op)}, fsw(c));"
        if m == "fnstcw":
            return f"st<u16>({self.ea(ops[0])}, c.fcw);"
        if m == "fldcw":
            return f"c.fcw = ld<u16>({self.ea(ops[0])});"
        if m == "ffreep":
            return "fpop(c);"
        if m.startswith("fcmov"):
            return f"if ({COND[{'e': 'e', 'ne': 'ne', 'b': 'b', 'nb': 'ae', 'be': 'be', 'nbe': 'a', 'u': 'p', 'nu': 'np'}[m[5:]]]}) ST(c, 0) = ST(c, {self.sti(ops[-1])});"
        simple = {"fchs": "ST(c, 0) = -ST(c, 0);", "fabs": "ST(c, 0) = std::fabs(ST(c, 0));",
                  "fsqrt": "ST(c, 0) = std::sqrt(ST(c, 0));", "fsin": "ST(c, 0) = std::sin(ST(c, 0));",
                  "fcos": "ST(c, 0) = std::cos(ST(c, 0));", "frndint": "ST(c, 0) = fround(c, ST(c, 0));",
                  "f2xm1": "ST(c, 0) = std::exp2(ST(c, 0)) - 1.0;",
                  "fscale": "ST(c, 0) = std::ldexp(ST(c, 0), int(std::trunc(ST(c, 1))));",
                  "fyl2x": "ST(c, 1) = ST(c, 1) * std::log2(ST(c, 0)); fpop(c);",
                  "fpatan": "ST(c, 1) = std::atan2(ST(c, 1), ST(c, 0)); fpop(c);",
                  "fptan": "ST(c, 0) = std::tan(ST(c, 0)); fpush(c, 1.0);",
                  "fsincos": "{ double v = ST(c, 0); ST(c, 0) = std::sin(v); fpush(c, std::cos(v)); }",
                  "fprem": "ST(c, 0) = std::fmod(ST(c, 0), ST(c, 1)); c.fsw &= ~0x0400;",
                  "fprem1": "ST(c, 0) = std::remainder(ST(c, 0), ST(c, 1)); c.fsw &= ~0x0400;",
                  "fxam": "fxam(c);", "fdecstp": "c.ftop = (c.ftop - 1) & 7;",
                  "fincstp": "c.ftop = (c.ftop + 1) & 7;", "fninit": "c.ftop = 0; c.fcw = 0x37F; c.fsw = 0;"}
        if m in simple:
            return simple[m]
        raise Unsupported(m)

    def simd(self, m, ops):
        if m == "movss":
            d, s = ops
            if d.type == OP_MEM:
                return f"st<float>({self.ea(d)}, {self.xmm(s)}.f[0]);"
            if s.type == OP_MEM:
                x = self.xmm(d)
                return f"{x}.f[0] = ldf({self.ea(s)}); {x}.u[1] = {x}.u[2] = {x}.u[3] = 0;"
            return f"{self.xmm(d)}.f[0] = {self.xmm(s)}.f[0];"
        if m in ("movaps", "movups", "movntps", "movapd", "movdqa", "movdqu"):
            d, s = ops
            if d.type == OP_MEM:
                return f"st<Xmm>({self.ea(d)}, {self.xmm(s)});"
            return f"{self.xmm(d)} = {self.xmm_src(s)};"
        if m in ("movlps", "movhps"):
            d, s = ops
            k = 0 if m == "movlps" else 1
            if d.type == OP_MEM:
                return f"st<u64>({self.ea(d)}, {self.xmm(s)}.q[{k}]);"
            return f"{self.xmm(d)}.q[{k}] = ld<u64>({self.ea(s)});"
        if m == "movlhps":
            return f"{self.xmm(ops[0])}.q[1] = {self.xmm(ops[1])}.q[0];"
        if m == "movhlps":
            return f"{self.xmm(ops[0])}.q[0] = {self.xmm(ops[1])}.q[1];"
        if m in SSE_SCALAR:
            x = self.xmm(ops[0])
            return f"{{ float a = {x}.f[0], b = {self.fscalar(ops[1])}; {x}.f[0] = {SSE_SCALAR[m].format(a='a', b='b')}; }}"
        if m in SSE_PACKED_F or m in SSE_PACKED_U:
            x = self.xmm(ops[0])
            lane, expr = ("f", SSE_PACKED_F[m]) if m in SSE_PACKED_F else ("u", SSE_PACKED_U[m])
            return (f"{{ Xmm s = {self.xmm_src(ops[1])}; for (int k = 0; k < 4; ++k) "
                    f"{x}.{lane}[k] = {expr.format(a=f'{x}.{lane}[k]', b=f's.{lane}[k]')}; }}")
        if m in ("comiss", "ucomiss"):
            return f"comiss(f, {self.xmm(ops[0])}.f[0], {self.fscalar(ops[1])});"
        if m == "cvtsi2ss":
            return f"{self.xmm(ops[0])}.f[0] = float(s32({self.rd(ops[1], 4)}));"
        if m in ("cvttss2si", "cvtss2si"):
            fn = "cvtt(" if m == "cvttss2si" else "cvt_round(c, "
            return self.wr(ops[0], f"{fn}{self.fscalar(ops[1])})")
        if m == "cvtpi2ps":
            x = self.xmm(ops[0])
            return f"{{ Mmx s; s.q = {self.mm_src(ops[1])}; {x}.f[0] = float(s32(s.d[0])); {x}.f[1] = float(s32(s.d[1])); }}"
        if m == "shufps":
            x, imm = self.xmm(ops[0]), ops[2].imm
            sel = [imm & 3, (imm >> 2) & 3, (imm >> 4) & 3, (imm >> 6) & 3]
            return (f"{{ Xmm a = {x}, b = {self.xmm_src(ops[1])}; "
                    f"{x}.u[0] = a.u[{sel[0]}]; {x}.u[1] = a.u[{sel[1]}]; {x}.u[2] = b.u[{sel[2]}]; {x}.u[3] = b.u[{sel[3]}]; }}")
        if m in ("unpcklps", "unpckhps"):
            x, o = self.xmm(ops[0]), 0 if m == "unpcklps" else 2
            return (f"{{ Xmm a = {x}, b = {self.xmm_src(ops[1])}; "
                    f"{x}.u[0] = a.u[{o}]; {x}.u[1] = b.u[{o}]; {x}.u[2] = a.u[{o + 1}]; {x}.u[3] = b.u[{o + 1}]; }}")
        if m == "ldmxcsr":
            return f"c.mxcsr = ld<u32>({self.ea(ops[0])});"
        if m == "stmxcsr":
            return f"st<u32>({self.ea(ops[0])}, c.mxcsr);"
        # MMX
        if m == "movd":
            d, s = ops
            if d.type == OP_REG and self.name(d.reg).startswith("mm"):
                return f"c.mm[{self.name(d.reg)[2]}].q = {self.rd(s, 4)};"
            return self.wr(d, f"u32(c.mm[{self.name(s.reg)[2]}].q)")
        if m == "movq":
            d, s = ops
            if d.type == OP_MEM:
                return f"st<u64>({self.ea(d)}, {self.mm_src(s)});"
            return f"c.mm[{self.name(d.reg)[2]}].q = {self.mm_src(s)};"
        if m in MMX:
            lane, n, expr = MMX[m]
            d = f"c.mm[{self.name(ops[0].reg)[2]}].q"
            return f"{d} = lanes<{lane}, {n}>({d}, {self.mm_src(ops[1])}, []({lane} x, {lane} y) {{ return {lane}({expr}); }});"
        if m in MMX_Q:
            d = f"c.mm[{self.name(ops[0].reg)[2]}].q"
            return f"{{ u64 a = {d}, b = {self.mm_src(ops[1])}; {d} = {MMX_Q[m]}; }}"
        if m in MMX_SHIFT:
            lane, n, sym = MMX_SHIFT[m]
            d = f"c.mm[{self.name(ops[0].reg)[2]}].q"
            cnt = str(ops[1].imm) if ops[1].type == OP_IMM else self.mm_src(ops[1])
            bits = 64 // n
            fill = f"(x < 0 ? -1 : 0)" if lane[0] == "s" else "0"
            return (f"{{ u64 k = {cnt}; {d} = lanes<{lane}, {n}>({d}, 0, [k]({lane} x, {lane}) {{ "
                    f"return {lane}(k >= {bits} ? {lane}({fill}) : {lane}(x {sym} k)); }}); }}")
        if m in UNPACK:
            lane, n, high = UNPACK[m]
            d = f"c.mm[{self.name(ops[0].reg)[2]}].q"
            o = n // 2 if high else 0
            return (f"{{ {lane} a[{n}], b[{n}], r[{n}]; u64 s = {self.mm_src(ops[1])}; std::memcpy(a, &{d}, 8); std::memcpy(b, &s, 8); "
                    f"for (int k = 0; k < {n // 2}; ++k) {{ r[2 * k] = a[{o} + k]; r[2 * k + 1] = b[{o} + k]; }} std::memcpy(&{d}, r, 8); }}")
        if m == "pshufw":
            d, imm = f"c.mm[{self.name(ops[0].reg)[2]}]", ops[2].imm
            return (f"{{ Mmx s; s.q = {self.mm_src(ops[1])}; " +
                    " ".join(f"{d}.w[{k}] = s.w[{(imm >> 2 * k) & 3}];" for k in range(4)) + " }")
        if m == "pmaddwd":
            d = f"c.mm[{self.name(ops[0].reg)[2]}]"
            return (f"{{ Mmx s; s.q = {self.mm_src(ops[1])}; Mmx a = {d}; "
                    f"{d}.d[0] = u32(s32(a.sw[0]) * s.sw[0] + s32(a.sw[1]) * s.sw[1]); "
                    f"{d}.d[1] = u32(s32(a.sw[2]) * s.sw[2] + s32(a.sw[3]) * s.sw[3]); }}")
        if m in ("packssdw", "packuswb", "packsswb"):
            src_t, n, dst_t = {"packssdw": ("s32", 2, "s16"), "packuswb": ("s16", 4, "u8"),
                               "packsswb": ("s16", 4, "s8")}[m]
            d = f"c.mm[{self.name(ops[0].reg)[2]}].q"
            return (f"{{ {src_t} a[{n}], b[{n}]; {dst_t} r[{2 * n}]; u64 s = {self.mm_src(ops[1])}; "
                    f"std::memcpy(a, &{d}, 8); std::memcpy(b, &s, 8); "
                    f"for (int k = 0; k < {n}; ++k) {{ r[k] = sat<{dst_t}>(a[k]); r[{n} + k] = sat<{dst_t}>(b[k]); }} "
                    f"std::memcpy(&{d}, r, 8); }}")
        if m in ("cvtps2pi", "cvttps2pi"):
            d = f"c.mm[{self.name(ops[0].reg)[2]}]"
            s_ = self.xmm_src(ops[1]) if ops[1].type == OP_REG else f"ld<Xmm>({self.ea(ops[1])})"
            fn = "cvtt(s.f[{k}])" if m == "cvttps2pi" else "cvt_round(c, s.f[{k}])"
            return (f"{{ Xmm s = {s_}; {d}.d[0] = u32({fn.format(k=0)}); {d}.d[1] = u32({fn.format(k=1)}); }}")
        if m == "psadbw":
            d = f"c.mm[{self.name(ops[0].reg)[2]}]"
            return (f"{{ Mmx s; s.q = {self.mm_src(ops[1])}; u32 t = 0; for (int k = 0; k < 8; ++k) "
                    f"t += {d}.b[k] > s.b[k] ? {d}.b[k] - s.b[k] : s.b[k] - {d}.b[k]; {d}.q = t; }}")
        raise Unsupported(m)

    # ---- whole function ----
    def emit(self):
        order = sorted(self.body)
        code, missing = [], collections.Counter()
        p = self.p
        for idx, va in enumerate(order):
            i = p.insns[va]
            try:
                line = self.insn_code(i)
            except (Unsupported, KeyError, IndexError) as e:
                missing[i.mnemonic] += 1
                line = f'unimplemented(c, 0x{va:X}u, "{i.mnemonic} {i.op_str}");'
            code.append((va, f"    {line}" if line else ""))
            terminal = i.id in analyze.NORETURN_INS and i.mnemonic not in ("int3",)
            if i.mnemonic == "int3":
                code.append((None, "    return;"))
                terminal = True
            if not terminal:
                nxt = va + i.size
                if idx + 1 >= len(order) or order[idx + 1] != nxt:
                    code.append((None, "    " + self.goto(nxt)))
        out = [f"void sub_{self.start:X}(Ctx& c) {{", "    Flags f{};", f"    SAFEPOINT(0x{self.start:X}u)"]
        if self.xdk:
            k, (lib, name, conv, stack) = self.xdk
            out.insert(0, f"// {lib} {name} ({conv}, {stack} bytes of stack arguments)")
            out.insert(3, f"    XDK_ENTRY({k})")
        if self.start != order[0]:
            out.append(f"    goto L_{self.start:X};")
            self.labels.add(self.start)
        for va, line in code:
            if va is not None and va in self.labels:
                out.append(f"L_{va:X}:;")
            if line:
                out.append(line)
        out.append("}")
        return "\n".join(out), missing


def load_symbols(path):
    """{address: (library, name, call convention, stack argument bytes)} from symbols.py output"""
    syms = {}
    if not os.path.exists(path):
        return syms
    for line in open(path):
        if line.startswith("#"):
            continue
        addr, lib, kind, name, conv, params = line.rstrip("\n").split("\t")
        if kind != "FUN":
            continue
        # psh = 4-byte stack argument, psh2 = 8-byte; ecx/edx are register arguments
        stack = sum(8 if p.strip().startswith("psh2 ") else 4 if p.strip().startswith("psh ") else 0
                    for p in params.split(",") if p.strip())
        syms[int(addr, 16)] = (lib, name, conv, stack)
    return syms


def main(xbe_path, out_dir, shards="32", symbols_path="symbols/xdk_symbols.tsv"):
    shards = int(shards)
    syms = load_symbols(symbols_path)
    syms.update(load_symbols(os.path.join(os.path.dirname(symbols_path), "manual_symbols.tsv")))
    prog = analyze.Program(xbe_path)
    prog.run(sorted(syms))
    lost = [a for a in syms if a not in prog.funcs]
    if lost:
        raise SystemExit("named functions outside code: " + " ".join(f"{a:x}" for a in lost))
    # the callee-popped byte count is in the function's own `ret N`; trust that over the parameter list
    for a, (lib, name, conv, stack) in list(syms.items()):
        rets = {i.operands[0].imm if i.operands else 0
                for i in (prog.insns[v] for v in prog.funcs[a]) if i.mnemonic == "ret"}
        if conv != "cdecl" and len(rets) == 1 and (n := rets.pop()) != stack:
            print(f"{name}: database says {stack} stack bytes, ret pops {n}; using {n}")
            syms[a] = (lib, name, conv, n)
    xdk_index = {a: k for k, a in enumerate(sorted(syms))}
    os.makedirs(out_dir, exist_ok=True)
    funcs = sorted(prog.funcs)
    missing = collections.Counter()
    files = [[] for _ in range(shards)]
    for n, start in enumerate(funcs):
        gen = FuncGen(prog, start, prog.funcs[start])
        if start in syms:
            gen.xdk = (xdk_index[start], syms[start])
        text, miss = gen.emit()
        missing += miss
        files[n * shards // len(funcs)].append(text)

    def write(name, text):
        path = os.path.join(out_dir, name)
        try:
            if open(path).read() == text:
                return  # keep timestamps so the build only redoes changed shards
        except FileNotFoundError:
            pass
        with open(path, "w", newline="\n") as f:
            f.write(text)

    write("funcs.h", "#pragma once\n#include \"x86.h\"\n" +
          "".join(f"void sub_{f:X}(Ctx& c);\n" for f in funcs))
    for k, parts in enumerate(files):
        write(f"recomp_{k:02}.cpp", "// generated by xboxrecomp/codegen.py\n#include \"funcs.h\"\n\n" +
              "\n\n".join(parts) + "\n")
    table = ",\n".join(f"    {{0x{f:X}u, sub_{f:X}}}" for f in funcs)
    write("func_table.cpp", "#include \"funcs.h\"\n#include \"func_table.h\"\n"
          f"const FuncEntry g_func_table[] = {{\n{table}\n}};\n"
          f"const unsigned g_func_count = {len(funcs)};\n")
    conv_ids = {"stdcall": 0, "cdecl": 1, "fastcall": 2, "thiscall": 3}
    entries = ",\n".join(f'    {{0x{a:X}u, "{lib}", "{name}", {conv_ids[conv]}, {stack}}}'
                         for a, (lib, name, conv, stack) in sorted(syms.items()))
    write("xdk_symbols.cpp", "#include \"func_table.h\"\n"
          f"const XdkSymbol g_xdk_symbols[] = {{\n{entries}\n}};\n"
          f"const unsigned g_xdk_symbol_count = {len(syms)};\n"
          f"XdkHook g_xdk_hook[{max(len(syms), 1)}];\n")
    thunks = ",\n".join(f"    {{0x{va:X}u, {o}}}" for va, o in sorted(prog.thunks.items()))
    write("kernel_thunks.cpp", "#include \"func_table.h\"\n"
          f"const KernelThunk g_kernel_thunks[] = {{\n{thunks}\n}};\n"
          f"const unsigned g_kernel_thunk_count = {len(prog.thunks)};\n")
    exports = []
    for line in open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "xboxkrnl.def")):
        if not line.strip() or line[0] == "#":
            continue
        ordinal, rest = line.split(None, 1)
        rest = rest.split()
        name, data = rest[0], len(rest) > 1 and rest[1] == "DATA"
        fast = name.startswith("@")
        name, _, argbytes = name.lstrip("@").partition("@")
        exports.append(f'    {{{ordinal}, "{name}", {argbytes or -1}, {int(fast)}, {int(data)}}}')
    write("kernel_exports.cpp", "#include \"func_table.h\"\n"
          "const KernelExport g_kernel_exports[] = {\n" + ",\n".join(exports) + "\n};\n"
          f"const unsigned g_kernel_export_count = {len(exports)};\n")
    print(f"{len(funcs)} functions, {sum(len(prog.funcs[f]) for f in funcs)} instructions")
    print(f"untranslated: {sum(missing.values())} " + " ".join(f"{m}:{n}" for m, n in missing.most_common()))


if __name__ == "__main__":
    main(*sys.argv[1:])
