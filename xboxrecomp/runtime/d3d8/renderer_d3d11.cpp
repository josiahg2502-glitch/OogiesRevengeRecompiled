// Direct3D 11 backend: window, swap chain, back buffer and depth buffer.
#include <d3d11_1.h>
#include <d3d11_4.h>
#include <d3d11sdklayers.h>
#include <dwmapi.h>
#include <dxgi1_2.h>
#include <windows.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <cstdio>
#include <cwchar>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

#include "../config.h"
#include "../runtime.h"
#include "renderer.h"

static HWND g_window;
static ID3D11Device* g_device;
static ID3D11DeviceContext1* g_ctx;
static IDXGISwapChain1* g_swap;
static ID3D11RenderTargetView* g_backbuffer;
static ID3D11DepthStencilView* g_depth;
static ID3D11ShaderResourceView* g_depth_view;  // the back buffer's depth as a texture (ambient occlusion)
static ID3D11Texture2D* g_scene;            // the game's back buffer (g_backbuffer is its view)
static ID3D11RenderTargetView* g_rt;        // what draws and clears go to: the back buffer or a render texture
static ID3D11DepthStencilView* g_rt_depth;  // its depth buffer, if it has one
static uint32_t g_rt_width, g_rt_height;
static uint32_t g_width, g_height;  // internal resolution: the game's size times the scale
static float g_scale;  // internal pixels per game pixel
static float g_wide = 1;  // the back buffer's width over 4:3 (game pixels on it are g_scale * g_wide wide)
float gfx_wide() { return g_wide; }
static float rt_x_scale() { return g_scale * (g_rt == g_backbuffer ? g_wide : 1); }  // game x to target pixels

// ---- in-between frames (120 fps) ----
// The game steps its world once per 59.94 Hz vblank. At 120 fps every game frame is recorded as it is drawn
// (targets, clears, copies, draws with their vertices and shader constants); before it is shown, the recording is
// drawn once more with each draw's constants and vertices halfway between this frame's and those of the same draw
// in the frame before: the picture between two game steps. A present thread shows the two half a frame apart.
static bool g_interp;  // [display] fps = 120
static std::atomic<unsigned> g_frames_shown;  // pictures presented (the title bar's rate)
static std::atomic<double> g_display_hz;      // the compositor's refresh rate, checked every 10 s
static double compositor_hz();
static ID3D11Texture2D* g_scene_mid;  // the in-between picture, the back buffer's size
static ID3D11RenderTargetView* g_backbuffer_mid;
static ID3D11ShaderResourceView* g_mid_view;
static ID3D11ShaderResourceView* g_scene_view;  // the back buffer as a texture, for blit
static bool g_flat_frame;  // the frame being presented drew no 3D world (see gfx_flat_frame)
static void fill_sides(ID3D11Texture2D* scene, ID3D11RenderTargetView* target);
namespace rec {
enum Kind : uint8_t { TARGET, CLEAR, COPY, SNAPSHOT, DRAW, AO };
struct Cmd {
    Kind kind;
    int a = -1, b = -1;                         // TARGET: id, depth; COPY: src, dst; DRAW: draw index
    uint32_t flags = 0, argb = 0, stencil = 0;  // CLEAR
    float z = 0;
    uint32_t first = 0, count = 0;              // CLEAR: its rects in Frame::rects
    bool has_rect = false;                      // COPY
    GfxRect rect = {};
    int32_t x = 0, y = 0;
};
struct Draw {
    GfxState s;
    int topology, consts;  // consts: index into Frame::consts, -1 for none
    uint32_t vfirst, vcount, stride, ifirst, icount;
    uint64_t key;          // what makes it "the same draw" in the next frame (with its order among equals)
};
struct Frame {
    std::vector<Cmd> cmds;
    std::vector<Draw> draws;
    std::vector<float> verts;
    std::vector<uint32_t> idx;
    std::vector<std::array<float, 768>> consts;  // the 192 vertex shader registers, one copy per change
    std::vector<GfxRect> rects;
};
Frame frames[2];
int cur;                 // the frame being recorded; cur ^ 1 is the one before
bool replaying;          // drawing a recording: nothing is recorded
int target = -1;         // the current render target, as the next frame starts with it
bool target_depth = true;
const float (*last_constants)[4];
uint64_t last_version;

bool on() { return g_interp && !replaying; }
void begin_frame() {
    cur ^= 1;
    Frame& f = frames[cur];
    f.cmds.clear(), f.draws.clear(), f.verts.clear(), f.idx.clear(), f.consts.clear(), f.rects.clear();
    last_constants = nullptr;
    Cmd c{TARGET};
    c.a = target, c.b = target_depth;
    f.cmds.push_back(c);
}
uint64_t key(const GfxState& s, int topology, uint32_t vcount, uint32_t stride, uint32_t icount) {
    uint64_t h = 1469598103934665603ull;
    auto mix = [&](uint64_t v) { h = (h ^ v) * 1099511628211ull; };
    mix(uint32_t(target)), mix(uint32_t(s.vs)), mix(uint32_t(s.ps)), mix(uint32_t(topology));
    for (int t : s.textures) mix(uint32_t(t));
    mix(vcount), mix(stride), mix(icount);
    return h;
}
void draw(const GfxState& s, int topology, const float* v, uint32_t vcount, uint32_t stride, const uint32_t* idx, uint32_t icount) {
    Frame& f = frames[cur];
    Draw d{s, topology, -1, uint32_t(f.verts.size()), vcount, stride, uint32_t(f.idx.size()), icount, key(s, topology, vcount, stride, icount)};
    if (s.vs_constants) {
        if (f.consts.empty() || s.vs_constants != last_constants || s.vs_version != last_version || !s.vs_version) {
            f.consts.emplace_back();
            std::memcpy(f.consts.back().data(), s.vs_constants, sizeof(float) * 768);
            last_constants = s.vs_constants, last_version = s.vs_version;
        }
        d.consts = int(f.consts.size() - 1);
    }
    f.verts.insert(f.verts.end(), v, v + size_t(vcount) * stride);
    if (idx) f.idx.insert(f.idx.end(), idx, idx + icount);
    Cmd c{DRAW};
    c.a = int(f.draws.size());
    f.draws.push_back(d);
    f.cmds.push_back(c);
}
}  // namespace rec

static void check(HRESULT hr, const char* what) {
    if (FAILED(hr)) fatal("Direct3D 11: %s failed (%08lX)", what, (unsigned long)hr);
}

// A driver update, a GPU reset or a graphics switch removes the device: say so instead of freezing on a black window
static void check_present(HRESULT hr) {
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        fatal("The graphics driver stopped responding (Direct3D device %s, %08lX).\nRestart the game; your progress since the "
              "last save is lost.", hr == DXGI_ERROR_DEVICE_RESET ? "reset" : "removed",
              (unsigned long)(g_device ? g_device->GetDeviceRemovedReason() : hr));
}

static bool g_resized;  // the window's client size changed: the swap chain follows at the next present
static unsigned g_size_changes;  // WM_SIZE count (the menu resizes the swap chain on its own)
static ID3D11RenderTargetView* g_window_view;  // the swap chain's buffer, at 60 fps
static std::mutex g_swap_mutex;   // the swap chain and g_shown: the present thread vs a window resize or the menu
static std::atomic<bool> g_menu_key;  // F1 was pressed (the in-game menu)

static void toggle_fullscreen(HWND h) {  // borderless fullscreen on the window's monitor, and back
    static WINDOWPLACEMENT saved = {sizeof saved};
    LONG style = GetWindowLongW(h, GWL_STYLE);
    if (style & WS_OVERLAPPEDWINDOW) {
        MONITORINFO mi = {sizeof mi};
        GetWindowPlacement(h, &saved);
        GetMonitorInfoW(MonitorFromWindow(h, MONITOR_DEFAULTTOPRIMARY), &mi);
        SetWindowLongW(h, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
        SetWindowPos(h, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left,
                     mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        ShowCursor(FALSE);
    } else {
        SetWindowLongW(h, GWL_STYLE, style | WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(h, &saved);
        SetWindowPos(h, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        ShowCursor(TRUE);
    }
}

constexpr UINT WM_SET_FULLSCREEN = WM_APP + 1;  // wParam: on (window changes happen on the window's own thread)

static LRESULT CALLBACK wndproc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_SET_FULLSCREEN:
        if (bool(wp) != !(GetWindowLongW(h, GWL_STYLE) & WS_OVERLAPPEDWINDOW)) toggle_fullscreen(h);
        return 0;
    case WM_CLOSE: std::_Exit(0);  // shortcut: no save-on-exit handshake with the game yet
    case WM_SIZE: g_resized = true, ++g_size_changes; return 0;
    case WM_SYSKEYDOWN:
        if (wp == VK_RETURN) return toggle_fullscreen(h), 0;  // Alt+Enter, like most PC games
        break;
    case WM_KEYDOWN:
        if (wp == VK_F11) toggle_fullscreen(h);
        if (wp == VK_F1 && !(lp & 0x40000000)) g_menu_key = true;  // not on auto-repeat
        return 0;
    }
    return DefWindowProcW(h, msg, wp, lp);
}

bool gfx_menu_requested() { return g_menu_key.exchange(false); }
void gfx_set_fullscreen(bool on) {
    if (g_window) PostMessageW(g_window, WM_SET_FULLSCREEN, on, 0);
}

void gfx_init(uint32_t width, uint32_t height) {
    if (g_device) return;  // already open (the menu opened the window before the game created its device)
    // the internal resolution: Config.toml [display] resolution (4K by default, or the screen's height);
    // OOGIE_SCALE=1.5 etc. picks a multiple of the game's size directly
    const char* scale_env = std::getenv("OOGIE_SCALE");
    int lines = config().resolution ? config().resolution : GetSystemMetrics(SM_CYSCREEN);
    float scale = scale_env ? std::strtof(scale_env, nullptr) : float(lines) / height;
    if (!(scale >= 1 && scale <= 9)) scale = 2160.f / height;
    g_scale = scale;
    // a wider picture: the back buffer gets the screen's (or the chosen) shape; the game's 3D view is widened to fill
    // it (D3DXMatrixPerspectiveFovLH) while its 2D layer keeps 4:3 in the middle (the vertex shader epilogue)
    float aspect = config().aspect ? config().aspect : float(GetSystemMetrics(SM_CXSCREEN)) / GetSystemMetrics(SM_CYSCREEN);
    g_wide = std::max(1.f, aspect * height / width);
    g_width = uint32_t(width * scale * g_wide + 0.5f) & ~1u, g_height = uint32_t(height * scale + 0.5f);

    WNDCLASSW wc = {};
    wc.lpfnWndProc = wndproc;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.hCursor = LoadCursorW(nullptr, MAKEINTRESOURCEW(32512));  // IDC_ARROW
    wc.lpszClassName = L"OogiesRevenge";
    RegisterClassW(&wc);
    RECT work;  // the window starts as large as fits the desktop at the game's aspect
    SystemParametersInfoW(SPI_GETWORKAREA, 0, &work, 0);
    LONG wh = (work.bottom - work.top) * 9 / 10, ww = LONG(wh * float(g_width) / g_height);
    if (ww > (work.right - work.left) * 9 / 10) ww = (work.right - work.left) * 9 / 10, wh = LONG(ww * float(g_height) / g_width);
    RECT r = {0, 0, ww, wh};
    AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
    // The window lives on a thread of its own that only handles its messages: the menu opens it on the main thread,
    // but the game draws from whichever guest thread it likes, and a window whose thread stops reading messages is
    // "not responding" to Windows, which then offers to close it.
    std::atomic<HWND> made{nullptr};
    std::thread([&] {
        HWND w = CreateWindowExW(0, wc.lpszClassName, L"The Nightmare Before Christmas: Oogie's Revenge",
                                 WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, r.right - r.left,
                                 r.bottom - r.top, nullptr, nullptr, wc.hInstance, nullptr);
        if (!w) fatal("could not create the game window");
        HICON icon = HICON(LoadImageW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(1), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE));  // the .rc's
        if (icon) SendMessageW(w, WM_SETICON, ICON_BIG, LPARAM(icon)), SendMessageW(w, WM_SETICON, ICON_SMALL, LPARAM(icon));
        if (config().fullscreen) toggle_fullscreen(w);
        made = w;
        MSG msg;
        while (GetMessageW(&msg, nullptr, 0, 0) > 0) TranslateMessage(&msg), DispatchMessageW(&msg);
    }).detach();
    while (!made) Sleep(1);
    g_window = made;

    D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;
    ID3D11DeviceContext* ctx;
    UINT device_flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    if (std::getenv("OOGIE_D3D_DEBUG")) device_flags |= D3D11_CREATE_DEVICE_DEBUG;  // debug layer messages at each present
    check(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, device_flags, &level, 1,
                            D3D11_SDK_VERSION, &g_device, nullptr, &ctx),
          "D3D11CreateDevice");
    check(ctx->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&g_ctx)), "context 11.1");
    ctx->Release();

    IDXGIDevice* dxgi_device;
    IDXGIAdapter* adapter;
    IDXGIFactory2* factory;
    check(g_device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgi_device)), "IDXGIDevice");
    check(dxgi_device->GetAdapter(&adapter), "GetAdapter");
    check(adapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&factory)), "IDXGIFactory2");
    DXGI_SWAP_CHAIN_DESC1 sd = {};  // the window's size (0 = its client area); gfx_present draws the scene into it
    sd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.SampleDesc.Count = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 2;
    sd.Scaling = DXGI_SCALING_STRETCH;
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    check(factory->CreateSwapChainForHwnd(g_device, g_window, &sd, nullptr, nullptr, &g_swap), "swap chain");
    factory->MakeWindowAssociation(g_window, DXGI_MWA_NO_ALT_ENTER);
    factory->Release(), adapter->Release(), dxgi_device->Release();

    // the game's back buffer is a texture of our own (copied to the swap chain at present), so the game can
    // copy from it and later effects can read it
    D3D11_TEXTURE2D_DESC bd = {};
    bd.Width = g_width, bd.Height = g_height, bd.MipLevels = 1, bd.ArraySize = 1;
    bd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    bd.SampleDesc.Count = 1;
    bd.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    check(g_device->CreateTexture2D(&bd, nullptr, &g_scene), "scene texture");
    check(g_device->CreateRenderTargetView(g_scene, nullptr, &g_backbuffer), "back buffer view");
    check(g_device->CreateShaderResourceView(g_scene, nullptr, &g_scene_view), "scene view");
    // [display] fps: 120 draws an in-between picture per game frame (auto: when the screen refreshes at 120 Hz+)
    int fps = std::getenv("OOGIE_FPS") ? std::atoi(std::getenv("OOGIE_FPS")) : config().fps;
    g_display_hz = compositor_hz();
    // a 60 Hz screen cannot show the in-between pictures: presenting them anyway held the device in Present and slowed
    // the game to half speed (4K: 30 fps), so 120 needs a screen of 100 Hz or more (OOGIE_FPS=120 forces it, testing)
    bool fast_screen = g_display_hz.load() >= 100;
    g_interp = std::getenv("OOGIE_FPS") ? fps == 120 : (fps == 120 || fps == 0) && fast_screen;
    if (fps == 120 && !fast_screen && !std::getenv("OOGIE_FPS"))
        std::fprintf(stderr, "[gfx] 120 fps needs a screen of 100 Hz or more; this one runs at %.0f Hz: 60 fps\n", g_display_hz.load());
    if (g_interp) {
        check(g_device->CreateTexture2D(&bd, nullptr, &g_scene_mid), "in-between texture");
        check(g_device->CreateRenderTargetView(g_scene_mid, nullptr, &g_backbuffer_mid), "in-between view");
        check(g_device->CreateShaderResourceView(g_scene_mid, nullptr, &g_mid_view), "in-between texture view");
        ID3D11Multithread* mt;  // the present thread copies and presents alongside the game's drawing
        check(g_ctx->QueryInterface(__uuidof(ID3D11Multithread), reinterpret_cast<void**>(&mt)), "multithread");
        mt->SetMultithreadProtected(TRUE);
        mt->Release();
        rec::begin_frame();
    }

    D3D11_TEXTURE2D_DESC dd = {};
    dd.Width = g_width, dd.Height = g_height, dd.MipLevels = 1, dd.ArraySize = 1;
    dd.Format = DXGI_FORMAT_R24G8_TYPELESS;  // D24S8, also readable by the ambient occlusion pass
    dd.SampleDesc.Count = 1;
    dd.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
    ID3D11Texture2D* depth;
    check(g_device->CreateTexture2D(&dd, nullptr, &depth), "depth buffer");
    D3D11_DEPTH_STENCIL_VIEW_DESC dsv = {};
    dsv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT, dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    check(g_device->CreateDepthStencilView(depth, &dsv, &g_depth), "depth view");
    D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
    srv.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS, srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D, srv.Texture2D.MipLevels = 1;
    check(g_device->CreateShaderResourceView(depth, &srv, &g_depth_view), "depth texture view");
    depth->Release();
    gfx_set_render_target(-1, true);
    std::fprintf(stderr, "[gfx] Direct3D 11 at %ux%u (game %ux%u), %d fps (screen %.0f Hz)\n", g_width, g_height, width, height,
                 g_interp ? 120 : 60, g_display_hz.load());
}

