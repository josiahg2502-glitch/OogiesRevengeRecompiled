// Xbox Direct3D 8 (XDK 5849), replaced: the game-facing API on top of the host renderer.
//
// Resources stay in the Xbox's own layout in guest memory, because the game also builds texture and
// vertex buffer headers itself (XGSetTextureHeader) and reads them back:
//   D3DResource       { Common, Data, Lock }            Common = refcount | type | flags
//   D3DPixelContainer { ..., Format, Size }              Data = physical address of the pixels
//   D3DSurface        { ..., Parent }
#include <windows.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../hle.h"
#include "../kernel.h"
#include "../menu/menu.h"
#include "renderer.h"
#include "psh.h"
#include "texture.h"
#include "vsh.h"

namespace {

constexpr u32 D3D_OK = 0;
constexpr u32 COMMON_REFCOUNT = 0xFFFF, COMMON_TYPE_MASK = 0x00070000, COMMON_D3DCREATED = 0x01000000;
constexpr u32 TYPE_VERTEXBUFFER = 0x00000000, TYPE_TEXTURE = 0x00040000, TYPE_SURFACE = 0x00050000;
constexpr u32 D3D_g_pDevice = 0x001E25E8;  // XbSymbolDatabase: D3D8__VAR__D3D_g_pDevice

// ---- formats ----
struct Format {
    u8 bytes;      // per pixel, or per 4x4 block when compressed
    bool linear;   // pitch-linear rather than swizzled
    bool compressed;
};

Format format_info(u32 f) {
    switch (f) {
    case 0x00: case 0x01: case 0x0B: case 0x19: return {1, false, false};             // L8 AL8 P8 A8
    case 0x02: case 0x03: case 0x04: case 0x05: case 0x1A: case 0x27: case 0x28:
    case 0x29: case 0x2C: case 0x2D: case 0x32: case 0x38: return {2, false, false};  // 16-bit swizzled
    case 0x06: case 0x07: case 0x2A: case 0x2B: case 0x33: case 0x40: case 0x41: case 0x42:
    case 0x43: case 0x44: return {4, false, false};                                   // 32-bit swizzled
    case 0x0C: return {8, false, true};                                                // DXT1
    case 0x0E: case 0x0F: return {16, false, true};                                    // DXT3, DXT5
    case 0x13: case 0x1B: case 0x1F: return {1, true, false};                          // LIN_L8 AL8 A8
    case 0x10: case 0x11: case 0x16: case 0x17: case 0x1C: case 0x1D: case 0x20: case 0x24: case 0x25:
    case 0x30: case 0x31: case 0x35: case 0x37: return {2, true, false};               // 16-bit linear
    case 0x12: case 0x1E: case 0x2E: case 0x2F: case 0x36: case 0x3F: return {4, true, false};  // 32-bit linear
    }
    fatal("unknown Xbox texture format %02X", f);
}

u32 gpu_va(u32 data) { return data < 0x08000000 ? CONTIGUOUS_BASE | data : data; }  // Data holds physical addresses
u32 phys(u32 va) { return va >= CONTIGUOUS_BASE && va < CONTIGUOUS_BASE + RAM_SIZE ? va - CONTIGUOUS_BASE : va; }

// Width, height and pitch of a pixel container (texture or surface) as the GPU sees it.
struct Dims {
    u32 format, width, height, depth, levels, pitch;
};

Dims dims(u32 res) {
    u32 fmt = ld<u32>(res + 12), size = ld<u32>(res + 16);
    Dims d;
    d.format = (fmt >> 8) & 0xFF;
    if (size) {  // linear: sizes in the Size field
        d.width = (size & 0xFFF) + 1, d.height = ((size >> 12) & 0xFFF) + 1, d.pitch = (((size >> 24) & 0xFF) + 1) * 64;
        d.depth = 1, d.levels = 1;
    } else {  // swizzled: log2 sizes in the Format field
        d.width = 1u << ((fmt >> 20) & 0xF), d.height = 1u << ((fmt >> 24) & 0xF), d.depth = 1u << ((fmt >> 28) & 0xF);
        d.levels = (fmt >> 16) & 0xF;
        Format f = format_info(d.format);
        d.pitch = f.compressed ? ((d.width + 3) / 4) * f.bytes : d.width * f.bytes;
    }
    return d;
}

u32 level_bytes(const Format& f, u32 w, u32 h, u32 d) {
    if (f.compressed) return ((w + 3) / 4) * ((h + 3) / 4) * f.bytes * d;
    return w * h * d * f.bytes;
}

// offset of a mip level inside a swizzled texture
u32 level_offset(const Dims& d, u32 level) {
    Format f = format_info(d.format);
    u32 off = 0;
    for (u32 l = 0; l < level; ++l)
        off += level_bytes(f, std::max(1u, d.width >> l), std::max(1u, d.height >> l), std::max(1u, d.depth >> l));
    return off;
}

u32 log2u(u32 v) {
    u32 r = 0;
    while ((1u << r) < v) ++r;
    return r;
}

// The "simple" render states as NV2A methods (subchannel 0, below 0x2000) -> last value written. A flat array:
// draw() reads ~40 of them per draw. ps_version changes when a pixel shader (combiner) register is written.
struct RenderStates {
    u32 value[0x800] = {};
    bool set[0x800] = {};
    u64 ps_version = 1;
    static bool combiner(u32 m) {  // NV097 combiner registers that make up the pixel shader
        return (m >= 0x260 && m <= 0x28C) || (m >= 0xA60 && m <= 0xADC) || m == 0x17F8 || (m >= 0x1E20 && m <= 0x1E78);
    }
    void put(u32 header, u32 v) {  // header: the push-buffer method word (0x40000 | method)
        u32 m = header & 0x1FFC;
        if (combiner(m)) ++ps_version;
        value[m >> 2] = v, set[m >> 2] = true;
    }
    std::string text() const {  // " 4MMMM=VVVVVVVV" for every state written (debug dumps)
        std::string out;
        for (u32 i = 0; i < 0x800; ++i)
            if (set[i]) {
                char b[32];
                std::snprintf(b, sizeof b, " %05X=%08X", 0x40000 | (i << 2), value[i]);
                out += b;
            }
        return out;
    }
};

// ---- device state the game can read back ----
struct State {
    u32 device = 0;
    u32 width = 640, height = 480;
    u32 backbuffer = 0, depth = 0, render_target = 0, zbuffer = 0;
    std::map<u32, std::array<float, 16>> transforms;
    struct {
        u32 x = 0, y = 0, w = 640, h = 480;
        float minz = 0, maxz = 1;
    } vp;                                  // the viewport, clamped to the render target as the XDK keeps it
    u32 rt_width = 640, rt_height = 480;  // size of the current render target
    float zscale = 16777215.f;            // depth-buffer units of the current z surface (the XDK's D3D__ZScale)
    u32 scissor_count = 0, scissor_exclusive = 0;
    std::vector<u8> scissor_rects;
    u8 tiles[8][24] = {};
    u32 textures[4] = {};
    u32 vertex_shader = 0, pixel_shader = 0, pixel_shader_def = 0, shader_constant_mode = 0;
    float vs_constants[192][4] = {};
    u64 vs_version = 1;  // bumped on every write to vs_constants (the renderer re-sends them then)
    RenderStates render_states;
    u32 cull_mode = 0, z_enable = 0, stencil_enable = 0, stencil_fail = 0, fog_color = 0, multisample = 0;
    u32 tex_coord_index[4] = {};
    struct Stream {
        u32 vb, stride;
    } streams[16] = {};
    float screen_offset[2] = {};
    u32 vblank_callback = 0, swap_callback = 0;
    u32 vblank_count = 0, swap_count = 0;
    u64 draws = 0, clears = 0, vblank_waits = 0;
    u64 draw_ns = 0;  // host time spent in draw(): the HLE's own cost per frame
    u64 offscreen_draws = 0;
    u64 pack_ns = 0, hash_ns = 0, gfx_ns = 0;  // parts of draw_ns: vertex packing, texture hashing, host API
} g;

// Frames that draw no 3D world into the back buffer (menus, the title, movies, loading screens): on a wide back buffer
// every 2D draw keeps one 4:3 placement (no edge stretching, so tiled art stays whole) and the renderer fills the sides.
// Decided by the frame before, as a draw cannot know what the rest of its frame will draw.
bool g_frame_3d = true, g_last_frame_3d = true;
// The ambient occlusion pass goes between the 3D world and the 2D layer. The game puts 2D effects between its world
// and its characters too, so the pass waits until as many 3D depth-writing draws as the frame before had (characters
// included) have been made; a frame that never gets there goes without (rather than darkening the HUD).
bool g_occlusion_done;
u32 g_world_draws, g_last_world_draws;
u32 g_boundaries, g_last_boundaries;  // 3D-to-2D turns into the back buffer this frame / the frame before
bool g_3d_since_boundary;

struct ScopedNs {  // adds the scope's duration to a counter
    u64& acc;
    std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
    explicit ScopedNs(u64& a) : acc(a) {}
    ~ScopedNs() { acc += u64((std::chrono::steady_clock::now() - t0).count()); }
};

// Vertex/pixel shaders: the guest gets a handle; the tokens are kept for the HLSL translator.
struct VertexShader {
    std::vector<u32> declaration, function;
};
std::unordered_map<u32, VertexShader> g_vertex_shaders;  // handle -> shader
std::unordered_map<u32, std::vector<u8>> g_pixel_shaders;   // handle -> D3DPIXELSHADERDEF copy

u32 new_resource(u32 size, u32 type, u32 data) {
    u32 r = kalloc(size);
    st<u32>(r, 1 | type | COMMON_D3DCREATED);
    st<u32>(r + 4, data);
    return r;
}

u32 add_ref(u32 res) {
    if (!res) return 0;
    u32 common = ld<u32>(res);
    u32 count = (common & COMMON_REFCOUNT) + 1;
    st<u32>(res, (common & ~COMMON_REFCOUNT) | (count & COMMON_REFCOUNT));
    return count;
}

// A linear surface over existing pixels.
u32 new_surface(u32 data, u32 format, u32 width, u32 height, u32 pitch, u32 parent) {
    u32 s = new_resource(0x18, TYPE_SURFACE, data);
    st<u32>(s + 12, 1 | (2 << 4) | (format << 8));  // DMA channel A, 2D
    st<u32>(s + 16, (width - 1) | ((height - 1) << 12) | ((pitch / 64 - 1) << 24));
    st<u32>(s + 20, parent);
    return s;
}

// The XDK's SetViewport feeds hardware constants 58 (viewport scale) and 59 (viewport offset) through
// NV097_SET_VIEWPORT_SCALE/OFFSET: scale = (W/2, -H/2, (MaxZ-MinZ)*zscale, 0) and
// offset = (X + W/2 + ssx, Y + H/2 + ssy, MinZ*zscale, 0); vertex programs use them to reach screen space.
void update_viewport_constants() {
    auto& v = g.vp;
    float scale[4] = {v.w * 0.5f, -float(v.h) * 0.5f, (v.maxz - v.minz) * g.zscale, 0};
    float offset[4] = {v.x + v.w * 0.5f + g.screen_offset[0], v.y + v.h * 0.5f + g.screen_offset[1], v.minz * g.zscale, 0};
    std::memcpy(g.vs_constants[58], scale, 16), std::memcpy(g.vs_constants[59], offset, 16), ++g.vs_version;
}

void set_viewport(u32 x, u32 y, u32 w, u32 h, float minz, float maxz) {
    // clamped to the target as the XDK does: the right/bottom edges stop at the surface
    x = std::min(x, g.rt_width), y = std::min(y, g.rt_height);
    u32 right = std::min(x + w, g.rt_width), bottom = std::min(y + h, g.rt_height);
    g.vp = {x, y, right - x, bottom - y, minz, maxz};
    update_viewport_constants();
}

void once(const char* name) {
    static std::unordered_map<std::string, bool> seen;
    if (!seen[name]) {
        seen[name] = true;
        std::fprintf(stderr, "[d3d] %s\n", name);  // the first of each kind
    }
}

// ---- vertical blank: a 60 Hz guest thread, like the Xbox's GPU interrupt + DPC ----
std::chrono::steady_clock::time_point g_next_vblank;
HANDLE g_vblank_event = CreateEventW(nullptr, FALSE, FALSE, nullptr);  // set at every guest vblank

void wait_vblank_after(u32 count) {  // with the guest lock released
    while (g.vblank_count == count) WaitForSingleObject(g_vblank_event, 20);
}

void vblank_thread() {
    Ctx c;
    thread_setup(c, 0x10000, 0);
    auto period = std::chrono::nanoseconds(1000000000ll * 1001 / 60000);  // NTSC 59.94 Hz
    g_next_vblank = std::chrono::steady_clock::now() + period;
    auto last = std::chrono::steady_clock::now();
    auto distrust_until = last;  // until then the display does not pace the game
    for (;;) {
        // a display that is off or asleep answers WaitForVBlank at once: those "vblanks" would run the game
        // (one step per vblank) many times too fast, so one sooner than 3/4 of a frame waits for the clock.
        // Asleep it can also answer at about 30 Hz (the game at half speed): one later than 1.5 frames hands the
        // pacing to the clock for 2 s, then the display is tried again.
        bool display = last >= distrust_until && gfx_wait_vblank();
        auto waited = std::chrono::steady_clock::now() - last;
        if (display && waited > period * 3 / 2) distrust_until = std::chrono::steady_clock::now() + std::chrono::seconds(2);
        if (display && waited >= period * 3 / 4 && waited <= period * 3 / 2) {
            g_next_vblank = std::chrono::steady_clock::now() + period;
        } else {
            if (g_next_vblank < last + period * 3 / 4) g_next_vblank = last + period;
            std::this_thread::sleep_until(g_next_vblank);
            g_next_vblank += period;
            if (std::chrono::steady_clock::now() > g_next_vblank) g_next_vblank = std::chrono::steady_clock::now() + period;
        }
        last = std::chrono::steady_clock::now();
        guest_lock();
        ++g.vblank_count;
        SetEvent(g_vblank_event);
        if (g.vblank_callback) {
            u32 data = c.esp - 64;  // D3DVBLANKDATA { VBlank, Swap, Flags } below the stack top
            c.esp -= 64;
            st<u32>(data, g.vblank_count), st<u32>(data + 4, g.swap_count), st<u32>(data + 8, 0);
            st<u8>(c.fs_base + KPCR_IRQL, 2);
            static const bool slow_log = std::getenv("OOGIE_HITCH_TRACE") != nullptr;  // testing
            auto t0 = std::chrono::steady_clock::now();
            call_guest(c, g.vblank_callback, {data});
            if (double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count(); slow_log && ms > 5)
                std::fprintf(stderr, "[slow] vblank callback took %.1f ms\n", ms);
            st<u8>(c.fs_base + KPCR_IRQL, 0);
            c.esp += 64;
        }
        signal_any();
        guest_unlock();
    }
}

}  // namespace

