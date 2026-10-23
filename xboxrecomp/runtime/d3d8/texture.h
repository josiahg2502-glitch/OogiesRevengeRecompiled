// Xbox texture decoding: swizzled/linear layouts and the NV2A formats, to 32-bit RGBA.
#pragma once
#include <cstdint>
#include <vector>

// Morton-order offset (in texels) of (x, y) in a swizzled width x height texture.
inline uint32_t swizzle_offset(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    uint32_t offset = 0, bit = 1;
    for (uint32_t i = 1; i < width || i < height; i <<= 1) {
        if (i < width) {
            if (x & i) offset |= bit;
            bit <<= 1;
        }
        if (i < height) {
            if (y & i) offset |= bit;
            bit <<= 1;
        }
    }
    return offset;
}

// Decodes level 0 of a texture's pixels into RGBA8 (r in the low byte). Returns false for formats it
// does not know (the caller shows those as magenta).
bool decode_texture(const uint8_t* src, uint32_t format, uint32_t width, uint32_t height, uint32_t pitch,
                    std::vector<uint32_t>& out);
