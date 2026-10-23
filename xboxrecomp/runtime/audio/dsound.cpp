// Xbox DirectSound (XDK 5849), replaced: buffers, streams and voices mixed on the PC.
//
// XACT and Bink stay recompiled and call the IDirectSound* entry points below. Guest objects are small
// blocks with a vtable (stream packets arrive through IDirectSoundStream::Process via the vtable);
// all audio state lives here. A mixer on the audio thread reads sample data straight from guest memory;
// finished stream packets are reported back on a guest thread, as the Xbox does from its DPC.
//
// 3D voices get the XDK's 3D attenuation and Doppler pitch, and their 3D bins the Xbox HRTF table's interaural
// delay plus a level difference by direction; the I3DL2 reverb is approximated (reverb.h). Not modelled: the HRTF
// spectra, the rest of the DSP effects image, parametric EQ filters (see set_filter), envelopes and LFOs (this
// game sets none; StopEx always comes without the release flags).
#include <windows.h>

#include <cmath>
#include <cstdlib>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <deque>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../config.h"
#include "../hle.h"
#include "../kernel.h"
#include "adpcm.h"
#include "audio_out.h"
#include "reverb.h"

namespace {

constexpr u32 DS_OK = 0, E_PENDING_ = 0x8000000A, E_ABORT_ = 0x80004004, DSERR_INVALIDCALL_ = 0x88780032;
constexpr u16 FORMAT_PCM = 1, FORMAT_XBOX_ADPCM = 0x69;
constexpr u32 DSBPLAY_LOOPING = 1, DSBPLAY_FROMSTART = 2;
constexpr u32 DSBSTATUS_PLAYING = 1, DSBSTATUS_LOOPING = 4;
constexpr u32 DSSTREAMSTATUS_READY = 1, DSSTREAMSTATUS_PLAYING = 2, DSSTREAMSTATUS_PAUSED = 4,
              DSSTREAMSTATUS_STARVED = 8;

struct WaveFormat {
    u16 tag = FORMAT_PCM, channels = 1;
    u32 rate = 48000;
    u16 block_align = 2, bits = 16;

    u32 frames(u32 bytes) const {
        return tag == FORMAT_XBOX_ADPCM ? bytes / block_align * adpcm::SAMPLES_PER_BLOCK : bytes / block_align;
    }
    u32 bytes(u32 frames) const {
        return tag == FORMAT_XBOX_ADPCM ? frames / adpcm::SAMPLES_PER_BLOCK * block_align : frames * block_align;
    }
};

WaveFormat read_format(u32 wfx) {
    WaveFormat f;
    if (!wfx) return f;
    f.tag = ld<u16>(wfx), f.channels = ld<u16>(wfx + 2), f.rate = ld<u32>(wfx + 4);
    f.block_align = ld<u16>(wfx + 12), f.bits = ld<u16>(wfx + 14);
    if (f.channels < 1 || f.channels > 6) f.channels = 1;
    if (!f.block_align) f.block_align = u16(f.channels * std::max<u16>(f.bits / 8, 1));
    if (f.tag != FORMAT_PCM && f.tag != FORMAT_XBOX_ADPCM)
        std::fprintf(stderr, "[dsound] unsupported wave format %04X: voice will be silent\n", f.tag);
    return f;
}

float db(s32 hundredths) { return hundredths <= -10000 ? 0.f : std::pow(10.f, float(hundredths) / 2000.f); }

// Interleaved int16 frames decoded from guest memory (ADPCM is decoded once; PCM is copied).
std::vector<s16> decode(const WaveFormat& f, u32 data, u32 bytes) {
    std::vector<s16> out;
    if (!data || !bytes) return out;
    if (f.tag == FORMAT_XBOX_ADPCM) {
        u32 blocks = bytes / f.block_align;
        out.resize(size_t(blocks) * adpcm::SAMPLES_PER_BLOCK * f.channels);
        for (u32 b = 0; b < blocks; ++b)
            adpcm::decode_block(g_mem + data + b * f.block_align, f.channels,
                                &out[size_t(b) * adpcm::SAMPLES_PER_BLOCK * f.channels]);
    } else if (f.tag == FORMAT_PCM && f.bits == 8) {
        out.resize(bytes);
        for (u32 k = 0; k < bytes; ++k) out[k] = s16((g_mem[data + k] - 128) << 8);
    } else if (f.tag == FORMAT_PCM) {
        out.resize(bytes / 2);
        std::memcpy(out.data(), g_mem + data, out.size() * 2);
    }
    return out;
}

struct Packet {
    // XMEDIAPACKET { pvBuffer, dwMaxSize, pdwCompletedSize, pdwStatus, hEvent/pContext, prtTimestamp }: copied at
    // submit time like the original (the game builds it on its stack and it is gone by completion)
    u32 max_size = 0, size_ptr = 0, status_ptr = 0, context = 0;
    std::vector<s16> pcm;
    u32 frames = 0;
    double pos = 0;
};

struct Voice {
    bool stream = false;
    u32 guest = 0, refs = 1;
    WaveFormat fmt;
    s32 volume = 0, headroom = 0, pitch = 0;
    std::vector<std::pair<u32, s32>> mixbins;  // (bin, hundredths of dB); empty = default speakers
    // 3D voice data from the XDK's 3D calculator (DS3DVOICEDATA dwords at +4..+0x34, by index), applied while
    // Use3DVoiceData is on, as CMcpxVoiceClient's volume (0x20A3F2) and pitch (0x20A646) code does
    bool use3d = false, hrtf = false;  // hrtf: an HRTF direction (flag 0x40) has been set
    s32 d3[14] = {};
    // interaural delay of the 3D bins: the far ear hears the source itd samples later (smoothed toward the target)
    float itd = 0, itd_target = 0;
    s32 itd_az = 0, itd_el = 0x7FFFFFFF;  // the direction (float bits) the target was looked up for
    float history[64] = {};
    u32 history_pos = 0;

    // buffer
    u32 data = 0, bytes = 0;
    bool own_data = false;
    u32 play_start = 0, play_len = 0, loop_start = 0, loop_len = 0;  // bytes
    bool playing = false, looping = false;
    double pos = 0;  // frames from the start of the buffer
    u32 block = ~0u;                                  // the ADPCM block decoded in `block_pcm` (of `block_data`)
    u32 block_data = 0;
    s16 block_pcm[adpcm::SAMPLES_PER_BLOCK * 2] = {};

