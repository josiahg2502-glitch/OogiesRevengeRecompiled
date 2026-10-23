// Encodes two sines with an IMA ADPCM encoder in the Xbox block layout, decodes them with
// adpcm::decode_block and checks the decoder reproduces the encoder's reconstruction exactly.
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "audio/adpcm.h"

static uint8_t encode(int sample, int& pred, int& index) {
    int s = adpcm::steps()[index], diff = sample - pred;
    uint8_t nib = 0;
    if (diff < 0) nib = 8, diff = -diff;
    if (diff >= s) nib |= 4, diff -= s;
    if (diff >= s / 2) nib |= 2, diff -= s / 2;
    if (diff >= s / 4) nib |= 1;
    adpcm::step(nib, pred, index);  // keep the encoder's state identical to the decoder's
    return nib;
}

int main() {
    const int channels = 2, blocks = 20;
    std::vector<int16_t> input(blocks * 64 * channels);
    for (size_t f = 0; f < input.size() / channels; ++f) {
        input[f * 2] = int16_t(12000 * std::sin(f * 0.05));
        input[f * 2 + 1] = int16_t(8000 * std::sin(f * 0.13 + 1));
    }
    std::vector<uint8_t> data(blocks * 36 * channels);
    std::vector<int16_t> recon(input.size());
    int pred[2] = {}, index[2] = {};
    for (int b = 0; b < blocks; ++b) {
        uint8_t* block = &data[b * 36 * channels];
        const int16_t* in = &input[b * 64 * channels];
        for (int ch = 0; ch < channels; ++ch) {
            pred[ch] = in[ch];
            recon[b * 64 * channels + ch] = in[ch];
            block[ch * 4] = uint8_t(pred[ch]), block[ch * 4 + 1] = uint8_t(pred[ch] >> 8);
            block[ch * 4 + 2] = uint8_t(index[ch]), block[ch * 4 + 3] = 0;
        }
        for (int word = 0; word < 8; ++word)
            for (int ch = 0; ch < channels; ++ch)
                for (int n = 0; n < 8; ++n) {
                    int frame = 1 + word * 8 + n;
                    int target = frame < 64 ? in[frame * channels + ch] : in[63 * channels + ch];
                    uint8_t nib = encode(target, pred[ch], index[ch]);
                    if (frame < 64) recon[(b * 64 + frame) * channels + ch] = int16_t(pred[ch]);
                    block[4 * channels + (word * channels + ch) * 4 + n / 2] |= uint8_t(nib << ((n & 1) * 4));
                }
    }
    int16_t out[64 * 2];
    int mismatches = 0;
    double err = 0;
    for (int b = 0; b < blocks; ++b) {
        adpcm::decode_block(&data[b * 36 * channels], channels, out);
        for (int k = 0; k < 64 * channels; ++k) {
            mismatches += out[k] != recon[b * 64 * channels + k];
            if (b > 0) err = std::fmax(err, std::abs(out[k] - input[b * 64 * channels + k]));
        }
    }
    // exact match with the encoder, and the signal is followed once the step size has adapted
    if (mismatches || err > 1500) {
        std::printf("adpcm: %d mismatches, max error %.0f\n", mismatches, err);
        return 1;
    }
    std::printf("adpcm ok (exact, max error after adaptation %.0f)\n", err);
    return 0;
}
