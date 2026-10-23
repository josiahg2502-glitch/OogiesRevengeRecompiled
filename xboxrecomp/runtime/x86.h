// Guest CPU state and instruction helpers used by the generated code.
#pragma once
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <type_traits>
#include <utility>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

union Xmm {
    float f[4];
    u32 u[4];
    u64 q[2];
};

union Mmx {
    u64 q;
    u32 d[2];
    u16 w[4];
    s16 sw[4];
    u8 b[8];
};

// Flags live in locals of each generated function: compilers never keep them live across a call. A jump into another
// function (a tail jump, or into code the analysis split off as its own function) carries them in Ctx::jf.
struct Flags {
    u8 cf, zf, sf, of, pf;
};

struct Ctx {
    u32 eax, ecx, edx, ebx, esp, ebp, esi, edi;
    Flags jf{};     // the flags at a jump into another function (its first instruction may test them)
    u32 df;         // direction flag
    u32 fs_base;    // guest address of the thread's KPCR (fs:0)
    // x87: double precision is what the Xbox libraries run at (they set PC to 53 bits)
    double st[8];
    u32 ftop;
    u16 fcw = 0x027F, fsw;
    Mmx mm[8];
    Xmm xmm[8];
    u32 mxcsr = 0x1F80;
};


extern u8* g_mem;  // 4 GB host reservation; guest address a lives at g_mem + a

template <class T> inline T ld(u32 a) { T v; std::memcpy(&v, g_mem + a, sizeof v); return v; }
template <class T> inline void st(u32 a, T v) { std::memcpy(g_mem + a, &v, sizeof v); }
#define LD8(a) ld<u8>(a)
#define LD16(a) ld<u16>(a)
#define LD32(a) ld<u32>(a)
#define LD64(a) ld<u64>(a)

inline void set8l(u32& r, u8 v) { r = (r & 0xFFFFFF00u) | v; }
inline void set8h(u32& r, u8 v) { r = (r & 0xFFFF00FFu) | (u32(v) << 8); }
inline void set16(u32& r, u16 v) { r = (r & 0xFFFF0000u) | v; }

inline void push32(Ctx& c, u32 v) { c.esp -= 4; st<u32>(c.esp, v); }
inline u32 pop32(Ctx& c) { u32 v = ld<u32>(c.esp); c.esp += 4; return v; }

template <class T> constexpr unsigned BITS = sizeof(T) * 8;
template <class T> inline u8 msb(T v) { return u8(v >> (BITS<T> - 1)) & 1; }
inline u8 parity(u32 v) { return u8(~__builtin_popcount(v & 0xFF) & 1); }
template <class T> inline T szp(Flags& f, T r) { f.zf = r == 0; f.sf = msb(r); f.pf = parity(r); return r; }

template <class T> inline T add_f(Flags& f, T a, T b, u8 cin = 0) {
    T r = T(a + b + cin);
    f.cf = cin ? r <= a : r < a;
    f.of = msb(T((a ^ r) & (b ^ r)));
    return szp(f, r);
}
template <class T> inline T sub_f(Flags& f, T a, T b, u8 bin = 0) {
    T r = T(a - b - bin);
    f.cf = bin ? a <= b : a < b;
    f.of = msb(T((a ^ b) & (a ^ r)));
    return szp(f, r);
}
template <class T> inline T logic_f(Flags& f, T r) { f.cf = f.of = 0; return szp(f, r); }
template <class T> inline T inc_f(Flags& f, T a) { T r = T(a + 1); f.of = r == T(T(1) << (BITS<T> - 1)); return szp(f, r); }
template <class T> inline T dec_f(Flags& f, T a) { T r = T(a - 1); f.of = a == T(T(1) << (BITS<T> - 1)); return szp(f, r); }
template <class T> inline T neg_f(Flags& f, T a) { f.cf = a != 0; T r = T(0 - a); f.of = r == T(T(1) << (BITS<T> - 1)) && a == r; return szp(f, r); }

