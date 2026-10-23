#include "texture.h"

#include <cstring>

namespace {

uint32_t rgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a) { return r | (g << 8) | (b << 16) | (a << 24); }
uint32_t expand(uint32_t v, int bits) { return bits == 8 ? v : (v << (8 - bits)) | (v >> (2 * bits - 8 > 0 ? 2 * bits - 8 : 0)); }

// one texel of an uncompressed format
uint32_t texel(uint32_t f, uint32_t v) {
    switch (f) {
    case 0x06: case 0x12: return rgba((v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF, v >> 24);  // A8R8G8B8
    case 0x07: case 0x1E: return rgba((v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF, 0xFF);     // X8R8G8B8
    case 0x3F: case 0x40: return rgba(v >> 24, (v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF);  // A8B8G8R8
    case 0x05: case 0x11:  // R5G6B5
        return rgba(expand((v >> 11) & 31, 5), expand((v >> 5) & 63, 6), expand(v & 31, 5), 0xFF);
    case 0x02: case 0x10:  // A1R5G5B5
        return rgba(expand((v >> 10) & 31, 5), expand((v >> 5) & 31, 5), expand(v & 31, 5), v & 0x8000 ? 0xFF : 0);
    case 0x03: case 0x1C:  // X1R5G5B5
        return rgba(expand((v >> 10) & 31, 5), expand((v >> 5) & 31, 5), expand(v & 31, 5), 0xFF);
    case 0x04: case 0x1D:  // A4R4G4B4
        return rgba(((v >> 8) & 15) * 17, ((v >> 4) & 15) * 17, (v & 15) * 17, ((v >> 12) & 15) * 17);
    case 0x00: case 0x13: return rgba(v & 0xFF, v & 0xFF, v & 0xFF, 0xFF);  // L8
    case 0x01: case 0x1B: return rgba(v & 0xFF, v & 0xFF, v & 0xFF, v & 0xFF);  // AL8
    case 0x19: case 0x1F: return rgba(0xFF, 0xFF, 0xFF, v & 0xFF);  // A8
    case 0x1A: case 0x20: return rgba(v & 0xFF, v & 0xFF, v & 0xFF, (v >> 8) & 0xFF);  // A8L8
    }
    return rgba(0xFF, 0, 0xFF, 0xFF);
}

int bytes_per_texel(uint32_t f) {
    switch (f) {
    case 0x06: case 0x07: case 0x12: case 0x1E: case 0x3F: case 0x40: return 4;
    case 0x02: case 0x03: case 0x04: case 0x05: case 0x10: case 0x11: case 0x1A: case 0x1C: case 0x1D: case 0x20:
        return 2;
    case 0x00: case 0x01: case 0x13: case 0x19: case 0x1B: case 0x1F: return 1;
    }
    return 0;
}

bool linear(uint32_t f) { return (f >= 0x10 && f <= 0x13) || (f >= 0x1B && f <= 0x20) || f == 0x3F; }

void color565(uint16_t v, uint32_t& r, uint32_t& g, uint32_t& b) {
    r = expand((v >> 11) & 31, 5), g = expand((v >> 5) & 63, 6), b = expand(v & 31, 5);
}

// DXT1/3/5 (S3TC); textures are stored as 4x4 blocks in row order
void decode_dxt(const uint8_t* src, uint32_t f, uint32_t w, uint32_t h, std::vector<uint32_t>& out) {
    uint32_t block_bytes = f == 0x0C ? 8 : 16, bw = (w + 3) / 4, bh = (h + 3) / 4;
    for (uint32_t by = 0; by < bh; ++by)
        for (uint32_t bx = 0; bx < bw; ++bx) {
            const uint8_t* b = src + (by * bw + bx) * block_bytes;
            const uint8_t* color = f == 0x0C ? b : b + 8;
            uint16_t c0 = uint16_t(color[0] | color[1] << 8), c1 = uint16_t(color[2] | color[3] << 8);
            uint32_t r[4], g[4], bl[4], a[4] = {255, 255, 255, 255};
            color565(c0, r[0], g[0], bl[0]);
            color565(c1, r[1], g[1], bl[1]);
            if (c0 > c1 || f != 0x0C) {
                r[2] = (2 * r[0] + r[1]) / 3, g[2] = (2 * g[0] + g[1]) / 3, bl[2] = (2 * bl[0] + bl[1]) / 3;
                r[3] = (r[0] + 2 * r[1]) / 3, g[3] = (g[0] + 2 * g[1]) / 3, bl[3] = (bl[0] + 2 * bl[1]) / 3;
            } else {
                r[2] = (r[0] + r[1]) / 2, g[2] = (g[0] + g[1]) / 2, bl[2] = (bl[0] + bl[1]) / 2;
                r[3] = g[3] = bl[3] = 0, a[3] = 0;
            }
            uint8_t alpha[16];
            if (f == 0x0E) {  // DXT3: explicit 4-bit alpha
                for (int k = 0; k < 16; ++k) alpha[k] = uint8_t(((b[k / 2] >> (4 * (k & 1))) & 15) * 17);
            } else if (f == 0x0F) {  // DXT5: interpolated alpha
                uint8_t a0 = b[0], a1 = b[1], tab[8] = {a0, a1};
                for (int k = 2; k < 8; ++k)
                    tab[k] = a0 > a1 ? uint8_t(((8 - k) * a0 + (k - 1) * a1) / 7)
                                     : k < 6 ? uint8_t(((6 - k) * a0 + (k - 1) * a1) / 5) : (k == 6 ? 0 : 255);
                uint64_t bits = 0;
                for (int k = 0; k < 6; ++k) bits |= uint64_t(b[2 + k]) << (8 * k);
                for (int k = 0; k < 16; ++k) alpha[k] = tab[(bits >> (3 * k)) & 7];
            }
            uint32_t idx = uint32_t(color[4] | color[5] << 8 | color[6] << 16 | uint32_t(color[7]) << 24);
            for (int k = 0; k < 16; ++k) {
                uint32_t x = bx * 4 + (k & 3), y = by * 4 + (k >> 2);
                if (x >= w || y >= h) continue;
                uint32_t i = (idx >> (2 * k)) & 3;
                uint32_t al = f == 0x0C ? a[i] : alpha[k];
                out[y * w + x] = rgba(r[i], g[i], bl[i], al);
            }
        }
}

}  // namespace

bool decode_texture(const uint8_t* src, uint32_t f, uint32_t w, uint32_t h, uint32_t pitch,
                    std::vector<uint32_t>& out) {
    out.assign(size_t(w) * h, rgba(0xFF, 0, 0xFF, 0xFF));
    if (f == 0x0C || f == 0x0E || f == 0x0F) {
        decode_dxt(src, f, w, h, out);
        return true;
    }
    int bpp = bytes_per_texel(f);
    if (!bpp) return false;
    bool lin = linear(f);
    for (uint32_t y = 0; y < h; ++y)
        for (uint32_t x = 0; x < w; ++x) {
            const uint8_t* p = lin ? src + y * pitch + x * bpp : src + swizzle_offset(x, y, w, h) * bpp;
            uint32_t v = 0;
            std::memcpy(&v, p, bpp);
            out[y * w + x] = texel(f, v);
        }
    return true;
}
