// NV2A vertex shader microcode -> HLSL.
//
// A program is { u16 type, u16 instruction count } then 16 bytes per instruction. Each instruction
// pairs a MAC op (vector) and an ILU op (scalar) reading up to three inputs A, B, C, each a temp (r),
// vertex input (v) or constant (c, optionally a0-relative), with swizzle and negate. Field layout as
// in xemu/Cxbx; checked against this game's shaders (mov oD0,v1 / mov oT0.xy,v2 / add oPos,v0,c12).
#include "vsh.h"

#include <cstdio>
#include <string>

namespace {

struct Field {
    int dword, bit, bits;
};
// clang-format off
constexpr Field ILU{1, 25, 3}, MAC{1, 21, 4}, CONST{1, 13, 8}, V{1, 9, 4},
    A_NEG{1, 8, 1}, A_SWZ{1, 0, 8}, A_R{2, 28, 4}, A_MUX{2, 26, 2},
    B_NEG{2, 25, 1}, B_SWZ{2, 17, 8}, B_R{2, 13, 4}, B_MUX{2, 11, 2},
    C_NEG{2, 10, 1}, C_SWZ{2, 2, 8}, C_R_HIGH{2, 0, 2}, C_R_LOW{3, 30, 2}, C_MUX{3, 28, 2},
    OUT_MAC_MASK{3, 24, 4}, OUT_R{3, 20, 4}, OUT_ILU_MASK{3, 16, 4}, OUT_O_MASK{3, 12, 4},
    OUT_ORB{3, 11, 1}, OUT_ADDRESS{3, 3, 8}, OUT_MUX{3, 2, 1}, A0X{3, 1, 1}, FINAL{3, 0, 1};
// clang-format on

uint32_t get(const uint32_t* ins, Field f) { return (ins[f.dword] >> f.bit) & ((1u << f.bits) - 1); }

enum { MUX_R = 1, MUX_V = 2, MUX_C = 3 };
enum { MAC_NOP, MAC_MOV, MAC_MUL, MAC_ADD, MAC_MAD, MAC_DP3, MAC_DPH, MAC_DP4, MAC_DST, MAC_MIN, MAC_MAX, MAC_SLT,
       MAC_SGE, MAC_ARL };
enum { ILU_NOP, ILU_MOV, ILU_RCP, ILU_RCC, ILU_RSQ, ILU_EXP, ILU_LOG, ILU_LIT };

const char* output_name(uint32_t a) {
    switch (a) {
    case 0: return "oPos";
    case 3: return "oD0";
    case 4: return "oD1";
    case 5: return "oFog";
    case 6: return "oPts";
    case 7: return "oB0";
    case 8: return "oB1";
    case 9: return "oT0";
    case 10: return "oT1";
    case 11: return "oT2";
    case 12: return "oT3";
    }
    return nullptr;
}

std::string mask(uint32_t m) {  // write mask bits: 8 = x, 4 = y, 2 = z, 1 = w
    std::string s = ".";
    if (m & 8) s += 'x';
    if (m & 4) s += 'y';
    if (m & 2) s += 'z';
    if (m & 1) s += 'w';
    return s;
}

std::string swizzle(uint32_t swz) {  // 2 bits per component, x first in the high bits
    static const char comp[] = "xyzw";
    std::string s = ".";
    for (int k = 3; k >= 0; --k) s += comp[(swz >> (2 * k)) & 3];
    return s;
}

std::string input(const uint32_t* ins, Field neg, Field swz, uint32_t mux, uint32_t reg) {
    std::string base;
    switch (mux) {
    case MUX_R: base = reg == 12 ? "oPos" : "r[" + std::to_string(reg) + "]"; break;  // r12 reads oPos
    case MUX_V: base = "v[" + std::to_string(get(ins, V)) + "]"; break;
    case MUX_C:
        base = get(ins, A0X) ? "c[clamp(a0 + " + std::to_string(get(ins, CONST)) + ", 0, 191)]"
                             : "c[" + std::to_string(get(ins, CONST)) + "]";
        break;
    default: base = "float4(0, 0, 0, 0)"; break;
    }
    return std::string(get(ins, neg) ? "-" : "") + "(" + base + swizzle(get(ins, swz)) + ")";
}

}  // namespace

bool vsh_projects(const std::vector<uint32_t>& program) {
    uint32_t count = program.empty() ? 0 : program[0] >> 16;
    for (uint32_t n = 0; n < count && program.size() >= 1 + (n + 1) * 4; ++n) {
        uint32_t ilu = get(&program[1 + n * 4], ILU);
        if (ilu == ILU_RCP || ilu == ILU_RCC) return true;
    }
    return false;
}