template <class T> inline T shl_f(Flags& f, T a, u8 n) {
    n &= 31;
    if (!n) return a;
    T r = n < BITS<T> ? T(a << n) : 0;
    f.cf = n <= BITS<T> ? (a >> (BITS<T> - n)) & 1 : 0;
    f.of = msb(r) ^ f.cf;
    return szp(f, r);
}
template <class T> inline T shr_f(Flags& f, T a, u8 n) {
    n &= 31;
    if (!n) return a;
    T r = n < BITS<T> ? T(a >> n) : 0;
    f.cf = (a >> (n - 1)) & 1;
    f.of = msb(a);
    return szp(f, r);
}
template <class T> inline T sar_f(Flags& f, T a, u8 n) {
    typedef std::make_signed_t<T> S;
    n &= 31;
    if (!n) return a;
    if (n >= BITS<T>) n = BITS<T> - 1, f.cf = msb(a); else f.cf = (S(a) >> (n - 1)) & 1;
    T r = T(S(a) >> n);
    f.of = 0;
    return szp(f, r);
}
template <class T> inline T rol_f(Flags& f, T a, u8 n) {
    n &= 31;
    if (!n) return a;
    n %= BITS<T>;
    T r = n ? T((a << n) | (a >> (BITS<T> - n))) : a;
    f.cf = r & 1;
    f.of = msb(r) ^ f.cf;
    return r;
}
template <class T> inline T ror_f(Flags& f, T a, u8 n) {
    n &= 31;
    if (!n) return a;
    n %= BITS<T>;
    T r = n ? T((a >> n) | (a << (BITS<T> - n))) : a;
    f.cf = msb(r);
    f.of = msb(r) ^ (u8(r >> (BITS<T> - 2)) & 1);
    return r;
}
template <class T> inline T rcl_f(Flags& f, T a, u8 n) {
    n = (n & 31) % (BITS<T> + 1);
    for (; n; --n) { u8 c = msb(a); a = T((a << 1) | f.cf); f.cf = c; }
    f.of = msb(a) ^ f.cf;
    return a;
}
template <class T> inline T rcr_f(Flags& f, T a, u8 n) {
    n = (n & 31) % (BITS<T> + 1);
    f.of = msb(a) ^ f.cf;
    for (; n; --n) { u8 c = a & 1; a = T((a >> 1) | (T(f.cf) << (BITS<T> - 1))); f.cf = c; }
    return a;
}
inline u32 shld_f(Flags& f, u32 a, u32 b, u8 n) {
    n &= 31;
    if (!n) return a;
    u32 r = (a << n) | (b >> (32 - n));
    f.cf = (a >> (32 - n)) & 1;
    f.of = msb(r) ^ msb(a);
    return szp(f, r);
}
inline u32 shrd_f(Flags& f, u32 a, u32 b, u8 n) {
    n &= 31;
    if (!n) return a;
    u32 r = (a >> n) | (b << (32 - n));
    f.cf = (a >> (n - 1)) & 1;
    f.of = msb(r) ^ msb(a);
    return szp(f, r);
}
template <class T> inline T imul_f(Flags& f, T a, T b) {
    typedef std::make_signed_t<T> S;
    s64 w = s64(S(a)) * s64(S(b));
    T r = T(w);
    f.cf = f.of = w != s64(S(r));
    return szp(f, r);
}

// one-operand mul/div on the eax:edx pair
inline void mul32(Ctx& c, Flags& f, u32 v) { u64 r = u64(c.eax) * v; c.eax = u32(r); c.edx = u32(r >> 32); f.cf = f.of = c.edx != 0; }
inline void imul32(Ctx& c, Flags& f, u32 v) { s64 r = s64(s32(c.eax)) * s32(v); c.eax = u32(r); c.edx = u32(u64(r) >> 32); f.cf = f.of = r != s32(r); }
inline void mul8(Ctx& c, Flags& f, u8 v) { u16 r = u16((c.eax & 0xFF) * v); set16(c.eax, r); f.cf = f.of = (r >> 8) != 0; }
[[noreturn]] void guest_fault(Ctx& c, const char* what, u32 pc);
inline void div32(Ctx& c, u32 v, u32 pc) {
    if (!v) return guest_fault(c, "divide by zero", pc);
    u64 n = (u64(c.edx) << 32) | c.eax;
    c.eax = u32(n / v); c.edx = u32(n % v);
}
inline void idiv32(Ctx& c, u32 v, u32 pc) {
    if (!v) return guest_fault(c, "divide by zero", pc);
    s64 n = s64((u64(c.edx) << 32) | c.eax);
    c.eax = u32(n / s32(v)); c.edx = u32(n % s32(v));
}
inline void div16(Ctx& c, u16 v, u32 pc) {
    if (!v) return guest_fault(c, "divide by zero", pc);
    u32 n = ((c.edx & 0xFFFF) << 16) | (c.eax & 0xFFFF);
    set16(c.eax, u16(n / v)); set16(c.edx, u16(n % v));
}
inline void div8(Ctx& c, u8 v, u32 pc) {
    if (!v) return guest_fault(c, "divide by zero", pc);
    u16 n = u16(c.eax);
    set8l(c.eax, u8(n / v)); set8h(c.eax, u8(n % v));
}
inline void idiv8(Ctx& c, u8 v, u32 pc) {
    if (!v) return guest_fault(c, "divide by zero", pc);
    s16 n = s16(c.eax);
    set8l(c.eax, u8(n / s8(v))); set8h(c.eax, u8(n % s8(v)));
}

inline u32 bsf_f(Flags& f, u32 v, u32 old) { f.zf = v == 0; return v ? __builtin_ctz(v) : old; }

inline u8 get_flags8(const Flags& f) { return u8(f.cf | 2 | (f.pf << 2) | (f.zf << 6) | (f.sf << 7)); }
inline void set_flags8(Flags& f, u8 v) { f.cf = v & 1; f.pf = (v >> 2) & 1; f.zf = (v >> 6) & 1; f.sf = (v >> 7) & 1; }
inline u32 get_eflags(const Ctx& c, const Flags& f) { return get_flags8(f) | (c.df << 10) | (f.of << 11) | 0x200; }
inline void set_eflags(Ctx& c, Flags& f, u32 v) { set_flags8(f, u8(v)); c.df = (v >> 10) & 1; f.of = (v >> 11) & 1; }