    // stream
    std::deque<Packet> packets;
    bool paused = false;
    u32 callback = 0, context = 0;
};

struct Completion {
    Voice* voice;
    u32 size_ptr, status_ptr, context, status, completed;
};

std::mutex g_mx;  // voices, packets, completions
std::unordered_map<u32, Voice*> g_voices;
std::vector<Completion> g_done;
u32 g_ds;  // the IDirectSound singleton
u32 g_buffer_vtable, g_stream_vtable, g_ds_vtable;
u64 g_mixed_frames;  // for the --audio check: frames that carried sound
double g_peak;
double g_send_energy;  // sum of squares sent to the I3DL2 reverb (OOGIE_AUDIO_STATS)

s32 pitch_for(u32 rate) { return s32(std::lround(4096.0 * std::log2(double(rate ? rate : 48000) / 48000.0))); }

Voice* voice(u32 guest) {
    auto it = g_voices.find(guest);
    if (it == g_voices.end()) fatal("DirectSound call on unknown object %08X", guest);
    return it->second;
}

// left/right gain of a mix bin; FX sends (6+) and LFE go nowhere until effects exist
void bin_gains(u32 bin, float& l, float& r) {
    switch (bin) {
    case 0: case 4: l = 1, r = 0; return;   // front left, back left
    case 1: case 5: l = 0, r = 1; return;   // front right, back right
    case 2: l = r = 0.7071f; return;         // center
    // the 3D (crosstalk-cancelled) bins, which the Xbox's DSP folds into the speakers: on stereo, left and right
    case 6: case 8: l = 1, r = 0; return;   // XTLK front left, back left
    case 7: case 9: l = 0, r = 1; return;   // XTLK front right, back right
    default: l = r = 0; return;
    }
}

// sample of channel ch at integer frame f of a voice's data
inline float sample_at(Voice& v, const std::vector<s16>& pcm, u32 f, int ch) {
    size_t i = size_t(f) * v.fmt.channels + ch;
    return i < pcm.size() ? pcm[i] / 32768.f : 0.f;
}

// Sample f, channel ch of a sound buffer, read live from guest memory: PCM directly (Bink rewrites its ring buffer
// while it plays), ADPCM one 64-sample block at a time. The game makes a new buffer object over its 1.9 MB effects
// bank for every sound it starts; decoding the whole bank each time held the voice lock for 12-20 ms (dropped frames).
float buffer_sample(Voice& v, u32 f, int ch) {
    const WaveFormat& w = v.fmt;
    if (w.tag == FORMAT_XBOX_ADPCM) {
        u32 b = f / adpcm::SAMPLES_PER_BLOCK;
        if (b != v.block || v.data != v.block_data) {
            if (u64(b + 1) * w.block_align > v.bytes || w.channels > 2) return 0.f;
            adpcm::decode_block(g_mem + v.data + b * w.block_align, w.channels, v.block_pcm);
            v.block = b, v.block_data = v.data;
        }
        return v.block_pcm[(f % adpcm::SAMPLES_PER_BLOCK) * w.channels + ch] / 32768.f;
    }
    if (w.tag != FORMAT_PCM) return 0.f;  // a format decode() does not know: silent, as before
    size_t i = size_t(f) * w.channels + ch;
    if (w.bits == 8) return i < v.bytes ? (g_mem[v.data + i] - 128) / 128.f : 0.f;
    return i * 2 + 1 < v.bytes ? ld<s16>(v.data + u32(i * 2)) / 32768.f : 0.f;
}

// The interaural delay in samples (+: the left ear lags) the Xbox's HRTF table gives a direction, found as
// the XDK's full-HRTF lookup does (0x20798E): elevation in 6-degree rows, azimuth columns of 3, 6 or 12 degrees
// by elevation, folded front/back in its 5-channel mode; the delay is byte 31 of the entry's left-ear filter.
float hrtf_itd(float az, float el) {
    constexpr u32 kIndex = 0x220878, kFilters = 0x20F2B8, kMode = 0x221B00;  // in the game's XDK data
    if (!std::isfinite(az) || !std::isfinite(el)) return 0;
    int eq = int(el < 0 ? el - 3 : el + 3) / 6 * 6;
    float a = std::fabs(az);
    int aq = std::abs(eq) == 90 ? 0 : std::abs(eq) > 60 ? int(a + 6) / 12 * 12 : std::abs(eq) > 30 ? int(a + 3) / 6 * 6 : int(a + 1.5f) / 3 * 3;
    u32 mode = ld<u32>(kMode);
    if (((mode & 0xFFFF) == 2 || (mode & 0x10000)) && aq > 90) aq = 180 - aq;
    u32 ai = u32(aq / 3), ei = u32((eq + 90) / 6);
    if (ai >= 61) ai = 0;
    if (ei >= 31) ei = 0;
    u32 entry = ld<u16>(kIndex + 2 * (ai * 31 + ei));
    float delay = float(ld<u8>(kFilters + entry * 32 + 31));
    return az < 0 ? -delay : delay;
}

void mix_voice(Voice& v, float* out, float* send, u32 frames, u32 rate) {  // send: the I3DL2 reverb bin (mono)
    float gl = 0, gr = 0;
    float base = db(v.volume - v.headroom);
    // the music is XACT's stereo stream on the default speakers (dialogue and effects are buffers): [audio] music
    const float music = config().music / 100.f;  // live: the in-game menu changes it
    if (v.stream && v.fmt.channels == 2 && v.mixbins.empty()) base *= music;
    float chl[6] = {}, chr[6] = {}, chs[6] = {};
    float xl = 0, xr = 0;  // a mono 3D voice's 3D bins (6-9), heard through the interaural delay
    bool spatial = v.use3d && v.hrtf && v.fmt.channels == 1;
    if (v.mixbins.empty()) {
        if (v.fmt.channels == 1) chl[0] = chr[0] = base;
        else chl[0] = base, chr[1] = base;
    } else {
        // 3D attenuations in hundredths of dB, each clamped to [-10000, 0], by bin group (the XDK's formula)
        s32 t_front = 0, t_xfront = 0, t_xback = 0, t_center = 0, t_room = 0;
        if (v.use3d) {
            auto clamp = [](s32 x) { return x < -10000 ? -10000 : x > 0 ? 0 : x; };
            const s32* d = v.d3;
            t_front = clamp(d[1] + d[2]);
            t_xfront = clamp(d[7] + d[5] + d[3] + t_front), t_xback = clamp(d[7] + d[4] + t_front);
            t_center = clamp(d[7] + d[6] + d[3] + t_front), t_room = clamp(d[8] + t_front);
        }
        // The Xbox runs the 3D bins (6-9) through an HRTF filter pair picked by the source's azimuth (+0x28, positive
        // to the right: the XDK puts the near-ear filter in the right slot) and elevation (+0x2C), in degrees. Here
        // the direction gives the table's interaural delay and an equal-power level difference on its left-right part.
        // shortcut: no HRTF spectra (the table's 8-bit taps don't decode to a plausible response yet)
        float ear_l = 1, ear_r = 1;
        if (v.use3d && v.hrtf) {
            float az, el;
            std::memcpy(&az, &v.d3[10], 4), std::memcpy(&el, &v.d3[11], 4);
            float lateral = std::sin(az * 0.0174533f) * std::cos(el * 0.0174533f);
            if (std::isfinite(lateral)) ear_l = std::sqrt(1 - lateral), ear_r = std::sqrt(1 + lateral);  // centre stays at 1
            if (v.d3[10] != v.itd_az || v.d3[11] != v.itd_el) v.itd_target = hrtf_itd(az, el), v.itd_az = v.d3[10], v.itd_el = v.d3[11];
        }
        // A 3D voice's first four hardware mix slots always feed the HRTF submixes (the 3D bins 6-9, as xemu's
        // voice processor does); the game's own list then only adds sends such as reverb (10) and LFE (3).
        static const std::vector<std::pair<u32, s32>> hrtf_bins = {{6, 0}, {8, 0}, {7, 0}, {9, 0}};
        bool has_3d_bins = false;
        for (auto& [bin, vol] : v.mixbins) has_3d_bins |= bin >= 6 && bin <= 9;
        std::vector<std::pair<u32, s32>> all = v.mixbins;
        if (v.use3d && !has_3d_bins) all.insert(all.begin(), hrtf_bins.begin(), hrtf_bins.end());
        for (size_t k = 0; k < all.size(); ++k) {
            int ch = int(k % v.fmt.channels);
            u32 bin = all[k].first;
            bin_gains(bin, gl, gr);
            if (bin >= 6 && bin <= 9) gl *= ear_l, gr *= ear_r;
            s32 t = bin == 2 ? t_center : bin == 6 || bin == 7 ? t_xfront : bin == 8 || bin == 9 ? t_xback : bin == 10 ? t_room : t_front;
            float g = base * db(all[k].second + t);
            if (spatial && bin >= 6 && bin <= 9) xl += gl * g, xr += gr * g;
            else chl[ch] += gl * g, chr[ch] += gr * g;
            if (bin == 10) chs[ch] += g;
        }
    }
    double step = 48000.0 * std::exp2((v.pitch + (v.use3d ? v.d3[9] : 0)) / 4096.0) / rate;  // + the 3D (Doppler) pitch
    int channels = v.fmt.channels;
    float itd_scale = rate / 48000.f;  // the table's delays are in samples of the APU's 48 kHz
    auto delayed = [&](float d) {  // the 3D voice's input d samples ago (linear between samples)
        u32 di = u32(d);
        float frac = d - float(di), a = v.history[(v.history_pos - di) & 63], b = v.history[(v.history_pos - di - 1) & 63];
        return a + (b - a) * frac;
    };
    auto emit = [&](u32 i, int ch, float s) {
        out[i * 2] += s * chl[ch], out[i * 2 + 1] += s * chr[ch], send[i] += s * chs[ch];
        if (!spatial) return;
        v.history[v.history_pos & 63] = s;
        v.itd += 0.01f * (v.itd_target * itd_scale - v.itd);  // glides when the source moves, no clicks
        out[i * 2] += delayed(std::max(v.itd, 0.f)) * xl, out[i * 2 + 1] += delayed(std::max(-v.itd, 0.f)) * xr;
        ++v.history_pos;
    };

    if (v.stream) {
        if (v.paused) return;
        for (u32 i = 0; i < frames && !v.packets.empty(); ++i) {
            Packet& p = v.packets.front();
            u32 f = u32(p.pos);
            float t = float(p.pos - f);
            for (int ch = 0; ch < channels; ++ch) {
                float a = sample_at(v, p.pcm, f, ch), b = f + 1 < p.frames ? sample_at(v, p.pcm, f + 1, ch) : a;
                emit(i, ch, a + (b - a) * t);
            }
            p.pos += step;
            if (p.pos >= p.frames) {
                g_done.push_back({&v, p.size_ptr, p.status_ptr, p.context, DS_OK, p.max_size});
                v.packets.pop_front();
            }
        }
        return;
    }

    if (!v.playing || !v.data) return;
    auto sample = [&](u32 f, int ch) { return buffer_sample(v, f, ch); };
    u32 total = v.fmt.frames(v.bytes);
    u32 end = v.play_len ? std::min(total, v.fmt.frames(v.play_start + v.play_len)) : total;
    u32 loop_begin = v.fmt.frames(v.loop_start);
    u32 loop_end = v.loop_len ? std::min(total, v.fmt.frames(v.loop_start + v.loop_len)) : end;
    if (v.looping) end = loop_end;
    for (u32 i = 0; i < frames; ++i) {
        if (v.pos >= end) {
            if (!v.looping || loop_end <= loop_begin) {
                v.playing = false;
                return;
            }
            v.pos = loop_begin + std::fmod(v.pos - end, double(loop_end - loop_begin));
        }
        u32 f = u32(v.pos);
        float t = float(v.pos - f);
        for (int ch = 0; ch < channels; ++ch) {
            float a = sample(f, ch);
            float b = f + 1 < end ? sample(f + 1, ch) : (v.looping ? sample(loop_begin, ch) : a);
            emit(i, ch, a + (b - a) * t);
        }
        v.pos += step;
    }
}

I3dl2 g_i3dl2;          // the listener's room, from SetI3DL2Listener (under g_mx)
bool g_i3dl2_changed = true;

std::atomic<bool> g_paused;  // the in-game menu is open: every voice holds where it is

void mix(float* out, u32 frames, u32 rate) {
    std::memset(out, 0, frames * 2 * sizeof(float));
    if (g_paused) return;
    std::lock_guard<std::mutex> lock(g_mx);
    struct Timer {  // testing: a mix pass that holds the voices long
        u32 frames;
        std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
        ~Timer() {
            static const bool on = std::getenv("OOGIE_HITCH_TRACE") != nullptr;
            double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
            if (on && ms > 2) std::fprintf(stderr, "[slow] mix of %u frames took %.1f ms\n", frames, ms);
        }
    } timer{frames};
    static std::vector<float> send;
    send.assign(frames, 0.f);
    static const bool probe = std::getenv("OOGIE_HITCH_TRACE") != nullptr;  // testing: what a slow pass spends its time on
    std::vector<std::pair<double, Voice*>> cost;
    auto tv = std::chrono::steady_clock::now();
    for (auto& [guest, v] : g_voices) {
        mix_voice(*v, out, send.data(), frames, rate);
        if (probe) {
            auto now = std::chrono::steady_clock::now();
            cost.push_back({std::chrono::duration<double, std::milli>(now - tv).count(), v});
            tv = now;
        }
    }
    auto tr = std::chrono::steady_clock::now();
    static Reverb reverb;
    static u32 reverb_rate;
    if (g_i3dl2_changed || reverb_rate != rate) reverb.set(g_i3dl2, rate), reverb_rate = rate, g_i3dl2_changed = false;
    reverb.process(send.data(), out, frames);
    if (probe) {
        double total = 0, rv = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - tr).count();
        for (auto& [ms, v] : cost) total += ms;
        if (total + rv > 2) {
            std::sort(cost.begin(), cost.end(), [](auto& a, auto& b) { return a.first > b.first; });
            std::string top;
            for (size_t k = 0; k < cost.size() && k < 3; ++k) {
                Voice* v = cost[k].second;
                char b[160];
                std::snprintf(b, sizeof b, " [%.1f ms %08X %s tag %X %u ch %u bit %u bytes playing %d 3d %d]", cost[k].first, v->guest,
                              v->stream ? "stream" : "buffer", v->fmt.tag, v->fmt.channels, v->fmt.bits, v->bytes, v->playing, v->use3d);
                top += b;
            }
            std::fprintf(stderr, "[slowmix] %zu voices %.1f ms, reverb %.1f ms, slowest:%s\n", g_voices.size(), total, rv, top.c_str());
        }
    }
    for (u32 i = 0; i < frames; ++i) g_send_energy += double(send[i]) * send[i];  // OOGIE_AUDIO_STATS
    bool loud = false;
    // OOGIE_AUDIO_DUMP=file: the mix before the volume and limiter as raw 32-bit float stereo at `rate` Hz (checking sound without speakers)
    static FILE* dump = std::getenv("OOGIE_AUDIO_DUMP") ? std::fopen(std::getenv("OOGIE_AUDIO_DUMP"), "wb") : nullptr;
    if (dump) std::fwrite(out, sizeof(float), frames * 2, dump), std::fflush(dump);
    // [audio] volume (100 = the Xbox's own level; up to 200 for quiet speakers), then a peak
    // limiter instead of hard clipping: the gain dips at once when a sample would pass 0.95 and recovers in ~80 ms
    const float gain = config().volume / 100.f;
    static float limit = 1;
    const float release = 1 - std::exp(-1.f / (0.08f * float(rate)));
    for (u32 i = 0; i < frames; ++i) {
        float l = out[i * 2] * gain, r = out[i * 2 + 1] * gain, a = std::max(std::fabs(l), std::fabs(r));
        if (a > 0.0005f) loud = true;
        if (a > g_peak) g_peak = a;
        float need = a * limit > 0.95f ? 0.95f / a : 1.f;
        limit = need < limit ? need : limit + (1 - limit) * release;
        out[i * 2] = std::clamp(l * limit, -1.f, 1.f), out[i * 2 + 1] = std::clamp(r * limit, -1.f, 1.f);
    }
    if (loud) g_mixed_frames += frames;
}

