#include "reverb.h"

#include <algorithm>

namespace {
const int kComb[8] = {1116, 1188, 1277, 1356, 1422, 1491, 1557, 1617};  // Freeverb's tunings at 44.1 kHz
const int kAllpass[4] = {556, 441, 341, 225};
const int kSpread = 23;  // right channel lengths: decorrelates the two sides
float db(int32_t hundredths) { return hundredths <= -10000 ? 0.f : std::pow(10.f, hundredths / 2000.f); }
}  // namespace

void Reverb::set(const I3dl2& p, unsigned rate) {
    float scale = rate / 44100.f;
    if (rate != rate_) {
        for (int s = 0; s < 2; ++s) {
            for (int k = 0; k < 8; ++k) comb_[s][k].buf.assign(size_t((kComb[k] + s * kSpread) * scale), 0.f), comb_[s][k].pos = 0;
            for (int k = 0; k < 4; ++k) allpass_[s][k].buf.assign(size_t((kAllpass[k] + s * kSpread) * scale), 0.f), allpass_[s][k].pos = 0;
        }
        rate_ = rate;
    }
    float t60 = std::clamp(p.decay_time, 0.1f, 20.f);
    // high frequencies die away decay_hf_ratio times as fast: more damping in the feedback for a low ratio
    float damp = std::clamp(0.7f - 0.35f * p.decay_hf_ratio, 0.f, 0.9f);
    for (int s = 0; s < 2; ++s)
        for (auto& c : comb_[s]) {
            c.feedback = std::pow(10.f, -3.f * float(c.buf.size()) / (t60 * float(rate)));  // -60 dB after t60
            c.damp = damp;
        }
    // the late reverb's level, relative to the room; the network's own gain is about 1/0.015 (Freeverb)
    wet_ = db(std::clamp(p.room + p.reverb, -10000, 0)) * 0.015f * 3.f;
    input_lp_ = std::clamp(db(p.room_hf), 0.f, 1.f);  // room HF attenuation: a gentle low-pass on the send
    delay_.assign(size_t(std::clamp(p.reflections_delay + p.reverb_delay, 0.f, 0.3f) * rate) + 1, 0.f), delay_pos_ = 0;
}

void Reverb::process(const float* in, float* out, unsigned frames) {
    if (wet_ <= 0 || !rate_) return;
    for (unsigned i = 0; i < frames; ++i) {
        float x = delay_[delay_pos_];
        delay_[delay_pos_] = in[i];
        if (++delay_pos_ == delay_.size()) delay_pos_ = 0;
        lp_state_ += (x - lp_state_) * (0.2f + 0.8f * input_lp_);
        x = lp_state_;
        for (int s = 0; s < 2; ++s) {
            float y = 0;
            for (auto& c : comb_[s]) y += c.run(x);
            for (auto& a : allpass_[s]) y = a.run(y);
            out[i * 2 + s] += y * wet_;
        }
    }
}