void gfx_clear(uint32_t flags, uint32_t argb, float z, uint32_t stencil, const GfxRect* rects, uint32_t count) {
    if (rec::on()) {
        rec::Cmd c{rec::CLEAR};
        c.flags = flags, c.argb = argb, c.z = z, c.stencil = stencil, c.first = uint32_t(rec::frames[rec::cur].rects.size()), c.count = count;
        rec::frames[rec::cur].rects.insert(rec::frames[rec::cur].rects.end(), rects, rects + count);
        rec::frames[rec::cur].cmds.push_back(c);
    }
    static const char* debug_color = std::getenv("OOGIE_CLEAR_COLOR");  // e.g. FF00FF00: shows what clears reach
    if (debug_color) argb = std::strtoul(debug_color, nullptr, 16);
    if (flags & 0xF0) {
        float color[4] = {((argb >> 16) & 0xFF) / 255.f, ((argb >> 8) & 0xFF) / 255.f, (argb & 0xFF) / 255.f,
                          (argb >> 24) / 255.f};
        if (count) {
            D3D11_RECT r[16];
            uint32_t n = count < 16 ? count : 16;
            float s = g_scale, sx = rt_x_scale();  // rects are in game pixels
            for (uint32_t k = 0; k < n; ++k)
                r[k] = {std::lround(rects[k].x1 * sx), std::lround(rects[k].y1 * s), std::lround(rects[k].x2 * sx), std::lround(rects[k].y2 * s)};
            g_ctx->ClearView(g_rt, color, r, n);
        } else {
            g_ctx->ClearRenderTargetView(g_rt, color);
        }
    }
    UINT ds = (flags & 1 ? D3D11_CLEAR_DEPTH : 0) | (flags & 2 ? D3D11_CLEAR_STENCIL : 0);
    if (ds && g_rt_depth) g_ctx->ClearDepthStencilView(g_rt_depth, ds, z, UINT8(stencil));  // shortcut: ignores rects
}

// OOGIE_SCREENSHOT=<file.bmp>: saves the back buffer at every present (for automated checks)
static void save_texture(ID3D11Texture2D* buf, const char* path);
static void screenshot(const char* path) {
    ID3D11Texture2D* buf = g_scene;
    buf->AddRef();
    save_texture(buf, path);
    buf->Release();
}
static void save_texture(ID3D11Texture2D* buf, const char* path) {
    D3D11_TEXTURE2D_DESC d;
    buf->GetDesc(&d);
    if ((d.Format >= 70 && d.Format <= 84) || d.Format >= 94) return;  // block-compressed: the BMP writer below handles 32-bit pixels only
    d.Usage = D3D11_USAGE_STAGING, d.BindFlags = 0, d.CPUAccessFlags = D3D11_CPU_ACCESS_READ, d.MiscFlags = 0;
    ID3D11Texture2D* staging;
    if (SUCCEEDED(g_device->CreateTexture2D(&d, nullptr, &staging))) {
        g_ctx->CopyResource(staging, buf);
        D3D11_MAPPED_SUBRESOURCE m;
        if (SUCCEEDED(g_ctx->Map(staging, 0, D3D11_MAP_READ, 0, &m))) {
            std::string tmp = std::string(path) + ".tmp";  // renamed when complete: a kill never leaves half a file
            if (FILE* f = std::fopen(tmp.c_str(), "wb")) {
                BITMAPFILEHEADER fh = {0x4D42, DWORD(54 + d.Width * d.Height * 4), 0, 0, 54};
                BITMAPINFOHEADER ih = {sizeof ih, LONG(d.Width), -LONG(d.Height), 1, 32, BI_RGB};
                std::fwrite(&fh, sizeof fh, 1, f), std::fwrite(&ih, sizeof ih, 1, f);
                std::vector<uint8_t> row(d.Width * 4);
                for (UINT y = 0; y < d.Height; ++y) {  // the window ignores alpha, so the capture is opaque too
                    std::memcpy(row.data(), static_cast<uint8_t*>(m.pData) + y * m.RowPitch, row.size());
                    for (UINT x = 0; x < d.Width; ++x) row[x * 4 + 3] = 255;
                    std::fwrite(row.data(), 4, d.Width, f);
                }
                std::fclose(f);
                MoveFileExA(tmp.c_str(), path, MOVEFILE_REPLACE_EXISTING);
            }
            g_ctx->Unmap(staging, 0);
        }
        staging->Release();
    }
}

unsigned g_presents;
static void drain_debug_messages();

static double compositor_hz() {  // the refresh rate DWM composes at (the window's display), 0 if unknown
    DWM_TIMING_INFO t = {sizeof t};
    return SUCCEEDED(DwmGetCompositionTimingInfo(nullptr, &t)) && t.rateRefresh.uiDenominator
               ? double(t.rateRefresh.uiNumerator) / t.rateRefresh.uiDenominator : 0;
}

// shortcut: the output is taken once; a window moved to another display keeps the first one's vblank timing
static std::atomic<IDXGIOutput*> g_output{nullptr};

bool gfx_wait_vblank() {
    IDXGIOutput* out = g_output.load();
    if (!out) return false;
    // only a display refreshing at 59-61 Hz may stand in for the Xbox's vblank (others would speed the game up or
    // slow it down), or one at 119-121 Hz every second refresh; its rate is asked of the compositor again every
    // 10 s, as the window can move or modes change
    static int per_vblank;  // display refreshes per game vblank: 1, 2 or 0 (not usable)
    static unsigned calls;
    if (calls++ % 600 == 0) {
        double hz = compositor_hz();
        g_display_hz = hz;
        per_vblank = hz > 59 && hz < 61 ? 1 : hz > 119 && hz < 121 ? 2 : 0;
    }
    for (int k = 0; k < per_vblank; ++k)
        if (FAILED(out->WaitForVBlank())) return false;
    return per_vblank > 0;
}

namespace {
ID3DBlob* compile(const std::string& src, const char* target);  // below, with the shader cache
}
static bool g_pipeline_touched;  // gfx_present changed pipeline state behind gfx_draw's back

// Draws the scene into the window: 4:3 with black bars (or stretched: [display] aspect), averaging the texels
// under each window pixel when the scene is larger (4K on a 1080p screen) and Catmull-Rom when it is smaller
static void blit(ID3D11ShaderResourceView* src, ID3D11RenderTargetView* dst, float w, float h, float shape = 0) {
    static ID3D11VertexShader* vs;
    static ID3D11PixelShader* ps;
    static ID3D11SamplerState* smp;
    if (!vs) {
        ID3DBlob* v = compile("float4 main(uint id : SV_VertexID, out float2 uv : TEXCOORD0) : SV_Position {\n"
                              "  uv = float2((id << 1) & 2, id & 2); return float4(uv * float2(2, -2) + float2(-1, 1), 0, 1); }\n",
                              "vs_5_0");
        ID3DBlob* f = compile(
            "Texture2D scene : register(t0); SamplerState smp : register(s0);\n"
            "float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {\n"
            "  float2 size; scene.GetDimensions(size.x, size.y);\n"
            "  float2 step = max(abs(ddx(uv)), abs(ddy(uv))) * size;  // scene texels per window pixel\n"
            "  int n = clamp(int(ceil(max(step.x, step.y))), 1, 4);\n"
            "  if (n == 1) {  // magnified: Catmull-Rom (9 bilinear taps)\n"
            "    float2 sp = uv * size, p1 = floor(sp - 0.5) + 0.5, t = sp - p1;\n"
            "    float2 w0 = t * (-0.5 + t * (1 - 0.5 * t)), w1 = 1 + t * t * (-2.5 + 1.5 * t);\n"
            "    float2 w2 = t * (0.5 + t * (2 - 1.5 * t)), w3 = t * t * (-0.5 + 0.5 * t), w12 = w1 + w2;\n"
            "    float2 a = (p1 - 1) / size, b = (p1 + w2 / w12) / size, c = (p1 + 2) / size;\n"
            "    float3 r = (scene.SampleLevel(smp, float2(a.x, a.y), 0).rgb * w0.x + scene.SampleLevel(smp, float2(b.x, a.y), 0).rgb * w12.x\n"
            "              + scene.SampleLevel(smp, float2(c.x, a.y), 0).rgb * w3.x) * w0.y\n"
            "            + (scene.SampleLevel(smp, float2(a.x, b.y), 0).rgb * w0.x + scene.SampleLevel(smp, float2(b.x, b.y), 0).rgb * w12.x\n"
            "              + scene.SampleLevel(smp, float2(c.x, b.y), 0).rgb * w3.x) * w12.y\n"
            "            + (scene.SampleLevel(smp, float2(a.x, c.y), 0).rgb * w0.x + scene.SampleLevel(smp, float2(b.x, c.y), 0).rgb * w12.x\n"
            "              + scene.SampleLevel(smp, float2(c.x, c.y), 0).rgb * w3.x) * w3.y;\n"
            "    return float4(saturate(r), 1);\n"
            "  }\n"
            "  float3 sum = 0;  // minified: the average of an n x n grid of bilinear taps over the pixel's footprint\n"
            "  float2 d = max(abs(ddx(uv)), abs(ddy(uv)));\n"
            "  for (int y = 0; y < n; ++y) for (int x = 0; x < n; ++x)\n"
            "    sum += scene.SampleLevel(smp, uv + d * ((float2(x, y) + 0.5) / n - 0.5), 0).rgb;\n"
            "  return float4(sum / (n * n), 1);\n"
            "}\n",
            "ps_5_0");
        if (!v || !f) fatal("the presentation shaders did not compile");
        check(g_device->CreateVertexShader(v->GetBufferPointer(), v->GetBufferSize(), nullptr, &vs), "present vs");
        check(g_device->CreatePixelShader(f->GetBufferPointer(), f->GetBufferSize(), nullptr, &ps), "present ps");
        v->Release(), f->Release();
        D3D11_SAMPLER_DESC sd = {};
        sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sd.MaxLOD = D3D11_FLOAT32_MAX;
        check(g_device->CreateSamplerState(&sd, &smp), "present sampler");
    }
    float vw = w, vh = h;
    if (!config().stretch || shape) {  // the picture's shape, centred with black bars
        float aspect = shape ? shape : float(g_width) / float(g_height);
        if (w / h > aspect) vw = h * aspect;
        else vh = w / aspect;
    }
    const float black[4] = {0, 0, 0, 1};
    g_ctx->ClearRenderTargetView(dst, black);
    g_ctx->OMSetRenderTargets(1, &dst, nullptr);
    D3D11_VIEWPORT vp = {std::floor((w - vw) / 2), std::floor((h - vh) / 2), std::floor(vw), std::floor(vh), 0, 1};
    g_ctx->RSSetViewports(1, &vp);
    g_ctx->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
    g_ctx->OMSetDepthStencilState(nullptr, 0);
    g_ctx->RSSetState(nullptr);
    g_ctx->IASetInputLayout(nullptr);
    g_ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    g_ctx->VSSetShader(vs, nullptr, 0);
    g_ctx->PSSetShader(ps, nullptr, 0);
    g_ctx->PSSetShaderResources(0, 1, &src);
    g_ctx->PSSetSamplers(0, 1, &smp);
    g_ctx->Draw(3, 0);
    ID3D11ShaderResourceView* none = nullptr;
    g_ctx->PSSetShaderResources(0, 1, &none);  // the scene is drawn into again next frame
    g_pipeline_touched = true;
}


