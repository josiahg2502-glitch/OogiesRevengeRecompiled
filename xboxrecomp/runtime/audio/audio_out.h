// PC audio output.
#pragma once
#include <cstdint>

// Fills `frames` interleaved stereo float frames at `rate` Hz. Runs on the audio thread.
typedef void (*AudioMixFn)(float* out, uint32_t frames, uint32_t rate);
void audio_start(AudioMixFn mix);
// The in-game menu: silence, with every voice held where it is (dsound.cpp).
void audio_pause(bool on);
