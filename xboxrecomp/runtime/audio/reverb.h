// The I3DL2 room reverb the Xbox's DSP runs on the I3DL2 mix bin, approximated with a Freeverb network tuned
// from the game's DSI3DL2LISTENER (decay time and HF ratio, room/reverb levels, pre-delay).
#pragma once
#include <cmath>
#include <cstdint>
#include <vector>

struct I3dl2 {  // DSI3DL2LISTENER
    int32_t room = -10000, room_hf = 0;
    float rolloff = 0, decay_time = 1.49f, decay_hf_ratio = 0.83f;
    int32_t reflections = -2602;
    float reflections_delay = 0.007f;
    int32_t reverb = 200;
    float reverb_delay = 0.011f, diffusion = 100, density = 100, hf_reference = 5000;
};

class Reverb {
public:
    void set(const I3dl2& p, unsigned rate);
    // adds the reverb of `in` (mono send, `frames` samples) into the stereo `out`
    void process(const float* in, float* out, unsigned frames);
    bool active() const { return wet_ > 0; }

private:
    struct Comb {
        std::vector<float> buf;
        size_t pos = 0;
        float store = 0, feedback = 0, damp = 0;
        float run(float x) {
            float y = buf[pos];
            store = y * (1 - damp) + store * damp;
            buf[pos] = x + store * feedback;
            if (++pos == buf.size()) pos = 0;
            return y;
        }
    };
    struct Allpass {
        std::vector<float> buf;
        size_t pos = 0;
        float run(float x) {
            float b = buf[pos], y = b - x;
            buf[pos] = x + b * 0.5f;
            if (++pos == buf.size()) pos = 0;
            return y;
        }
    };
    Comb comb_[2][8];
    Allpass allpass_[2][4];
    std::vector<float> delay_;  // pre-delay
    size_t delay_pos_ = 0;
    float wet_ = 0, input_lp_ = 0, lp_state_ = 0;
    unsigned rate_ = 0;
};