// Reports finished stream packets to the game: status, size, completion event or stream callback.
void service(Ctx& c) {
    std::vector<Completion> done;
    auto t_lock = std::chrono::steady_clock::now();
    {
        std::lock_guard<std::mutex> lock(g_mx);
        done.swap(g_done);
    }
    static const bool slow_probe = std::getenv("OOGIE_HITCH_TRACE") != nullptr;  // testing
    if (double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t_lock).count(); slow_probe && ms > 2)
        std::fprintf(stderr, "[slow] audio service waited %.1f ms for the mixer lock\n", ms);
    for (auto& d : done) {
        if (d.size_ptr) st<u32>(d.size_ptr, d.completed);
        if (d.status_ptr) st<u32>(d.status_ptr, d.status);
        u32 event_or_context = d.context;
        static const bool slow_log = std::getenv("OOGIE_HITCH_TRACE") != nullptr;  // testing
        auto t0 = std::chrono::steady_clock::now();
        if (d.voice->callback) call_guest(c, d.voice->callback, {d.voice->context, event_or_context, d.status});
        else if (event_or_context) set_event(object_from_handle(c, event_or_context));
        if (double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count(); slow_log && ms > 2)
            std::fprintf(stderr, "[slow] stream callback %08X (voice %08X, %zu done) took %.1f ms\n", d.voice->callback, d.voice->guest, done.size(), ms);
    }
}

