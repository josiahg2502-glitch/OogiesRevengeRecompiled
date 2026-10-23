// Reading the menu's art from the disc (see menu_art.h).
#include "menu_art.h"

#include <algorithm>
#include <cstdio>
#include <cstring>

namespace {

bool read_file(const std::string& path, std::vector<uint8_t>& out) {
    FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) return false;
    std::fseek(f, 0, SEEK_END);
    long n = std::ftell(f);
    std::fseek(f, 0, SEEK_SET);
    out.resize(n > 0 ? size_t(n) : 0);
    bool ok = n > 0 && std::fread(out.data(), 1, out.size(), f) == out.size();
    std::fclose(f);
    return ok;
}

uint32_t u32le(const uint8_t* p) { return p[0] | p[1] << 8 | p[2] << 16 | uint32_t(p[3]) << 24; }

uint32_t rgb565(uint16_t c) {
    uint32_t r = (c >> 11) & 31, g = (c >> 5) & 63, b = c & 31;
    return (r * 255 / 31) << 16 | (g * 255 / 63) << 8 | (b * 255 / 31);
}

// One 4x4 block's colours (the DXT1 part; `alpha_block` = DXT3/5 always use 4 colours).
void color_block(const uint8_t* b, bool alpha_block, uint32_t out[16]) {
    uint16_t c0 = uint16_t(b[0] | b[1] << 8), c1 = uint16_t(b[2] | b[3] << 8);
    uint32_t p[4] = {rgb565(c0) | 0xFF000000u, rgb565(c1) | 0xFF000000u, 0, 0};
    auto mix = [](uint32_t a, uint32_t c, int wa, int wc, int d) {
        uint32_t r = 0;
        for (int s = 0; s < 24; s += 8) r |= ((((a >> s) & 255) * wa + ((c >> s) & 255) * wc) / d) << s;
        return r | 0xFF000000u;
    };
    if (c0 > c1 || alpha_block) p[2] = mix(p[0], p[1], 2, 1, 3), p[3] = mix(p[0], p[1], 1, 2, 3);
    else p[2] = mix(p[0], p[1], 1, 1, 2), p[3] = 0;  // DXT1 1-bit alpha: transparent black
    uint32_t bits = u32le(b + 4);
    for (int i = 0; i < 16; ++i) out[i] = p[(bits >> (2 * i)) & 3];
}

}  // namespace

Image dds_decode(const uint8_t* p, size_t n) {
    Image img;
    if (n < 128 || std::memcmp(p, "DDS ", 4) != 0) return img;
    int h = int(u32le(p + 12)), w = int(u32le(p + 16));
    uint32_t pf_flags = u32le(p + 80), bits = u32le(p + 88);
    const uint8_t* d = p + 128;
    size_t left = n - 128;
    if (w <= 0 || h <= 0 || w > 4096 || h > 4096) return img;
    img.w = w, img.h = h, img.px.assign(size_t(w) * h, 0);
    if (pf_flags & 4) {  // FourCC: DXT1/3/5
        int kind = p[87] - '0';
        size_t block = kind == 1 ? 8 : 16;
        size_t need = size_t((w + 3) / 4) * ((h + 3) / 4) * block;
        if ((kind != 1 && kind != 3 && kind != 5) || left < need) return Image{};
        for (int by = 0; by < (h + 3) / 4; ++by)
            for (int bx = 0; bx < (w + 3) / 4; ++bx, d += block) {
                uint32_t c[16];
                color_block(kind == 1 ? d : d + 8, kind != 1, c);
                uint8_t a[16];
                if (kind == 3)
                    for (int i = 0; i < 16; ++i) a[i] = uint8_t(((d[i / 2] >> (4 * (i & 1))) & 15) * 17);
                else if (kind == 5) {
                    uint8_t a0 = d[0], a1 = d[1], t[8] = {a0, a1};
                    if (a0 > a1) for (int k = 1; k < 7; ++k) t[k + 1] = uint8_t(((7 - k) * a0 + k * a1) / 7);
                    else {
                        for (int k = 1; k < 5; ++k) t[k + 1] = uint8_t(((5 - k) * a0 + k * a1) / 5);
                        t[6] = 0, t[7] = 255;
                    }
                    uint64_t idx = 0;
                    for (int k = 0; k < 6; ++k) idx |= uint64_t(d[2 + k]) << (8 * k);
                    for (int i = 0; i < 16; ++i) a[i] = t[(idx >> (3 * i)) & 7];
                }
                for (int i = 0; i < 16; ++i) {
                    int x = bx * 4 + (i & 3), y = by * 4 + (i >> 2);
                    if (x >= w || y >= h) continue;
                    uint32_t v = c[i];
                    if (kind != 1) v = (v & 0xFFFFFF) | uint32_t(a[i]) << 24;
                    img.px[size_t(y) * w + x] = v;
                }
            }
    } else if (bits == 32 && left >= size_t(w) * h * 4) {  // A8R8G8B8
        for (size_t i = 0; i < img.px.size(); ++i) img.px[i] = u32le(d + 4 * i);
    } else {
        return Image{};
    }
    return img;
}