// The menu: a BGRA canvas drawn on the CPU, shown in the window at its own shape, one per vertical refresh.
void gfx_show_canvas(const uint32_t* bgra, uint32_t w, uint32_t h) {
    static ID3D11Texture2D* tex;
    static ID3D11ShaderResourceView* view;
    static ID3D11RenderTargetView* out;
    static uint32_t tw, th;
    if (!tex || tw != w || th != h) {
        if (view) view->Release(), tex->Release();
        D3D11_TEXTURE2D_DESC d = {};
        d.Width = w, d.Height = h, d.MipLevels = 1, d.ArraySize = 1, d.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        d.SampleDesc.Count = 1, d.Usage = D3D11_USAGE_DEFAULT, d.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        check(g_device->CreateTexture2D(&d, nullptr, &tex), "menu canvas");
        check(g_device->CreateShaderResourceView(tex, nullptr, &view), "menu canvas view");
        tw = w, th = h;
    }
    g_ctx->UpdateSubresource(tex, 0, nullptr, bgra, w * 4, 0);
    std::lock_guard<std::mutex> l(g_swap_mutex);  // the 120 fps present thread may still be showing the game's last frame
    static unsigned size_seen;
    if (size_seen != g_size_changes) {  // g_resized stays set: the game's own presenting follows the size too
        size_seen = g_size_changes;
        if (g_window_view) g_window_view->Release(), g_window_view = nullptr;
        check(g_swap->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0), "resize swap chain");
    }
    if (!out) {
        ID3D11Texture2D* buf;
        check(g_swap->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buf)), "swap chain buffer");
        check(g_device->CreateRenderTargetView(buf, nullptr, &out), "swap chain view");
        buf->Release();
    }
    DXGI_SWAP_CHAIN_DESC1 sd;
    g_swap->GetDesc1(&sd);
    blit(view, out, float(sd.Width), float(sd.Height), float(w) / float(h));
    check_present(g_swap->Present(1, 0));
    out->Release(), out = nullptr;  // the game's own presenting takes over the swap chain afterwards
    if (g_rt) g_ctx->OMSetRenderTargets(1, &g_rt, g_rt_depth);  // the in-game menu: back to the game's target
}

std::vector<uint32_t> gfx_scene_pixels(uint32_t& w, uint32_t& h) {
    std::vector<uint32_t> px;
    D3D11_TEXTURE2D_DESC d;
    g_scene->GetDesc(&d);
    d.Usage = D3D11_USAGE_STAGING, d.BindFlags = 0, d.CPUAccessFlags = D3D11_CPU_ACCESS_READ, d.MiscFlags = 0;
    ID3D11Texture2D* staging;
    if (FAILED(g_device->CreateTexture2D(&d, nullptr, &staging))) return px;
    g_ctx->CopyResource(staging, g_scene);
    D3D11_MAPPED_SUBRESOURCE m;
    if (SUCCEEDED(g_ctx->Map(staging, 0, D3D11_MAP_READ, 0, &m))) {
        w = d.Width, h = d.Height, px.resize(size_t(w) * h);
        for (UINT y = 0; y < h; ++y) std::memcpy(&px[size_t(y) * w], static_cast<uint8_t*>(m.pData) + y * m.RowPitch, w * 4);
        g_ctx->Unmap(staging, 0);
    }
    staging->Release();
    return px;
}

// 60 fps: the scene straight into the window, presented by the game's thread at its vblank
static void blit_scene() {
    ID3D11RenderTargetView*& out = g_window_view;
    if (g_resized && out) out->Release(), out = nullptr;
    if (g_resized) {
        g_resized = false;
        check(g_swap->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0), "resize swap chain");
    }
    if (!out) {
        ID3D11Texture2D* buf;
        check(g_swap->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buf)), "swap chain buffer");
        check(g_device->CreateRenderTargetView(buf, nullptr, &out), "swap chain view");
        buf->Release();
    }
    DXGI_SWAP_CHAIN_DESC1 sd;
    g_swap->GetDesc1(&sd);
    blit(g_scene_view, out, float(sd.Width), float(sd.Height));
}

// ---- in-between frames: drawing them and showing them (see "in-between frames (120 fps)" above) ----

// Draws the last recording into g_scene_mid, each draw halfway to the same draw in the frame before. False (nothing
// drawn) when there is no frame before or the two hardly match: a cut or a load, where halfway would be a blend.
static bool draw_in_between() {
    using namespace rec;
    Frame& now = frames[cur];
    Frame& before = frames[cur ^ 1];
    static const bool log = std::getenv("OOGIE_INTERP_LOG") != nullptr;
    if (before.draws.empty() || now.draws.empty()) return false;
    std::unordered_map<uint64_t, std::vector<int>> pool;  // the frame before's draws by key, in order
    for (int i = 0; i < int(before.draws.size()); ++i) pool[before.draws[i].key].push_back(i);
    // how far a draw's shader constants (its matrices) moved: the relative change over the registers that differ
    auto change_of = [&](const Draw& a, const Draw& b) {
        if (a.consts < 0 || b.consts < 0) return 0.f;
        const float* x = now.consts[a.consts].data();
        const float* y = before.consts[b.consts].data();
        float diff = 0, size = 0;
        for (int r = 0; r < 768; r += 4) {
            float dr = 0, sr = 0;
            for (int k = r; k < r + 4; ++k) dr += std::fabs(x[k] - y[k]), sr += std::fabs(x[k]) + std::fabs(y[k]);
            if (dr > 0) diff += dr, size += sr;
        }
        return size > 0 ? diff / size : 0.f;
    };
    std::unordered_map<uint64_t, std::vector<bool>> taken;
    std::unordered_map<uint64_t, size_t> used;
    std::vector<int> match(now.draws.size(), -1);
    size_t matched = 0;
    for (size_t i = 0; i < now.draws.size(); ++i) {
        auto it = pool.find(now.draws[i].key);
        if (it == pool.end()) continue;
        const std::vector<int>& cand = it->second;
        if (cand.size() <= 16) {
            // alike draws (the same skeleton, pumpkin or prop several times) come in the order the game sorts them,
            // which changes as they move: each takes the one of the frame before that moved least, not the n-th
            std::vector<bool>& t = taken[now.draws[i].key];
            t.resize(cand.size());
            int best = -1;
            float best_change = 0;
            for (size_t k = 0; k < cand.size(); ++k) {
                if (t[k]) continue;
                float ch = change_of(now.draws[i], before.draws[cand[k]]);
                if (best < 0 || ch < best_change) best = int(k), best_change = ch;
            }
            if (best >= 0) t[best] = true, match[i] = cand[best], ++matched;
        } else {
            size_t& u = used[now.draws[i].key];
            if (u < cand.size()) match[i] = cand[u++], ++matched;
        }
    }
    if (matched * 2 < now.draws.size()) {
        if (log) std::fprintf(stderr, "[interp] frame %u: only %zu of %zu draws matched\n", g_presents, matched, now.draws.size());
        return false;
    }
    // a camera cut: the same draws, but their matrices jump (halfway would be a view from nowhere). Measured as the
    // median relative change of the shader constants over the matched draws that have them.
    std::vector<float> change;
    for (size_t i = 0; i < now.draws.size(); ++i) {
        const Draw& d = now.draws[i];
        if (match[i] < 0 || d.consts < 0 || d.s.stencil || before.draws[match[i]].consts < 0) continue;
        const float* x = now.consts[d.consts].data();
        const float* y = before.consts[before.draws[match[i]].consts].data();
        float diff = 0, size = 0;  // over the registers that changed (most never do, and would hide a jump)
        for (int r = 0; r < 768; r += 4) {
            float dr = 0, sr = 0;
            for (int k = r; k < r + 4; ++k) dr += std::fabs(x[k] - y[k]), sr += std::fabs(x[k]) + std::fabs(y[k]);
            if (dr > 0) diff += dr, size += sr;
        }
        change.push_back(size > 0 ? diff / size : 0);
    }
    float median = 0;
    if (!change.empty()) {
        std::nth_element(change.begin(), change.begin() + change.size() / 2, change.end());
        median = change[change.size() / 2];
    }
    if (log && (median > 0.02f || g_presents % 120 == 0))
        std::fprintf(stderr, "[interp] frame %u: constants changed %.4f (%zu draws), %zu of %zu draws matched\n", g_presents, median,
                     change.size(), matched, now.draws.size());
    if (median > 0.2f) {
        if (log) {  // OOGIE_INTERP_LOG=dir: the frame after each detected cut, to check what was skipped
            char path[300];
            std::snprintf(path, sizeof path, "%s/cut%05u.bmp", std::getenv("OOGIE_INTERP_LOG"), g_presents);
            save_texture(g_scene, path);
        }
        return false;
    }
    std::swap(g_scene, g_scene_mid), std::swap(g_backbuffer, g_backbuffer_mid);
    g_ctx->CopyResource(g_scene, g_scene_mid);  // what the frame starts on, if it does not clear
    replaying = true;
    static float mixed[192][4];
    static uint64_t version = 1ull << 62;  // above any version the D3D8 layer hands out
    int last_now = -2, last_before = -2;
    std::vector<float> v;
    for (const Cmd& c : now.cmds) switch (c.kind) {
    case TARGET: gfx_set_render_target(c.a, c.b != 0); break;
    case CLEAR: gfx_clear(c.flags, c.argb, c.z, c.stencil, c.count ? &now.rects[c.first] : nullptr, c.count); break;
    case COPY: gfx_copy(c.a, c.b, c.has_rect ? &c.rect : nullptr, c.x, c.y); break;
    case SNAPSHOT: gfx_backbuffer_snapshot(); break;
    case AO: gfx_ambient_occlusion(); break;
    case DRAW: {
        const Draw& d = now.draws[c.a];
        // stencil draws are drawn as in this frame: the game builds its shadow volumes anew from each frame's
        // silhouette edges (1700 quads alike), so the n-th quad of two frames is not the same edge
        // stencil draws and 2D are drawn as in this frame: 2D animates by jumping texture coordinates between
        // sprite-sheet cells (the HUD's pumpkins), and halfway between two cells is a smear
        const Draw* m = match[c.a] >= 0 && !d.s.stencil && !d.s.flat ? &before.draws[match[c.a]] : nullptr;
        GfxState s = d.s;
        if (d.consts >= 0) {
            int b = m && m->consts >= 0 ? m->consts : -1;
            if (d.consts != last_now || b != last_before) {
                const float* x = now.consts[d.consts].data();
                float* out = &mixed[0][0];
                if (b < 0) std::memcpy(out, x, sizeof mixed);
                else for (int k = 0; k < 768; ++k) out[k] = 0.5f * (x[k] + before.consts[b][k]);
                last_now = d.consts, last_before = b, ++version;
            }
            s.vs_constants = mixed, s.vs_version = version;
        }
        const float* verts = &now.verts[d.vfirst];
        size_t n = size_t(d.vcount) * d.stride;
        if (m && m->stride == d.stride && m->vcount == d.vcount && m->icount == d.icount &&
            (!d.icount || !std::memcmp(&now.idx[d.ifirst], &before.idx[m->ifirst], d.icount * 4)) &&
            std::memcmp(verts, &before.verts[m->vfirst], n * 4)) {  // vertices the game moves itself (2D, effects)
            v.resize(n);
            const float* y = &before.verts[m->vfirst];
            for (size_t k = 0; k < n; ++k) v[k] = 0.5f * (verts[k] + y[k]);
            verts = v.data();
        }
        gfx_draw(s, d.topology, verts, d.vcount, d.stride, d.icount ? &now.idx[d.ifirst] : nullptr, d.icount);
        break;
    }
    }
    replaying = false;
    std::swap(g_scene, g_scene_mid), std::swap(g_backbuffer, g_backbuffer_mid);
    gfx_set_render_target(target, target_depth);  // the game carries on where its frame ended
    return true;
}

// The present thread: each game frame arrives as two window-sized pictures (in-between, then the frame), shown half a
// game frame apart: on a 120 Hz screen at its next two refreshes, elsewhere by the clock. The device is
// multithread-protected, and this thread only copies and presents, which touch no pipeline state.
struct ShownSet {
    ID3D11Texture2D* tex[2] = {};
    ID3D11RenderTargetView* rtv[2] = {};
};
static ShownSet g_shown[2];       // alternate frames use alternate sets, so one can be shown while the next is drawn
static UINT g_shown_w, g_shown_h;
static std::mutex g_job_mutex;
static std::condition_variable g_job_cv;
static uint64_t g_job_seq;
static int g_job_set;
static std::chrono::steady_clock::time_point g_job_time;