// The audio "DPC": a guest thread that hands finished packets back every few milliseconds.
void service_thread() {
    Ctx c;
    thread_setup(c, 0x10000, 0);
    bool stats = std::getenv("OOGIE_AUDIO_STATS") != nullptr;
    for (unsigned tick = 1;; ++tick) {
        Sleep(4);
        if (stats && tick % 250 == 0) {  // every ~1 s: what plays, and how loud
            std::lock_guard<std::mutex> lock(g_mx);
            unsigned playing = 0, in3d = 0;
            std::string sample;  // one playing 3D voice's attenuations: what distance does to it
            std::map<u32, unsigned> bins;  // mix bin -> playing voices sending to it
            for (auto& [g, v] : g_voices) {
                bool on = v->stream ? !v->packets.empty() : v->playing;
                if (on)
                    for (auto& [bin, vol] : v->mixbins) ++bins[bin];
                if (on) {  // every playing voice's levels: volume, bins, 3D attenuation
                    std::string s;
                    for (auto& [bin, vol] : v->mixbins) s += " " + std::to_string(bin) + ":" + std::to_string(vol);
                    std::fprintf(stderr, "[dsound] voice %08X %s %u ch vol %d headroom %d 3d %d (%d %d %d %d) bins%s\n", v->guest,
                                 v->stream ? "stream" : "buffer", v->fmt.channels, v->volume, v->headroom, v->use3d, v->d3[1], v->d3[2],
                                 v->d3[5], v->d3[7], s.c_str());
                }
                playing += on, in3d += on && v->use3d;
                if (on && v->use3d && sample.empty()) {
                    char b[96];
                    std::snprintf(b, sizeof b, ", e.g. 3D %d %d %d %d pitch %d", v->d3[1], v->d3[2], v->d3[3], v->d3[7], v->d3[9]);
                    sample = b;
                }
            }
            std::fprintf(stderr, "[dsound] %zu voices, %u playing (%u in 3D%s), %.1f s of audible output, peak %.2f, reverb send rms %.4f\n",
                         g_voices.size(), playing, in3d, sample.c_str(), g_mixed_frames / 48000.0, g_peak, std::sqrt(g_send_energy / 48000.0));
            g_send_energy = 0;
            std::string used;
            for (auto& [bin, n] : bins) used += " " + std::to_string(bin) + "x" + std::to_string(n);
            std::fprintf(stderr, "[dsound] bins in use:%s\n", used.c_str());
        }
        guest_lock();
        static const bool slow_log = std::getenv("OOGIE_HITCH_TRACE") != nullptr;  // testing
        auto t0 = std::chrono::steady_clock::now();
        st<u8>(c.fs_base + KPCR_IRQL, 2);
        service(c);
        st<u8>(c.fs_base + KPCR_IRQL, 0);
        if (double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count(); slow_log && ms > 5)
            std::fprintf(stderr, "[slow] audio service (stream callbacks) took %.1f ms\n", ms);
        guest_unlock();
    }
}