Image stm_image(const std::string& archive, const std::string& entry) {
    std::vector<uint8_t> d;
    if (!read_file(archive, d) || d.size() < 0x20 || std::memcmp(d.data(), "@STM", 4) != 0) return Image{};
    // entries: 24-byte name, offset, size; a size with the top bit set is a folder: its count, at `offset`
    struct Walk {
        const std::vector<uint8_t>& d;
        Image find(uint32_t table, uint32_t count, const std::string& path, const std::string& want) const {
            for (uint32_t i = 0; i < count; ++i) {
                uint32_t e = table + i * 32;
                if (e + 32 > d.size()) return Image{};
                std::string name(reinterpret_cast<const char*>(&d[e]), strnlen(reinterpret_cast<const char*>(&d[e]), 24));
                uint32_t off = u32le(&d[e + 24]), size = u32le(&d[e + 28]);
                if (size & 0x80000000u) {
                    Image r = find(off, size & 0x7FFFFFFF, path + name + "/", want);
                    if (!r.empty()) return r;
                } else if (path + name == want && size_t(off) + size <= d.size()) {
                    return dds_decode(&d[off], size);
                }
            }
            return Image{};
        }
    };
    return Walk{d}.find(0x20, u32le(&d[0x1C]), "", entry);
}

Image xbe_image(uint32_t offset, int w, int h) {
    std::vector<uint8_t> d;
    if (!read_file("Disc/files/default.xbe", d) || size_t(offset) + 128 > d.size()) return Image{};
    if (int(u32le(&d[offset + 16])) != w || int(u32le(&d[offset + 12])) != h) return Image{};
    return dds_decode(&d[offset], d.size() - offset);
}

Image crop(const Image& src, int x0, int y0, int x1, int y1) {
    Image r;
    x0 = std::clamp(x0, 0, src.w), x1 = std::clamp(x1, x0, src.w), y0 = std::clamp(y0, 0, src.h), y1 = std::clamp(y1, y0, src.h);
    r.w = x1 - x0, r.h = y1 - y0, r.px.resize(size_t(r.w) * r.h);
    for (int y = 0; y < r.h; ++y) std::memcpy(&r.px[size_t(y) * r.w], &src.px[size_t(y0 + y) * src.w + x0], size_t(r.w) * 4);
    return r;
}

Image scale(const Image& src, int w, int h) {
    Image r;
    if (src.empty() || w <= 0 || h <= 0) return r;
    r.w = w, r.h = h, r.px.resize(size_t(w) * h);
    float sx = float(src.w) / w, sy = float(src.h) / h;
    int nx = std::max(1, int(sx + 0.5f)), ny = std::max(1, int(sy + 0.5f));  // taps per axis when shrinking
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x) {
            float acc[4] = {}, wsum = 0;
            for (int j = 0; j < ny; ++j)
                for (int i = 0; i < nx; ++i) {
                    float fx = (x + (i + 0.5f) / nx) * sx - 0.5f, fy = (y + (j + 0.5f) / ny) * sy - 0.5f;
                    int x0 = std::clamp(int(std::floor(fx)), 0, src.w - 1), y0 = std::clamp(int(std::floor(fy)), 0, src.h - 1);
                    int x1 = std::min(x0 + 1, src.w - 1), y1 = std::min(y0 + 1, src.h - 1);
                    float tx = std::clamp(fx - std::floor(fx), 0.f, 1.f), ty = std::clamp(fy - std::floor(fy), 0.f, 1.f);
                    const uint32_t c[4] = {src.at(x0, y0), src.at(x1, y0), src.at(x0, y1), src.at(x1, y1)};
                    const float wt[4] = {(1 - tx) * (1 - ty), tx * (1 - ty), (1 - tx) * ty, tx * ty};
                    for (int k = 0; k < 4; ++k) {  // alpha-weighted, so transparent texels do not darken edges
                        float a = float(c[k] >> 24) / 255.f * wt[k];
                        acc[0] += float((c[k] >> 16) & 255) * a, acc[1] += float((c[k] >> 8) & 255) * a;
                        acc[2] += float(c[k] & 255) * a, acc[3] += a;
                    }
                    wsum += 1;
                }
            float a = acc[3] / wsum;
            uint32_t out = uint32_t(std::clamp(a * 255.f + 0.5f, 0.f, 255.f)) << 24;
            if (acc[3] > 0)
                out |= uint32_t(std::clamp(acc[0] / acc[3], 0.f, 255.f)) << 16 | uint32_t(std::clamp(acc[1] / acc[3], 0.f, 255.f)) << 8 |
                       uint32_t(std::clamp(acc[2] / acc[3], 0.f, 255.f));
            r.px[size_t(y) * w + x] = out;
        }
    return r;
}

Image flip_x(const Image& src) {
    Image r = src;
    for (int y = 0; y < r.h; ++y) std::reverse(r.px.begin() + size_t(y) * r.w, r.px.begin() + size_t(y + 1) * r.w);
    return r;
}