static void show(int set, int which) {
    std::lock_guard<std::mutex> l(g_swap_mutex);
    ID3D11Texture2D* buf;
    if (!g_shown[set].tex[which] || FAILED(g_swap->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buf)))) return;
    D3D11_TEXTURE2D_DESC a, b;
    buf->GetDesc(&a), g_shown[set].tex[which]->GetDesc(&b);
    bool fits = a.Width == b.Width && a.Height == b.Height;
    if (fits) g_ctx->CopyResource(buf, g_shown[set].tex[which]);
    buf->Release();
    // the window was just resized (or restored, or made fullscreen) and the pictures not yet: presenting now would
    // show a buffer nothing was drawn into (white flashes)
    if (!fits) return;
    // never waits for a free buffer: it would hold the (multithread-protected) device and stall the game's drawing;
    // a picture the screen has no room for is dropped
    HRESULT hr = g_swap->Present(0, DXGI_PRESENT_DO_NOT_WAIT);
    check_present(hr);
    if (hr != DXGI_ERROR_WAS_STILL_DRAWING) ++g_frames_shown;
    if (!g_output.load()) {  // the display the window is on, for gfx_wait_vblank
        IDXGIOutput* out = nullptr;
        if (SUCCEEDED(g_swap->GetContainingOutput(&out))) g_output = out;
    }
}

static void present_thread() {
    uint64_t seen = 0;
    for (;;) {
        int set;
        std::chrono::steady_clock::time_point t0;
        {
            std::unique_lock<std::mutex> l(g_job_mutex);
            g_job_cv.wait(l, [&] { return g_job_seq != seen; });
            seen = g_job_seq, set = g_job_set, t0 = g_job_time;
        }
        show(set, 0);
        double hz = g_display_hz.load();
        IDXGIOutput* out = g_output.load();
        if (out && hz > 119 && hz < 121) out->WaitForVBlank();
        else std::this_thread::sleep_until(t0 + std::chrono::nanoseconds(1000000000ll * 1001 / 120000));
        {
            std::lock_guard<std::mutex> l(g_job_mutex);
            if (g_job_seq != seen) continue;  // running late: the next frame is already waiting
        }
        show(set, 1);
    }
}

static void present_in_between() {
    // a resized window: the swap chain and the shown pictures follow, at a moment the present thread is not using them
    if (g_resized || !g_shown[0].tex[0]) {
        std::unique_lock<std::mutex> l(g_swap_mutex, std::try_to_lock);
        if (l.owns_lock()) {
            if (g_resized) check(g_swap->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0), "resize swap chain");
            g_resized = false;
            DXGI_SWAP_CHAIN_DESC1 sd;
            g_swap->GetDesc1(&sd);
            g_shown_w = sd.Width, g_shown_h = sd.Height;
            for (ShownSet& s : g_shown)
                for (int k = 0; k < 2; ++k) {
                    if (s.rtv[k]) s.rtv[k]->Release(), s.tex[k]->Release();
                    D3D11_TEXTURE2D_DESC d = {};
                    d.Width = g_shown_w, d.Height = g_shown_h, d.MipLevels = 1, d.ArraySize = 1;
                    d.Format = DXGI_FORMAT_B8G8R8A8_UNORM, d.SampleDesc.Count = 1, d.BindFlags = D3D11_BIND_RENDER_TARGET;
                    check(g_device->CreateTexture2D(&d, nullptr, &s.tex[k]), "shown picture");
                    check(g_device->CreateRenderTargetView(s.tex[k], nullptr, &s.rtv[k]), "shown picture view");
                    const float black[4] = {0, 0, 0, 1};
                    g_ctx->ClearRenderTargetView(s.rtv[k], black);  // new textures hold anything until drawn into
                }
        }
    }
    // The game steps once per vblank, so a frame the GPU cannot finish in time slows the game itself (4K with ray
    // tracing on an RTX 3060 ran at 30 fps: half speed). In-between pictures double the drawing: while frames come
    // late they pause (3 s, doubling up to a minute while it keeps happening) and the game keeps its own speed.
    bool paused;
    {
        using namespace std::chrono;
        static steady_clock::time_point last = steady_clock::now(), paused_until;
        static int late, on_time, pause_s = 3;
        auto now = steady_clock::now();
        double ms = duration<double, std::milli>(now - last).count();
        last = now;
        late = ms > 18.5 ? late + 1 : 0;
        on_time = ms > 18.5 ? 0 : on_time + 1;
        if (on_time > 600) pause_s = 3;  // 10 s on time: the next pause starts short again
        if (now >= paused_until && late >= 3) {
            paused_until = now + seconds(pause_s);
            static int told;
            if (told++ < 5) std::fprintf(stderr, "[gfx] in-between frames paused for %d s: frames are late (%.0f ms)\n", pause_s, ms);
            pause_s = std::min(pause_s * 2, 60);
        }
        paused = now < paused_until;
    }
    if (paused || !draw_in_between()) g_ctx->CopyResource(g_scene_mid, g_scene);
    else if (g_flat_frame) fill_sides(g_scene_mid, g_backbuffer_mid);
    static int set;
    set ^= 1;
    if (g_shown[set].tex[0]) {
        blit(g_mid_view, g_shown[set].rtv[0], float(g_shown_w), float(g_shown_h));
        blit(g_scene_view, g_shown[set].rtv[1], float(g_shown_w), float(g_shown_h));
    }
    {
        std::lock_guard<std::mutex> l(g_job_mutex);
        g_job_set = set, g_job_time = std::chrono::steady_clock::now(), ++g_job_seq;
    }
    g_job_cv.notify_one();
    static bool started = (std::thread(present_thread).detach(), true);
    (void)started;
}

void gfx_present() {
    if (g_flat_frame) fill_sides(g_scene, g_backbuffer);
    if (g_interp) present_in_between();
    else blit_scene();
    static const char* shot = std::getenv("OOGIE_SCREENSHOT");
    if (shot) screenshot(shot);
    // OOGIE_FRAMES=dir,first,count: saves `count` consecutive presented frames from present number `first`
    static const char* frames = std::getenv("OOGIE_FRAMES");
    unsigned presents = g_presents;
    if (frames) {
        char dir[260] = {};
        unsigned first = 0, count = 0, step = 1;  // optional 4th value: keep every step-th frame
        std::sscanf(frames, "%259[^,],%u,%u,%u", dir, &first, &count, &step);
        if (presents >= first && presents < first + count * step && (presents - first) % (step ? step : 1) == 0) {
            char path[300];
            std::snprintf(path, sizeof path, "%s/f%05u.bmp", dir, presents);
            screenshot(path);
            if (g_interp) {  // and the in-between picture shown before it
                std::snprintf(path, sizeof path, "%s/f%05u_mid.bmp", dir, presents);
                save_texture(g_scene_mid, path);
            }
        }
    }
    // OOGIE_SHOTS=dir,start,every: a frame at each `every` seconds of wall time from `start` (runs at different rates compare)
    static const char* shots = std::getenv("OOGIE_SHOTS");
    if (shots) {
        static char dir[260];
        static double start = -1, every = 1, t0 = GetTickCount64() / 1000.0;
        static int taken;
        if (start < 0) std::sscanf(shots, "%259[^,],%lf,%lf", dir, &start, &every);
        double t = GetTickCount64() / 1000.0 - t0;
        if (t >= start + taken * every) {
            char path[300];
            std::snprintf(path, sizeof path, "%s/t%06.1f.bmp", dir, start + taken++ * every);
            screenshot(path);
        }
    }
    ++g_presents;
    if (g_interp) {
        rec::begin_frame();  // the present thread shows this frame; the next one is recorded from here
    } else {
        check_present(g_swap->Present(0, 0));  // the game's own 59.94 Hz vblank paces frames; DWM shows each at the next refresh
        ++g_frames_shown;
        if (!g_output.load()) {  // the display the window is on, for gfx_wait_vblank
            IDXGIOutput* out = nullptr;
            if (SUCCEEDED(g_swap->GetContainingOutput(&out))) g_output = out;
        }
    }
    if (std::getenv("OOGIE_D3D_DEBUG")) drain_debug_messages();
    g_ctx->OMSetRenderTargets(1, &g_rt, g_rt_depth);  // back to the game's target
    static bool titled;
    if (titled && !config().show_fps)  // turned off in the menu
        SetWindowTextW(g_window, L"The Nightmare Before Christmas: Oogie's Revenge"), titled = false;
    if (config().show_fps) {  // [display] show_fps: the frame rate in the window title, once a second
        titled = true;
        static auto last = std::chrono::steady_clock::now();
        static unsigned last_shown;
        auto now = std::chrono::steady_clock::now();
        double s = std::chrono::duration<double>(now - last).count();
        if (s >= 1) {
            unsigned shown = g_frames_shown;
            wchar_t title[128];
            std::swprintf(title, 128, L"The Nightmare Before Christmas: Oogie's Revenge - %.0f fps", (shown - last_shown) / s);
            SetWindowTextW(g_window, title);
            last = now, last_shown = shown;
        }
    }
}

// OOGIE_D3D_DEBUG: prints the debug layer's messages (the first 60) so an invalid call is not silent
static void drain_debug_messages() {
    static ID3D11InfoQueue* queue = nullptr;
    static bool tried = false;
    static int printed = 0;
    if (!tried) tried = true, g_device->QueryInterface(__uuidof(ID3D11InfoQueue), reinterpret_cast<void**>(&queue));
    if (!queue) return;
    UINT64 n = queue->GetNumStoredMessages();
    for (UINT64 i = 0; i < n && printed < 60; ++i) {
        SIZE_T len = 0;
        queue->GetMessage(i, nullptr, &len);
        if (!len) continue;
        std::vector<char> buf(len);
        auto* m = reinterpret_cast<D3D11_MESSAGE*>(buf.data());
        if (SUCCEEDED(queue->GetMessage(i, m, &len)) && m->Severity <= D3D11_MESSAGE_SEVERITY_WARNING)
            std::fprintf(stderr, "[d3d11] %.*s\n", int(m->DescriptionByteLength), m->pDescription), ++printed;
    }
    queue->ClearStoredMessages();
}

