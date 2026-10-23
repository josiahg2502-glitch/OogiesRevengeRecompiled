// The host graphics backend the D3D8 replacement draws through.
#pragma once
#include <cstdint>
#include <string>
#include <vector>

struct GfxRect {
    int32_t x1, y1, x2, y2;
};

// Opens the window and creates the device; width/height are the game's back buffer size.
void gfx_init(uint32_t width, uint32_t height);
// D3DCLEAR flags: 0x01 depth, 0x02 stencil, 0xF0 color (any of the four channel bits)
void gfx_clear(uint32_t flags, uint32_t argb, float z, uint32_t stencil, const GfxRect* rects, uint32_t count);
// Shows the back buffer. Blocks for vsync; the caller releases the guest lock around it.
void gfx_present();
// Waits for the window's display to start a vertical blank; true when that display runs at 60 Hz
// (its vblank then paces the game smoothly), false when the caller should keep its own 59.94 Hz clock.
bool gfx_wait_vblank();
extern unsigned g_presents;  // frames presented so far
extern uint64_t g_shader_compiles, g_shader_compile_ns;  // host shader compiles so far and their time
// Handles window messages; call often from the thread that called gfx_init.
void gfx_pump();

// Shaders compiled from HLSL; -1 if compilation failed (the error is printed once).
// inputs: vertex registers fed as float4 TEXCOORD<reg>, packed in this order.
int gfx_vertex_shader(const std::string& hlsl, const std::vector<int>& inputs);
int gfx_pixel_shader(const std::string& hlsl);

// Textures: format is a DXGI_FORMAT; data holds `levels` mip levels back to back (rows `pitch`
// bytes apart at level 0, halving). Returns an id; update replaces the contents.
// A render_target texture is made at the host scale and can be drawn into.
int gfx_texture_create(uint32_t width, uint32_t height, int format, bool cube, bool render_target = false);
void gfx_texture_update(int id, const void* data, uint32_t pitch, uint32_t face);
// Directs draws and clears at a render_target texture (id) or the back buffer (-1); with_depth binds a
// depth buffer sized like it (the back buffer always has its own).
void gfx_set_render_target(int id, bool with_depth);
// A texture holding a copy of the back buffer as it is now (for draws that read the frame they draw into).
int gfx_backbuffer_snapshot();
// A movie plane texture just updated with a new frame: returns a cleaned copy (denoised, temporally steadied)
int gfx_video_filter(int id);
float gfx_wide();
// The frame about to be presented drew no 3D world (a menu, movie or loading screen): with a back buffer wider than
// 4:3 its sides are filled with a blurred, darkened extension of the 4:3 picture.
void gfx_flat_frame(bool flat);
// The menu: shows a BGRA canvas (any size, kept at its shape) and waits for the next refresh. gfx_init first.
void gfx_show_canvas(const uint32_t* bgra, uint32_t w, uint32_t h);
// The in-game menu: F1 was pressed since the last call; the frame last drawn (BGRA); window or fullscreen now.
bool gfx_menu_requested();
std::vector<uint32_t> gfx_scene_pixels(uint32_t& w, uint32_t& h);
void gfx_set_fullscreen(bool on);
// The game's 3D camera (projection x/y scale, near and far planes), for gfx_ambient_occlusion.
void gfx_set_camera(float p00, float p11, float zn, float zf);
// Ray-traced ambient occlusion over the 3D world drawn so far ([display] ray_tracing); call once per frame, after the
// world and before the 2D layer.
void gfx_ambient_occlusion();  // the back buffer's width over the game's 4:3 width (1 = 4:3; 2.37 = 32:9)
bool gfx_texture_is_picture(int id);  // an uploaded image at least 256 wide (not a render target): art, not an effect
bool gfx_texture_is_target(int id);
bool gfx_texture_is_image(int id);    // an uploaded image of at least 8x8 (not a solid-colour 1x1 texture)   // something drawn into (a render target or a capture of the back buffer)
void gfx_texture_dump(int id, const char* path);  // saves a host texture as a BMP (debugging)
void gfx_scene_dump(const char* path);            // saves the back buffer as it is now (debugging)
int gfx_texture_compare(int id, const void* data, uint32_t pitch, uint32_t rows);  // first differing row, -1 if equal
// Copies rect (game pixels; null = all) of a render_target texture or the back buffer (-1) to another at (x, y).
void gfx_copy(int src, int dst, const GfxRect* rect, int32_t dst_x, int32_t dst_y);

struct GfxState {
    int vs = -1, ps = -1;
    int textures[4] = {-1, -1, -1, -1};
    bool cube[4] = {};
    uint32_t address[4][3] = {};  // D3DTADDRESS per stage (u, v, w): 1 wrap, 2 mirror, 3 clamp, 4 border
    bool linear_filter[4] = {true, true, true, true};
    float tscale[4][4] = {};      // texcoord scale per stage (1/size for linear textures)
    const float (*vs_constants)[4] = nullptr;  // 192 registers; null = the shader reads none
    uint64_t vs_version = 0;                    // changes whenever the registers do (0 = always re-send)
    float screen[4] = {};         // 2/w, 2/h, 1/zmax
    float fog_color[4] = {};
    float fog_params[4] = {};     // start, end, density, mode: -1 fog off, 0 oFog.x is the factor, 1 exp, 2 exp2, 3 linear
    float alpha_test[4] = {};     // ref, func, enabled
    bool blend = false;
    uint32_t blend_src = 1, blend_dst = 0, blend_op = 0x8006;  // GL enums as the NV2A takes them
    uint32_t color_mask = 0x01010101;                            // a r g b bytes
    bool z_enable = false, z_write = true;
    uint32_t z_func = 0x203;                                     // GL_LEQUAL
    bool stencil = false;                                        // stencil test, GL enums as the NV2A takes them
    uint32_t stencil_func = 0x207, stencil_ref = 0, stencil_mask = 0xFF, stencil_write_mask = 0xFF;
    uint32_t stencil_fail = 0x1E00, stencil_zfail = 0x1E00, stencil_pass = 0x1E00;  // GL_KEEP
    int cull = 0;                                                // 0 none, 1 cull clockwise, 2 cull counter-clockwise
    bool scissor = false;
    bool flat = false;            // a 2D draw (the HUD, menus, screen effects): not interpolated at 120 fps
    GfxRect scissor_rect = {};
};

// topology: D3D11_PRIMITIVE_TOPOLOGY; vertices: `stride_floats` floats per vertex; indices optional
void gfx_draw(const GfxState& s, int topology, const float* vertices, uint32_t vertex_count, uint32_t stride_floats,
              const uint32_t* indices, uint32_t index_count);