std::vector<std::pair<u32, s32>> read_mixbins(u32 p) {  // DSMIXBINS { count, DSMIXBINVOLUMEPAIR* { bin, volume } }
    std::vector<std::pair<u32, s32>> bins;
    if (!p) return bins;
    u32 n = std::min(ld<u32>(p), 8u), pairs = ld<u32>(p + 4);
    for (u32 k = 0; k < n; ++k) bins.push_back({ld<u32>(pairs + 8 * k), ld<s32>(pairs + 8 * k + 4)});
    return bins;
}

void once(const char* what) {
    static std::unordered_map<std::string, bool> seen;
    if (!seen[what]) {
        seen[what] = true;
        std::fprintf(stderr, "[dsound] %s: not modelled yet\n", what);
    }
}

u32 add_ref_voice(u32 guest) {
    std::lock_guard<std::mutex> lock(g_mx);
    return ++voice(guest)->refs;
}

// Aborts a voice's pending packets: size and status are written now (the caller holds the guest lock), the
// completion event or callback follows from the service thread
static void abort_packets(Voice* v, bool now) {  // under g_mx
    for (auto& p : v->packets) {
        if (now) {
            if (p.size_ptr) st<u32>(p.size_ptr, 0);
            if (p.status_ptr) st<u32>(p.status_ptr, E_ABORT_);
            g_done.push_back({v, 0, 0, p.context, E_ABORT_, 0});
        } else {
            g_done.push_back({v, p.size_ptr, p.status_ptr, p.context, E_ABORT_, 0});
        }
    }
}

u32 release_voice(u32 guest) {
    std::lock_guard<std::mutex> lock(g_mx);
    Voice* v = voice(guest);
    if (--v->refs) return v->refs;
    abort_packets(v, true);
    v->packets.clear();
    v->playing = false;
    // shortcut: the Voice stays allocated (pending completions point at it); a few KB per freed voice
    g_voices.erase(guest);
    return 0;
}

u32 new_object(u32 vtable) {
    u32 o = kalloc(0x20);
    st<u32>(o, vtable);
    return o;
}

// ---- vtable entries the game reaches without a named wrapper ----
template <int Slot> u32 unknown_slot(Ctx& c) {
    fatal("DirectSound vtable slot %d called on %08X from %08X: not implemented", Slot, sarg(c, 0), ld<u32>(c.esp));
}
template <int... S> void fill_unknown(u32 vt, std::integer_sequence<int, S...>) {
    ((st<u32>(vt + 4 * S, hle_thunk(unknown_slot<S>, 0, "DirectSound vtable slot"))), ...);
}

u32 ref_add(Ctx& c) { return add_ref_voice(sarg(c, 0)); }
u32 ref_release(Ctx& c) {
    u32 o = sarg(c, 0);
    if (o == g_ds) return 1;  // the DirectSound object lives as long as the game
    return release_voice(o);
}

// XMediaObject on streams
u32 stream_get_info(Ctx& c) {  // XMEDIAINFO { dwFlags, dwInputSize, dwOutputSize, dwMaxLookahead }
    u32 info = sarg(c, 1);
    st<u32>(info, 0x00000003), st<u32>(info + 4, 0), st<u32>(info + 8, 0), st<u32>(info + 12, 0);
    return DS_OK;
}
u32 stream_status(u32 guest) {
    std::lock_guard<std::mutex> lock(g_mx);
    Voice* v = voice(guest);
    u32 s = DSSTREAMSTATUS_READY;
    if (v->paused) s |= DSSTREAMSTATUS_PAUSED;
    if (!v->packets.empty()) s |= DSSTREAMSTATUS_PLAYING;
    else s |= DSSTREAMSTATUS_STARVED;
    return s;
}
u32 stream_get_status(Ctx& c) { return st<u32>(sarg(c, 1), stream_status(sarg(c, 0))), DS_OK; }
u32 stream_process(Ctx& c) {
    u32 guest = sarg(c, 0), packet = sarg(c, 1);
    if (!packet) return DS_OK;
    Packet p;
    p.max_size = ld<u32>(packet + 4), p.size_ptr = ld<u32>(packet + 8), p.status_ptr = ld<u32>(packet + 12);
    p.context = ld<u32>(packet + 16);
    if (p.status_ptr) st<u32>(p.status_ptr, E_PENDING_);
    std::lock_guard<std::mutex> lock(g_mx);
    Voice* v = voice(guest);
    if (v->packets.size() > 64) return DSERR_INVALIDCALL_;
    p.pcm = decode(v->fmt, ld<u32>(packet), ld<u32>(packet + 4));
    p.frames = u32(p.pcm.size() / v->fmt.channels);
    v->packets.push_back(std::move(p));
    return DS_OK;
}
u32 stream_discontinuity(Ctx&) { return DS_OK; }  // the stream simply runs dry after its last packet
u32 flush_stream(u32 guest, bool now) {
    std::lock_guard<std::mutex> lock(g_mx);
    Voice* v = voice(guest);
    abort_packets(v, now);
    v->packets.clear();
    return DS_OK;
}
u32 stream_flush(Ctx& c) { return flush_stream(sarg(c, 0), true); }