void gfx_pump() {
    MSG msg;
    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

// ---- drawing ----
#include <d3dcompiler.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstring>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

uint64_t g_shader_compiles, g_shader_compile_ns;

namespace {

typedef HRESULT(WINAPI* CompileFn)(LPCVOID, SIZE_T, LPCSTR, const D3D_SHADER_MACRO*, ID3DInclude*, LPCSTR, LPCSTR, UINT,
                                   UINT, ID3DBlob**, ID3DBlob**);

typedef HRESULT(WINAPI* CreateBlobFn)(SIZE_T, ID3DBlob**);

// Compiled shaders are kept in cache\shaders by a hash of their source, so a shader costs its 30-60 ms compile
// once ever instead of a stutter the first time each effect appears in every session
ID3DBlob* compile(const std::string& src, const char* target) {
    static HMODULE dll = [] {
        HMODULE m = LoadLibraryW(L"d3dcompiler_47.dll");
        if (!m) fatal("d3dcompiler_47.dll not found (part of Windows 10/11)");
        CreateDirectoryW(L"cache", nullptr), CreateDirectoryW(L"cache\\shaders", nullptr);
        return m;
    }();
    static CompileFn fn = reinterpret_cast<CompileFn>(GetProcAddress(dll, "D3DCompile"));
    static CreateBlobFn create_blob = reinterpret_cast<CreateBlobFn>(GetProcAddress(dll, "D3DCreateBlob"));
    uint64_t key = 1469598103934665603ull;
    for (const char* p = target; *p; ++p) key = (key ^ uint8_t(*p)) * 1099511628211ull;
    for (char ch : src) key = (key ^ uint8_t(ch)) * 1099511628211ull;
    char path[64];
    std::snprintf(path, sizeof path, "cache\\shaders\\%016llx.cso", (unsigned long long)key);
    if (FILE* f = std::fopen(path, "rb")) {
        std::fseek(f, 0, SEEK_END);
        long size = std::ftell(f);
        std::fseek(f, 0, SEEK_SET);
        ID3DBlob* blob = nullptr;
        bool ok = size > 0 && create_blob && SUCCEEDED(create_blob(SIZE_T(size), &blob)) &&
                  std::fread(blob->GetBufferPointer(), 1, size_t(size), f) == size_t(size);
        std::fclose(f);
        if (ok) return blob;
        if (blob) blob->Release();
    }
    auto t0 = std::chrono::steady_clock::now();
    ID3DBlob *code = nullptr, *errors = nullptr;
    HRESULT hr = fn(src.data(), src.size(), nullptr, nullptr, nullptr, "main", target, D3DCOMPILE_OPTIMIZATION_LEVEL2,
                    0, &code, &errors);
    if (FAILED(hr)) {
        std::fprintf(stderr, "[gfx] %s compile failed:\n%s\n--- source ---\n%s\n", target,
                     errors ? static_cast<const char*>(errors->GetBufferPointer()) : "?", src.c_str());
        if (errors) errors->Release();
        return nullptr;
    }
    if (errors) errors->Release();
    ++g_shader_compiles, g_shader_compile_ns += uint64_t(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - t0).count());
    if (FILE* f = std::fopen(path, "wb")) std::fwrite(code->GetBufferPointer(), 1, code->GetBufferSize(), f), std::fclose(f);
    return code;
}

struct VertexShader {
    ID3D11VertexShader* vs;
    ID3D11InputLayout* layout;
};
std::vector<VertexShader> g_vs;
std::vector<ID3D11PixelShader*> g_ps;

struct Texture {
    ID3D11Texture2D* tex;
    ID3D11ShaderResourceView* srv;
    ID3D11RenderTargetView* rtv;  // render targets only
    ID3D11DepthStencilView* dsv;  // made on the first draw into it with depth
    uint32_t width, height;
};
std::vector<Texture> g_textures;

// Vertex and index data stream through two ring buffers: appended without waiting on the GPU (NO_OVERWRITE),
// restarted with DISCARD when full, so 3000 draws a frame do not each rename a buffer
struct Ring {
    ID3D11Buffer* buf = nullptr;
    uint32_t size = 0, pos = 0;
};
Ring g_vb, g_ib;
ID3D11Buffer* g_cb_vs;
ID3D11Buffer* g_cb_ps;

struct PsConstants {
    float tscale[4][4];
    float fog_color[4];
    float fog_params[4];
    float alpha_test[4];
};

D3D11_BLEND blend_factor(uint32_t gl) {
    switch (gl) {
    case 0: return D3D11_BLEND_ZERO;
    case 1: return D3D11_BLEND_ONE;
    case 0x300: return D3D11_BLEND_SRC_COLOR;
    case 0x301: return D3D11_BLEND_INV_SRC_COLOR;
    case 0x302: return D3D11_BLEND_SRC_ALPHA;
    case 0x303: return D3D11_BLEND_INV_SRC_ALPHA;
    case 0x304: return D3D11_BLEND_DEST_ALPHA;
    case 0x305: return D3D11_BLEND_INV_DEST_ALPHA;
    case 0x306: return D3D11_BLEND_DEST_COLOR;
    case 0x307: return D3D11_BLEND_INV_DEST_COLOR;
    case 0x308: return D3D11_BLEND_SRC_ALPHA_SAT;
    case 0x8001: case 0x8003: return D3D11_BLEND_BLEND_FACTOR;
    case 0x8002: case 0x8004: return D3D11_BLEND_INV_BLEND_FACTOR;
    }
    return D3D11_BLEND_ONE;
}

D3D11_BLEND alpha_factor(D3D11_BLEND b) {  // color factors are not allowed on the alpha channel
    switch (b) {
    case D3D11_BLEND_SRC_COLOR: return D3D11_BLEND_SRC_ALPHA;
    case D3D11_BLEND_INV_SRC_COLOR: return D3D11_BLEND_INV_SRC_ALPHA;
    case D3D11_BLEND_DEST_COLOR: return D3D11_BLEND_DEST_ALPHA;
    case D3D11_BLEND_INV_DEST_COLOR: return D3D11_BLEND_INV_DEST_ALPHA;
    default: return b;
    }
}

D3D11_BLEND_OP blend_op(uint32_t gl) {
    switch (gl) {
    case 0x800A: return D3D11_BLEND_OP_SUBTRACT;
    case 0x800B: return D3D11_BLEND_OP_REV_SUBTRACT;
    case 0x8007: return D3D11_BLEND_OP_MIN;
    case 0x8008: return D3D11_BLEND_OP_MAX;
    }
    return D3D11_BLEND_OP_ADD;
}

D3D11_COMPARISON_FUNC compare(uint32_t gl) {
    switch (gl & 0xF) {  // GL_NEVER 0x200 .. GL_ALWAYS 0x207
    case 0: return D3D11_COMPARISON_NEVER;
    case 1: return D3D11_COMPARISON_LESS;
    case 2: return D3D11_COMPARISON_EQUAL;
    case 3: return D3D11_COMPARISON_LESS_EQUAL;
    case 4: return D3D11_COMPARISON_GREATER;
    case 5: return D3D11_COMPARISON_NOT_EQUAL;
    case 6: return D3D11_COMPARISON_GREATER_EQUAL;
    }
    return D3D11_COMPARISON_ALWAYS;
}

D3D11_TEXTURE_ADDRESS_MODE address(uint32_t a) {
    switch (a) {
    case 2: return D3D11_TEXTURE_ADDRESS_MIRROR;
    case 3: return D3D11_TEXTURE_ADDRESS_CLAMP;
    case 4: return D3D11_TEXTURE_ADDRESS_BORDER;
    case 5: return D3D11_TEXTURE_ADDRESS_CLAMP;  // D3DTADDRESS_CLAMPTOEDGE
    }
    return D3D11_TEXTURE_ADDRESS_WRAP;
}

// State objects by the FNV-1a hash of their zero-initialized description (a 64-bit collision is not a concern)
template <class Desc, class Obj, class Make> Obj* cached(std::unordered_map<uint64_t, Obj*>& cache, const Desc& d, Make make) {
    uint64_t key = 1469598103934665603ull;
    for (size_t k = 0; k < sizeof d; ++k) key = (key ^ reinterpret_cast<const uint8_t*>(&d)[k]) * 1099511628211ull;
    auto it = cache.find(key);
    if (it != cache.end()) return it->second;
    Obj* o = nullptr;
    make(d, &o);
    return cache[key] = o;
}

uint32_t append(Ring& r, UINT bind, const void* data, uint32_t bytes) {  // returns the byte offset of the data
    if (bytes > r.size) {
        if (r.buf) r.buf->Release();
        r.size = std::max<uint32_t>(bytes * 2, 8 << 20), r.pos = r.size;
        D3D11_BUFFER_DESC d = {r.size, D3D11_USAGE_DYNAMIC, bind, D3D11_CPU_ACCESS_WRITE, 0, 0};
        check(g_device->CreateBuffer(&d, nullptr, &r.buf), "dynamic buffer");
    }
    uint32_t at = (r.pos + 15) & ~15u;
    D3D11_MAP mode = D3D11_MAP_WRITE_NO_OVERWRITE;
    if (at + bytes > r.size) at = 0, mode = D3D11_MAP_WRITE_DISCARD;
    D3D11_MAPPED_SUBRESOURCE m;
    check(g_ctx->Map(r.buf, 0, mode, 0, &m), "map buffer");
    std::memcpy(static_cast<uint8_t*>(m.pData) + at, data, bytes);
    g_ctx->Unmap(r.buf, 0);
    r.pos = at + bytes;
    return at;
}

void constants(ID3D11Buffer*& buf, const void* data, uint32_t bytes) {
    if (!buf) {
        D3D11_BUFFER_DESC d = {(bytes + 15) & ~15u, D3D11_USAGE_DYNAMIC, D3D11_BIND_CONSTANT_BUFFER,
                               D3D11_CPU_ACCESS_WRITE, 0, 0};
        check(g_device->CreateBuffer(&d, nullptr, &buf), "constant buffer");
    }
    D3D11_MAPPED_SUBRESOURCE m;
    check(g_ctx->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &m), "map constants");
    std::memcpy(m.pData, data, bytes);
    g_ctx->Unmap(buf, 0);
}

}  // namespace

int gfx_vertex_shader(const std::string& hlsl, const std::vector<int>& inputs) {
    ID3DBlob* code = compile(hlsl, "vs_5_0");
    if (!code) return -1;
    VertexShader v = {};
    check(g_device->CreateVertexShader(code->GetBufferPointer(), code->GetBufferSize(), nullptr, &v.vs), "vertex shader");
    std::vector<D3D11_INPUT_ELEMENT_DESC> el;
    for (size_t k = 0; k < inputs.size(); ++k)
        el.push_back({"TEXCOORD", UINT(inputs[k]), DXGI_FORMAT_R32G32B32A32_FLOAT, 0, UINT(16 * k),
                      D3D11_INPUT_PER_VERTEX_DATA, 0});
    if (!el.empty())
        check(g_device->CreateInputLayout(el.data(), UINT(el.size()), code->GetBufferPointer(), code->GetBufferSize(),
                                          &v.layout),
              "input layout");
    code->Release();
    g_vs.push_back(v);
    return int(g_vs.size() - 1);
}

int gfx_pixel_shader(const std::string& hlsl) {
    ID3DBlob* code = compile(hlsl, "ps_5_0");
    if (!code) return -1;
    ID3D11PixelShader* ps;
    check(g_device->CreatePixelShader(code->GetBufferPointer(), code->GetBufferSize(), nullptr, &ps), "pixel shader");
    code->Release();
    g_ps.push_back(ps);
    return int(g_ps.size() - 1);
}

int gfx_texture_create(uint32_t w, uint32_t h, int format, bool cube, bool render_target) {
    Texture t = {};
    if (render_target) w = uint32_t(w * g_scale + 0.5f), h = uint32_t(h * g_scale + 0.5f);
    D3D11_TEXTURE2D_DESC d = {};
    d.Width = w, d.Height = h, d.MipLevels = 1, d.ArraySize = cube ? 6 : 1;
    d.Format = DXGI_FORMAT(format);
    d.SampleDesc.Count = 1;
    d.BindFlags = D3D11_BIND_SHADER_RESOURCE | (render_target ? D3D11_BIND_RENDER_TARGET : 0);
    d.MiscFlags = cube ? D3D11_RESOURCE_MISC_TEXTURECUBE : 0;
    check(g_device->CreateTexture2D(&d, nullptr, &t.tex), "texture");
    check(g_device->CreateShaderResourceView(t.tex, nullptr, &t.srv), "texture view");
    if (render_target) check(g_device->CreateRenderTargetView(t.tex, nullptr, &t.rtv), "render target view");
    t.width = w, t.height = h;
    g_textures.push_back(t);
    return int(g_textures.size() - 1);
}

void gfx_texture_dump(int id, const char* path) { if (id >= 0) save_texture(g_textures[id].tex, path); }
void gfx_scene_dump(const char* path) { save_texture(g_scene, path); }

// Compares a host texture's level 0 with `bytes` of source data (`pitch` per row): returns the first differing row or -1
int gfx_texture_compare(int id, const void* data, uint32_t pitch, uint32_t rows) {
    if (id < 0) return -2;
    ID3D11Texture2D* tex = g_textures[id].tex;
    D3D11_TEXTURE2D_DESC d;
    tex->GetDesc(&d);
    d.Usage = D3D11_USAGE_STAGING, d.BindFlags = 0, d.CPUAccessFlags = D3D11_CPU_ACCESS_READ, d.MiscFlags = 0;
    ID3D11Texture2D* staging;
    if (FAILED(g_device->CreateTexture2D(&d, nullptr, &staging))) return -3;
    g_ctx->CopyResource(staging, tex);
    D3D11_MAPPED_SUBRESOURCE m;
    int result = -4;
    if (SUCCEEDED(g_ctx->Map(staging, 0, D3D11_MAP_READ, 0, &m))) {
        result = -1;
        for (uint32_t r = 0; r < rows; ++r)
            if (std::memcmp(static_cast<const uint8_t*>(m.pData) + r * m.RowPitch, static_cast<const uint8_t*>(data) + r * pitch, pitch)) {
                result = int(r);
                break;
            }
        std::fprintf(stderr, "[gfx] compare id %d: host pitch %u format %u size %ux%u\n", id, m.RowPitch, d.Format, d.Width, d.Height);
        g_ctx->Unmap(staging, 0);
    }
    staging->Release();
    return result;
}

int gfx_backbuffer_snapshot() {
    if (rec::on()) rec::frames[rec::cur].cmds.push_back(rec::Cmd{rec::SNAPSHOT});
    static int id = -1;
    if (id < 0) id = gfx_texture_create(uint32_t(g_width / g_scale + 0.5f), uint32_t(g_height / g_scale + 0.5f), 87, false, true);
    g_ctx->CopyResource(g_textures[id].tex, g_scene);
    static const char* dump = std::getenv("OOGIE_SNAPSHOT_DUMP");  // dir: the scene as the game first reads it, every 120 frames
    static unsigned last = ~0u;
    if (dump && g_presents % 120 == 0 && g_presents != last) {
        char path[300];
        std::snprintf(path, sizeof path, "%s/snap%05u.bmp", dump, g_presents);
        save_texture(g_textures[id].tex, path);
        last = g_presents;
    }
    return id;
}

// Loading screens and scene changes mix single 2D-only frames with 3D ones: the side fill switching on and off each
// frame flashed the borders, so it changes only after three frames in a row of the other kind
void gfx_flat_frame(bool flat) {
    static int run;
    run = flat == g_flat_frame ? 0 : run + 1;
    if (run >= 3) g_flat_frame = flat, run = 0;
}

