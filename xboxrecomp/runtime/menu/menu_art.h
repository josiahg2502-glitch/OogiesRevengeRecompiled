// The menu's art, read from the player's own disc: Oogie's Revenge keeps its interface textures in @STM archives
// (stm_data\*.stm) as DDS files (.pig), and a few (the subtitle font, the loading scarecrow) inside default.xbe.
#pragma once
#include <cstdint>
#include <string>
#include <vector>

struct Image {
    int w = 0, h = 0;
    std::vector<uint32_t> px;  // 0xAARRGGBB, straight alpha
    bool empty() const { return px.empty(); }
    uint32_t at(int x, int y) const { return px[size_t(y) * w + x]; }
};

// DXT1/DXT3/DXT5 or 32-bit uncompressed DDS; empty if the data is not one.
Image dds_decode(const uint8_t* p, size_t n);
// An entry of an @STM archive ("menu/pig/sbmenu04.pig" in "Disc/files/stm_data/sbuty_u.stm"), decoded; empty if missing.
Image stm_image(const std::string& archive, const std::string& entry);
// The DDS image at `offset` in default.xbe, if it is one of w x h; empty otherwise.
Image xbe_image(uint32_t offset, int w, int h);

Image crop(const Image& src, int x0, int y0, int x1, int y1);
Image scale(const Image& src, int w, int h);  // bilinear (box-averaged when shrinking)
Image flip_x(const Image& src);