// ---- device ----
HLE(Direct3D_CreateDevice) {
    u32 pp = sarg(c, 4), out = sarg(c, 5);
    g.width = ld<u32>(pp) ? ld<u32>(pp) : 640;
    g.height = ld<u32>(pp + 4) ? ld<u32>(pp + 4) : 480;
    std::fprintf(stderr, "[d3d] CreateDevice %ux%u format %02X buffers %u multisample %08X flags %08X interval %08X\n",
                 g.width, g.height, ld<u32>(pp + 8), ld<u32>(pp + 12), ld<u32>(pp + 16), ld<u32>(pp + 0x28),
                 ld<u32>(pp + 0x30));
    gfx_init(g.width, g.height);

    // the device the game holds; D3D's own code finds it through D3D_g_pDevice
    g.device = kalloc(0x24A0);  // sizeof(CDevice): Direct3D_CreateDevice clears 0x928 dwords
    st<u32>(D3D_g_pDevice, g.device);
    st<u32>(out, g.device);

    u32 pitch = (g.width * 4 + 63) & ~63u;
    g.backbuffer = new_surface(phys(contiguous_alloc(pitch * g.height, 0x1000)), 0x1E, g.width, g.height, pitch, 0);
    g.depth = new_surface(phys(contiguous_alloc(pitch * g.height, 0x1000)), 0x2E, g.width, g.height, pitch, 0);
    g.render_target = g.backbuffer, g.zbuffer = g.depth;
    g.rt_width = g.width, g.rt_height = g.height;
    set_viewport(0, 0, g.width, g.height, 0, 1);
    std::thread(vblank_thread).detach();
    return D3D_OK;
}
HLE_REGISTER(Direct3D_CreateDevice)

// Clears some of the colour channels (Xbox D3DCLEAR_TARGET_R/G/B/A = 0x10/0x20/0x40/0x80): a full-screen quad of
// the colour with the other channels write-masked. The game clears only alpha before its destination-alpha effects.
static void clear_channels(u32 flags, u32 argb, const std::vector<GfxRect>& rects) {
    static int vs = -2, ps = -2;
    if (vs == -2) {
        vs = gfx_vertex_shader(
            "struct VIn { float4 v0 : TEXCOORD0; float4 v3 : TEXCOORD3; };\n"
            "struct VOut { float4 pos : SV_Position; float4 d0 : COLOR0; float4 d1 : COLOR1; float4 t0 : TEXCOORD0;\n"
            "  float4 t1 : TEXCOORD1; float4 t2 : TEXCOORD2; float4 t3 : TEXCOORD3; float fog : FOG; };\n"
            "VOut main(VIn i) { VOut o = (VOut)0; o.pos = i.v0; o.d0 = i.v3; return o; }\n",
            {0, 3});
        ps = gfx_pixel_shader(
            "struct VOut { float4 pos : SV_Position; float4 d0 : COLOR0; float4 d1 : COLOR1; float4 t0 : TEXCOORD0;\n"
            "  float4 t1 : TEXCOORD1; float4 t2 : TEXCOORD2; float4 t3 : TEXCOORD3; float fog : FOG; };\n"
            "float4 main(VOut i) : SV_Target { return i.d0; }\n");
    }
    if (vs < 0 || ps < 0) return;
    GfxState s;
    s.vs = vs, s.ps = ps;
    s.color_mask = (flags & 0x80 ? 0x01000000 : 0) | (flags & 0x10 ? 0x10000 : 0) | (flags & 0x20 ? 0x100 : 0) | (flags & 0x40 ? 1 : 0);
    float r = ((argb >> 16) & 0xFF) / 255.f, gr = ((argb >> 8) & 0xFF) / 255.f, b = (argb & 0xFF) / 255.f, a = (argb >> 24) / 255.f;
    float quad[4][8] = {{-1, -1, 0, 1, r, gr, b, a}, {-1, 1, 0, 1, r, gr, b, a}, {1, -1, 0, 1, r, gr, b, a}, {1, 1, 0, 1, r, gr, b, a}};
    if (rects.empty()) return gfx_draw(s, 5, &quad[0][0], 4, 8, nullptr, 0);
    for (const GfxRect& rect : rects) s.scissor = true, s.scissor_rect = rect, gfx_draw(s, 5, &quad[0][0], 4, 8, nullptr, 0);
}

HLE(D3DDevice_Clear) {
    ++g.clears;
    u32 count = sarg(c, 0), rects = sarg(c, 1), flags = sarg(c, 2), color = sarg(c, 3), stencil = sarg(c, 5);
    float z = sargf(c, 4);
    std::vector<GfxRect> r(rects ? count : 0);
    if (rects) std::memcpy(r.data(), g_mem + rects, count * sizeof(GfxRect));
    static u32 last = 0x12345678;
    if (g_trace && color != last) trace("[d3d] clear color %08X flags %X", color, flags), last = color;
    if ((flags & 0xF0) && (flags & 0xF0) != 0xF0) clear_channels(flags, color, r), flags &= ~0xF0u;
    gfx_clear(flags, color, z, stencil, rects ? r.data() : nullptr, rects ? count : 0);
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_Clear)

namespace {
}
HLE(D3DDevice_Swap) {
    {  // OOGIE_FRAME_LOG=first,count: per present: draws and clears since the last one, caller, guest thread
        static const char* fl = std::getenv("OOGIE_FRAME_LOG");
        static u64 last_draws, last_clears, last_waits;
        if (fl) {
            unsigned first = 0, count = 0;
            std::sscanf(fl, "%u,%u", &first, &count);
            if (g.swap_count >= first && g.swap_count < first + count)
                std::fprintf(stderr, "[frame] %u: %llu draws, %llu clears, %llu vblank waits, guest vblank %u\n",
                             g.swap_count, (unsigned long long)(g.draws - last_draws),
                             (unsigned long long)(g.clears - last_clears),
                             (unsigned long long)(g.vblank_waits - last_waits), g.vblank_count);
            last_draws = g.draws, last_clears = g.clears, last_waits = g.vblank_waits;
        }
    }
    gfx_pump();
    g_last_world_draws = g_world_draws, g_world_draws = 0, g_occlusion_done = false;
    g_last_boundaries = g_boundaries, g_boundaries = 0, g_3d_since_boundary = false;
    gfx_flat_frame(!g_frame_3d);  // a 2D-only frame: the renderer fills the wide sides
    g_last_frame_3d = g_frame_3d, g_frame_3d = false;
    // presentation interval ONE (the game's): the flip waits for a vertical blank, so at most one frame per vblank
    static u32 last_flip;
    guest_unlock();  // let the other guest threads run meanwhile
    wait_vblank_after(last_flip);
    guest_lock();
    // presented with the lock held: other guest threads draw and upload too (Bink's decoder sends movie frames), and two
    // threads in the Direct3D 11 context at once crash it (d3d11.dll access violations at movie start)
    gfx_present();
    last_flip = g.vblank_count;
    ++g.swap_count;
    // F1: the in-game menu, over this frame, with the guest lock held (every guest thread waits, the sound holds)
    static const u32 menu_at = std::getenv("OOGIE_MENU_AT") ? u32(std::atoi(std::getenv("OOGIE_MENU_AT"))) : 0;  // testing
    bool paused = gfx_menu_requested() || g.swap_count == menu_at;
    if (paused) menu_overlay();
    if (const char* snap = std::getenv("OOGIE_SNAP")) g_trace_d3d_now = g.swap_count == u32(std::strtoul(snap, nullptr, 10));
    if (g.swap_callback) {
        u32 data = c.esp - 64;  // D3DSWAPDATA below our stack
        u32 sp = c.esp;
        c.esp -= 64;
        st<u32>(data, g.swap_count), st<u32>(data + 4, g.vblank_count);
        st<u32>(data + 8, 0), st<u32>(data + 12, 0), st<u32>(data + 16, 16);
        call_guest(c, g.swap_callback, {data});
        c.esp = sp;
    }
    static auto last = std::chrono::steady_clock::now(), prev = last;
    static u32 frames, hitches;
    static double worst;
    auto now = std::chrono::steady_clock::now();
    double ms = paused ? 0 : std::chrono::duration<double, std::milli>(now - prev).count();
    prev = now;
    worst = ms > worst ? ms : worst;
    hitches += ms > 25;  // a frame shown for 2+ refreshes: visible stutter
    {  // a long frame names its likely cause: our draw work, shader compiles or file reads
        static u64 draw_ns, compiles, compile_ns, io_ns;
        if (ms > 40 && g.swap_count > 1)
            std::fprintf(stderr, "[hitch] frame %u took %.0f ms: draw() %.1f ms, %llu shader compiles %.1f ms, file io %.1f ms\n", g.swap_count, ms,
                         (g.draw_ns - draw_ns) / 1e6, (unsigned long long)(g_shader_compiles - compiles), (g_shader_compile_ns - compile_ns) / 1e6,
                         (g_io_ns - io_ns) / 1e6);
        static const bool slices = std::getenv("OOGIE_HITCH_TRACE") != nullptr;
        static auto frame_start = now;
        if (slices) {  // the guest threads that ran during this frame (thread(priority)@start+duration, ms from the last present)
            std::string s = guest_slices_since(frame_start);
            if (ms > 25 && g.swap_count > 1) std::fprintf(stderr, "[slices] frame %u took %.1f ms:%s\n", g.swap_count, ms, s.c_str());
            frame_start = now;
        }
        draw_ns = g.draw_ns, compiles = g_shader_compiles, compile_ns = g_shader_compile_ns, io_ns = g_io_ns;
    }
    if (++frames == 120) {
        double s = std::chrono::duration<double>(now - last).count();
        std::string threads = guest_cpu_report();
        static u32 last_vblank;
        static u64 last_draws, last_draw_ns, last_offscreen, last_pack, last_hash, last_gfx, last_io_bytes, last_io_ns;
        std::fprintf(stderr,
                     "[d3d] %.1f fps, worst frame %.1f ms, %u hitches, %.1f vblanks/s, %llu draws/frame (%llu offscreen), "
                     "%.1f ms/frame in draw() (pack %.1f, hash %.1f, gfx %.1f), io %.1f MB in %.0f ms, threads%s\n",
                     frames / s, worst, hitches, (g.vblank_count - last_vblank) / s,
                     (unsigned long long)((g.draws - last_draws) / frames),
                     (unsigned long long)((g.offscreen_draws - last_offscreen) / frames), (g.draw_ns - last_draw_ns) / 1e6 / frames,
                     (g.pack_ns - last_pack) / 1e6 / frames, (g.hash_ns - last_hash) / 1e6 / frames, (g.gfx_ns - last_gfx) / 1e6 / frames,
                     (g_io_bytes - last_io_bytes) / 1048576.0, (g_io_ns - last_io_ns) / 1e6, threads.c_str());
        last_vblank = g.vblank_count, last_draws = g.draws, last_draw_ns = g.draw_ns, last_offscreen = g.offscreen_draws;
        last_pack = g.pack_ns, last_hash = g.hash_ns, last_gfx = g.gfx_ns, last_io_bytes = g_io_bytes, last_io_ns = g_io_ns;
        last = now, frames = 0, hitches = 0, worst = 0;
        std::fflush(stderr);  // the log goes out in one write every 2 s (see main: stderr is buffered)
    }
    return g.swap_count;
}
HLE_REGISTER(D3DDevice_Swap)