// A 2D-only frame on a back buffer wider than 4:3 (menus, title, movies): the 4:3 picture sits in the middle and the
// sides get the same picture zoomed to cover the screen, heavily blurred (a small mip level) and darkened, the way
// 4:3 pictures are shown on wide screens. The middle is left exactly as the game drew it.
static void fill_sides(ID3D11Texture2D* scene, ID3D11RenderTargetView* target) {
    if (g_wide < 1.01f) return;
    static ID3D11VertexShader* vs;
    static ID3D11PixelShader* ps;
    static ID3D11SamplerState* smp;
    static ID3D11Texture2D* copy;
    static ID3D11ShaderResourceView* copy_view;
    static ID3D11Buffer* cb;
    if (!vs) {
        ID3DBlob* v = compile("float4 main(uint id : SV_VertexID) : SV_Position {\n"
                              "  float2 uv = float2((id << 1) & 2, id & 2); return float4(uv * float2(2, -2) + float2(-1, 1), 0, 1); }\n",
                              "vs_5_0");
        ID3DBlob* f = compile(
            "Texture2D t : register(t0); SamplerState s : register(s0);\n"
            "cbuffer C : register(b0) { float wide, level, width, height; };\n"
            "float4 main(float4 pos : SV_Position) : SV_Target {\n"
            "  float2 uv = pos.xy / float2(width, height);\n"
            "  if (abs(uv.x - 0.5) < 0.5 / wide) discard;  // the game's own 4:3 picture\n"
            "  float2 src = 0.5 + (uv - 0.5) / wide;        // that picture zoomed to cover the screen\n"
            "  float2 d = exp2(level) / float2(width, height);\n"
            "  float3 c = 0;\n"
            "  [unroll] for (int y = -1; y <= 1; ++y) [unroll] for (int x = -1; x <= 1; ++x)\n"
            "    c += t.SampleLevel(s, src + float2(x, y) * d, level).rgb;\n"
            "  return float4(c / 9 * 0.6, 1);\n"
            "}\n",
            "ps_5_0");
        if (!v || !f) fatal("the side fill shaders did not compile");
        check(g_device->CreateVertexShader(v->GetBufferPointer(), v->GetBufferSize(), nullptr, &vs), "side fill vs");
        check(g_device->CreatePixelShader(f->GetBufferPointer(), f->GetBufferSize(), nullptr, &ps), "side fill ps");
        v->Release(), f->Release();
        D3D11_SAMPLER_DESC sd = {};
        sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sd.MaxLOD = D3D11_FLOAT32_MAX;
        check(g_device->CreateSamplerState(&sd, &smp), "side fill sampler");
        D3D11_TEXTURE2D_DESC td = {};
        td.Width = g_width, td.Height = g_height, td.MipLevels = 0, td.ArraySize = 1;
        td.Format = DXGI_FORMAT_B8G8R8A8_UNORM, td.SampleDesc.Count = 1;
        td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET, td.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
        check(g_device->CreateTexture2D(&td, nullptr, &copy), "side fill copy");
        check(g_device->CreateShaderResourceView(copy, nullptr, &copy_view), "side fill copy view");
        D3D11_BUFFER_DESC bd = {16, D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0, 0, 0};
        check(g_device->CreateBuffer(&bd, nullptr, &cb), "side fill constants");
    }
    g_ctx->CopySubresourceRegion(copy, 0, 0, 0, 0, scene, 0, nullptr);
    g_ctx->GenerateMips(copy_view);
    float level = std::max(0.f, std::log2(float(g_height)) - 5.5f);  // ~1/45 of the height per texel: a soft blur
    float constants[4] = {g_wide, level, float(g_width), float(g_height)};
    g_ctx->UpdateSubresource(cb, 0, nullptr, constants, 0, 0);
    ID3D11ShaderResourceView* none = nullptr;
    g_ctx->PSSetShaderResources(0, 1, &none);
    g_ctx->OMSetRenderTargets(1, &target, nullptr);
    D3D11_VIEWPORT vp = {0, 0, float(g_width), float(g_height), 0, 1};
    g_ctx->RSSetViewports(1, &vp);
    g_ctx->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
    g_ctx->OMSetDepthStencilState(nullptr, 0);
    g_ctx->RSSetState(nullptr);
    g_ctx->IASetInputLayout(nullptr);
    g_ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    g_ctx->VSSetShader(vs, nullptr, 0);
    g_ctx->PSSetShader(ps, nullptr, 0);
    g_ctx->PSSetConstantBuffers(0, 1, &cb);
    g_ctx->PSSetShaderResources(0, 1, &copy_view);
    g_ctx->PSSetSamplers(0, 1, &smp);
    g_ctx->Draw(3, 0);
    g_ctx->PSSetShaderResources(0, 1, &none);
    g_ctx->OMSetRenderTargets(1, &g_rt, g_rt_depth);
    g_pipeline_touched = true;
}

// ---- ray-traced ambient occlusion ([display] ray_tracing) ----
// After the 3D world and before the 2D layer, rays are marched through the depth buffer: from each pixel's surface
// point, 8 directions in screen space, 6 steps each within a radius in world units, keeping the highest rise of the
// geometry above the surface (horizon-based ambient occlusion). Corners, creases and the ground under characters
// darken as light reaching them is blocked. Computed at half resolution, blurred without crossing depth edges, then
// multiplied into the scene. Positions come from the depth and the game's camera (D3DXMatrixPerspectiveFovLH).
static float g_cam[4] = {0, 0, 2, 10000};  // x scale (P00), y scale (P11), near, far: the game's last 3D camera
void gfx_set_camera(float p00, float p11, float zn, float zf) { g_cam[0] = p00, g_cam[1] = p11, g_cam[2] = zn, g_cam[3] = zf; }

void gfx_ambient_occlusion() {
    static const char* env = std::getenv("OOGIE_RT");
    bool on = env ? std::atoi(env) != 0 : config().ray_tracing;  // the in-game menu can turn it on and off
    if (!on || !g_cam[0] || !g_depth_view) return;
    if (rec::on()) rec::frames[rec::cur].cmds.push_back(rec::Cmd{rec::AO});
    static ID3D11VertexShader* vs;
    static ID3D11PixelShader *ps_ao, *ps_blur, *ps_apply;
    static ID3D11SamplerState *point, *linear;
    static ID3D11BlendState* multiply;
    static ID3D11Buffer* cb;
    static ID3D11Texture2D* tex[2];
    static ID3D11RenderTargetView* rtv[2];
    static ID3D11ShaderResourceView* srv[2];
    static UINT w, h;
    if (!vs) {
        const char* common =
            "Texture2D<float> depth : register(t0); Texture2D<float> ao : register(t1);\n"
            "SamplerState pt : register(s0); SamplerState lin : register(s1);\n"
            "cbuffer C : register(b0) { float p00, p11, zn, zf, radius, strength, w, h, dx, dy, pad0, pad1; };\n"
            "float view_z(float d) { float q = zf / (zf - zn); return q * zn / max(q - d, 1e-6); }\n"
            "float3 view_pos(float2 uv) {\n"
            "  float z = view_z(depth.SampleLevel(pt, uv, 0));\n"
            "  return float3((uv.x * 2 - 1) / p00 * z, (1 - uv.y * 2) / p11 * z, z);\n"
            "}\n";
        ID3DBlob* v = compile("float4 main(uint id : SV_VertexID, out float2 uv : TEXCOORD0) : SV_Position {\n"
                              "  uv = float2((id << 1) & 2, id & 2); return float4(uv * float2(2, -2) + float2(-1, 1), 0, 1); }\n",
                              "vs_5_0");
        ID3DBlob* a = compile(std::string(common) +
            "float main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {\n"
            "  float d = depth.SampleLevel(pt, uv, 0);\n"
            "  if (d >= 0.99999) return 1;  // sky: nothing to occlude\n"
            "  float3 p = view_pos(uv);\n"
            "  float2 px = float2(1 / w, 1 / h);\n"
            "  float3 l = view_pos(uv - float2(px.x, 0)), r = view_pos(uv + float2(px.x, 0));\n"
            "  float3 t = view_pos(uv - float2(0, px.y)), b = view_pos(uv + float2(0, px.y));\n"
            "  float3 ddx_ = abs(r.z - p.z) < abs(p.z - l.z) ? r - p : p - l;  // the side without a depth edge\n"
            "  float3 ddy_ = abs(b.z - p.z) < abs(p.z - t.z) ? b - p : p - t;\n"
            "  float3 n = normalize(cross(ddy_, ddx_));\n"
            "  if (dot(n, -p) < 0) n = -n;  // facing the camera\n"
            "  float2 reach = float2(radius * p00 / p.z * 0.5, radius * p11 / p.z * 0.5);  // the radius on screen\n"
            "  float scale = min(1, 0.12 / max(reach.x, reach.y)); reach *= scale;  // near the camera: at most 12% of the screen\n"
            "  float noise = frac(52.9829189 * frac(dot(pos.xy, float2(0.06711056, 0.00583715))));  // interleaved gradient noise\n"
            "  float occlusion = 0;\n"
            "  [unroll] for (int i = 0; i < 8; ++i) {\n"
            "    float angle = (i + noise) * 0.78539816;\n"
            "    float2 dir = float2(cos(angle), sin(angle)) * reach;\n"
            "    float horizon = 0;\n"
            "    [unroll] for (int s = 1; s <= 6; ++s) {\n"
            "      float2 suv = uv + dir * ((s - 0.5 + noise * 0.5) / 6);\n"
            "      if (any(suv < 0) || any(suv > 1)) break;\n"
            "      float3 v = view_pos(suv) - p;\n"
            "      float dist = length(v), r2 = radius * radius * scale * scale;\n"
            "      if (dist < 1e-4) continue;\n"
            "      float rise = dot(v, n) / dist - 0.1;  // how far above the surface the ray hit (sine), small bias\n"
            "      horizon = max(horizon, rise * saturate(1 - dist * dist / r2));\n"
            "    }\n"
            "    occlusion += horizon;\n"
            "  }\n"
            "  float fade = saturate((160 - p.z) / 80);  // far away the depth is too coarse: fades out from 80 to 160 units\n"
            "  return saturate(1 - strength * fade * occlusion / 8);\n"
            "}\n", "ps_5_0");
        ID3DBlob* bl = compile(std::string(common) +
            "float main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {\n"
            "  float z0 = view_z(depth.SampleLevel(pt, uv, 0)), sum = 0, wsum = 0;\n"
            "  [unroll] for (int k = -3; k <= 3; ++k) {\n"
            "    float2 o = uv + float2(dx, dy) * k;\n"
            "    float z = view_z(depth.SampleLevel(pt, o, 0));\n"
            "    float wt = exp(-k * k / 8.0) * saturate(1 - abs(z - z0) / (0.05 * z0));  // not across depth edges\n"
            "    sum += ao.SampleLevel(pt, o, 0) * wt; wsum += wt;\n"
            "  }\n"
            "  return sum / max(wsum, 1e-4);\n"
            "}\n", "ps_5_0");
        ID3DBlob* ap = compile(std::string(common) +
            "float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {\n"
            "  if (depth.SampleLevel(pt, uv, 0) >= 0.99999) discard;\n"
            "  return float4(ao.SampleLevel(lin, uv, 0).xxx, 1);\n"
            "}\n", "ps_5_0");
        if (!v || !a || !bl || !ap) fatal("the ambient occlusion shaders did not compile");
        check(g_device->CreateVertexShader(v->GetBufferPointer(), v->GetBufferSize(), nullptr, &vs), "ao vs");
        check(g_device->CreatePixelShader(a->GetBufferPointer(), a->GetBufferSize(), nullptr, &ps_ao), "ao ps");
        check(g_device->CreatePixelShader(bl->GetBufferPointer(), bl->GetBufferSize(), nullptr, &ps_blur), "ao blur ps");
        check(g_device->CreatePixelShader(ap->GetBufferPointer(), ap->GetBufferSize(), nullptr, &ps_apply), "ao apply ps");
        v->Release(), a->Release(), bl->Release(), ap->Release();
        D3D11_SAMPLER_DESC sd = {};
        sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
        sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        check(g_device->CreateSamplerState(&sd, &point), "ao point sampler");
        sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        check(g_device->CreateSamplerState(&sd, &linear), "ao linear sampler");
        D3D11_BLEND_DESC bd = {};  // scene colour times the occlusion; alpha untouched
        bd.RenderTarget[0].BlendEnable = TRUE;
        bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO, bd.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
        bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO, bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
        bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_RED | D3D11_COLOR_WRITE_ENABLE_GREEN | D3D11_COLOR_WRITE_ENABLE_BLUE;
        check(g_device->CreateBlendState(&bd, &multiply), "ao blend");
        D3D11_BUFFER_DESC cd = {48, D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0, 0, 0};
        check(g_device->CreateBuffer(&cd, nullptr, &cb), "ao constants");
        w = std::max(1u, g_width / 2), h = std::max(1u, g_height / 2);
        for (int k = 0; k < 2; ++k) {
            D3D11_TEXTURE2D_DESC td = {};
            td.Width = w, td.Height = h, td.MipLevels = 1, td.ArraySize = 1, td.Format = DXGI_FORMAT_R8_UNORM;
            td.SampleDesc.Count = 1, td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
            check(g_device->CreateTexture2D(&td, nullptr, &tex[k]), "ao texture");
            check(g_device->CreateRenderTargetView(tex[k], nullptr, &rtv[k]), "ao target");
            check(g_device->CreateShaderResourceView(tex[k], nullptr, &srv[k]), "ao view");
        }
    }
    // radius 9 world units (the camera's near plane is 2), strength 3: tuned by eye on Town Square captures
    auto pass = [&](ID3D11PixelShader* ps, ID3D11RenderTargetView* to, ID3D11ShaderResourceView* from, float sdx, float sdy, float vw, float vh) {
        float c[12] = {g_cam[0], g_cam[1], g_cam[2], g_cam[3], 9.f, 3.f, float(w), float(h), sdx, sdy, 0, 0};
        g_ctx->UpdateSubresource(cb, 0, nullptr, c, 0, 0);
        ID3D11ShaderResourceView* none[2] = {};
        g_ctx->PSSetShaderResources(0, 2, none);
        g_ctx->OMSetRenderTargets(1, &to, nullptr);
        D3D11_VIEWPORT vp = {0, 0, vw, vh, 0, 1};
        g_ctx->RSSetViewports(1, &vp);
        g_ctx->PSSetShader(ps, nullptr, 0);
        ID3D11ShaderResourceView* views[2] = {g_depth_view, from};
        g_ctx->PSSetShaderResources(0, 2, views);
        g_ctx->Draw(3, 0);
    };
    g_ctx->OMSetRenderTargets(0, nullptr, nullptr);  // the depth buffer is read, so it must not be bound for writing
    g_ctx->OMSetDepthStencilState(nullptr, 0);
    g_ctx->RSSetState(nullptr);
    g_ctx->IASetInputLayout(nullptr);
    g_ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    g_ctx->VSSetShader(vs, nullptr, 0);
    g_ctx->PSSetConstantBuffers(0, 1, &cb);
    ID3D11SamplerState* smp[2] = {point, linear};
    g_ctx->PSSetSamplers(0, 2, smp);
    g_ctx->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
    pass(ps_ao, rtv[0], nullptr, 0, 0, float(w), float(h));
    pass(ps_blur, rtv[1], srv[0], 1.f / w, 0, float(w), float(h));
    pass(ps_blur, rtv[0], srv[1], 0, 1.f / h, float(w), float(h));
    // OOGIE_RT_SAVE=dir,every: every `every` presents, the scene just before and after the occlusion (testing)
    static unsigned save_every = 0;
    static char save_dir[260];
    static const bool save = std::getenv("OOGIE_RT_SAVE") && std::sscanf(std::getenv("OOGIE_RT_SAVE"), "%259[^,],%u", save_dir, &save_every) == 2;
    bool saving = save && save_every && g_presents % save_every == 0 && !rec::replaying;
    char save_path[300];
    if (saving) std::snprintf(save_path, sizeof save_path, "%s/rt%05u_off.bmp", save_dir, g_presents), save_texture(g_scene, save_path);
    static const bool view = std::getenv("OOGIE_RT_VIEW") != nullptr;  // the occlusion itself, in grey (testing)
    g_ctx->OMSetBlendState(view ? nullptr : multiply, nullptr, 0xFFFFFFFF);
    pass(ps_apply, g_backbuffer, srv[0], 0, 0, float(g_width), float(g_height));
    if (saving) std::snprintf(save_path, sizeof save_path, "%s/rt%05u_on.bmp", save_dir, g_presents), save_texture(g_scene, save_path);
    ID3D11ShaderResourceView* none[2] = {};
    g_ctx->PSSetShaderResources(0, 2, none);
    g_ctx->OMSetRenderTargets(1, &g_rt, g_rt_depth);
    g_pipeline_touched = true;
}