const char* const g_wide_x_hlsl =
    "float wide_x(float x, float w, float k) {\n"
    "  if (abs(w - 1.0) >= 1e-4) return x;\n"
    "  float f = abs(k), a = abs(x);\n"
    "  bool textured = f > 100; if (textured) f -= 100;\n"
    "  bool keep = k > 0 && a >= 0.995 && (!textured || a <= 1.01);\n"
    "  return keep ? x : x / f;\n"
    "}\n";

std::string vsh_to_hlsl(const std::vector<uint32_t>& program, const std::vector<int>& inputs, std::string& error) {
    if (program.empty()) return error = "empty program", "";
    uint32_t count = program[0] >> 16;
    if (program.size() < 1 + count * 4) return error = "truncated program", "";

    std::string s =
        "cbuffer VS : register(b0) { float4 c[192]; float4 screen; };\n"
        "struct VIn {\n";
    for (int r : inputs) s += "  float4 v" + std::to_string(r) + " : TEXCOORD" + std::to_string(r) + ";\n";
    s += "};\n"
         "struct VOut { float4 pos : SV_Position; float4 d0 : COLOR0; float4 d1 : COLOR1; float4 t0 : TEXCOORD0;\n"
         "  float4 t1 : TEXCOORD1; float4 t2 : TEXCOORD2; float4 t3 : TEXCOORD3; float fog : FOG; };\n"
         "VOut main(VIn i) {\n"
         "  float4 v[16];\n"
         "  [unroll] for (int k = 0; k < 16; ++k) v[k] = float4(0, 0, 0, 1);\n";
    for (int r : inputs) s += "  v[" + std::to_string(r) + "] = i.v" + std::to_string(r) + ";\n";
    s += "  float4 r[12];\n"
         "  [unroll] for (int k = 0; k < 12; ++k) r[k] = float4(0, 0, 0, 0);\n"
         "  int a0 = 0;\n"
         "  float4 oPos = float4(0, 0, 0, 1), oD0 = float4(0, 0, 0, 1), oD1 = float4(0, 0, 0, 1);\n"  // outputs start as XYZ 0, W 1
         "  float4 oFog = float4(1, 1, 1, 1), oPts = float4(1, 1, 1, 1), oB0 = float4(0, 0, 0, 1), oB1 = oD1;\n"
         "  float4 oT0 = float4(0, 0, 0, 1), oT1 = oT0, oT2 = oT0, oT3 = oT0;\n";

    for (uint32_t n = 0; n < count; ++n) {
        const uint32_t* ins = &program[1 + n * 4];
        uint32_t mac = get(ins, MAC), ilu = get(ins, ILU);
        uint32_t c_reg = (get(ins, C_R_HIGH) << 2) | get(ins, C_R_LOW);
        std::string a = input(ins, A_NEG, A_SWZ, get(ins, A_MUX), get(ins, A_R));
        std::string b = input(ins, B_NEG, B_SWZ, get(ins, B_MUX), get(ins, B_R));
        std::string cc = input(ins, C_NEG, C_SWZ, get(ins, C_MUX), c_reg);
        std::string body = "  { // " + std::to_string(n) + "\n";
        // MAC (vector) op on A, B, C
        const char* m = nullptr;
        std::string me;
        switch (mac) {
        case MAC_NOP: break;
        case MAC_MOV: me = a; break;
        case MAC_MUL: me = a + " * " + b; break;
        case MAC_ADD: me = a + " + " + cc; break;
        case MAC_MAD: me = a + " * " + b + " + " + cc; break;
        case MAC_DP3: me = "dot(" + a + ".xyz, " + b + ".xyz).xxxx"; break;
        case MAC_DPH: me = "(dot(" + a + ".xyz, " + b + ".xyz) + " + b + ".w).xxxx"; break;
        case MAC_DP4: me = "dot(" + a + ", " + b + ").xxxx"; break;
        case MAC_DST: me = "float4(1, " + a + ".y * " + b + ".y, " + a + ".z, " + b + ".w)"; break;
        case MAC_MIN: me = "min(" + a + ", " + b + ")"; break;
        case MAC_MAX: me = "max(" + a + ", " + b + ")"; break;
        case MAC_SLT: me = "float4(" + a + " < " + b + ")"; break;
        case MAC_SGE: me = "float4(" + a + " >= " + b + ")"; break;
        case MAC_ARL: body += "    a0 = int(floor(" + a + ".x + 0.001));\n"; break;  // NV2A rounds near-integers up
        default: return error = "MAC op " + std::to_string(mac), "";
        }
        (void)m;
        // ILU (scalar) op on C.x
        std::string ie;
        std::string x = cc + ".x";
        switch (ilu) {
        case ILU_NOP: break;
        case ILU_MOV: ie = cc; break;
        case ILU_RCP: ie = "(1.0 / " + x + ").xxxx"; break;
        case ILU_RCC: ie = "rcc(" + x + ").xxxx"; break;
        case ILU_RSQ: ie = "(1.0 / sqrt(abs(" + x + "))).xxxx"; break;
        case ILU_EXP: ie = "float4(exp2(floor(" + x + ")), frac(" + x + "), exp2(" + x + "), 1)"; break;
        case ILU_LOG: ie = "vlog(" + x + ")"; break;
        case ILU_LIT: ie = "lit_(" + cc + ")"; break;
        default: return error = "ILU op " + std::to_string(ilu), "";
        }
        // inputs are read before anything is written
        if (!me.empty()) body += "    float4 mac = " + me + ";\n";
        if (!ie.empty()) body += "    float4 ilu = " + ie + ";\n";
        uint32_t mac_mask = get(ins, OUT_MAC_MASK), ilu_mask = get(ins, OUT_ILU_MASK), o_mask = get(ins, OUT_O_MASK);
        uint32_t out_r = get(ins, OUT_R);
        if (!me.empty() && mac_mask) {
            std::string dst = out_r == 12 ? "oPos" : "r[" + std::to_string(out_r) + "]";
            body += "    " + dst + mask(mac_mask) + " = mac" + mask(mac_mask) + ";\n";
        }
        if (!ie.empty() && ilu_mask) {  // a paired MAC + ILU instruction puts the ILU temp result in r1 (MAC owns OUT_R)
            uint32_t r = !me.empty() ? 1 : out_r;
            std::string dst = r == 12 ? "oPos" : "r[" + std::to_string(r) + "]";
            body += "    " + dst + mask(ilu_mask) + " = ilu" + mask(ilu_mask) + ";\n";
        }
        if (o_mask) {
            bool from_ilu = get(ins, OUT_MUX);
            if ((from_ilu && ie.empty()) || (!from_ilu && me.empty())) {
                // the selected unit did nothing this instruction: nothing to write
            } else if (!get(ins, OUT_ORB)) {
                return error = "write to constant register", "";
            } else if (const char* o = output_name(get(ins, OUT_ADDRESS))) {
                body += std::string("    ") + o + mask(o_mask) + " = " + (from_ilu ? "ilu" : "mac") + mask(o_mask) + ";\n";
            } else {
                return error = "output register " + std::to_string(get(ins, OUT_ADDRESS)), "";
            }
        }
        s += body + "  }\n";
        if (get(ins, FINAL)) break;
    }
    // oPos is in screen pixels (x, y), depth-buffer units (z) and w; to D3D11 clip space
    s += "  VOut o;\n"
         "  float w = abs(oPos.w) < 1e-10 ? 1.0 : oPos.w;\n"
         "  o.pos = float4(wide_x(oPos.x * screen.x - 1.0, w, screen.w) * w, (1.0 - oPos.y * screen.y) * w, oPos.z * screen.z * w, w);\n"
         "  o.d0 = oD0; o.d1 = oD1; o.t0 = oT0; o.t1 = oT1; o.t2 = oT2; o.t3 = oT3; o.fog = oFog.x;\n"
         "  return o;\n"
         "}\n";
    std::string helpers = std::string(g_wide_x_hlsl) +
        "float rcc(float x) { float r = 1.0 / x; float m = abs(r); m = clamp(m, 5.42101e-20, 1.884467e19);\n"
        "  return r < 0 ? -m : m; }\n"
        "float4 vlog(float x) { float a = abs(x); if (a == 0) return float4(-1e38, 1, -1e38, 1);\n"
        "  float e = floor(log2(a)); return float4(e, a / exp2(e), log2(a), 1); }\n"
        "float4 lit_(float4 s) { float d = max(s.x, 0); float sp = s.x > 0 ? pow(max(s.y, 0), clamp(s.w, -127.9961, 127.9961)) : 0;\n"
        "  return float4(1, d, sp, 1); }\n";
    return helpers + s;
}
