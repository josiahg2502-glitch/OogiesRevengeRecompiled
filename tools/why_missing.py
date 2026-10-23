"""Why is an address not a recompiled function? usage: python tools/why_missing.py <hex address>..."""
import os
import struct
import sys

root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(root, "xboxrecomp"))
import analyze  # noqa: E402
import codegen  # noqa: E402

syms = codegen.load_symbols(os.path.join(root, "symbols", "xdk_symbols.tsv"))
p = analyze.Program(os.path.join(root, "Disc", "files", "default.xbe"))
owner = p.run(sorted(syms))
for arg in sys.argv[1:]:
    t = int(arg, 16)
    print(f"== {t:08x}: function={t in p.funcs} owner={owner.get(t, 0):08x} rejected={t in p.rejected} "
          f"table_bytes={t in p.table_bytes}")
    p.bad = False
    body, _ = p.explore(t)
    bad = [v for v in sorted(body) if p.insns[v].mnemonic in analyze.BOGUS or analyze.bogus_operands(p.insns[v])]
    print(f"   explore: {len(body)} instructions, junk: " +
          " ".join(f"{v:x}:{p.insns[v].mnemonic} {p.insns[v].op_str}" for v in bad[:5]))
    needle = struct.pack("<I", t)
    for s in p.xbe.sections:
        raw = p.xbe.read(s.va, s.raw_size)
        o = raw.find(needle)
        while o >= 0:
            print(f"   pointer in {s.name} at {s.va + o:08x} (owner {owner.get(s.va + o, 0):08x})")
            o = raw.find(needle, o + 1)