HLE(D3DDevice_BlockUntilVerticalBlank) {
    ++g.vblank_waits;
    gfx_pump();
    u32 start = g.vblank_count;
    guest_unlock();
    wait_vblank_after(start);
    guest_lock();
    return 0;
}
HLE_REGISTER(D3DDevice_BlockUntilVerticalBlank)

HLE(D3DDevice_SetVerticalBlankCallback) { return g.vblank_callback = sarg(c, 0), 0; }
HLE_REGISTER(D3DDevice_SetVerticalBlankCallback)
HLE(D3DDevice_SetSwapCallback) { return g.swap_callback = sarg(c, 0), 0; }
HLE_REGISTER(D3DDevice_SetSwapCallback)
// shortcut: gamma ramp ignored; this game's last ramp (set once at startup) is the identity, upgrade if another sets one
HLE(D3DDevice_SetGammaRamp) { return 0; }
HLE_REGISTER(D3DDevice_SetGammaRamp)

// ---- render targets ----
HLE(D3DDevice_GetBackBuffer2) {
    add_ref(g.backbuffer);
    return g.backbuffer;  // index -1 (front buffer) gets the same surface
}
HLE_REGISTER(D3DDevice_GetBackBuffer2)
HLE(D3DDevice_GetRenderTarget2) {
    add_ref(g.render_target);
    return g.render_target;
}
HLE_REGISTER(D3DDevice_GetRenderTarget2)
HLE(D3DDevice_GetDepthStencilSurface2) {
    add_ref(g.zbuffer);
    return g.zbuffer;
}
HLE_REGISTER(D3DDevice_GetDepthStencilSurface2)
static std::string surface_desc(u32 s) {
    if (!s) return "null";
    u32 fmt = ld<u32>(s + 12), size = ld<u32>(s + 16);
    char buf[96];
    if (size)
        std::snprintf(buf, sizeof buf, "%08X fmt %02X %ux%u linear", s, (fmt >> 8) & 0xFF, (size & 0xFFF) + 1,
                      ((size >> 12) & 0xFFF) + 1);
    else
        std::snprintf(buf, sizeof buf, "%08X fmt %02X %ux%u swizzled", s, (fmt >> 8) & 0xFF, 1u << ((fmt >> 20) & 0xF),
                      1u << ((fmt >> 24) & 0xF));
    return buf;
}
namespace {
int render_texture(u32 surface);  // the host texture a guest surface renders into (with the texture cache)
}
HLE(D3DDevice_SetRenderTarget) {
    u32 target = sarg(c, 0), z = sarg(c, 1);
    if (target) g.render_target = target;
    g.zbuffer = z;
    if (z) {  // the XDK keeps the old z scale when no depth surface comes along
        u32 zfmt = (ld<u32>(z + 12) >> 8) & 0xFF;
        g.zscale = zfmt == 0x2C || zfmt == 0x30 ? 65535.f : 16777215.f;  // D16 or D24
    }
    Dims d = dims(g.render_target);
    g.rt_width = d.width, g.rt_height = d.height;
    if (g.render_target == g.backbuffer) gfx_set_render_target(-1, true);
    else gfx_set_render_target(render_texture(g.render_target), z != 0);
    set_viewport(0, 0, g.rt_width, g.rt_height, 0, 1);  // the XDK resets the viewport to the whole target
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_SetRenderTarget)
namespace {
int host_surface(u32 surface);  // the host side of a surface that is drawn or copied into
}
HLE(D3DDevice_CopyRects) {  // (pSourceSurface, pSourceRectsArray, cRects, pDestinationSurface, pDestPointsArray)
    u32 src = sarg(c, 0), rects = sarg(c, 1), count = sarg(c, 2), dst = sarg(c, 3), points = sarg(c, 4);
    once(("CopyRects " + surface_desc(src) + " -> " + surface_desc(dst) + " rects " + std::to_string(count)).c_str());
    int from = host_surface(src), to = host_surface(dst);
    if (!count) return gfx_copy(from, to, nullptr, 0, 0), D3D_OK;
    for (u32 k = 0; k < count; ++k) {
        GfxRect r;
        std::memcpy(&r, g_mem + rects + 16 * k, 16);
        s32 x = points ? s32(ld<u32>(points + 8 * k)) : 0, y = points ? s32(ld<u32>(points + 8 * k + 4)) : 0;
        gfx_copy(from, to, &r, x, y);
    }
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_CopyRects)

HLE(D3DSurface_GetDesc) {
    u32 s = sarg(c, 0), out = sarg(c, 1);
    Dims d = dims(s);
    Format f = format_info(d.format);
    st<u32>(out, d.format);                           // Format
    st<u32>(out + 4, 1);                              // Type: D3DRTYPE_SURFACE
    bool depth = (d.format >= 0x2A && d.format <= 0x2C) || (d.format >= 0x2E && d.format <= 0x31);  // D24S8, F24S8, D16, F16 (+LIN_)
    st<u32>(out + 8, depth ? 2 : s == g.backbuffer || s == g.render_target ? 1 : 0);  // Usage: DEPTHSTENCIL / RENDERTARGET
    st<u32>(out + 12, level_bytes(f, d.width, d.height, 1));
    st<u32>(out + 16, 0x11);                          // MultiSampleType: D3DMULTISAMPLE_NONE on Xbox
    st<u32>(out + 20, d.width), st<u32>(out + 24, d.height);
    return D3D_OK;
}
HLE_REGISTER(D3DSurface_GetDesc)

// ---- resources ----
HLE(D3DResource_AddRef) { return add_ref(sarg(c, 0)); }
HLE_REGISTER(D3DResource_AddRef)
HLE(D3DResource_Release) {
    u32 res = sarg(c, 0), common = ld<u32>(res);
    u32 count = common & COMMON_REFCOUNT;
    if (count) --count;
    st<u32>(res, (common & ~COMMON_REFCOUNT) | count);
    return count;  // shortcut: memory is not reclaimed at zero (bump allocators); fine until it runs out
}
HLE_REGISTER(D3DResource_Release)
HLE(D3DResource_BlockUntilNotBusy) { return 0; }
HLE_REGISTER(D3DResource_BlockUntilNotBusy)

HLE(D3DDevice_CreateTexture2) {
    u32 w = sarg(c, 0), h = sarg(c, 1), depth = sarg(c, 2), levels = sarg(c, 3), format = sarg(c, 5),
        type = sarg(c, 6);
    if (!depth) depth = 1;
    Format f = format_info(format);
    u32 tex = new_resource(0x14, TYPE_TEXTURE, 0);
    u32 bytes = 0;
    if (f.linear) {
        u32 pitch = (w * f.bytes + 63) & ~63u;
        bytes = pitch * h;
        st<u32>(tex + 12, 1 | (2 << 4) | (format << 8) | (1 << 16));
        st<u32>(tex + 16, (w - 1) | ((h - 1) << 12) | ((pitch / 64 - 1) << 24));
    } else {
        if (!levels) levels = log2u(std::max(w, h)) + 1;
        u32 dim = type == 4 ? 3 : 2;  // D3DRTYPE_VOLUMETEXTURE
        st<u32>(tex + 12, 1 | (type == 5 ? 4 : 0) | (dim << 4) | (format << 8) | ((levels & 0xF) << 16) |
                              (log2u(w) << 20) | (log2u(h) << 24) | (log2u(depth) << 28));
        Dims d = dims(tex);
        bytes = level_offset(d, levels) * (type == 5 ? 6 : 1);
    }
    st<u32>(tex + 4, phys(contiguous_alloc((bytes + 127) & ~127u, 128)));
    return tex;
}
HLE_REGISTER(D3DDevice_CreateTexture2)

HLE(D3DTexture_GetSurfaceLevel2) {
    u32 tex = sarg(c, 0), level = sarg(c, 1);
    Dims d = dims(tex);
    Format f = format_info(d.format);
    u32 w = std::max(1u, d.width >> level), h = std::max(1u, d.height >> level);
    u32 s = new_resource(0x18, TYPE_SURFACE, ld<u32>(tex + 4) + (f.linear ? 0 : level_offset(d, level)));
    // a surface of a swizzled texture keeps the swizzled format with the level's log2 size
    if (f.linear) {
        st<u32>(s + 12, ld<u32>(tex + 12));
        st<u32>(s + 16, ld<u32>(tex + 16));
    } else {
        st<u32>(s + 12, (ld<u32>(tex + 12) & 0x0000FFFF) | (1 << 16) | (log2u(w) << 20) | (log2u(h) << 24));
    }
    st<u32>(s + 20, tex);
    add_ref(tex);
    return s;
}
HLE_REGISTER(D3DTexture_GetSurfaceLevel2)

namespace {
void texture_locked(u32 tex);  // the guest may write the pixels: check them at the next draw
}
HLE(D3DTexture_LockRect) {
    u32 tex = sarg(c, 0), level = sarg(c, 1), out = sarg(c, 2), rect = sarg(c, 3);
    texture_locked(tex);
    Dims d = dims(tex);
    Format f = format_info(d.format);
    u32 w = std::max(1u, d.width >> level);
    u32 pitch = f.linear ? d.pitch : f.compressed ? ((w + 3) / 4) * f.bytes : w * f.bytes;
    u32 bits = gpu_va(ld<u32>(tex + 4)) + (f.linear ? 0 : level_offset(d, level));
    if (rect && f.linear) bits += ld<u32>(rect + 4) * pitch + ld<u32>(rect) * f.bytes;
    st<u32>(out, pitch);
    st<u32>(out + 4, bits);
    return D3D_OK;
}
HLE_REGISTER(D3DTexture_LockRect)

HLE(D3DDevice_CreateVertexBuffer2) {
    u32 len = sarg(c, 0);
    return new_resource(0xC, TYPE_VERTEXBUFFER, phys(contiguous_alloc((len + 127) & ~127u, 128)));
}
HLE_REGISTER(D3DDevice_CreateVertexBuffer2)
HLE(D3DVertexBuffer_Lock2) { return gpu_va(ld<u32>(sarg(c, 0) + 4)); }
HLE_REGISTER(D3DVertexBuffer_Lock2)

