// Xbox pixel shaders (NV2A register combiners, D3DPIXELSHADERDEF) -> HLSL.
//
// D3DPIXELSHADERDEF (0xF0 bytes): AlphaInputs[8] 0x00, FinalInputsABCD 0x20, FinalInputsEFG 0x24,
// Constant0[8] 0x28, Constant1[8] 0x48, AlphaOutputs[8] 0x68, RGBInputs[8] 0x88, CompareMode 0xA8,
// FinalConstant0 0xAC, FinalConstant1 0xB0, RGBOutputs[8] 0xB4, CombinerCount 0xD4, TextureModes 0xD8,
// DotMapping 0xDC, InputTexture 0xE0, C0Mapping 0xE4, C1Mapping 0xE8, FinalCombinerConstants 0xEC.
#include "psh.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

namespace {

uint32_t word(const uint8_t* def, uint32_t off) {
    uint32_t v;
    std::memcpy(&v, def + off, 4);
    return v;
}

std::string color(uint32_t argb) {  // D3DCOLOR constant as an HLSL float4 (r, g, b, a)
    char b[96];
    std::snprintf(b, sizeof b, "float4(%.6f, %.6f, %.6f, %.6f)", ((argb >> 16) & 0xFF) / 255.0, ((argb >> 8) & 0xFF) / 255.0,
                  (argb & 0xFF) / 255.0, (argb >> 24) / 255.0);
    return b;
}

// one combiner input byte: register (bits 0-3), alpha channel (bit 4), mapping (bits 5-7)
std::string input(uint32_t byte, bool alpha_portion, const std::string& c0, const std::string& c1) {
    static const char* regs[16] = {"zero", "C0", "C1", "fog", "v0", "v1", "", "", "t0", "t1", "t2", "t3", "r0", "r1",
                                   "v1r0", "ef"};
    uint32_t reg = byte & 0xF;
    bool alpha = byte & 0x10;
    std::string r = reg == 1 ? c0 : reg == 2 ? c1 : regs[reg];
    if (r.empty()) r = "zero";
    std::string v;
    if (alpha_portion) v = r + (alpha ? ".aaa" : ".bbb");  // alpha portion: blue or alpha, replicated
    else v = r + (alpha ? ".aaa" : ".rgb");
    switch (byte >> 5) {
    case 0: return "max(" + v + ", 0)";                    // unsigned identity
    case 1: return "(1 - saturate(" + v + "))";            // unsigned invert
    case 2: return "(2 * max(" + v + ", 0) - 1)";          // expand normal
    case 3: return "(-2 * max(" + v + ", 0) + 1)";         // expand negate
    case 4: return "(max(" + v + ", 0) - 0.5)";            // half-bias normal
    case 5: return "(-max(" + v + ", 0) + 0.5)";           // half-bias negate
    case 6: return v;                                      // signed identity
    default: return "(-" + v + ")";                        // signed negate
    }
}

const char* dst(uint32_t reg) {  // combiner output register, or nullptr to discard
    switch (reg) {
    case 4: return "v0";
    case 5: return "v1";
    case 8: return "t0";
    case 9: return "t1";
    case 10: return "t2";
    case 11: return "t3";
    case 12: return "r0";
    case 13: return "r1";
    }
    return nullptr;
}

std::string scale(uint32_t mapping, const std::string& x) {  // output mapping, bits 15-17 of the output word
    switch (mapping) {
    case 1: return "(" + x + " - 0.5)";
    case 2: return "(" + x + " * 2)";
    case 3: return "((" + x + " - 0.5) * 2)";
    case 4: return "(" + x + " * 4)";
    case 6: return "(" + x + " * 0.5)";
    }
    return x;
}

// one portion (rgb or alpha) of a general combiner stage
std::string portion(uint32_t in, uint32_t out, bool alpha, const std::string& c0, const std::string& c1, int stage) {
    std::string A = input(in >> 24, alpha, c0, c1), B = input((in >> 16) & 0xFF, alpha, c0, c1);
    std::string C = input((in >> 8) & 0xFF, alpha, c0, c1), D = input(in & 0xFF, alpha, c0, c1);
    std::string p = alpha ? "a" : "c";
    std::string n = std::to_string(stage);
    bool cd_dot = out & 0x1000, ab_dot = out & 0x2000, mux = out & 0x4000;
    uint32_t map = (out >> 15) & 7;
    std::string s;
    std::string ab = ab_dot ? "dot(" + A + ", " + B + ").xxx" : A + " * " + B;
    std::string cd = cd_dot ? "dot(" + C + ", " + D + ").xxx" : C + " * " + D;
    s += "    float3 " + p + "ab" + n + " = clamp(" + scale(map, ab) + ", -1, 1);\n";
    s += "    float3 " + p + "cd" + n + " = clamp(" + scale(map, cd) + ", -1, 1);\n";
    std::string sum = mux ? "(mux ? (" + cd + ") : (" + ab + "))" : "(" + ab + " + " + cd + ")";
    s += "    float3 " + p + "sum" + n + " = clamp(" + scale(map, sum) + ", -1, 1);\n";
    return s;
}

std::string write(uint32_t out, bool alpha, int stage) {
    std::string p = alpha ? "a" : "c", n = std::to_string(stage), s;
    auto put = [&](uint32_t reg, const std::string& v, bool blue_to_alpha) {
        const char* d = dst(reg);
        if (!d) return;
        if (alpha) s += std::string("    ") + d + ".a = " + v + ".x;\n";
        else {
            s += std::string("    ") + d + ".rgb = " + v + ";\n";
            if (blue_to_alpha) s += std::string("    ") + d + ".a = " + v + ".z;\n";
        }
    };
    put((out >> 4) & 0xF, p + "ab" + n, !alpha && (out & 0x80000));
    put(out & 0xF, p + "cd" + n, !alpha && (out & 0x40000));
    put((out >> 8) & 0xF, p + "sum" + n, false);
    return s;
}

}  // namespace