void make_vtables() {
    if (g_buffer_vtable) return;
    for (u32* vt : {&g_buffer_vtable, &g_stream_vtable, &g_ds_vtable}) {
        *vt = kalloc(4 * 32);
        fill_unknown(*vt, std::make_integer_sequence<int, 32>());
        st<u32>(*vt, hle_thunk(ref_add, 4, "DirectSound AddRef"));
        st<u32>(*vt + 4, hle_thunk(ref_release, 4, "DirectSound Release"));
    }
    st<u32>(g_stream_vtable + 8, hle_thunk(stream_get_info, 8, "IDirectSoundStream::GetInfo"));
    st<u32>(g_stream_vtable + 12, hle_thunk(stream_get_status, 8, "IDirectSoundStream::GetStatus"));
    st<u32>(g_stream_vtable + 16, hle_thunk(stream_process, 12, "IDirectSoundStream::Process"));
    st<u32>(g_stream_vtable + 20, hle_thunk(stream_discontinuity, 4, "IDirectSoundStream::Discontinuity"));
    st<u32>(g_stream_vtable + 24, hle_thunk(stream_flush, 4, "IDirectSoundStream::Flush"));
}

#define WITH_VOICE(expr)                       \
    std::lock_guard<std::mutex> lock(g_mx);    \
    Voice* v = voice(sarg(c, 0));              \
    expr;                                      \
    return DS_OK;

}  // namespace

void audio_pause(bool on) { g_paused = on; }

// ---- IDirectSound ----
HLE(DirectSoundCreate) {
    if (!g_ds) {
        make_vtables();
        g_ds = new_object(g_ds_vtable);
        audio_start(mix);
        std::thread(service_thread).detach();
    }
    st<u32>(sarg(c, 1), g_ds);
    return DS_OK;
}
HLE_REGISTER(DirectSoundCreate)
HLE(DirectSoundDoWork) {
    service(c);
    return 0;
}
HLE_REGISTER(DirectSoundDoWork)
// DirectSoundUseFullHRTF stays recompiled: it installs the HRTF routine Calculate3D calls
HLE(XAudioDownloadEffectsImage) {
    once("XAudioDownloadEffectsImage (DSP effects)");
    if (u32 out = sarg(c, 3)) st<u32>(out, kalloc(0x100));  // DSEFFECTIMAGEDESC with no effects
    return DS_OK;
}
HLE_REGISTER(XAudioDownloadEffectsImage)
HLE(IDirectSound_Release) { return 1; }
HLE_REGISTER(IDirectSound_Release)
HLE(IDirectSound_GetCaps) {
    u32 caps = sarg(c, 1);  // DSCAPS { free 2D buffers, free 3D buffers, free SGEs, memory allocated }
    st<u32>(caps, 256), st<u32>(caps + 4, 64), st<u32>(caps + 8, 2047), st<u32>(caps + 12, 0);
    return DS_OK;
}
HLE_REGISTER(IDirectSound_GetCaps)
HLE(IDirectSound_GetOutputLevels) { return std::memset(g_mem + sarg(c, 1), 0, 64), DS_OK; }
HLE_REGISTER(IDirectSound_GetOutputLevels)
HLE(IDirectSound_SetMixBinHeadroom) { return DS_OK; }
HLE_REGISTER(IDirectSound_SetMixBinHeadroom)
HLE(IDirectSound_SetI3DL2Listener) {  // (this, DSI3DL2LISTENER*, dwApply)
    u32 l = sarg(c, 1);
    if (!l) return DS_OK;
    I3dl2 p;
    p.room = ld<s32>(l), p.room_hf = ld<s32>(l + 4), p.rolloff = ld<float>(l + 8), p.decay_time = ld<float>(l + 0xC);
    p.decay_hf_ratio = ld<float>(l + 0x10), p.reflections = ld<s32>(l + 0x14), p.reflections_delay = ld<float>(l + 0x18);
    p.reverb = ld<s32>(l + 0x1C), p.reverb_delay = ld<float>(l + 0x20), p.diffusion = ld<float>(l + 0x24);
    p.density = ld<float>(l + 0x28), p.hf_reference = ld<float>(l + 0x2C);
    std::lock_guard<std::mutex> lock(g_mx);
    g_i3dl2 = p, g_i3dl2_changed = true;
    static int told;
    if (told++ < 8)
        std::fprintf(stderr, "[dsound] I3DL2 room %d hf %d decay %.2f s ratio %.2f reflections %d reverb %d delay %.3f\n", p.room,
                     p.room_hf, p.decay_time, p.decay_hf_ratio, p.reflections, p.reverb, p.reverb_delay);
    return DS_OK;
}
HLE_REGISTER(IDirectSound_SetI3DL2Listener)
HLE(IDirectSound_CommitDeferredSettings) { return DS_OK; }
HLE_REGISTER(IDirectSound_CommitDeferredSettings)

HLE(IDirectSound_CreateSoundBuffer) {
    u32 desc = sarg(c, 1), out = sarg(c, 2);  // DSBUFFERDESC { dwSize, dwFlags, dwBufferBytes, lpwfxFormat, lpMixBins }
    auto* v = new Voice;
    v->guest = new_object(g_buffer_vtable);
    v->fmt = read_format(ld<u32>(desc + 12));
    v->pitch = pitch_for(v->fmt.rate);
    v->mixbins = read_mixbins(ld<u32>(desc + 16));
    if (u32 bytes = ld<u32>(desc + 8)) {
        v->data = contiguous_alloc(bytes, 4096), v->bytes = bytes, v->own_data = true;
    }
    std::lock_guard<std::mutex> lock(g_mx);
    g_voices[v->guest] = v;
    st<u32>(out, v->guest);
    return DS_OK;
}
HLE_REGISTER(IDirectSound_CreateSoundBuffer)

HLE(IDirectSound_CreateSoundStream) {
    // DSSTREAMDESC { dwFlags, dwMaxAttachedPackets, lpwfxFormat, lpfnCallback, lpvContext, lpMixBins }
    u32 desc = sarg(c, 1), out = sarg(c, 2);
    auto* v = new Voice;
    v->stream = true;
    v->guest = new_object(g_stream_vtable);
    v->fmt = read_format(ld<u32>(desc + 8));
    v->pitch = pitch_for(v->fmt.rate);
    v->callback = ld<u32>(desc + 12), v->context = ld<u32>(desc + 16);
    v->mixbins = read_mixbins(ld<u32>(desc + 20));
    std::lock_guard<std::mutex> lock(g_mx);
    g_voices[v->guest] = v;
    st<u32>(out, v->guest);
    return DS_OK;
}
HLE_REGISTER(IDirectSound_CreateSoundStream)