// The whole of one rendered surface drawn over the whole of another of a different size (the wide back buffer
// captured into the game's 4:3 texture, or back): the picture is scaled, as a raw copy would cut it off.
bool gfx_texture_is_picture(int id) { return id >= 0 && !g_textures[id].rtv && g_textures[id].width >= 256; }
bool gfx_texture_is_target(int id) { return id >= 0 && g_textures[id].rtv; }
bool gfx_texture_is_image(int id) { return id >= 0 && !g_textures[id].rtv && g_textures[id].width >= 8 && g_textures[id].height >= 8; }

static void stretch_copy(ID3D11Texture2D* from, ID3D11RenderTargetView* to, UINT w, UINT h) {
    static ID3D11VertexShader* vs;
    static ID3D11PixelShader* ps;
    static ID3D11SamplerState* smp;
    if (!vs) {
        ID3DBlob* v = compile("float4 main(uint id : SV_VertexID, out float2 uv : TEXCOORD0) : SV_Position {\n"
                              "  uv = float2((id << 1) & 2, id & 2); return float4(uv * float2(2, -2) + float2(-1, 1), 0, 1); }\n",
                              "vs_5_0");
        ID3DBlob* f = compile("Texture2D t : register(t0); SamplerState s : register(s0);\n"
                              "float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target { return t.SampleLevel(s, uv, 0); }\n",
                              "ps_5_0");
        if (!v || !f) fatal("the copy shaders did not compile");
        check(g_device->CreateVertexShader(v->GetBufferPointer(), v->GetBufferSize(), nullptr, &vs), "copy vs");
        check(g_device->CreatePixelShader(f->GetBufferPointer(), f->GetBufferSize(), nullptr, &ps), "copy ps");
        v->Release(), f->Release();
        D3D11_SAMPLER_DESC sd = {};
        sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sd.MaxLOD = D3D11_FLOAT32_MAX;
        check(g_device->CreateSamplerState(&sd, &smp), "copy sampler");
    }
    ID3D11ShaderResourceView* view;
    check(g_device->CreateShaderResourceView(from, nullptr, &view), "copy source view");
    ID3D11ShaderResourceView* none = nullptr;
    g_ctx->PSSetShaderResources(0, 1, &none);
    g_ctx->OMSetRenderTargets(1, &to, nullptr);
    D3D11_VIEWPORT vp = {0, 0, float(w), float(h), 0, 1};
    g_ctx->RSSetViewports(1, &vp);
    g_ctx->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
    g_ctx->OMSetDepthStencilState(nullptr, 0);
    g_ctx->RSSetState(nullptr);
    g_ctx->IASetInputLayout(nullptr);
    g_ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    g_ctx->VSSetShader(vs, nullptr, 0);
    g_ctx->PSSetShader(ps, nullptr, 0);
    g_ctx->PSSetShaderResources(0, 1, &view);
    g_ctx->PSSetSamplers(0, 1, &smp);
    g_ctx->Draw(3, 0);
    g_ctx->PSSetShaderResources(0, 1, &none);
    view->Release();
    g_ctx->OMSetRenderTargets(1, &g_rt, g_rt_depth);
    g_pipeline_touched = true;
}

void gfx_copy(int src, int dst, const GfxRect* rect, int32_t dst_x, int32_t dst_y) {
    if (rec::on()) {
        rec::Cmd c{rec::COPY};
        c.a = src, c.b = dst, c.has_rect = rect != nullptr, c.rect = rect ? *rect : GfxRect{}, c.x = dst_x, c.y = dst_y;
        rec::frames[rec::cur].cmds.push_back(c);
    }
    ID3D11Texture2D* s = src < 0 ? g_scene : g_textures[src].tex;
    ID3D11Texture2D* d = dst < 0 ? g_scene : g_textures[dst].tex;
    D3D11_TEXTURE2D_DESC sd, dd;
    s->GetDesc(&sd), d->GetDesc(&dd);
    ID3D11RenderTargetView* to = dst < 0 ? g_backbuffer : g_textures[dst].rtv;
    if (!rect && (src < 0) != (dst < 0) && (sd.Width != dd.Width || sd.Height != dd.Height) && to)
        return stretch_copy(s, to, dd.Width, dd.Height);
    if (sd.Format != dd.Format) {  // shortcut: only rendered surfaces copy (B8G8R8A8); uploaded textures would need a blit
        static bool told;
        if (!told) told = true, std::fprintf(stderr, "[gfx] copy between texture formats %u and %u: skipped\n", sd.Format, dd.Format);
        return;
    }
    float k = g_scale, ks = k * (src < 0 ? g_wide : 1), kd = k * (dst < 0 ? g_wide : 1);  // the back buffer is wider
    static int told_wide;
    if (g_wide > 1 && (src < 0) != (dst < 0) && told_wide++ < 8)
        std::fprintf(stderr, "[gfx] wide copy %d -> %d (%ux%u -> %ux%u) rect %d frame %u\n", src, dst, sd.Width, sd.Height,
                     dd.Width, dd.Height, rect ? 1 : 0, g_presents);
    D3D11_BOX box = {0, 0, 0, sd.Width, sd.Height, 1};
    if (rect) box = {UINT(std::lround(rect->x1 * ks)), UINT(std::lround(rect->y1 * k)), 0, UINT(std::lround(rect->x2 * ks)), UINT(std::lround(rect->y2 * k)), 1};
    box.right = std::min(box.right, sd.Width), box.bottom = std::min(box.bottom, sd.Height);
    UINT x = UINT(std::lround(dst_x * kd)), y = UINT(std::lround(dst_y * k));
    if (x >= dd.Width || y >= dd.Height || box.right <= box.left || box.bottom <= box.top) return;
    box.right = std::min(box.right, box.left + (dd.Width - x)), box.bottom = std::min(box.bottom, box.top + (dd.Height - y));
    g_ctx->CopySubresourceRegion(d, 0, x, y, 0, s, 0, &box);
}

// what the last draw bound; binding a render target can unbind a view of the same texture, so a target change clears it
static ID3D11ShaderResourceView* g_last_views[8];
static ID3D11SamplerState* g_last_smp[4];

void gfx_set_render_target(int id, bool with_depth) {
    if (!rec::replaying) rec::target = id, rec::target_depth = with_depth;
    if (rec::on()) {
        rec::Cmd c{rec::TARGET};
        c.a = id, c.b = with_depth;
        rec::frames[rec::cur].cmds.push_back(c);
    }
    std::memset(g_last_views, 0, sizeof g_last_views), std::memset(g_last_smp, 0, sizeof g_last_smp);
    ID3D11ShaderResourceView* none[8] = {};
    g_ctx->PSSetShaderResources(0, 8, none);  // the new target may be bound as a texture of the last draw
    if (id < 0) {
        g_rt = g_backbuffer, g_rt_depth = g_depth, g_rt_width = g_width, g_rt_height = g_height;
    } else {
        Texture& t = g_textures[id];
        if (with_depth && !t.dsv) {
            D3D11_TEXTURE2D_DESC dd = {};
            dd.Width = t.width, dd.Height = t.height, dd.MipLevels = 1, dd.ArraySize = 1;
            dd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
            dd.SampleDesc.Count = 1;
            dd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
            ID3D11Texture2D* depth;
            check(g_device->CreateTexture2D(&dd, nullptr, &depth), "render target depth");
            check(g_device->CreateDepthStencilView(depth, nullptr, &t.dsv), "render target depth view");
            depth->Release();
        }
        g_rt = t.rtv, g_rt_depth = with_depth ? t.dsv : nullptr, g_rt_width = t.width, g_rt_height = t.height;
    }
    g_ctx->OMSetRenderTargets(1, &g_rt, g_rt_depth);
}

void gfx_texture_update(int id, const void* data, uint32_t pitch, uint32_t face) {
    g_ctx->UpdateSubresource(g_textures[id].tex, face, nullptr, data, pitch, 0);
}

// Pipeline state is only re-sent when it differs from the last draw's (3000 draws a frame add up)
template <class T> bool changed(T& last, const T& now) {
    if (!std::memcmp(&last, &now, sizeof now)) return false;
    std::memcpy(&last, &now, sizeof now);
    return true;
}