std::string psh_to_hlsl(const uint8_t* def, std::string& error) {
    uint32_t count_word = word(def, 0xD4), stages = count_word & 0xFF;
    uint32_t modes = word(def, 0xD8);
    if (stages > 8) return error = "combiner count " + std::to_string(stages), "";
    std::string s =
        "Texture2D tex0 : register(t0); Texture2D tex1 : register(t1); Texture2D tex2 : register(t2); Texture2D tex3 : register(t3);\n"
        "TextureCube cube0 : register(t4); TextureCube cube1 : register(t5); TextureCube cube2 : register(t6); TextureCube cube3 : register(t7);\n"
        "SamplerState smp0 : register(s0); SamplerState smp1 : register(s1); SamplerState smp2 : register(s2); SamplerState smp3 : register(s3);\n"
        "cbuffer PS : register(b1) { float4 tscale[4]; float4 fog_color; float4 fog_params; float4 alpha_test; };\n"
        "struct VOut { float4 pos : SV_Position; float4 d0 : COLOR0; float4 d1 : COLOR1; float4 t0 : TEXCOORD0;\n"
        "  float4 t1 : TEXCOORD1; float4 t2 : TEXCOORD2; float4 t3 : TEXCOORD3; float fog : FOG; };\n"
        // Catmull-Rom (9 bilinear taps) where a texel covers over 1.5 pixels, so 640x480 art and movies upscale
        // sharp instead of smeared; tscale[k].z = 1 when the stage filters linearly
        "float4 sample2d(Texture2D t, SamplerState s, float2 uv, float4 ts) {\n"
        "  float2 size; t.GetDimensions(size.x, size.y);\n"
        "  float2 dx = ddx(uv), dy = ddy(uv), fw = (abs(dx) + abs(dy)) * size;\n"
        "  [branch] if (ts.z == 0 || max(fw.x, fw.y) > 0.66) return t.SampleGrad(s, uv, dx, dy);\n"
        "  float2 sp = uv * size, p1 = floor(sp - 0.5) + 0.5, f = sp - p1;\n"
        "  float2 w0 = f * (-0.5 + f * (1 - 0.5 * f)), w1 = 1 + f * f * (-2.5 + 1.5 * f);\n"
        "  float2 w2 = f * (0.5 + f * (2 - 1.5 * f)), w3 = f * f * (-0.5 + 0.5 * f), w12 = w1 + w2;\n"
        "  float2 a = (p1 - 1) / size, b = (p1 + w2 / w12) / size, c = (p1 + 2) / size;\n"
        "  float4 r = (t.SampleLevel(s, float2(a.x, a.y), 0) * w0.x + t.SampleLevel(s, float2(b.x, a.y), 0) * w12.x\n"
        "            + t.SampleLevel(s, float2(c.x, a.y), 0) * w3.x) * w0.y\n"
        "          + (t.SampleLevel(s, float2(a.x, b.y), 0) * w0.x + t.SampleLevel(s, float2(b.x, b.y), 0) * w12.x\n"
        "            + t.SampleLevel(s, float2(c.x, b.y), 0) * w3.x) * w12.y\n"
        "          + (t.SampleLevel(s, float2(a.x, c.y), 0) * w0.x + t.SampleLevel(s, float2(b.x, c.y), 0) * w12.x\n"
        "            + t.SampleLevel(s, float2(c.x, c.y), 0) * w3.x) * w3.y;\n"
        "  return saturate(r);\n"
        "}\n"
        "float4 main(VOut i) : SV_Target {\n"
        "  float4 zero = float4(0, 0, 0, 0);\n"
        "  float4 v0 = saturate(i.d0), v1 = saturate(i.d1);\n"
        "  float4 t0 = zero, t1 = zero, t2 = zero, t3 = zero, r0 = zero, r1 = zero;\n"
        // the fog register: colour and the factor D3DRS_FOGENABLE/FOGTABLEMODE make of the vertex shader's oFog.x
        // (fog_params: start, end, density, mode; 1 = no fog)
        "  float d = i.fog, fogf = fog_params.w < 0 ? 1 : fog_params.w == 3 ? (fog_params.y - d) / max(fog_params.y - fog_params.x, 1e-6)\n"
        "    : fog_params.w == 1 ? exp(-d * fog_params.z) : fog_params.w == 2 ? exp(-d * d * fog_params.z * fog_params.z) : d;\n"
        "  float4 fog = float4(fog_color.rgb, saturate(fogf));\n";
    // alpha_test.w: 1 = vertex colours forced white, 2 = textures forced white (OOGIE_PS_DEBUG cycles them)
    s += "  if (alpha_test.w == 1) v0 = float4(1, 1, 1, 1), v1 = float4(0, 0, 0, 1);\n";
    // texture stages: 5 bits each
    for (int k = 0; k < 4; ++k) {
        uint32_t mode = (modes >> (5 * k)) & 0x1F;
        std::string n = std::to_string(k), tc = "i.t" + n;
        switch (mode) {
        case 0: break;  // no texture
        case 1:         // PROJECT2D
        case 2:         // PROJECT3D: no volume textures yet, sampled as 2D
            s += "  t" + n + " = sample2d(tex" + n + ", smp" + n + ", " + tc + ".xy / " + tc + ".w * tscale[" + n + "].xy, tscale[" + n + "]);\n";
            break;
        case 3: s += "  t" + n + " = cube" + n + ".Sample(smp" + n + ", " + tc + ".xyz);\n"; break;
        case 4: s += "  t" + n + " = saturate(" + tc + ");\n"; break;  // PASSTHRU
        default:
            return error = "texture mode " + std::to_string(mode) + " on stage " + n, "";
        }
    }
    s += "  if (alpha_test.w == 2) t0 = float4(1, 1, 1, 1);\n  if (alpha_test.w == 3) t1 = float4(1, 1, 1, 1);\n"
         "  if (alpha_test.w == 4) t2 = t3 = float4(1, 1, 1, 1);\n";
    s += "  r0.a = t0.a;\n";  // NV2A starts r0.a as texture 0's alpha
    bool unique_c0 = count_word & 0x1000, unique_c1 = count_word & 0x10000;
    bool mux_msb = count_word & 0x100;
    for (uint32_t st = 0; st < stages; ++st) {
        std::string c0 = "C0_" + std::to_string(st), c1 = "C1_" + std::to_string(st);
        s += "  {\n";
        s += "    float4 " + c0 + " = " + color(word(def, 0x28 + 4 * (unique_c0 ? st : 0))) + ";\n";
        s += "    float4 " + c1 + " = " + color(word(def, 0x48 + 4 * (unique_c1 ? st : 0))) + ";\n";
        s += mux_msb ? "    bool mux = r0.a >= 0.5;\n" : "    bool mux = frac(r0.a * 255.0 / 2.0) >= 0.5;\n";
        uint32_t rgb_in = word(def, 0x88 + 4 * st), rgb_out = word(def, 0xB4 + 4 * st);
        uint32_t a_in = word(def, 0x00 + 4 * st), a_out = word(def, 0x68 + 4 * st);
        s += portion(rgb_in, rgb_out, false, c0, c1, int(st));
        s += portion(a_in, a_out, true, c0, c1, int(st));
        s += write(rgb_out, false, int(st));  // all results computed before any register is written
        s += write(a_out, true, int(st));
        s += "  }\n";
    }
    // final combiner: rgb = A*B + (1-A)*C + D, alpha = G; E*F and v1+r0 are extra inputs
    uint32_t abcd = word(def, 0x20), efg = word(def, 0x24);
    std::string fc0 = color(word(def, 0xAC)), fc1 = color(word(def, 0xB0));
    s += "  float4 FC0 = " + fc0 + ", FC1 = " + fc1 + ";\n";
    if (!abcd && !efg) {
        s += "  float4 result = r0;\n";  // no final combiner: r0 is the output
    } else {
        auto fin = [&](uint32_t byte, bool alpha) {
            std::string v = input(byte, alpha, "FC0", "FC1");
            return v;
        };
        uint32_t setting = efg & 0xFF;
        s += std::string("  float4 v1s = ") + (setting & 0x40 ? "1 - v1" : "v1") + ";\n";
        s += std::string("  float4 r0s = ") + (setting & 0x20 ? "1 - r0" : "r0") + ";\n";
        s += std::string("  float4 v1r0 = ") + (setting & 0x80 ? "saturate(v1s + r0s)" : "(v1s + r0s)") + ";\n";
        s += "  float4 ef = float4(" + fin(efg >> 24, false) + " * " + fin((efg >> 16) & 0xFF, false) + ", 1);\n";
        s += "  float3 fa = " + fin(abcd >> 24, false) + ", fb = " + fin((abcd >> 16) & 0xFF, false) + ";\n";
        s += "  float3 fc = " + fin((abcd >> 8) & 0xFF, false) + ", fd = " + fin(abcd & 0xFF, false) + ";\n";
        s += "  float4 result = float4(fa * fb + (1 - fa) * fc + fd, " + fin((efg >> 8) & 0xFF, true) + ".x);\n";
    }
    // debugging outputs: 5 = the raw texel of stage 0, 6 = stage 0's texture coordinates, 7 = the vertex colour
    s += "  if (alpha_test.w == 5) result = float4(t0.rgb, 1);\n"
         "  if (alpha_test.w == 6) result = float4(frac(i.t0.xy / i.t0.w), 0, 1);\n"
         "  if (alpha_test.w == 7) result = float4(v0.rgb, 1);\n";
    // alpha test (D3D function 1..8 in alpha_test.y, reference in alpha_test.x, enabled when alpha_test.z)
    s += "  if (alpha_test.z > 0) {\n"
         "    float a = round(saturate(result.a) * 255.0), ref = alpha_test.x;\n"
         "    int f = int(alpha_test.y);\n"
         "    bool ok = f == 8 || (f == 2 && a < ref) || (f == 3 && a == ref) || (f == 4 && a <= ref) ||\n"
         "                (f == 5 && a > ref) || (f == 6 && a != ref) || (f == 7 && a >= ref);\n"
         "    if (!ok) discard;\n"
         "  }\n"
         "  return result;\n"
         "}\n";
    return s;
}