// ---- state the game sets and reads back ----
HLE(D3DDevice_SetTransform) {
    std::array<float, 16> m;
    std::memcpy(m.data(), g_mem + sarg(c, 1), 64);
    g.transforms[sarg(c, 0)] = m;
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_SetTransform)
HLE(D3DDevice_GetTransform) {
    auto it = g.transforms.find(sarg(c, 0));
    float id[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    std::memcpy(g_mem + sarg(c, 1), it != g.transforms.end() ? it->second.data() : id, 64);
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_GetTransform)
// D3DXMatrixPerspectiveFovLH(pOut, fovy, Aspect, zn, zf), the game's camera (symbols/manual_symbols.tsv): on a back
// buffer wider than 4:3 the view widens to match (same height), and the game culls against the wider frustum too
HLE(D3DXMatrixPerspectiveFovLH) {
    u32 out = sarg(c, 0);
    double fovy = sargf(c, 1), aspect = double(sargf(c, 2)) * gfx_wide(), zn = sargf(c, 3), zf = sargf(c, 4);
    double ys = std::cos(fovy / 2) / std::sin(fovy / 2), q = zf / (zf - zn);
    float m[16] = {float(ys / aspect), 0, 0, 0, 0, float(ys), 0, 0, 0, 0, float(q), 1, 0, 0, float(-q * zn), 0};
    gfx_set_camera(float(ys / aspect), float(ys), float(zn), float(zf));
    std::memcpy(g_mem + out, m, sizeof m);
    return out;
}
HLE_REGISTER(D3DXMatrixPerspectiveFovLH)
// The game's own visibility test (0x81B90 boxes, 0x81D50 spheres, symbols/manual_symbols.tsv) checks objects against
// the view's half-width at 0x3ECA50, which the camera (0x81E60) sets to 320 / zoom: the 4:3 screen. On a wider picture,
// scenery and props in the extra width were culled though in view (pumpkins popping at the sides). Set from the
// half-height (240 / zoom, never widened) times 4/3 and the widening, so calling it again changes nothing.
static void widen_cull() { st<float>(0x3ECA50, ld<float>(0x3ECA34) * (4.f / 3.f) * gfx_wide()); }
HLE_BEFORE(CullTestBox) { widen_cull(); }
HLE_BEFORE_REGISTER(CullTestBox)
HLE_BEFORE(CullTestSphere) { widen_cull(); }
HLE_BEFORE_REGISTER(CullTestSphere)
HLE(D3DDevice_SetViewport) {  // D3DVIEWPORT8 { X, Y, Width, Height, MinZ, MaxZ }
    u32 p = sarg(c, 0);
    float minz, maxz;
    std::memcpy(&minz, g_mem + p + 16, 4), std::memcpy(&maxz, g_mem + p + 20, 4);
    set_viewport(ld<u32>(p), ld<u32>(p + 4), ld<u32>(p + 8), ld<u32>(p + 12), minz, maxz);
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_SetViewport)
HLE(D3DDevice_GetViewport) {
    u32 p = sarg(c, 0);
    st<u32>(p, g.vp.x), st<u32>(p + 4, g.vp.y), st<u32>(p + 8, g.vp.w), st<u32>(p + 12, g.vp.h);
    std::memcpy(g_mem + p + 16, &g.vp.minz, 4), std::memcpy(g_mem + p + 20, &g.vp.maxz, 4);
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_GetViewport)
HLE(D3DDevice_SetScissors) {
    g.scissor_count = sarg(c, 0), g.scissor_exclusive = sarg(c, 1);
    g.scissor_rects.assign(g_mem + sarg(c, 2), g_mem + sarg(c, 2) + 16 * (sarg(c, 2) ? g.scissor_count : 0));
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_SetScissors)
HLE(D3DDevice_GetScissors) {
    if (sarg(c, 0)) st<u32>(sarg(c, 0), g.scissor_count);
    if (sarg(c, 1)) st<u32>(sarg(c, 1), g.scissor_exclusive);
    if (sarg(c, 2) && !g.scissor_rects.empty()) std::memcpy(g_mem + sarg(c, 2), g.scissor_rects.data(), g.scissor_rects.size());
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_GetScissors)
HLE(D3DDevice_SetTile) { return std::memcpy(g.tiles[sarg(c, 0) & 7], g_mem + sarg(c, 1), 24), D3D_OK; }
HLE_REGISTER(D3DDevice_SetTile)
HLE(D3DDevice_GetTile) { return std::memcpy(g_mem + sarg(c, 1), g.tiles[sarg(c, 0) & 7], 24), D3D_OK; }
HLE_REGISTER(D3DDevice_GetTile)
HLE(D3DDevice_SetTexture) { return g.textures[sarg(c, 0) & 3] = sarg(c, 1), D3D_OK; }
HLE_REGISTER(D3DDevice_SetTexture)
HLE(D3DDevice_GetTexture2) {
    u32 t = g.textures[sarg(c, 0) & 3];
    add_ref(t);
    return t;
}
HLE_REGISTER(D3DDevice_GetTexture2)
HLE(D3DDevice_SetStreamSource) {
    g.streams[sarg(c, 0) & 15] = {sarg(c, 1), sarg(c, 2)};
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_SetStreamSource)
HLE(D3DDevice_SetScreenSpaceOffset) {
    g.screen_offset[0] = sargf(c, 0), g.screen_offset[1] = sargf(c, 1);
    update_viewport_constants();
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_SetScreenSpaceOffset)

// render states
HLE(D3DDevice_SetRenderState_Simple) { return g.render_states.put(c.ecx, c.edx), 0; }  // ecx = NV2A method
HLE_REGISTER(D3DDevice_SetRenderState_Simple)
// The XDK's own state arrays in this XBE (XDK 5849 statically linked): the game writes the deferred render
// states (D3DRS 92..135: fog, lighting, ...) and texture stage states (D3DTSS 0..21: address, filter, ...)
// straight into them, and the XDK applied them to the GPU lazily at draw time, so draw() reads them there.
constexpr u32 kRenderState = 0x1E2350;         // D3D__RenderState[]: one dword per D3DRENDERSTATETYPE
constexpr u32 kTextureState = 0x1E2150;        // D3D__TextureState[4][32]
constexpr u32 kRenderStateMethods = 0x270630;  // NV2A push header for each simple render state (0..91)
u32 drs(u32 state) { return ld<u32>(kRenderState + 4 * state); }
u32 tss(u32 stage, u32 state) { return ld<u32>(kTextureState + 4 * (32 * stage + state)); }
// SetRenderState by index: simple states push to the GPU (our render_states), deferred ones are stored,
// complex ones have their own function (those this game uses are here)
HLE(D3DDevice_SetRenderStateNotInline) {
    u32 state = sarg(c, 0), value = sarg(c, 1);
    if (state < 92) g.render_states.put(ld<u32>(kRenderStateMethods + 4 * state), value);
    if (state < 136) return st<u32>(kRenderState + 4 * state, value), 0;
    switch (state) {
    case 136: return st<u32>(kRenderState + 4 * state, value), 0;  // D3DRS_PSTEXTUREMODES
    case 138: return g.fog_color = value, 0;
    case 143: return g.z_enable = value, 0;
    case 144: return g.stencil_enable = value, 0;
    case 145: return g.stencil_fail = value, 0;
    case 147: return g.cull_mode = value, 0;
    default: {
        static std::unordered_map<u32, bool> told;
        if (!told[state]) told[state] = true, std::fprintf(stderr, "[d3d] SetRenderStateNotInline(%u, %08X) not handled\n", state, value);
        return 0;
    }
    }
}
HLE_REGISTER(D3DDevice_SetRenderStateNotInline)
HLE(D3DDevice_SetRenderState_CullMode) { return g.cull_mode = sarg(c, 0), 0; }
HLE_REGISTER(D3DDevice_SetRenderState_CullMode)
HLE(D3DDevice_SetRenderState_ZEnable) { return g.z_enable = sarg(c, 0), 0; }
HLE_REGISTER(D3DDevice_SetRenderState_ZEnable)
HLE(D3DDevice_SetRenderState_StencilEnable) { return g.stencil_enable = sarg(c, 0), 0; }
HLE_REGISTER(D3DDevice_SetRenderState_StencilEnable)
HLE(D3DDevice_SetRenderState_StencilFail) { return g.stencil_fail = sarg(c, 0), 0; }
HLE_REGISTER(D3DDevice_SetRenderState_StencilFail)
HLE(D3DDevice_SetRenderState_FogColor) { return g.fog_color = sarg(c, 0), 0; }
HLE_REGISTER(D3DDevice_SetRenderState_FogColor)
HLE(D3DDevice_SetRenderState_MultiSampleAntiAlias) { return g.multisample = sarg(c, 0), 0; }
HLE_REGISTER(D3DDevice_SetRenderState_MultiSampleAntiAlias)
HLE(D3DDevice_SetRenderState_RopZCmpAlwaysRead) { return 0; }  // an NV2A tuning bit with no PC meaning
HLE_REGISTER(D3DDevice_SetRenderState_RopZCmpAlwaysRead)
HLE(D3DDevice_SetTextureState_TexCoordIndex) { return g.tex_coord_index[sarg(c, 0) & 3] = sarg(c, 1), 0; }
HLE_REGISTER(D3DDevice_SetTextureState_TexCoordIndex)

// ---- shaders ----
HLE(D3DDevice_CreateVertexShader) {
    u32 decl = sarg(c, 0), func = sarg(c, 1), out = sarg(c, 2);
    VertexShader vs;
    if (decl)
        for (u32 p = decl;; p += 4) {
            u32 t = ld<u32>(p);
            vs.declaration.push_back(t);
            if (t == 0xFFFFFFFF) break;  // D3DVSD_END
            if (t >> 29 == 4)            // D3DVSD_CONST(addr, n): n float4s of data follow (may hold FFFFFFFF)
                for (u32 k = 0; k < 4 * ((t >> 25) & 0xF); ++k) vs.declaration.push_back(ld<u32>(p += 4));
        }
    if (func) {  // Xbox vertex shader program: { u16 type, u16 instruction count }, 16 bytes per instruction
        u32 count = ld<u16>(func + 2);
        vs.function.resize(1 + count * 4);
        std::memcpy(vs.function.data(), g_mem + func, vs.function.size() * 4);
    }
    u32 handle = kalloc(0x20) | 1;  // programmable shader handles are odd
    g_vertex_shaders[handle] = std::move(vs);
    st<u32>(out, handle);
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_CreateVertexShader)
// D3DVSD_CONST(addr, n) tokens load n float4s into hardware constants addr.. (no SCM correction: the XDK
// writes addr straight into NV097_SET_TRANSFORM_CONSTANT_LOAD) each time the program is loaded, since the
// XDK's LoadVertexShader replays the pushbuffer it built at creation.
static void trace_constant(const char* who, s32 r);
static void load_declaration_constants(u32 handle) {
    auto it = g_vertex_shaders.find(handle);
    if (it == g_vertex_shaders.end()) return;
    const std::vector<u32>& d = it->second.declaration;
    for (size_t i = 0; i < d.size() && d[i] != 0xFFFFFFFF; ++i) {
        if (d[i] >> 29 != 4) continue;
        u32 reg = d[i] & 0xFF, n = (d[i] >> 25) & 0xF;
        for (u32 k = 0; k < n && i + 4 < d.size(); ++k, i += 4)
            if (reg + k < 192) std::memcpy(g.vs_constants[reg + k], &d[i + 1], 16), ++g.vs_version, trace_constant("declaration", s32(reg + k));
    }
}
std::unordered_map<u32, u32> g_loaded_programs;  // microcode address -> handle, from LoadVertexShader

HLE(D3DDevice_SetVertexShader) {
    u32 handle = sarg(c, 0);
    g.vertex_shader = handle;
    if (handle & 1) {  // a programmable shader: the XDK loads and selects its program
        auto it = g_vertex_shaders.find(handle);
        if (it != g_vertex_shaders.end() && !it->second.function.empty()) load_declaration_constants(handle);
    }
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_SetVertexShader)
HLE(D3DDevice_GetVertexShader) { return st<u32>(sarg(c, 0), g.vertex_shader), D3D_OK; }
HLE_REGISTER(D3DDevice_GetVertexShader)
HLE(D3DDevice_GetVertexShaderSize) {
    auto it = g_vertex_shaders.find(sarg(c, 0));
    bool known = it != g_vertex_shaders.end() && !it->second.function.empty();
    st<u32>(sarg(c, 1), known ? it->second.function[0] >> 16 : 0);  // instruction count from the program header
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_GetVertexShaderSize)
HLE(D3DDevice_LoadVertexShader) {  // (Handle, Address): the program and its declaration constants go in
    u32 handle = sarg(c, 0), address = sarg(c, 1);
    g_loaded_programs[address] = handle;
    load_declaration_constants(handle);
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_LoadVertexShader)
HLE(D3DDevice_SelectVertexShader) {  // (Handle, Address): Handle 0 means whatever was loaded at Address
    u32 handle = sarg(c, 0), address = sarg(c, 1);
    auto it = g_loaded_programs.find(address);
    u32 program = it == g_loaded_programs.end() ? handle : it->second;
    if (!handle) handle = program;
    if (!handle) return std::fprintf(stderr, "[d3d] SelectVertexShader(0, %u): nothing loaded there\n", address), D3D_OK;
    if (handle != program) {  // shortcut: the declaration's own program is run; split decl/program pairs would need a combined key
        static bool told;
        if (!told) told = true, std::fprintf(stderr, "[d3d] SelectVertexShader: declaration %08X with program %08X\n", handle, program);
    }
    g.vertex_shader = handle;
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_SelectVertexShader)
HLE(D3DDevice_SetShaderConstantMode) { return g.shader_constant_mode = sarg(c, 0), D3D_OK; }
HLE_REGISTER(D3DDevice_SetShaderConstantMode)

// These fast entry points take the hardware constant index (0..191): D3D writes ecx straight into
// the NV2A constant-load slot and its shadow table at 0x1E1530 + ecx*16.
// OOGIE_TRACE_CONST=12,25: logs every write of those vertex shader constants (debugging)
static bool traced_constant(s32 r) {
    static const char* env = std::getenv("OOGIE_TRACE_CONST");
    if (!env) return false;
    char buf[16];
    std::snprintf(buf, sizeof buf, ",%d,", r);
    return (std::string(",") + env + ",").find(buf) != std::string::npos;
}
static void trace_constant(const char* who, s32 r) {
    if (!traced_constant(r)) return;
    const float* v = g.vs_constants[r];
    std::fprintf(stderr, "[const] frame %u %s c[%d] = %g %g %g %g\n", g.swap_count, who, r, v[0], v[1], v[2], v[3]);
}
static void set_constants(s32 reg, u32 data, u32 count) {
    for (u32 k = 0; k < count; ++k) {
        s32 r = reg + s32(k);
        if (r >= 0 && r < 192) std::memcpy(g.vs_constants[r], g_mem + data + 16 * k, 16), ++g.vs_version, trace_constant("set", r);
    }
}
HLE(D3DDevice_SetVertexShaderConstant1) {
    for (u32 k = 0; k < 1; ++k)
        if (traced_constant(s32(c.ecx + k))) { static int n; if (n++ < 20) std::fprintf(stderr, "[const] caller %08X ecx %u data %08X\n", ld<u32>(c.esp), c.ecx, c.edx); }
    return set_constants(s32(c.ecx), c.edx, 1), D3D_OK;
}
HLE_REGISTER(D3DDevice_SetVertexShaderConstant1)
HLE(D3DDevice_SetVertexShaderConstant4) {
    for (u32 k = 0; k < 4; ++k)
        if (traced_constant(s32(c.ecx + k))) { static int n; if (n++ < 20) std::fprintf(stderr, "[const] caller %08X ecx %u data %08X\n", ld<u32>(c.esp), c.ecx, c.edx); }
    return set_constants(s32(c.ecx), c.edx, 4), D3D_OK;
}
HLE_REGISTER(D3DDevice_SetVertexShaderConstant4)
HLE(D3DDevice_SetVertexShaderConstantNotInline) {  // count is in DWORDs (the original copies with rep movsd)
    return set_constants(s32(c.ecx), c.edx, sarg(c, 0) / 4), D3D_OK;
}
HLE_REGISTER(D3DDevice_SetVertexShaderConstantNotInline)

HLE(D3DDevice_CreatePixelShader) {
    u32 handle = kalloc(0x20);
    g_pixel_shaders[handle].assign(g_mem + sarg(c, 0), g_mem + sarg(c, 0) + 0xF0);  // D3DPIXELSHADERDEF
    st<u32>(sarg(c, 1), handle);
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_CreatePixelShader)
// D3DPIXELSHADERDEF byte offsets and the NV2A methods SetPixelShader pushes them to: alpha inputs, final
// inputs, constants 0/1 + alpha outputs + rgb inputs, compare mode, final constants, rgb outputs + count,
// texture modes, dot mapping + input texture
constexpr struct { u32 off, method, count; } kPsRegs[] = {{0x00, 0x260, 8}, {0x20, 0x288, 2}, {0x28, 0xA60, 32}, {0xA8, 0x17F8, 1},
                                                          {0xAC, 0x1E20, 2}, {0xB4, 0x1E40, 9},  {0xD8, 0x1B68, 1},  {0xDC, 0x1E74, 2}};
// What the XDK's SetPixelShader does with a definition: pushes its registers (so later
// SetRenderState(D3DRS_PS*) calls overwrite them one at a time) and copies it into D3D__RenderState[0..56]
static void set_pixel_shader_def(const u8* def) {
    auto word = [def](u32 off) { u32 v; std::memcpy(&v, def + off, 4); return v; };
    for (auto& r : kPsRegs)
        for (u32 k = 0; k < r.count; ++k) g.render_states.put(r.method + 4 * k, word(r.off + 4 * k));
    std::memcpy(g_mem + kRenderState, def, 57 * 4);
    st<u32>(kRenderState + 136 * 4, word(0xD8));  // D3DRS_PSTEXTUREMODES
}
HLE(D3DDevice_SetPixelShader) {
    g.pixel_shader = sarg(c, 0);
    g.pixel_shader_def = 0;
    if (auto it = g_pixel_shaders.find(g.pixel_shader); it != g_pixel_shaders.end()) set_pixel_shader_def(it->second.data());
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_SetPixelShader)
HLE(D3DDevice_SetPixelShaderProgram) {
    g.pixel_shader = 0;
    g.pixel_shader_def = sarg(c, 0);
    set_pixel_shader_def(g_mem + g.pixel_shader_def);
    return D3D_OK;
}
HLE_REGISTER(D3DDevice_SetPixelShaderProgram)
HLE(D3DDevice_GetPixelShader) { return st<u32>(sarg(c, 0), g.pixel_shader), D3D_OK; }
HLE_REGISTER(D3DDevice_GetPixelShader)

// OOGIE_DUMP_TEXTURES=<dir>: writes every texture the first time a draw uses it (debugging)
// OOGIE_DUMP_SHADERS=<file>: appends every vertex/pixel shader and render-state set a draw uses (debugging)
static void dump_shaders(u32 prim, u32 stride) {
    static const char* path = std::getenv("OOGIE_DUMP_SHADERS");
    if (!path) return;
    static std::unordered_map<std::string, bool> seen;
    FILE* f = std::fopen(path, "a");
    if (!f) return;
    char key[64];
    std::snprintf(key, sizeof key, "vs%08X", g.vertex_shader);
    if (!seen[key]) {
        seen[key] = true;
        auto it = g_vertex_shaders.find(g.vertex_shader);
        std::fprintf(f, "VS %08X\n decl:", g.vertex_shader);
        if (it != g_vertex_shaders.end()) {
            for (u32 t : it->second.declaration) std::fprintf(f, " %08X", t);
            std::fprintf(f, "\n func:");
            for (u32 t : it->second.function) std::fprintf(f, " %08X", t);
        } else {
            std::fprintf(f, " (fixed function / FVF)");
        }
        std::fprintf(f, "\n");
    }
    u32 ps = g.pixel_shader_def ? g.pixel_shader_def : g.pixel_shader;
    std::snprintf(key, sizeof key, "ps%08X", ps);
    if (!seen[key]) {
        seen[key] = true;
        std::fprintf(f, "PS %08X%s\n def:", ps, g.pixel_shader_def ? " (program)" : "");
        const u8* def = nullptr;
        auto it = g_pixel_shaders.find(g.pixel_shader);
        if (g.pixel_shader_def) def = g_mem + g.pixel_shader_def;
        else if (it != g_pixel_shaders.end()) def = it->second.data();
        for (u32 k = 0; def && k < 0xF0; k += 4) std::fprintf(f, " %08X", *reinterpret_cast<const u32*>(def + k));
        std::fprintf(f, "\n");
    }
    // the render state at this draw (NV2A method -> value), and the draw shape
    std::string rs = g.render_states.text();
    std::snprintf(key, sizeof key, "%zu", std::hash<std::string>{}(rs + key));
    if (!seen[key]) {
        seen[key] = true;
        std::fprintf(f, "DRAW prim %u stride %u vs %08X ps %08X tex %08X %08X cull %u z %u\n rs:%s\n", prim, stride,
                     g.vertex_shader, ps, g.textures[0], g.textures[1], g.cull_mode, g.z_enable, rs.c_str());
    }
    std::fclose(f);
}

static void dump_textures() {
    static const char* dir = std::getenv("OOGIE_DUMP_TEXTURES");
    static std::unordered_map<u32, bool> seen;
    static const u64 after = std::getenv("OOGIE_DUMP_AFTER") ? std::strtoull(std::getenv("OOGIE_DUMP_AFTER"), nullptr, 10) : 0;
    if (!dir || g.draws < after) return;  // OOGIE_DUMP_AFTER=<draws>: wait until textures are filled in
    for (u32 tex : g.textures) {
        if (!tex || seen[ld<u32>(tex + 4)]) continue;
        seen[ld<u32>(tex + 4)] = true;
        Dims d = dims(tex);
        std::vector<u32> rgba;
        bool known = decode_texture(g_mem + gpu_va(ld<u32>(tex + 4)), d.format, d.width, d.height, d.pitch, rgba);
        char path[512];
        std::snprintf(path, sizeof path, "%s/%03zu_%08X_fmt%02X_%ux%u%s.bmp", dir, seen.size(), tex, d.format, d.width,
                      d.height, known ? "" : "_unknown");
        if (FILE* f = std::fopen(path, "wb")) {
            BITMAPFILEHEADER fh = {0x4D42, DWORD(54 + rgba.size() * 4), 0, 0, 54};
            BITMAPINFOHEADER ih = {sizeof ih, LONG(d.width), -LONG(d.height), 1, 32, BI_RGB};
            std::fwrite(&fh, sizeof fh, 1, f), std::fwrite(&ih, sizeof ih, 1, f);
            for (u32 p : rgba) {  // RGBA -> BGRA
                u32 bgra = (p & 0xFF00FF00) | ((p & 0xFF) << 16) | ((p >> 16) & 0xFF);
                std::fwrite(&bgra, 4, 1, f);
            }
            std::fclose(f);
        }
    }
}

// ---- drawing ----
namespace {

// a vertex declaration element: stream, input register, D3DVSDT type, byte offset in the stream
struct Element {
    u32 stream, reg, type, offset;
};

struct CompiledVS {
    int id = -1;
    std::vector<Element> elements;
    std::vector<int> inputs;  // registers, in the packed order the host input layout uses
    bool projects = false;    // draws the 3D world (perspective divide / untransformed FVF), not a 2D layer
};

std::unordered_map<u32, CompiledVS> g_vs_cache;   // handle -> compiled
std::unordered_map<u64, int> g_ps_cache;          // hash of the definition -> host pixel shader

// FNV-1a over 8-byte words: only change detection is needed, and this runs 8x faster than the byte form
u64 fnv(const void* p, size_t n) {
    u64 h = 1469598103934665603ull;
    const u8* b = static_cast<const u8*>(p);
    size_t k = 0;
    for (; k + 8 <= n; k += 8) {
        u64 w;
        std::memcpy(&w, b + k, 8);
        h = (h ^ w) * 1099511628211ull;
    }
    for (; k < n; ++k) h = (h ^ b[k]) * 1099511628211ull;
    return h;
}

u32 type_size(u32 type) {
    switch (type) {
    case 0x12: case 0x40: case 0x25: case 0x21: case 0x16: case 0x44: return 4;  // FLOAT1 D3DCOLOR SHORT2 NORMSHORT2 NORMPACKED3 PBYTE4
    case 0x22: case 0x45: case 0x41: return 8;                                    // FLOAT2 SHORT4 NORMSHORT4
    case 0x32: case 0x72: return 12;                                              // FLOAT3 FLOAT2H
    case 0x42: return 16;                                                         // FLOAT4
    case 0x11: case 0x15: case 0x24: return 2;                                    // NORMSHORT1 SHORT1 PBYTE2
    case 0x31: case 0x35: return 6;                                               // NORMSHORT3 SHORT3
    case 0x14: return 1;                                                          // PBYTE1
    case 0x34: return 3;                                                          // PBYTE3
    case 0x02: return 0;                                                          // NONE
    }
    return 0xFFFFFFFF;
}

// one vertex attribute to float4 (missing components (0, 0, 0, 1))
void attribute(u32 type, u32 a, float* o) {
    o[0] = o[1] = o[2] = 0, o[3] = 1;
    auto s16n = [](s16 v) { return std::max(-1.f, v / 32767.f); };
    switch (type) {
    case 0x12: case 0x22: case 0x32: case 0x42:
        std::memcpy(o, g_mem + a, 4 * ((type >> 4) & 0xF));
        break;
    case 0x40: {  // D3DCOLOR: ARGB in a DWORD
        u32 v = ld<u32>(a);
        o[0] = ((v >> 16) & 0xFF) / 255.f, o[1] = ((v >> 8) & 0xFF) / 255.f, o[2] = (v & 0xFF) / 255.f, o[3] = (v >> 24) / 255.f;
        break;
    }
    case 0x15: case 0x25: case 0x35: case 0x45:
        for (u32 k = 0; k < ((type >> 4) & 0xF); ++k) o[k] = ld<s16>(a + 2 * k);
        break;
    case 0x11: case 0x21: case 0x31: case 0x41:
        for (u32 k = 0; k < ((type >> 4) & 0xF); ++k) o[k] = s16n(ld<s16>(a + 2 * k));
        break;
    case 0x14: case 0x24: case 0x34: case 0x44:
        for (u32 k = 0; k < ((type >> 4) & 0xF); ++k) o[k] = ld<u8>(a + k) / 255.f;
        break;
    case 0x16: {  // NORMPACKED3: 11, 11, 10 signed bits
        u32 v = ld<u32>(a);
        o[0] = std::max(-1.f, float(s32(v << 21) >> 21) / 1023.f);
        o[1] = std::max(-1.f, float(s32(v << 10) >> 21) / 1023.f);
        o[2] = std::max(-1.f, float(s32(v) >> 22) / 511.f);
        break;
    }
    case 0x72: {  // FLOAT2H: x, y, w (z = 0)
        float f[3];
        std::memcpy(f, g_mem + a, 12);
        o[0] = f[0], o[1] = f[1], o[3] = f[2];
        break;
    }
    }
}

// Fixed-function vertex formats (even "shader handles" are D3DFVF codes). Input registers used here:
// 0 position, 1 normal, 3 diffuse, 4 specular, 9 + k texture coordinate set k.
// Untransformed positions read world*view*projection from c[0..3] (set per draw).
// shortcut: no fixed-function lighting, fog or texture transforms yet; add them when a scene uses them.
std::unordered_map<std::string, CompiledVS> g_fvf_cache;

CompiledVS* fvf_shader(u32 fvf) {
    u32 tci[4];
    for (int k = 0; k < 4; ++k) tci[k] = g.tex_coord_index[k] & 0xFFFF;
    std::string key = std::to_string(fvf) + "/" + std::to_string(tci[0]) + std::to_string(tci[1]) +
                      std::to_string(tci[2]) + std::to_string(tci[3]);
    auto hit = g_fvf_cache.find(key);
    if (hit != g_fvf_cache.end()) return hit->second.id >= 0 ? &hit->second : nullptr;
    CompiledVS& cv = g_fvf_cache[key];
    u32 pos = fvf & 0xE, offset = 0;
    bool rhw = pos == 0x4;
    cv.projects = !rhw;
    if (pos != 0x2 && pos != 0x4) {
        std::fprintf(stderr, "[d3d] FVF %08X: position type %X (vertex blending) not drawn yet\n", fvf, pos);
        return nullptr;
    }
    cv.elements.push_back({0, 0, u32(rhw ? 0x42 : 0x32), 0}), cv.inputs.push_back(0);
    offset = rhw ? 16 : 12;
    if (fvf & 0x10) cv.elements.push_back({0, 1, 0x32, offset}), cv.inputs.push_back(1), offset += 12;
    if (fvf & 0x40) cv.elements.push_back({0, 3, 0x40, offset}), cv.inputs.push_back(3), offset += 4;
    if (fvf & 0x80) cv.elements.push_back({0, 4, 0x40, offset}), cv.inputs.push_back(4), offset += 4;
    u32 sets = (fvf >> 8) & 0xF;
    for (u32 k = 0; k < sets; ++k) {
        static const u32 floats[4] = {2, 3, 4, 1};  // D3DFVF_TEXCOORDSIZE code -> components
        u32 n = floats[(fvf >> (16 + 2 * k)) & 3];
        cv.elements.push_back({0, 9 + k, (n << 4) | 2, offset}), cv.inputs.push_back(int(9 + k));
        offset += 4 * n;
    }
    std::string s = std::string(g_wide_x_hlsl) + "cbuffer VS : register(b0) { float4 c[192]; float4 screen; };\nstruct VIn {\n";
    for (int r : cv.inputs) s += "  float4 v" + std::to_string(r) + " : TEXCOORD" + std::to_string(r) + ";\n";
    s += "};\n"
         "struct VOut { float4 pos : SV_Position; float4 d0 : COLOR0; float4 d1 : COLOR1; float4 t0 : TEXCOORD0;\n"
         "  float4 t1 : TEXCOORD1; float4 t2 : TEXCOORD2; float4 t3 : TEXCOORD3; float fog : FOG; };\n"
         "VOut main(VIn i) {\n  VOut o;\n";
    if (rhw)  // screen pixels, z in 0..1, rhw = 1/w
        s += "  float w = i.v0.w == 0 ? 1.0 : 1.0 / i.v0.w;\n"
             "  o.pos = float4(wide_x(i.v0.x * screen.x - 1.0, w, screen.w) * w, (1.0 - i.v0.y * screen.y) * w, i.v0.z * w, w);\n";
    else
        s += "  o.pos = mul(float4(i.v0.xyz, 1), float4x4(c[0], c[1], c[2], c[3]));\n";
    s += std::string("  o.d0 = ") + (fvf & 0x40 ? "i.v3" : "float4(1, 1, 1, 1)") + ";\n";
    s += std::string("  o.d1 = ") + (fvf & 0x80 ? "i.v4" : "float4(0, 0, 0, 0)") + ";\n";
    for (int k = 0; k < 4; ++k) {
        // the vertex decoder already fills components a set does not have with (0, 0, 0, 1)
        std::string src = tci[k] < sets ? "i.v" + std::to_string(9 + tci[k]) : "float4(0, 0, 0, 1)";
        s += "  o.t" + std::to_string(k) + " = " + src + ";\n";
    }
    s += "  o.fog = 1;\n  return o;\n}\n";
    cv.id = gfx_vertex_shader(s, cv.inputs);
    return cv.id >= 0 ? &cv : nullptr;
}

CompiledVS* vertex_shader() {
    if (!(g.vertex_shader & 1)) return fvf_shader(g.vertex_shader);  // even handles are FVF codes
    auto hit = g_vs_cache.find(g.vertex_shader);
    if (hit != g_vs_cache.end()) return hit->second.id >= 0 ? &hit->second : nullptr;
    CompiledVS& cv = g_vs_cache[g.vertex_shader];
    auto it = g_vertex_shaders.find(g.vertex_shader);
    if (it == g_vertex_shaders.end()) {
        std::fprintf(stderr, "[d3d] vertex shader %08X was never created\n", g.vertex_shader);
        return nullptr;
    }
    // declaration: STREAM(n) = 0x20000000 | n, REG(r, type) = 0x40000000 | type << 16 | r,
    // SKIP(dwords) = 0x50000000 | n << 16, END = 0xFFFFFFFF
    u32 stream = 0, offset = 0;
    const std::vector<u32>& decl = it->second.declaration;
    for (size_t i = 0; i < decl.size(); ++i) {
        u32 t = decl[i];
        if (t == 0xFFFFFFFF) break;
        u32 kind = t >> 29;
        if (kind == 0) continue;                                   // D3DVSD_NOP
        if (kind == 4) { i += 4 * ((t >> 25) & 0xF); continue; }  // D3DVSD_CONST: loaded with the program
        if (kind == 1) stream = t & 0xF, offset = 0;
        else if (kind == 2 && (t & 0x10000000)) offset += 4 * ((t >> 16) & 0xF);
        else if (kind == 2) {
            u32 type = (t >> 16) & 0xFF, reg = t & 0x1F, size = type_size(type);
            if (size == 0xFFFFFFFF) {
                std::fprintf(stderr, "[d3d] vertex type %02X in shader %08X: not drawn\n", type, g.vertex_shader);
                return nullptr;
            }
            if (size) cv.elements.push_back({stream, reg, type, offset}), cv.inputs.push_back(int(reg));
            offset += size;
        } else {
            std::fprintf(stderr, "[d3d] declaration token %08X in shader %08X: not handled\n", t, g.vertex_shader);
        }
    }
    std::string error;
    std::string hlsl = vsh_to_hlsl(it->second.function, cv.inputs, error);
    if (hlsl.empty()) {
        std::fprintf(stderr, "[d3d] vertex shader %08X not translated: %s\n", g.vertex_shader, error.c_str());
        return nullptr;
    }
    static const bool print = std::getenv("OOGIE_PRINT_SHADERS") != nullptr;  // the HLSL of each new shader
    if (print) std::fprintf(stderr, "[vs %08X]\n%s\n", g.vertex_shader, hlsl.c_str());
    cv.projects = vsh_projects(it->second.function);
    cv.id = gfx_vertex_shader(hlsl, cv.inputs);
    return cv.id >= 0 ? &cv : nullptr;
}

u32 rs(u32 method, u32 fallback);
int build_pixel_shader();

int pixel_shader() {
    static u64 last_version;
    static u32 last_modes, last_shader, last_def;
    static int last_id = -1;
    if (g.render_states.ps_version == last_version && drs(136) == last_modes && g.pixel_shader == last_shader &&
        g.pixel_shader_def == last_def)
        return last_id;
    last_version = g.render_states.ps_version, last_modes = drs(136), last_shader = g.pixel_shader, last_def = g.pixel_shader_def;
    return last_id = build_pixel_shader();
}

int build_pixel_shader() {
    if (!g.pixel_shader_def && !g_pixel_shaders.count(g.pixel_shader)) {
        static bool told;
        if (!told) told = true, std::fprintf(stderr, "[d3d] fixed-function pixel pipeline: not drawn yet\n");
        return -1;
    }
    // the definition as the GPU has it now: what SetPixelShader pushed plus later SetRenderState(D3DRS_PS*)
    // edits (combiner constants), and the texture modes from D3DRS_PSTEXTUREMODES
    u8 def[0xF0] = {};
    for (auto& r : kPsRegs)
        for (u32 k = 0; k < r.count; ++k) {
            u32 v = rs(r.method + 4 * k, 0);
            std::memcpy(def + r.off + 4 * k, &v, 4);
        }
    u32 modes = drs(136);
    std::memcpy(def + 0xD8, &modes, 4);
    u64 h = fnv(def, 0xE4);
    auto hit = g_ps_cache.find(h);
    if (hit != g_ps_cache.end()) return hit->second;
    std::string error, hlsl = psh_to_hlsl(def, error);
    if (hlsl.empty()) std::fprintf(stderr, "[d3d] pixel shader not translated: %s\n", error.c_str());
    static const bool print = std::getenv("OOGIE_PRINT_SHADERS") != nullptr;
    if (print && !hlsl.empty()) {
        std::fprintf(stderr, "[ps %016llX def", (unsigned long long)h);
        for (u32 k = 0; k < 0xF0; k += 4) std::fprintf(stderr, " %08X", *reinterpret_cast<const u32*>(def + k));
        std::fprintf(stderr, "]\n%s\n", hlsl.c_str());
    }
    return g_ps_cache[h] = hlsl.empty() ? -1 : gfx_pixel_shader(hlsl);
}

// Host copies of guest textures, refreshed when the guest bytes change (checked once per frame).
struct HostTexture {
    int id = -1;
    u32 format_word = 0, size_word = 0;
    u64 hash = 0, checked_frame = ~0ull;
    bool rendered = false;  // drawn by the host: the guest bytes never hold these pixels
    u32 owner = 0;          // the guest texture (or surface) that was rendered into; others at this address upload
    u32 width = 0, height = 0;
    u64 changed_frame = 0;  // when the guest bytes last differed
    bool dirty = false;     // locked by the guest since the last check
    u32 host_w = 0, host_h = 0;  // the host texture's size and format (debugging)
    int host_format = 0;
    u32 changes = 0;   // uploads of new contents
    int video_id = -1;  // a movie plane's cleaned copy (gfx_video_filter), what draws sample
};
std::unordered_map<u32, HostTexture> g_tex_cache;  // pixel data address -> host texture

// shortcut: a rendered texture is never refreshed from guest memory again; a reload of other pixels
// into the same memory would be missed (revisit if a level shows stale render targets)
int render_texture(u32 surface) {
    u32 data = gpu_va(ld<u32>(surface + 4));
    Dims d = dims(surface);
    HostTexture& h = g_tex_cache[data];
    if (!h.rendered || h.width != d.width || h.height != d.height) {
        h.id = gfx_texture_create(d.width, d.height, 87, false, true);  // DXGI_FORMAT_B8G8R8A8_UNORM, like the back buffer
        h.rendered = true, h.width = d.width, h.height = d.height;
    }
    u32 parent = ld<u32>(surface + 20);  // a texture's level surface names its texture at +0x14
    h.owner = parent ? parent : surface;
    return h.id;
}

void texture_locked(u32 tex) {
    auto it = g_tex_cache.find(gpu_va(ld<u32>(tex + 4)));
    if (it != g_tex_cache.end()) it->second.dirty = true;
}

int host_surface(u32 surface) {
    if (surface == g.backbuffer) return -1;
    auto it = g_tex_cache.find(gpu_va(ld<u32>(surface + 4)));
    if (it != g_tex_cache.end() && !it->second.rendered && it->second.id >= 0) return it->second.id;  // an uploaded texture
    return render_texture(surface);
}

std::unordered_set<int> g_movie_textures;  // host textures holding movie planes (and their cleaned copies)

int texture(u32 tex, float* tscale, bool& cube) {
    cube = false;
    tscale[0] = tscale[1] = 1;
    if (!tex) return -1;
    Dims d = dims(tex);
    Format f = format_info(d.format);
    u32 fmt_word = ld<u32>(tex + 12), size_word = ld<u32>(tex + 16);
    if (fmt_word & 4) {
        static bool told;
        if (!told) told = true, std::fprintf(stderr, "[d3d] cube textures: not drawn yet\n");
        return -1;
    }
    u32 data = gpu_va(ld<u32>(tex + 4));
    u32 bytes = f.compressed ? ((d.width + 3) / 4) * ((d.height + 3) / 4) * f.bytes
                             : (f.linear ? d.pitch * d.height : d.width * d.height * f.bytes);
    if (f.linear) tscale[0] = 1.f / d.width, tscale[1] = 1.f / d.height;  // linear textures take texel coordinates
    // the game's own texture headers over the back buffer (post-processing reads the frame): the pixels are on
    // the host, so sample a snapshot of the scene instead of the untouched guest memory
    if (data == gpu_va(ld<u32>(g.backbuffer + 4))) return gfx_backbuffer_snapshot();
    HostTexture& h = g_tex_cache[data];
    if (h.rendered) {  // the memory of a render target: ours only for the object that was rendered into
        if (h.owner == tex) return h.id;
        h = HostTexture{};  // another texture object over the same memory: back to uploading the guest bytes
    }
    bool same = h.id >= 0 && h.format_word == fmt_word && h.size_word == size_word;
    auto drawn = [&] { return h.video_id >= 0 ? h.video_id : h.id; };  // a movie plane is sampled cleaned
    if (same && h.checked_frame == g.swap_count) return drawn();
    // the guest bytes are re-hashed every frame while they keep changing (movie frames, animated UI) and
    // every 16th frame once they have been stable for a second, unless the guest locked the texture
    if (same && !h.dirty && g.swap_count - h.changed_frame > 60 && g.swap_count - h.checked_frame < 16) return drawn();
    u64 hash;
    {
        ScopedNs t(g.hash_ns);
        hash = fnv(g_mem + data, bytes);
    }
    h.checked_frame = g.swap_count, h.dirty = false;
    if (same && h.hash == hash) return drawn();
    h.changed_frame = g.swap_count;
    bool fresh = !same;
    if (fresh) h.changes = 0, h.video_id = -1;
    h.format_word = fmt_word, h.size_word = size_word, h.hash = hash;
    if (f.compressed) {  // DXT is stored unswizzled: upload as BC1/2/3
        int dxgi = d.format == 0x0C ? 71 : d.format == 0x0E ? 74 : 77;  // DXGI_FORMAT_BC1/BC2/BC3_UNORM
        if (fresh) h.id = gfx_texture_create((d.width + 3) & ~3u, (d.height + 3) & ~3u, dxgi, false), h.host_w = d.width, h.host_h = d.height, h.host_format = dxgi;
        gfx_texture_update(h.id, g_mem + data, ((d.width + 3) / 4) * f.bytes, 0);
    } else {
        std::vector<u32> rgba;
        decode_texture(g_mem + data, d.format, d.width, d.height, d.pitch, rgba);
        if (fresh) h.id = gfx_texture_create(d.width, d.height, 28, false), h.host_w = d.width, h.host_h = d.height, h.host_format = 28;  // DXGI_FORMAT_R8G8B8A8_UNORM
        gfx_texture_update(h.id, rgba.data(), d.width * 4, 0);
    }
    // Bink's Y/U/V planes: linear L8 textures that get new contents frame after frame
    static const bool no_filter = std::getenv("OOGIE_NO_VIDEO_FILTER") != nullptr;  // A/B checks
    if (d.format == 0x13 && ++h.changes >= 2) {
        if (!no_filter) h.video_id = gfx_video_filter(h.id);
        g_movie_textures.insert(h.id), g_movie_textures.insert(drawn());
    }
    return drawn();
}

u32 rs(u32 method, u32 fallback) {  // NV2A render state as the game last wrote it (subchannel 0 methods)
    u32 i = (method & 0x1FFC) >> 2;
    return g.render_states.set[i] ? g.render_states.value[i] : fallback;
}

void draw(u32 prim, u32 count, u32 start, u32 up_data, u32 up_stride) {
    ScopedNs timer(g.draw_ns);
    if (g.render_target != g.backbuffer) ++g.offscreen_draws;
    {  // OOGIE_ONLY_TEX=physical data address: only draws whose stage-0 texture lives there are drawn (debugging)
        static const char* only = std::getenv("OOGIE_ONLY_TEX");
        static const u32 data = only ? u32(std::strtoul(only, nullptr, 16)) : 0;
        if (only && (!g.textures[0] || ld<u32>(g.textures[0] + 4) != data)) return;
    }
    {  // OOGIE_ONLY_VS=handle: only draws with that vertex shader are drawn (debugging)
        static const char* only = std::getenv("OOGIE_ONLY_VS");
        static const u32 handle = only ? u32(std::strtoul(only, nullptr, 16)) : 0;
        if (only && g.vertex_shader != handle) return;
    }
    {  // OOGIE_SKIP_VS=handle: draws with that vertex shader are not drawn (debugging); their state is printed 3 times
        static const char* skip = std::getenv("OOGIE_SKIP_VS");
        static const u32 handle = skip ? u32(std::strtoul(skip, nullptr, 16)) : 0;
        if (skip && g.vertex_shader == handle) {
            static int n;
            if (n++ < 3)
                std::fprintf(stderr, "[skip] vs %08X stencil %u func %X ref %u fail %X zfail %X pass %X z %u zfunc %X zwrite %u blend %u %X/%X cull %X mask %X\n",
                             handle, g.stencil_enable, rs(0x364, 0x207), rs(0x368, 0), g.stencil_fail, rs(0x374, 0x1E00), rs(0x378, 0x1E00),
                             g.z_enable, rs(0x354, 0x203), rs(0x35C, 1), rs(0x304, 0), rs(0x344, 1), rs(0x348, 0), g.cull_mode, rs(0x358, 0x01010101));
            return;
        }
    }
    CompiledVS* vs = vertex_shader();
    {  // OOGIE_DRAW_LOG=first,count: every draw of those frames, one line each: frame, shader, stage 0 texture data, vertices (testing)
        static const char* env = std::getenv("OOGIE_DRAW_LOG");
        static unsigned first, n;
        if (env && !n) std::sscanf(env, "%u,%u", &first, &n);
        if (env && g.swap_count >= first && g.swap_count < first + n)
            std::fprintf(stderr, "[dl] %u vs %08X tex %08X n %u z %u\n", g.swap_count, g.vertex_shader,
                         g.textures[0] ? ld<u32>(g.textures[0] + 4) : 0, count, rs(0x35C, 1));
    }
    static std::string line;  // OOGIE_DRAW_SEQ's
    {  // OOGIE_DRAW_SEQ=first,count: each frame's draws in order: P 3D (Z writes), p 3D (no Z writes), 2 2D,
       // s 2D with stencil, A the occlusion pass, t into another target (testing)
        static const char* seq = std::getenv("OOGIE_DRAW_SEQ");
        static unsigned first, count;
        static u32 line_frame = ~0u;
        if (seq) {
            if (!count) std::sscanf(seq, "%u,%u", &first, &count);
            if (line_frame != g.swap_count) {
                if (!line.empty()) std::fprintf(stderr, "[seq] %u: %s\n", line_frame, line.c_str());
                line.clear(), line_frame = g.swap_count;
            }
            if (g.swap_count >= first && g.swap_count < first + count)
                line += g.render_target != g.backbuffer ? 't' : !vs || !vs->projects ? (g.stencil_enable ? 's' : '2')
                        : rs(0x35C, 1) ? 'P' : 'p';
        }
    }
    if (vs && g.render_target == g.backbuffer) {
        if (vs->projects) {
            g_frame_3d = true, g_3d_since_boundary = true;
            if (rs(0x35C, 1)) ++g_world_draws;  // depth writes on (NV097_SET_DEPTH_MASK)
        } else if (g_frame_3d) {
            // The occlusion goes in once the world (characters included) is done: at the frame's last turn from 3D to
            // 2D. The game turns to 2D mid-world too (Town Square: a full-screen pass between two 3D batches), so the
            // last turn is the one the frame before ended its world at; failing that, where this frame has drawn about
            // as much world as the last. The count alone missed whenever a fight changed it (one frame in ~130
            // without the occlusion: a flicker).
            bool boundary = g_3d_since_boundary && !g.stencil_enable;  // a stencil pass (shadows) is part of the world
            if (boundary) ++g_boundaries, g_3d_since_boundary = false;
            bool by_structure = boundary && g_boundaries == g_last_boundaries;
            bool by_count = g_last_world_draws && g_world_draws + std::max(4u, g_last_world_draws / 50) >= g_last_world_draws;
            if (!g_occlusion_done && (by_structure || by_count)) {
                gfx_ambient_occlusion(), g_occlusion_done = true;
                line += 'A';
            }
        }
    }
    int ps = pixel_shader();
    // OOGIE_SOLID_PS=1 paints every draw magenta with blending off; OOGIE_NO_Z=1 drops the depth test (debugging)
    // OOGIE_CYCLE_DEBUG=1 cycles every 60 frames: normal, no depth test, no blending, no alpha test, full color
    // mask, no culling (a frame recording then shows which state blanks a scene)
    static const bool solid = std::getenv("OOGIE_SOLID_PS") != nullptr, cycle = std::getenv("OOGIE_CYCLE_DEBUG") != nullptr;
    u32 phase = cycle ? (g.swap_count / 60) % 6 : 0;
    static const bool no_z_env = std::getenv("OOGIE_NO_Z") != nullptr;
    bool no_z = no_z_env || phase == 1, no_blend = phase == 2, no_alpha_test = phase == 3;
    bool full_mask = phase == 4, no_cull = phase == 5;
    static const int solid_ps = solid ? gfx_pixel_shader("float4 main() : SV_Target { return float4(1, 0, 1, 1); }") : -1;
    if (solid) ps = solid_ps;
    if (!vs || ps < 0 || !count) return;

    // vertices: every declared input as float4, packed
    u32 n_in = u32(vs->elements.size());
    static std::vector<float> verts;  // reused: draw() runs under the guest lock, one at a time
    verts.resize(size_t(count) * n_in * 4);
    {
        ScopedNs pack_timer(g.pack_ns);
        for (u32 i = 0; i < count; ++i)
        for (u32 k = 0; k < n_in; ++k) {
            const Element& e = vs->elements[k];
            u32 base, stride;
            if (up_data) base = up_data, stride = up_stride;  // DrawVerticesUP: stream 0 is the caller's array
            else base = gpu_va(ld<u32>(g.streams[e.stream].vb + 4)), stride = g.streams[e.stream].stride;
            attribute(e.type, base + (start + i) * stride + e.offset, &verts[(size_t(i) * n_in + k) * 4]);
        }
    }

    // primitive: Xbox D3DPT 1 points, 2 lines, 3 line loop, 4 line strip, 5 triangles, 6 strip, 7 fan,
    // 8 quads, 9 quad strip, 10 polygon
    int topology;
    static std::vector<u32> idx;
    idx.clear();
    switch (prim) {
    case 1: topology = 1; break;
    case 2: topology = 2; break;
    case 4: topology = 3; break;
    case 5: topology = 4; break;
    case 6: case 9: topology = 5; break;
    case 3:
        topology = 3;
        for (u32 i = 0; i < count; ++i) idx.push_back(i);
        idx.push_back(0);
        break;
    case 7: case 10:
        topology = 4;
        for (u32 i = 1; i + 1 < count; ++i) idx.insert(idx.end(), {0, i, i + 1});
        break;
    case 8:
        topology = 4;
        for (u32 q = 0; q + 3 < count; q += 4) idx.insert(idx.end(), {q, q + 1, q + 2, q, q + 2, q + 3});
        break;
    default: return;
    }

    GfxState s;
    s.flat = vs && !vs->projects;
    s.vs = vs->id, s.ps = ps;
    for (int k = 0; k < 4; ++k) s.textures[k] = texture(g.textures[k], s.tscale[k], s.cube[k]);
    s.vs_constants = g.vs_constants, s.vs_version = g.vs_version;
    if (!(g.vertex_shader & 1) && (g.vertex_shader & 0xE) == 0x2) {  // untransformed FVF: c[0..3] = world*view*proj
        auto get = [](u32 state) {
            auto it = g.transforms.find(state);
            std::array<float, 16> m = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
            return it == g.transforms.end() ? m : it->second;
        };
        auto mul = [](const std::array<float, 16>& a, const std::array<float, 16>& b) {
            std::array<float, 16> r{};
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    for (int k = 0; k < 4; ++k) r[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
            return r;
        };
        auto wvp = mul(mul(get(256), get(2)), get(3));  // D3DTS_WORLD, VIEW, PROJECTION
        static float fvf[192][4];  // the game's registers with c[0..3] replaced
        std::memcpy(fvf, g.vs_constants, sizeof fvf), std::memcpy(fvf, wvp.data(), 64);
        s.vs_constants = fvf, s.vs_version = 0;
    }
    s.screen[0] = 2.f / g.rt_width, s.screen[1] = 2.f / g.rt_height, s.screen[2] = 1.f / g.zscale;
    // a picture (a movie, or the game's own art such as a menu background) keeps its 4:3 shape on a wide back
    // buffer even when it covers the screen; effects (untextured fades, anything reading a render target or a
    // screen capture, like the 3D scene composited with a lookup texture) stretch
    bool movie = false, art = false, target = false, image = false;
    for (int t : s.textures)
        if (g_movie_textures.count(t)) movie = true;
        else art |= gfx_texture_is_picture(t), target |= gfx_texture_is_target(t), image |= gfx_texture_is_image(t);
    bool picture = movie || (art && !target);
    s.screen[3] = g.render_target != g.backbuffer ? 1.f
                  : picture || !g_last_frame_3d    ? -gfx_wide()
                  : image && !target               ? gfx_wide() + 100  // textured 2D: see g_wide_x_hlsl
                                                   : gfx_wide();
    u32 fog = g.fog_color;
    s.fog_color[0] = ((fog >> 16) & 0xFF) / 255.f, s.fog_color[1] = ((fog >> 8) & 0xFF) / 255.f;
    s.fog_color[2] = (fog & 0xFF) / 255.f, s.fog_color[3] = 1;
    // D3DRS_FOGSTART/END/DENSITY, and the mode when D3DRS_FOGENABLE (OOGIE_NO_FOG=1 turns fog off: debugging)
    static const bool no_fog = std::getenv("OOGIE_NO_FOG") != nullptr;
    for (int k = 0; k < 3; ++k) s.fog_params[k] = ld<float>(kRenderState + 4 * (94 + k));
    s.fog_params[3] = drs(92) && !no_fog ? float(drs(93)) : -1.f;
    for (int k = 0; k < 4; ++k) {  // D3DTSS_ADDRESSU/V/W and MAGFILTER (1 = D3DTEXF_POINT)
        for (u32 a = 0; a < 3; ++a) s.address[k][a] = tss(k, a);
        s.linear_filter[k] = tss(k, 3) != 1;
    }
    s.alpha_test[0] = float(rs(0x340, 0));                       // ALPHA_REF
    s.alpha_test[1] = float((rs(0x33C, 0x207) & 0xF) + 1);       // ALPHA_FUNC (GL) -> D3DCMP 1..8
    s.alpha_test[2] = rs(0x300, 0) ? 1.f : 0.f;                   // ALPHA_TEST_ENABLE
    static const bool ps_debug = std::getenv("OOGIE_PS_DEBUG") != nullptr;  // see psh.cpp
    s.alpha_test[3] = ps_debug ? float((g.swap_count / 60) % 8) : 0.f;  // normal, v0, t0, t1, t2+t3 white, t0 raw, uv, v0 raw
    s.blend = rs(0x304, 0) != 0;                                  // BLEND_ENABLE
    s.blend_src = rs(0x344, 1), s.blend_dst = rs(0x348, 0), s.blend_op = rs(0x350, 0x8006);
    s.color_mask = rs(0x358, 0x01010101);
    s.z_enable = g.z_enable != 0 && !no_z;
    s.z_write = rs(0x35C, 1) != 0;
    s.z_func = rs(0x354, 0x203);
    // NV097_SET_STENCIL_*: the game's shadow volumes depend on these
    s.stencil = g.stencil_enable != 0;
    s.stencil_write_mask = rs(0x360, 0xFF), s.stencil_func = rs(0x364, 0x207), s.stencil_ref = rs(0x368, 0);
    s.stencil_mask = rs(0x36C, 0xFF);
    static const u32 gl_op[] = {0x1E00, 0x1E00, 0, 0x1E01, 0x1E02, 0x1E03, 0x150A, 0x8507, 0x8508};  // D3DSTENCILOP 1..8
    s.stencil_fail = g.stencil_fail && g.stencil_fail <= 8 ? gl_op[g.stencil_fail] : rs(0x370, 0x1E00);
    s.stencil_zfail = rs(0x374, 0x1E00), s.stencil_pass = rs(0x378, 0x1E00);
    if (solid || no_blend) s.blend = false;
    if (solid || no_alpha_test) s.alpha_test[2] = 0;
    if (full_mask) s.color_mask = 0x01010101;
    if (no_cull) s.cull = 0;
    s.cull = g.cull_mode == 0x900 ? 1 : g.cull_mode == 0x901 ? 2 : 0;  // D3DCULL_CW / CCW (GL values)
    if (g.scissor_count && !g.scissor_exclusive && g.scissor_rects.size() >= 16) {
        s.scissor = true;
        std::memcpy(&s.scissor_rect, g.scissor_rects.data(), 16);
    }
    // the NV2A clips to the viewport rectangle (the XDK programs it as the surface clip)
    if (g.vp.x || g.vp.y || g.vp.w != g.rt_width || g.vp.h != g.rt_height) {
        GfxRect v = {s32(g.vp.x), s32(g.vp.y), s32(g.vp.x + g.vp.w), s32(g.vp.y + g.vp.h)};
        if (s.scissor) {
            s.scissor_rect.x1 = std::max(s.scissor_rect.x1, v.x1), s.scissor_rect.y1 = std::max(s.scissor_rect.y1, v.y1);
            s.scissor_rect.x2 = std::min(s.scissor_rect.x2, v.x2), s.scissor_rect.y2 = std::min(s.scissor_rect.y2, v.y2);
        } else {
            s.scissor = true, s.scissor_rect = v;
        }
    }
    ScopedNs t(g.gfx_ns);
    gfx_draw(s, topology, verts.data(), count, n_in * 4, idx.empty() ? nullptr : idx.data(), u32(idx.size()));
    {  // OOGIE_SNAP=frame,step,from,to,dir: in that frame, logs every draw and saves the back buffer every `step` draws,
       // and after every draw from..to also the draw's render target and stage 0 texture (debugging)
        static const char* env = std::getenv("OOGIE_SNAP");
        static u32 frame = 0, step = 0, from = 0, to = 0;
        static char dir[200] = {};
        static u64 first_draw = 0;
        if (env && !step) std::sscanf(env, "%u,%u,%u,%u,%199s", &frame, &step, &from, &to, dir);
        if (env && g.swap_count == frame) {
            if (!first_draw) first_draw = g.draws;
            u64 n = g.draws - first_draw;
            u32 t0 = g.textures[0];
            Dims d = t0 ? dims(t0) : Dims{};
            std::fprintf(stderr, "[snap] %llu vs %08X ps %08X t0 %08X(%ux%u fmt %02X data %08X) rt %08X blend %u %X/%X op %X z %u/%u stencil %u fog %u/%u count %u proj %d\n",
                         (unsigned long long)n, g.vertex_shader, g.pixel_shader, t0, d.width, d.height, d.format, t0 ? ld<u32>(t0 + 4) : 0,
                         g.render_target, s.blend, s.blend_src, s.blend_dst, s.blend_op, s.z_enable, s.z_write, s.stencil, drs(92), drs(93), count,
                         vs ? int(vs->projects) : -1);
            std::fprintf(stderr, "[snap] %llu vp %u,%u %ux%u rt %ux%u scissor %d %d,%d-%d,%d\n", (unsigned long long)n, g.vp.x, g.vp.y,
                         g.vp.w, g.vp.h, g.rt_width, g.rt_height, int(s.scissor), s.scissor_rect.x1, s.scissor_rect.y1, s.scissor_rect.x2,
                         s.scissor_rect.y2);
            char path[300];
            if (n % step == 0 || (n >= from && n <= to)) {
                std::snprintf(path, sizeof path, "%s/d%05llu.bmp", dir, (unsigned long long)n);
                gfx_scene_dump(path);
            }
            if (n >= from && n <= to) {
                if (g.render_target != g.backbuffer) {
                    std::snprintf(path, sizeof path, "%s/d%05llu_rt_%08X.bmp", dir, (unsigned long long)n, g.render_target);
                    gfx_texture_dump(render_texture(g.render_target), path);
                }
                std::snprintf(path, sizeof path, "%s/d%05llu_t0_%08X.bmp", dir, (unsigned long long)n, t0);
                gfx_texture_dump(s.textures[0], path);
                const float* d0 = g.vs_constants[0];
                std::fprintf(stderr, "[snap] %llu ps def", (unsigned long long)n);
                for (auto& r : kPsRegs)
                    for (u32 k = 0; k < r.count; ++k) std::fprintf(stderr, " %08X", rs(r.method + 4 * k, 0));
                std::fprintf(stderr, " | c0 %g %g %g %g | vertex 0:", d0[0], d0[1], d0[2], d0[3]);
                for (u32 k = 0; k < n_in * 4 && k < verts.size(); ++k) std::fprintf(stderr, " %g", verts[k]);
                std::fprintf(stderr, "\n");
            }
        }
    }
}

}  // namespace

HLE(D3DDevice_DrawVertices) {
    ++g.draws;
    dump_textures();
    dump_shaders(sarg(c, 0), g.streams[0].stride);
    draw(sarg(c, 0), sarg(c, 2), sarg(c, 1), 0, 0);  // (PrimitiveType, StartVertex, VertexCount)
    return 0;
}
HLE_REGISTER(D3DDevice_DrawVertices)
HLE(D3DDevice_DrawVerticesUP) {
    ++g.draws;
    dump_textures();
    dump_shaders(sarg(c, 0), sarg(c, 3));
    // OOGIE_DUMP_DRAWS=n: print the first n of these draws after OOGIE_DUMP_AFTER: shader, texture, vertices
    static const char* nd = std::getenv("OOGIE_DUMP_DRAWS");
    static u64 dumped;
    static const u64 after = std::getenv("OOGIE_DUMP_AFTER") ? std::strtoull(std::getenv("OOGIE_DUMP_AFTER"), nullptr, 10) : 0;
    if (nd && g.draws >= after && dumped < std::strtoull(nd, nullptr, 10)) {
        ++dumped;
        u32 type = sarg(c, 0), count = sarg(c, 1), data = sarg(c, 2), stride = sarg(c, 3);
        u32 tex = g.textures[0];
        std::fprintf(stderr, "[draw] #%llu from %08X prim %u count %u stride %u vshader %08X tex0 %08X",
                     (unsigned long long)g.draws, ld<u32>(c.esp), type, count, stride, g.vertex_shader, tex);
        if (tex) {
            Dims d = dims(tex);
            std::fprintf(stderr, " (fmt %02X %ux%u data %08X)", d.format, d.width, d.height, ld<u32>(tex + 4));
        }
        std::fprintf(stderr, " ps %08X/%08X z %u cull %u\n  stack:", g.pixel_shader, g.pixel_shader_def, g.z_enable,
                     g.cull_mode);
        // return addresses on the guest stack: values in .text right after a call instruction
        for (u32 k = 0, shown = 0; k < 256 && shown < 8; ++k) {
            u32 v = ld<u32>(c.esp + 4 * k);
            if (v < 0x12000 || v >= 0x1D1B68) continue;
            bool after_call = ld<u8>(v - 5) == 0xE8 || (ld<u8>(v - 6) == 0xFF && (ld<u8>(v - 5) & 0x38) == 0x10) ||
                              (ld<u8>(v - 2) == 0xFF && (ld<u8>(v - 1) & 0x38) == 0x10) ||
                              (ld<u8>(v - 3) == 0xFF && (ld<u8>(v - 2) & 0x38) == 0x10);
            if (after_call) std::fprintf(stderr, " %08X", v), ++shown;
        }
        std::fprintf(stderr, "\n  rs:");
        std::fprintf(stderr, "%s", g.render_states.text().c_str());
        std::fprintf(stderr, "\n");
        for (u32 v = 0; v < count && v < 8; ++v) {
            std::fprintf(stderr, "  v%u:", v);
            for (u32 k = 0; k < stride / 4; ++k) {
                u32 raw = ld<u32>(data + v * stride + 4 * k);
                float f;
                std::memcpy(&f, &raw, 4);
                std::fprintf(stderr, " %08X(%g)", raw, f);
            }
            std::fprintf(stderr, "\n");
        }
    }
    draw(sarg(c, 0), sarg(c, 1), 0, sarg(c, 2), sarg(c, 3));
    return 0;
}
HLE_REGISTER(D3DDevice_DrawVerticesUP)