// ---- x87 ----
inline double& ST(Ctx& c, int i) { return c.st[(c.ftop + i) & 7]; }
inline void fpush(Ctx& c, double v) { c.ftop = (c.ftop - 1) & 7; c.st[c.ftop] = v; }
inline double fpop(Ctx& c) { double v = c.st[c.ftop]; c.ftop = (c.ftop + 1) & 7; return v; }
inline u16 fsw(const Ctx& c) { return u16((c.fsw & ~0x3800) | (c.ftop << 11)); }
inline void fcom(Ctx& c, double a, double b) {
    c.fsw &= ~0x4500;  // C0 C2 C3
    if (std::isnan(a) || std::isnan(b)) c.fsw |= 0x4500;
    else if (a < b) c.fsw |= 0x0100;
    else if (a == b) c.fsw |= 0x4000;
}
inline void fcomi(Flags& f, double a, double b) {
    f.of = f.sf = 0;
    if (std::isnan(a) || std::isnan(b)) f.zf = f.pf = f.cf = 1;
    else { f.pf = 0; f.zf = a == b; f.cf = a < b; }
}
inline double fround(const Ctx& c, double v) {
    switch ((c.fcw >> 10) & 3) {
    case 0: return std::nearbyint(v);
    case 1: return std::floor(v);
    case 2: return std::ceil(v);
    default: return std::trunc(v);
    }
}
template <class T> inline T fist(const Ctx& c, double v) {
    double r = fround(c, v);
    typedef std::make_signed_t<T> S;
    if (!(r >= double(std::numeric_limits<S>::min()) && r <= double(std::numeric_limits<S>::max())))
        return T(std::numeric_limits<S>::min());  // x87 "integer indefinite"
    return T(S(r));
}
inline void fxam(Ctx& c) {
    double v = ST(c, 0);
    u16 cc = std::isnan(v) ? 0x0100 : std::isinf(v) ? 0x0500 : v == 0 ? 0x4000 : 0x0400;
    if (std::signbit(v)) cc |= 0x0200;
    c.fsw = u16((c.fsw & ~0x4700) | cc);
}
double ld80(u32 a);
void st80(u32 a, double v);

// ---- SSE (scalar float compare into EFLAGS) ----
inline void comiss(Flags& f, float a, float b) { fcomi(f, a, b); }
inline s32 cvtt(float v) {
    if (!(v >= -2147483648.0f && v < 2147483648.0f)) return INT32_MIN;
    return s32(v);
}
inline s32 cvt_round(const Ctx& c, float v) {
    double r;
    switch ((c.mxcsr >> 13) & 3) {
    case 0: r = std::nearbyint(double(v)); break;
    case 1: r = std::floor(double(v)); break;
    case 2: r = std::ceil(double(v)); break;
    default: r = std::trunc(double(v)); break;
    }
    if (!(r >= -2147483648.0 && r < 2147483648.0)) return INT32_MIN;
    return s32(r);
}
inline float ldf(u32 a) { return ld<float>(a); }
inline double ldd(u32 a) { return ld<double>(a); }

// ---- MMX lane helpers ----
template <class L, int N, class Op> inline u64 lanes(u64 a, u64 b, Op op) {
    L x[N], y[N];
    std::memcpy(x, &a, 8); std::memcpy(y, &b, 8);
    for (int i = 0; i < N; ++i) x[i] = op(x[i], y[i]);
    std::memcpy(&a, x, 8);
    return a;
}
template <class T> inline T sat(s32 v) {
    return T(v < std::numeric_limits<T>::min() ? std::numeric_limits<T>::min()
             : v > std::numeric_limits<T>::max() ? std::numeric_limits<T>::max() : v);
}

// ---- control flow into the runtime ----
// Set when another guest thread wants the CPU; generated code checks it at function entry and
// backward branches.
extern volatile u32 g_yield_request;
void guest_yield(Ctx& c, u32 pc);
#define SAFEPOINT(pc)     if (g_yield_request) guest_yield(c, pc);
// A hook returns true when it replaced the function (set eax, popped the arguments).
typedef bool (*XdkHook)(Ctx& c, u32 index);
extern XdkHook g_xdk_hook[];
#define XDK_ENTRY(k) if (g_xdk_hook[k] && g_xdk_hook[k](c, k)) return;
void dispatch(Ctx& c, u32 target);             // call/jmp to a computed address
[[noreturn]] void unimplemented(Ctx& c, u32 pc, const char* text);
void guest_cpuid(Ctx& c);
void guest_rdtsc(Ctx& c);
void guest_out(u32 port, u32 value, int size);
u32 guest_in(u32 port, int size);
void guest_int(Ctx& c, u32 vector, u32 pc);
