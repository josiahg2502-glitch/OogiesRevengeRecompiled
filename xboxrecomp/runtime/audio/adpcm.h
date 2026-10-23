// Xbox ADPCM (WAVE_FORMAT_XBOX_ADPCM, 0x0069): IMA ADPCM in 36-byte blocks per channel, 64 samples each.
// Block: one 4-byte header per channel { s16 first sample, u8 step index, u8 0 }, then 4-byte words of
// nibbles alternating between channels (low nibble first).
#pragma once
#include <cstdint>

namespace adpcm {

constexpr int SAMPLES_PER_BLOCK = 64;
constexpr int BYTES_PER_CHANNEL = 36;

inline const int16_t* steps() {
    static const int16_t t[89] = {
        7,     8,     9,     10,    11,    12,    13,    14,    16,    17,    19,    21,    23,    25,    28,
        31,    34,    37,    41,    45,    50,    55,    60,    66,    73,    80,    88,    97,    107,   118,
        130,   143,   157,   173,   190,   209,   230,   253,   279,   307,   337,   371,   408,   449,   494,
        544,   598,   658,   724,   796,   876,   963,   1060,  1166,  1282,  1411,  1552,  1707,  1878,  2066,
        2272,  2499,  2749,  3024,  3327,  3660,  4026,  4428,  4871,  5358,  5894,  6484,  7132,  7845,  8630,
        9493,  10442, 11487, 12635, 13899, 15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767};
    return t;
}

// One nibble of IMA ADPCM; updates the predictor and step index.
inline int16_t step(uint8_t nibble, int& predictor, int& index) {
    static const int8_t adjust[8] = {-1, -1, -1, -1, 2, 4, 6, 8};
    int s = steps()[index];
    int diff = s >> 3;
    if (nibble & 1) diff += s >> 2;
    if (nibble & 2) diff += s >> 1;
    if (nibble & 4) diff += s;
    predictor += (nibble & 8) ? -diff : diff;
    predictor = predictor < -32768 ? -32768 : predictor > 32767 ? 32767 : predictor;
    index += adjust[nibble & 7];
    index = index < 0 ? 0 : index > 88 ? 88 : index;
    return int16_t(predictor);
}

// Decodes one block of `channels` channels into 64 interleaved frames.
inline void decode_block(const uint8_t* block, int channels, int16_t* out) {
    int pred[8], idx[8];
    for (int ch = 0; ch < channels; ++ch) {
        pred[ch] = int16_t(block[ch * 4] | (block[ch * 4 + 1] << 8));
        idx[ch] = block[ch * 4 + 2] > 88 ? 88 : block[ch * 4 + 2];
        out[ch] = int16_t(pred[ch]);  // the header sample is the first frame
    }
    const uint8_t* data = block + 4 * channels;
    // 8 words of 8 nibbles per channel; the 64th nibble per channel is not used (63 + header = 64 frames)
    for (int word = 0; word < 8; ++word)
        for (int ch = 0; ch < channels; ++ch) {
            const uint8_t* w = data + (word * channels + ch) * 4;
            for (int n = 0; n < 8; ++n) {
                int frame = 1 + word * 8 + n;
                uint8_t nib = (w[n >> 1] >> ((n & 1) * 4)) & 0xF;
                int16_t v = step(nib, pred[ch], idx[ch]);
                if (frame < SAMPLES_PER_BLOCK) out[frame * channels + ch] = v;
            }
        }
}

}  // namespace adpcm