void gfx_draw(const GfxState& s, int topology, const float* vertices, uint32_t vertex_count, uint32_t stride_floats,
              const uint32_t* indices, uint32_t index_count) {
    if (s.vs < 0 || s.ps < 0 || !vertex_count) return;
    if (rec::on()) rec::draw(s, topology, vertices, vertex_count, stride_floats, indices, index_count);
    static std::unordered_map<uint64_t, ID3D11BlendState*> blends;
    static std::unordered_map<uint64_t, ID3D11DepthStencilState*> depths;
    static std::unordered_map<uint64_t, ID3D11RasterizerState*> rasters;
    static std::unordered_map<uint64_t, ID3D11SamplerState*> samplers;
    static D3D11_BLEND_DESC last_bd;
    static D3D11_DEPTH_STENCIL_DESC last_dd;
    static UINT last_ref = ~0u;
    static D3D11_RASTERIZER_DESC last_rd;
    static D3D11_RECT last_scissor;
    static D3D11_VIEWPORT last_vp;
    static D3D11_SAMPLER_DESC last_sd[4];
    static ID3D11SamplerState* smp[4];
    static int last_vs = -1, last_ps = -1, last_topology = -1;
    static bool first = true;
    if (first || g_pipeline_touched) {  // nothing matches the first draw, or the first after a present
        std::memset(&last_bd, 0xFF, sizeof last_bd), std::memset(&last_dd, 0xFF, sizeof last_dd);
        std::memset(&last_rd, 0xFF, sizeof last_rd), std::memset(&last_vp, 0xFF, sizeof last_vp);
        std::memset(&last_scissor, 0xFF, sizeof last_scissor), std::memset(last_sd, 0xFF, sizeof last_sd);
        last_ref = ~0u, last_vs = last_ps = last_topology = -1;
        std::memset(g_last_views, 0, sizeof g_last_views), std::memset(g_last_smp, 0, sizeof g_last_smp);
        first = g_pipeline_touched = false;
    }

    D3D11_BLEND_DESC bd = {};
    auto& rt = bd.RenderTarget[0];
    rt.BlendEnable = s.blend;
    rt.SrcBlend = blend_factor(s.blend_src), rt.DestBlend = blend_factor(s.blend_dst);
    rt.SrcBlendAlpha = alpha_factor(rt.SrcBlend), rt.DestBlendAlpha = alpha_factor(rt.DestBlend);
    rt.BlendOp = rt.BlendOpAlpha = blend_op(s.blend_op);
    rt.RenderTargetWriteMask = UINT8(((s.color_mask >> 16) & 1 ? D3D11_COLOR_WRITE_ENABLE_RED : 0) |
                                     ((s.color_mask >> 8) & 1 ? D3D11_COLOR_WRITE_ENABLE_GREEN : 0) |
                                     (s.color_mask & 1 ? D3D11_COLOR_WRITE_ENABLE_BLUE : 0) |
                                     ((s.color_mask >> 24) & 1 ? D3D11_COLOR_WRITE_ENABLE_ALPHA : 0));
    if (changed(last_bd, bd)) {
        float factor[4] = {1, 1, 1, 1};
        g_ctx->OMSetBlendState(cached(blends, bd, [](const D3D11_BLEND_DESC& d, ID3D11BlendState** o) {
                                   check(g_device->CreateBlendState(&d, o), "blend state");
                               }),
                               factor, 0xFFFFFFFF);
    }

    D3D11_DEPTH_STENCIL_DESC dd = {};
    dd.DepthEnable = s.z_enable;
    dd.DepthWriteMask = s.z_write ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
    dd.DepthFunc = compare(s.z_func);
    dd.StencilEnable = s.stencil;
    dd.StencilReadMask = UINT8(s.stencil_mask), dd.StencilWriteMask = UINT8(s.stencil_write_mask);
    auto stencil_op = [](uint32_t gl) {
        switch (gl) {  // GL_ZERO, GL_KEEP, GL_REPLACE, GL_INCR (saturate), GL_DECR (saturate), GL_INVERT, GL_INCR_WRAP, GL_DECR_WRAP
        case 0: return D3D11_STENCIL_OP_ZERO;
        case 0x1E01: return D3D11_STENCIL_OP_REPLACE;
        case 0x1E02: return D3D11_STENCIL_OP_INCR_SAT;
        case 0x1E03: return D3D11_STENCIL_OP_DECR_SAT;
        case 0x150A: return D3D11_STENCIL_OP_INVERT;
        case 0x8507: return D3D11_STENCIL_OP_INCR;
        case 0x8508: return D3D11_STENCIL_OP_DECR;
        default: return D3D11_STENCIL_OP_KEEP;
        }
    };
    dd.FrontFace.StencilFunc = dd.BackFace.StencilFunc = compare(s.stencil_func);
    dd.FrontFace.StencilFailOp = dd.BackFace.StencilFailOp = stencil_op(s.stencil_fail);
    dd.FrontFace.StencilDepthFailOp = dd.BackFace.StencilDepthFailOp = stencil_op(s.stencil_zfail);
    dd.FrontFace.StencilPassOp = dd.BackFace.StencilPassOp = stencil_op(s.stencil_pass);
    UINT ref = s.stencil_ref;
    if (changed(last_dd, dd) | changed(last_ref, ref))
        g_ctx->OMSetDepthStencilState(cached(depths, dd, [](const D3D11_DEPTH_STENCIL_DESC& d, ID3D11DepthStencilState** o) {
                                          check(g_device->CreateDepthStencilState(&d, o), "depth state");
                                      }),
                                      ref);

    D3D11_RASTERIZER_DESC rd = {};
    rd.FillMode = D3D11_FILL_SOLID;
    rd.CullMode = s.cull == 0 ? D3D11_CULL_NONE : D3D11_CULL_BACK;
    rd.FrontCounterClockwise = s.cull == 1;  // cull 1 = clockwise faces culled, so counter-clockwise is front
    rd.ScissorEnable = s.scissor;
    rd.DepthClipEnable = TRUE;
    if (changed(last_rd, rd))
        g_ctx->RSSetState(cached(rasters, rd, [](const D3D11_RASTERIZER_DESC& d, ID3D11RasterizerState** o) {
            check(g_device->CreateRasterizerState(&d, o), "rasterizer state");
        }));
    D3D11_VIEWPORT vp = {0, 0, float(g_rt_width), float(g_rt_height), 0, 1};
    if (changed(last_vp, vp)) g_ctx->RSSetViewports(1, &vp);
    if (s.scissor) {
        // rounded: 2.25 * 1.3333334 is 2.9999998 in float, and a truncated 640 * that clipped the last column of
        // every frame at 16:9 1080p and 4K (the light line on the right)
        D3D11_RECT r = {std::lround(s.scissor_rect.x1 * rt_x_scale()), std::lround(s.scissor_rect.y1 * g_scale),
                        std::lround(s.scissor_rect.x2 * rt_x_scale()), std::lround(s.scissor_rect.y2 * g_scale)};
        if (changed(last_scissor, r)) g_ctx->RSSetScissorRects(1, &r);
    }

    ID3D11ShaderResourceView* views[8] = {};
    for (int k = 0; k < 4; ++k) {
        if (s.textures[k] >= 0) views[s.cube[k] ? 4 + k : k] = g_textures[s.textures[k]].srv;
        D3D11_SAMPLER_DESC sd = {};
        sd.Filter = s.linear_filter[k] ? D3D11_FILTER_MIN_MAG_MIP_LINEAR : D3D11_FILTER_MIN_MAG_MIP_POINT;
        sd.AddressU = address(s.address[k][0]), sd.AddressV = address(s.address[k][1]);
        sd.AddressW = address(s.address[k][2]);
        sd.MaxLOD = D3D11_FLOAT32_MAX;
        sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
        if (changed(last_sd[k], sd))
            smp[k] = cached(samplers, sd, [](const D3D11_SAMPLER_DESC& d, ID3D11SamplerState** o) {
                check(g_device->CreateSamplerState(&d, o), "sampler");
            });
    }
    if (std::memcmp(views, g_last_views, sizeof views)) g_ctx->PSSetShaderResources(0, 8, views), std::memcpy(g_last_views, views, sizeof views);
    if (std::memcmp(smp, g_last_smp, sizeof smp)) g_ctx->PSSetSamplers(0, 4, smp), std::memcpy(g_last_smp, smp, sizeof smp);

    // vertex constants: 3 KB, re-sent only when the game changed a register or the target size changed
    struct VsConstants {
        float c[192][4];
        float screen[4];
    };
    static const float (*last_c)[4];
    static uint64_t last_version;
    static float last_screen[4];
    if (s.vs_constants && (s.vs_constants != last_c || s.vs_version != last_version || !s.vs_version ||
                           std::memcmp(last_screen, s.screen, sizeof last_screen))) {
        if (!g_cb_vs) {
            D3D11_BUFFER_DESC d = {sizeof(VsConstants), D3D11_USAGE_DYNAMIC, D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, 0, 0};
            check(g_device->CreateBuffer(&d, nullptr, &g_cb_vs), "constant buffer");
            g_ctx->VSSetConstantBuffers(0, 1, &g_cb_vs);
        }
        D3D11_MAPPED_SUBRESOURCE m;
        check(g_ctx->Map(g_cb_vs, 0, D3D11_MAP_WRITE_DISCARD, 0, &m), "map constants");
        auto* out = static_cast<VsConstants*>(m.pData);
        std::memcpy(out->c, s.vs_constants, sizeof out->c), std::memcpy(out->screen, s.screen, sizeof out->screen);
        g_ctx->Unmap(g_cb_vs, 0);
        last_c = s.vs_constants, last_version = s.vs_version, std::memcpy(last_screen, s.screen, sizeof last_screen);
    }
    PsConstants psc;
    std::memcpy(psc.tscale, s.tscale, sizeof psc.tscale);
    for (int k = 0; k < 4; ++k) psc.tscale[k][2] = s.linear_filter[k] ? 1.f : 0.f;  // psh: bicubic when magnified
    std::memcpy(psc.fog_color, s.fog_color, sizeof psc.fog_color);
    std::memcpy(psc.fog_params, s.fog_params, sizeof psc.fog_params);
    std::memcpy(psc.alpha_test, s.alpha_test, sizeof psc.alpha_test);
    static PsConstants last_psc;
    static bool psc_sent;
    if (!psc_sent || std::memcmp(&psc, &last_psc, sizeof psc)) {
        bool fresh = !g_cb_ps;
        constants(g_cb_ps, &psc, sizeof psc);
        if (fresh) g_ctx->PSSetConstantBuffers(1, 1, &g_cb_ps);
        last_psc = psc, psc_sent = true;
    }

    const VertexShader& v = g_vs[s.vs];
    if (s.vs != last_vs) g_ctx->VSSetShader(v.vs, nullptr, 0), g_ctx->IASetInputLayout(v.layout), last_vs = s.vs;
    if (s.ps != last_ps) g_ctx->PSSetShader(g_ps[s.ps], nullptr, 0), last_ps = s.ps;
    if (topology != last_topology) g_ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY(topology)), last_topology = topology;
    UINT stride = stride_floats * 4;
    UINT offset = append(g_vb, D3D11_BIND_VERTEX_BUFFER, vertices, vertex_count * stride);
    g_ctx->IASetVertexBuffers(0, 1, &g_vb.buf, &stride, &offset);
    if (indices) {
        UINT at = append(g_ib, D3D11_BIND_INDEX_BUFFER, indices, index_count * 4);
        g_ctx->IASetIndexBuffer(g_ib.buf, DXGI_FORMAT_R32_UINT, at);
        g_ctx->DrawIndexed(index_count, 0, 0);
    } else {
        g_ctx->Draw(vertex_count, 0);
    }
}

// Movie frames: the game uploads each Bink frame as three 8-bit planes (Y, U, V) and converts them to RGB in its
// own shader. Each new plane is cleaned here first, at its own resolution: an edge-preserving bilateral filter
// takes out grain and Bink's block noise, then where the picture holds still it is averaged a little with the
// previous cleaned frame (the shimmer of the 640x480 footage). Stillness is judged between consecutive raw frames,
// never against the cleaned history, and the blend is light, so an old image dies out within frames (no burn-in).
int gfx_video_filter(int src) {
    static ID3D11VertexShader* vs;
    static ID3D11PixelShader* ps;
    struct State {
        int out[2] = {-1, -1};
        int last_in = -1;  // the previous raw plane, for telling stillness from motion
        int cur = 0;
        bool primed = false;
    };
    static std::unordered_map<int, State> states;
    if (!vs) {
        ID3DBlob* v = compile("float4 main(uint id : SV_VertexID) : SV_Position {\n"
                              "  float2 uv = float2((id << 1) & 2, id & 2); return float4(uv * float2(2, -2) + float2(-1, 1), 0, 1); }\n",
                              "vs_5_0");
        ID3DBlob* f = compile(
            "Texture2D cur : register(t0); Texture2D prev : register(t1); Texture2D last : register(t2);\n"
            "float4 main(float4 pos : SV_Position) : SV_Target {\n"
            "  int2 size; cur.GetDimensions(size.x, size.y);\n"
            "  int2 p = int2(pos.xy);\n"
            "  float4 c = cur.Load(int3(p, 0));\n"
            "  float sum = 0, wsum = 0, blur = 0, bsum = 0;\n"
            "  [unroll] for (int y = -2; y <= 2; ++y) [unroll] for (int x = -2; x <= 2; ++x) {\n"
            "    float v = cur.Load(int3(clamp(p + int2(x, y), 0, size - 1), 0)).r, d = v - c.r;\n"
            "    float ws = exp(-(x * x + y * y) / 4.5), w = ws * exp(-d * d / (2 * 0.04 * 0.04));\n"
            "    sum += v * w; wsum += w; blur += v * ws; bsum += ws;\n"
            "  }\n"
            "  float s = sum / wsum, pv = prev.Load(int3(p, 0)).r;\n"
            // edge-only sharpening: real edges (well above the grain) get some contrast back, flat areas none
            "  float detail = s - blur / bsum;\n"
            "  s = saturate(s + 0.45 * detail * smoothstep(0.015, 0.045, abs(detail)));\n"
            // motion: the largest change of 3x3 averages around the pixel (averages ignore the grain; the five
            // points catch an edge moving across), so only truly still areas are blended over time
            "  float motion = 0;\n"
            "  int2 at[5] = {int2(0, 0), int2(-2, 0), int2(2, 0), int2(0, -2), int2(0, 2)};\n"
            "  [unroll] for (int i = 0; i < 5; ++i) {\n"
            "    float a = 0, b = 0;\n"
            "    [unroll] for (int y = -1; y <= 1; ++y) [unroll] for (int x = -1; x <= 1; ++x) {\n"
            "      int3 q = int3(clamp(p + at[i] + int2(x, y), 0, size - 1), 0);\n"
            "      a += cur.Load(q).r, b += last.Load(q).r;\n"
            "    }\n"
            "    motion = max(motion, abs(a - b) / 9);\n"
            "  }\n"
            "  float k = 0.35 * exp(-pow(motion / 0.012, 2));\n"
            "  return float4(lerp(s, pv, k).xxx, c.a);\n"
            "}\n",
            "ps_5_0");
        if (!v || !f) fatal("the movie filter shaders did not compile");
        check(g_device->CreateVertexShader(v->GetBufferPointer(), v->GetBufferSize(), nullptr, &vs), "movie filter vs");
        check(g_device->CreatePixelShader(f->GetBufferPointer(), f->GetBufferSize(), nullptr, &ps), "movie filter ps");
        v->Release(), f->Release();
    }
    State& st = states[src];
    // a copy: the textures added below can move g_textures, and a reference into it would then read freed memory
    // (the d3d11.dll crash about one start in ten, at the first movie)
    const Texture in = g_textures[src];
    if (st.out[0] >= 0 && (g_textures[st.out[0]].width != in.width || g_textures[st.out[0]].height != in.height))
        st = State{};  // the id now holds a plane of another size (another movie): new buffers
    if (st.out[0] < 0)
        for (int* o : {&st.out[0], &st.out[1], &st.last_in}) {  // two cleaned frames and the last raw one
            Texture t = {};
            D3D11_TEXTURE2D_DESC d = {};
            d.Width = in.width, d.Height = in.height, d.MipLevels = 1, d.ArraySize = 1;
            d.Format = DXGI_FORMAT_R8G8B8A8_UNORM, d.SampleDesc.Count = 1;
            d.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
            check(g_device->CreateTexture2D(&d, nullptr, &t.tex), "movie filter texture");
            check(g_device->CreateShaderResourceView(t.tex, nullptr, &t.srv), "movie filter view");
            check(g_device->CreateRenderTargetView(t.tex, nullptr, &t.rtv), "movie filter target");
            t.width = in.width, t.height = in.height;
            g_textures.push_back(t);
            *o = int(g_textures.size() - 1);
        }
    int next = st.cur ^ 1;
    ID3D11ShaderResourceView* none[3] = {};
    g_ctx->PSSetShaderResources(0, 3, none);
    g_ctx->OMSetRenderTargets(1, &g_textures[st.out[next]].rtv, nullptr);
    D3D11_VIEWPORT vp = {0, 0, float(in.width), float(in.height), 0, 1};
    g_ctx->RSSetViewports(1, &vp);
    g_ctx->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
    g_ctx->OMSetDepthStencilState(nullptr, 0);
    g_ctx->RSSetState(nullptr);
    g_ctx->IASetInputLayout(nullptr);
    g_ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    g_ctx->VSSetShader(vs, nullptr, 0);
    g_ctx->PSSetShader(ps, nullptr, 0);
    ID3D11ShaderResourceView* views[3] = {in.srv, st.primed ? g_textures[st.out[st.cur]].srv : in.srv,
                                          st.primed ? g_textures[st.last_in].srv : in.srv};
    g_ctx->PSSetShaderResources(0, 3, views);
    g_ctx->Draw(3, 0);
    g_ctx->PSSetShaderResources(0, 3, none);
    g_ctx->CopyResource(g_textures[st.last_in].tex, in.tex);  // same size and format: the raw plane for next time
    g_ctx->OMSetRenderTargets(1, &g_rt, g_rt_depth);
    g_pipeline_touched = true;
    st.cur = next, st.primed = true;
    return st.out[st.cur];
}
