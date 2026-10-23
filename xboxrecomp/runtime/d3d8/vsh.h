// NV2A vertex shader microcode -> HLSL (vs_5_0).
#pragma once
#include <cstdint>
#include <string>
#include <vector>

// program: the Xbox program as passed to CreateVertexShader ({type, count} header, then 4 DWORDs per
// instruction). inputs: the vertex registers the declaration provides (others read (0,0,0,1)).
// The HLSL reads cbuffer b0 { float4 c[192]; float4 screen (2/w, 2/h, 1/zmax, wide) } (wide: see g_wide_x_hlsl).
// Returns "" and sets error for programs it cannot translate.
// wide_x(x, w, screen.w): a clip-space x on a back buffer wider than 4:3 (screen.w = F, its width over 4:3; 1 elsewhere).
// screen.w = F: an effect (untextured or reading a render target): on or past an edge it stays there. F + 100: textured
// 2D (fonts, HUD): only exactly on an edge, so text sliding in from off screen keeps the 4:3 placement.
// 3D vertices (w != 1) fill the width: the game's projection is widened to match. 2D ones (w = 1) keep 4:3 in the
// middle, except those on or past the screen's edges (full-screen fades, effects and the game's edge masks); screen.w < 0 (a picture: movie or art) keeps
// every 2D vertex 4:3.
extern const char* const g_wide_x_hlsl;
// True when the program takes a reciprocal (the XDK's perspective divide to screen space): a 3D shader. The game's 2D
// shaders pass screen positions through.
bool vsh_projects(const std::vector<uint32_t>& program);
std::string vsh_to_hlsl(const std::vector<uint32_t>& program, const std::vector<int>& inputs, std::string& error);