// ---- IDirectSoundBuffer ----
HLE(IDirectSoundBuffer_Release) { return release_voice(sarg(c, 0)); }
HLE_REGISTER(IDirectSoundBuffer_Release)
HLE(IDirectSoundBuffer_SetBufferData) { WITH_VOICE((v->data = sarg(c, 1), v->bytes = sarg(c, 2), v->pos = 0)) }
HLE_REGISTER(IDirectSoundBuffer_SetBufferData)
HLE(IDirectSoundBuffer_SetFormat) { WITH_VOICE((v->fmt = read_format(sarg(c, 1)), v->pitch = pitch_for(v->fmt.rate))) }
HLE_REGISTER(IDirectSoundBuffer_SetFormat)
HLE(IDirectSoundBuffer_SetPlayRegion) { WITH_VOICE((v->play_start = sarg(c, 1), v->play_len = sarg(c, 2))) }
HLE_REGISTER(IDirectSoundBuffer_SetPlayRegion)
HLE(IDirectSoundBuffer_SetLoopRegion) { WITH_VOICE((v->loop_start = sarg(c, 1), v->loop_len = sarg(c, 2))) }
HLE_REGISTER(IDirectSoundBuffer_SetLoopRegion)
HLE(IDirectSoundBuffer_SetCurrentPosition) { WITH_VOICE(v->pos = v->fmt.frames(sarg(c, 1))) }
HLE_REGISTER(IDirectSoundBuffer_SetCurrentPosition)
HLE(IDirectSoundBuffer_GetCurrentPosition) {
    std::lock_guard<std::mutex> lock(g_mx);
    Voice* v = voice(sarg(c, 0));
    u32 play = v->fmt.bytes(u32(v->pos));
    if (sarg(c, 1)) st<u32>(sarg(c, 1), play);
    if (sarg(c, 2)) st<u32>(sarg(c, 2), play);
    return DS_OK;
}
HLE_REGISTER(IDirectSoundBuffer_GetCurrentPosition)
HLE(IDirectSoundBuffer_Play) {
    std::lock_guard<std::mutex> lock(g_mx);
    Voice* v = voice(sarg(c, 0));
    u32 flags = sarg(c, 3);
    v->looping = flags & DSBPLAY_LOOPING;
    if (flags & DSBPLAY_FROMSTART || !v->playing) v->pos = v->fmt.frames(v->play_start);
    v->playing = true;
    return DS_OK;
}
HLE_REGISTER(IDirectSoundBuffer_Play)
HLE(IDirectSoundBuffer_Stop) { WITH_VOICE(v->playing = false) }
HLE_REGISTER(IDirectSoundBuffer_Stop)
HLE(IDirectSoundBuffer_StopEx) { WITH_VOICE(v->playing = false) }  // envelope release not modelled: stops at once
HLE_REGISTER(IDirectSoundBuffer_StopEx)
HLE(IDirectSoundBuffer_GetStatus) {
    std::lock_guard<std::mutex> lock(g_mx);
    Voice* v = voice(sarg(c, 0));
    st<u32>(sarg(c, 1), v->playing ? DSBSTATUS_PLAYING | (v->looping ? DSBSTATUS_LOOPING : 0) : 0);
    return DS_OK;
}
HLE_REGISTER(IDirectSoundBuffer_GetStatus)
HLE(IDirectSoundBuffer_Lock) {
    std::lock_guard<std::mutex> lock(g_mx);
    Voice* v = voice(sarg(c, 0));
    u32 offset = sarg(c, 1), bytes = sarg(c, 2), flags = sarg(c, 7);
    if (flags & 2) offset = 0, bytes = v->bytes;                // DSBLOCK_ENTIREBUFFER
    if (flags & 1) offset = v->fmt.bytes(u32(v->pos));          // DSBLOCK_FROMWRITECURSOR
    if (!v->bytes) return DSERR_INVALIDCALL_;
    offset %= v->bytes;
    u32 first = std::min(bytes, v->bytes - offset);
    st<u32>(sarg(c, 3), v->data + offset), st<u32>(sarg(c, 4), first);
    if (sarg(c, 5)) st<u32>(sarg(c, 5), first < bytes ? v->data : 0);
    if (sarg(c, 6)) st<u32>(sarg(c, 6), bytes - first);
    return DS_OK;
}
HLE_REGISTER(IDirectSoundBuffer_Lock)
HLE(IDirectSoundBuffer_Unlock) { return DS_OK; }
HLE_REGISTER(IDirectSoundBuffer_Unlock)
HLE(IDirectSoundBuffer_SetFrequency) {
    WITH_VOICE(v->pitch = pitch_for(sarg(c, 1) ? sarg(c, 1) : v->fmt.rate))
}
HLE_REGISTER(IDirectSoundBuffer_SetFrequency)
HLE(IDirectSoundBuffer_SetPitch) { WITH_VOICE(v->pitch = s32(sarg(c, 1))) }
HLE_REGISTER(IDirectSoundBuffer_SetPitch)
HLE(IDirectSoundBuffer_SetVolume) { WITH_VOICE(v->volume = s32(sarg(c, 1))) }
HLE_REGISTER(IDirectSoundBuffer_SetVolume)
HLE(IDirectSoundBuffer_SetHeadroom) { WITH_VOICE(v->headroom = s32(sarg(c, 1))) }
HLE_REGISTER(IDirectSoundBuffer_SetHeadroom)
HLE(IDirectSoundBuffer_SetMixBins) { WITH_VOICE(v->mixbins = read_mixbins(sarg(c, 1))) }
HLE_REGISTER(IDirectSoundBuffer_SetMixBins)

// DS3DVOICEDATA: dwFlags, then the fields each flag bit covers (as CDirectSoundVoice_Set3DVoiceData, 0x204196)
static void set_3d(Voice* v, u32 data) {
    static const struct { u32 bit, first, count; } fields[] = {
        {0x01, 1, 1}, {0x02, 2, 1}, {0x04, 3, 2}, {0x08, 5, 2}, {0x10, 7, 2}, {0x20, 9, 1}, {0x40, 10, 2}, {0x80, 12, 2}};
    u32 flags = ld<u32>(data);
    if (flags & 0x40) v->hrtf = true;
    for (auto& f : fields)
        if (flags & f.bit)
            for (u32 k = 0; k < f.count; ++k) v->d3[f.first + k] = ld<s32>(data + 4 * (f.first + k));
    static const bool stats = std::getenv("OOGIE_AUDIO_STATS") != nullptr;
    static int shown;
    if (stats && flags && shown < 40) {
        ++shown;
        std::fprintf(stderr, "[dsound] 3D data for %08X (use %d) at %08X:", v->guest, v->use3d, data);
        for (int k = 0; k < 16; ++k) std::fprintf(stderr, " %08X", ld<u32>(data + 4 * k));
        std::fprintf(stderr, " | %u channels, bins", v->fmt.channels);
        for (auto& [bin, vol] : v->mixbins) std::fprintf(stderr, " %u:%d", bin, vol);
        std::fprintf(stderr, "\n");
    }
}

