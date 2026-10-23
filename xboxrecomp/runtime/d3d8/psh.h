// Xbox register-combiner pixel shaders (D3DPIXELSHADERDEF) -> HLSL (ps_5_0).
#pragma once
#include <cstdint>
#include <string>

// def: the 0xF0-byte D3DPIXELSHADERDEF. The HLSL samples tex0..3 / cube0..3 with smp0..3 and reads
// cbuffer b1 { float4 tscale[4] (xy texcoord scale, z 1 = linear filter); float4 fog_color; float4 alpha_test (ref, D3DCMP func, enabled, 0) }.
// Returns "" and sets error for definitions it cannot translate.
std::string psh_to_hlsl(const uint8_t* def, std::string& error);
