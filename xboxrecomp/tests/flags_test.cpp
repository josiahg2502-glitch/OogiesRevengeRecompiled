// Checks the flag helpers in x86.h against the host CPU's own instructions.
#include <cstdio>
#include <random>
#include "x86.h"

u8* g_mem;
void guest_fault(const char*, u32) { __builtin_trap(); }

static const u32 MASK = 0x8C5;  // CF PF ZF SF OF

static u32 pack(const Flags& f) { return f.cf | (f.pf << 2) | (f.zf << 6) | (f.sf << 7) | (f.of << 11); }

#define HOST2(insn, T, a, b, r, fl)                                                          \
    do {                                                                                     \
        T r_ = a; u64 fl_;                                                                   \
        asm volatile(insn " %2, %0\n\tpushfq\n\tpopq %1" : "+r"(r_), "=r"(fl_) : "r"(b) : "cc"); \
        r = r_; fl = u32(fl_);                                                               \
    } while (0)

int failures;
template <class T> void check(const char* what, T a, T b, T got, T want, u32 gf, u32 wf, u32 mask) {
    if (got != want || (gf & mask) != (wf & mask)) {
        if (++failures < 20)
            std::printf("%s a=%llx b=%llx: got %llx/%03x want %llx/%03x\n", what, (unsigned long long)a,
                        (unsigned long long)b, (unsigned long long)got, gf & mask, (unsigned long long)want, wf & mask);
    }
}

int main() {
    std::mt19937 rng(1);
    auto pick = [&]() -> u32 {
        static const u32 edge[] = {0, 1, 0x7F, 0x80, 0xFF, 0x7FFF, 0x8000, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF};
        return rng() % 3 ? rng() : edge[rng() % 10];
    };
    for (int n = 0; n < 200000; ++n) {
        u32 a = pick(), b = pick(), r, fl;
        Flags f{};
        HOST2("addl", u32, a, b, r, fl); check("add32", a, b, add_f<u32>(f, a, b), r, pack(f), fl, MASK);
        HOST2("subl", u32, a, b, r, fl); check("sub32", a, b, sub_f<u32>(f, a, b), r, pack(f), fl, MASK);
        HOST2("andl", u32, a, b, r, fl); check("and32", a, b, logic_f<u32>(f, a & b), r, pack(f), fl, MASK);
        {
            u8 x = u8(a), y = u8(b), r8; u32 fl8;
            HOST2("addb", u8, x, y, r8, fl8); check<u8>("add8", x, y, add_f<u8>(f, x, y), r8, pack(f), fl8, MASK);
            HOST2("subb", u8, x, y, r8, fl8); check<u8>("sub8", x, y, sub_f<u8>(f, x, y), r8, pack(f), fl8, MASK);
        }
        for (u8 cin = 0; cin < 2; ++cin) {
            u32 r2; u64 fl2;
            r2 = a;
            asm volatile("bt $0, %3\n\tadcl %2, %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : "r"(b), "r"(u32(cin)) : "cc");
            check("adc32", a, b, add_f<u32>(f, a, b, cin), r2, pack(f), u32(fl2), MASK);
            r2 = a;
            asm volatile("bt $0, %3\n\tsbbl %2, %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : "r"(b), "r"(u32(cin)) : "cc");
            check("sbb32", a, b, sub_f<u32>(f, a, b, cin), r2, pack(f), u32(fl2), MASK);
        }
        u8 k = u8(b & 31);
        if (k) {
            // OF is only defined for 1-bit shifts
            u32 m = k == 1 ? MASK : (MASK & ~0x800u);
            u32 r2; u64 fl2;
            r2 = a; asm volatile("shll %%cl, %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : "c"(k) : "cc");
            check("shl32", a, u32(k), shl_f<u32>(f, a, k), r2, pack(f), u32(fl2), m);
            r2 = a; asm volatile("shrl %%cl, %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : "c"(k) : "cc");
            check("shr32", a, u32(k), shr_f<u32>(f, a, k), r2, pack(f), u32(fl2), m);
            r2 = a; asm volatile("sarl %%cl, %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : "c"(k) : "cc");
            check("sar32", a, u32(k), sar_f<u32>(f, a, k), r2, pack(f), u32(fl2), m);
            u32 rm = k == 1 ? 0x801u : 0x1u;  // rotates only define CF (and OF for 1)
            r2 = a; asm volatile("roll %%cl, %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : "c"(k) : "cc");
            check("rol32", a, u32(k), rol_f<u32>(f, a, k), r2, pack(f), u32(fl2), rm);
            r2 = a; asm volatile("rorl %%cl, %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : "c"(k) : "cc");
            check("ror32", a, u32(k), ror_f<u32>(f, a, k), r2, pack(f), u32(fl2), rm);
            r2 = a; asm volatile("shldl %%cl, %2, %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : "r"(b), "c"(k) : "cc");
            check("shld32", a, b, shld_f(f, a, b, k), r2, pack(f), u32(fl2), m);
            r2 = a; asm volatile("shrdl %%cl, %2, %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : "r"(b), "c"(k) : "cc");
            check("shrd32", a, b, shrd_f(f, a, b, k), r2, pack(f), u32(fl2), m);
            u8 x = u8(a), r8;
            asm volatile("sarb %%cl, %0\n\tpushfq\n\tpopq %1" : "+r"(x), "=r"(fl2) : "c"(k) : "cc");
            check<u8>("sar8", u8(a), k, sar_f<u8>(f, u8(a), k), x, pack(f), u32(fl2), k < 8 ? m : 0x8C4u);
        }
        {
            u32 r2; u64 fl2;
            r2 = a; asm volatile("incl %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : : "cc");
            check("inc32", a, 0u, inc_f<u32>(f, a), r2, pack(f), u32(fl2), MASK & ~1u);
            r2 = a; asm volatile("decl %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : : "cc");
            check("dec32", a, 0u, dec_f<u32>(f, a), r2, pack(f), u32(fl2), MASK & ~1u);
            r2 = a; asm volatile("negl %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : : "cc");
            check("neg32", a, 0u, neg_f<u32>(f, a), r2, pack(f), u32(fl2), MASK);
            r2 = a; asm volatile("imull %2, %0\n\tpushfq\n\tpopq %1" : "+r"(r2), "=r"(fl2) : "r"(b) : "cc");
            check("imul32", a, b, imul_f<u32>(f, a, b), r2, pack(f), u32(fl2), 0x801u);
        }
    }
    std::printf(failures ? "%d failures\n" : "flags ok\n", failures);
    return failures != 0;
}