// DSFILTERDESC { dwMode, dwQCoefficient, adwCoefficients[4] }: the voice filter in the APU's own format.
// shortcut: this game only sets mode 2 (parametric EQ, coefficients F2D4/566E per channel), whose coefficient
// format is undocumented (xemu leaves it unimplemented too); the voice plays unfiltered. Mode 1 (DLS2 low-pass,
// fc = 2^(c/4096), q = c/0x8000 per xemu) would be the one to add if another game uses it.
static void set_filter(Voice*, u32 desc) {
    if (desc && ld<u32>(desc) != 0) once("voice filters (parametric EQ)");
}

static void set_bin_volumes(Voice* v, u32 p) {
    for (auto& [bin, vol] : read_mixbins(p)) {
        bool found = false;
        for (auto& b : v->mixbins)
            if (b.first == bin) b.second = vol, found = true;
        if (!found) v->mixbins.push_back({bin, vol});
    }
}
HLE(IDirectSoundBuffer_SetMixBinVolumes_8) { WITH_VOICE(set_bin_volumes(v, sarg(c, 1))) }
HLE_REGISTER(IDirectSoundBuffer_SetMixBinVolumes_8)

static void voice_props(Voice* v, u32 out) {  // DSVOICEPROPS { count, pairs[8], lPitch, 5 more } = 0x5C bytes
    std::memset(g_mem + out, 0, 0x5C);
    for (u32 k = 0; k < 8; ++k) st<u32>(out + 4 + 8 * k, 0xFFFFFFFF), st<s32>(out + 8 + 8 * k, -10000);
    st<u32>(out, u32(v->mixbins.size()));
    for (size_t k = 0; k < v->mixbins.size() && k < 8; ++k)
        st<u32>(out + 4 + 8 * u32(k), v->mixbins[k].first), st<s32>(out + 8 + 8 * u32(k), v->mixbins[k].second);
    st<s32>(out + 68, v->pitch);
}
HLE(IDirectSoundBuffer_GetVoiceProperties) { WITH_VOICE(voice_props(v, sarg(c, 1))) }
HLE_REGISTER(IDirectSoundBuffer_GetVoiceProperties)
HLE(IDirectSoundBuffer_SetOutputBuffer) { return DS_OK; }  // submix routing: the voice goes to the speakers
HLE_REGISTER(IDirectSoundBuffer_SetOutputBuffer)
HLE(IDirectSoundBuffer_SetEG) { return once("envelopes"), DS_OK; }
HLE_REGISTER(IDirectSoundBuffer_SetEG)
HLE(IDirectSoundBuffer_SetLFO) { return once("LFOs"), DS_OK; }
HLE_REGISTER(IDirectSoundBuffer_SetLFO)
HLE(IDirectSoundBuffer_SetFilter) { WITH_VOICE(set_filter(v, sarg(c, 1))) }
HLE_REGISTER(IDirectSoundBuffer_SetFilter)
HLE(IDirectSoundBuffer_Set3DVoiceData) { WITH_VOICE(set_3d(v, sarg(c, 1))) }
HLE_REGISTER(IDirectSoundBuffer_Set3DVoiceData)
HLE(IDirectSoundBuffer_Use3DVoiceData) { WITH_VOICE(v->use3d = sarg(c, 1) != 0) }
HLE_REGISTER(IDirectSoundBuffer_Use3DVoiceData)

// ---- IDirectSoundStream (named wrappers; Process and friends come through the vtable) ----
HLE(IDirectSoundStream_SetFormat) { WITH_VOICE((v->fmt = read_format(sarg(c, 1)), v->pitch = pitch_for(v->fmt.rate))) }
HLE_REGISTER(IDirectSoundStream_SetFormat)
HLE(IDirectSoundStream_Pause) { WITH_VOICE(v->paused = sarg(c, 1) == 1) }  // DSSTREAMPAUSE_PAUSE
HLE_REGISTER(IDirectSoundStream_Pause)
HLE(IDirectSoundStream_FlushEx) { return flush_stream(sarg(c, 0), false); }  // asynchronous on the Xbox too
HLE_REGISTER(IDirectSoundStream_FlushEx)
HLE(IDirectSoundStream_SetPitch) { WITH_VOICE(v->pitch = s32(sarg(c, 1))) }
HLE_REGISTER(IDirectSoundStream_SetPitch)
HLE(IDirectSoundStream_SetVolume) { WITH_VOICE(v->volume = s32(sarg(c, 1))) }
HLE_REGISTER(IDirectSoundStream_SetVolume)
HLE(IDirectSoundStream_SetHeadroom) { WITH_VOICE(v->headroom = s32(sarg(c, 1))) }
HLE_REGISTER(IDirectSoundStream_SetHeadroom)
HLE(IDirectSoundStream_SetMixBins) { WITH_VOICE(v->mixbins = read_mixbins(sarg(c, 1))) }
HLE_REGISTER(IDirectSoundStream_SetMixBins)
HLE(IDirectSoundStream_SetMixBinVolumes_8) { WITH_VOICE(set_bin_volumes(v, sarg(c, 1))) }
HLE_REGISTER(IDirectSoundStream_SetMixBinVolumes_8)
HLE(IDirectSoundStream_GetVoiceProperties) { WITH_VOICE(voice_props(v, sarg(c, 1))) }
HLE_REGISTER(IDirectSoundStream_GetVoiceProperties)
HLE(IDirectSoundStream_SetOutputBuffer) { return DS_OK; }
HLE_REGISTER(IDirectSoundStream_SetOutputBuffer)
HLE(IDirectSoundStream_SetEG) { return once("envelopes"), DS_OK; }
HLE_REGISTER(IDirectSoundStream_SetEG)
HLE(IDirectSoundStream_SetLFO) { return once("LFOs"), DS_OK; }
HLE_REGISTER(IDirectSoundStream_SetLFO)
HLE(IDirectSoundStream_SetFilter) { WITH_VOICE(set_filter(v, sarg(c, 1))) }
HLE_REGISTER(IDirectSoundStream_SetFilter)
HLE(IDirectSoundStream_Set3DVoiceData) { WITH_VOICE(set_3d(v, sarg(c, 1))) }
HLE_REGISTER(IDirectSoundStream_Set3DVoiceData)
HLE(IDirectSoundStream_Use3DVoiceData) { WITH_VOICE(v->use3d = sarg(c, 1) != 0) }
HLE_REGISTER(IDirectSoundStream_Use3DVoiceData)

