// PC audio output: WASAPI shared mode, fed by a pull callback that mixes stereo float frames.
//
// The game's audio clock must keep running without a device: streams (movie sound, music) only complete as they
// are mixed, and a movie waits for its sound. So with no output device, or after one is unplugged, the mixer runs
// against a silent real-time clock and the default device is tried again every 2 seconds.
#include <audioclient.h>
#include <mmdeviceapi.h>
#include <windows.h>

#include <chrono>
#include <cstdio>
#include <thread>
#include <vector>

#include "audio_out.h"

namespace {

// GUIDs spelled out so no extra import library is needed
const CLSID kMMDeviceEnumerator = {0xBCDE0395, 0xE52F, 0x467C, {0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E}};
const IID kIMMDeviceEnumerator = {0xA95664D2, 0x9614, 0x4F35, {0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6}};
const IID kIAudioClient = {0x1CB9AD4C, 0xDBFA, 0x4C32, {0xB1, 0x78, 0xC2, 0xF5, 0x68, 0xA7, 0x03, 0xB2}};
const IID kIAudioRenderClient = {0xF294ACFC, 0x3146, 0x4483, {0xA7, 0xBF, 0xAD, 0xDC, 0xA7, 0xC2, 0x60, 0xE2}};
const GUID kFloatSubtype = {0x00000003, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}};

template <class T> void release(T*& p) {
    if (p) p->Release(), p = nullptr;
}

// Plays through the default output device until it fails or goes away. False: it could not be opened.
bool play_device(AudioMixFn mix, bool& told) {
    IMMDeviceEnumerator* en = nullptr;
    IMMDevice* dev = nullptr;
    IAudioClient* client = nullptr;
    IAudioRenderClient* render = nullptr;
    WAVEFORMATEX* fmt = nullptr;
    HANDLE ready = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    auto done = [&](const char* what, HRESULT hr) {
        if (what && !told) {
            told = true;
            std::fprintf(stderr, "[audio] %s failed (%08lX); running silently, trying again every 2 s\n", what, (unsigned long)hr);
        }
        if (client) client->Stop();
        release(render), release(client), release(dev), release(en);
        if (fmt) CoTaskMemFree(fmt);
        CloseHandle(ready);
        return !what;
    };
    HRESULT hr;
    if (FAILED(hr = CoCreateInstance(kMMDeviceEnumerator, nullptr, CLSCTX_ALL, kIMMDeviceEnumerator,
                                     reinterpret_cast<void**>(&en))))
        return done("device enumerator", hr);
    if (FAILED(hr = en->GetDefaultAudioEndpoint(eRender, eConsole, &dev))) return done("default output device", hr);
    if (FAILED(hr = dev->Activate(kIAudioClient, CLSCTX_ALL, nullptr, reinterpret_cast<void**>(&client))))
        return done("audio client", hr);
    if (FAILED(hr = client->GetMixFormat(&fmt))) return done("mix format", hr);
    bool is_float = fmt->wFormatTag == WAVE_FORMAT_IEEE_FLOAT ||
                    (fmt->wFormatTag == WAVE_FORMAT_EXTENSIBLE &&
                     reinterpret_cast<WAVEFORMATEXTENSIBLE*>(fmt)->SubFormat == kFloatSubtype);
    if (!is_float || fmt->wBitsPerSample != 32) return done("float mix format", E_FAIL);
    // 20 ms buffer, refilled on the device's event
    if (FAILED(hr = client->Initialize(AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_EVENTCALLBACK, 200000, 0, fmt,
                                       nullptr)))
        return done("initialize", hr);
    client->SetEventHandle(ready);
    if (FAILED(hr = client->GetService(kIAudioRenderClient, reinterpret_cast<void**>(&render))))
        return done("render client", hr);
    UINT32 size;
    client->GetBufferSize(&size);
    const unsigned channels = fmt->nChannels, rate = fmt->nSamplesPerSec;
    std::fprintf(stderr, "[audio] WASAPI %u Hz, %u channels, %u-frame buffer\n", rate, channels, size);
    told = false;
    std::vector<float> stereo(size * 2);
    client->Start();
    for (;;) {
        WaitForSingleObject(ready, 100);
        UINT32 padding;
        if (FAILED(hr = client->GetCurrentPadding(&padding))) break;  // unplugged or disabled: AUDCLNT_E_DEVICE_INVALIDATED
        UINT32 frames = size - padding;
        if (!frames) continue;
        BYTE* out;
        if (FAILED(hr = render->GetBuffer(frames, &out))) break;
        mix(stereo.data(), frames, rate);
        float* dst = reinterpret_cast<float*>(out);
        for (UINT32 f = 0; f < frames; ++f)
            for (unsigned ch = 0; ch < channels; ++ch)
                dst[f * channels + ch] = ch < 2 ? stereo[f * 2 + ch] : 0.f;  // stereo into front left/right
        render->ReleaseBuffer(frames, 0);
    }
    std::fprintf(stderr, "[audio] output device lost (%08lX); running silently\n", (unsigned long)hr);
    told = true;
    return done(nullptr, hr);
}

// Mixes into nothing at real-time speed for `ms` milliseconds, so the game's sound keeps time.
void run_silent(AudioMixFn mix, int ms) {
    constexpr unsigned rate = 48000;
    std::vector<float> stereo(rate / 50 * 2);  // up to 20 ms per step
    auto start = std::chrono::steady_clock::now(), last = start;
    double owed = 0;
    while (std::chrono::steady_clock::now() - start < std::chrono::milliseconds(ms)) {
        Sleep(10);
        auto now = std::chrono::steady_clock::now();
        owed += std::chrono::duration<double>(now - last).count() * rate;
        last = now;
        unsigned frames = unsigned(owed);
        if (frames > rate / 50) frames = rate / 50;  // a stall (the PC sleeping) is not made up for
        owed = owed > frames + rate / 50.0 ? 0 : owed - frames;
        if (frames) mix(stereo.data(), frames, rate);
    }
}

void run(AudioMixFn mix) {
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
    bool told = false;
    for (;;) {
        play_device(mix, told);  // returns when there is no device or it went away
        run_silent(mix, 2000);
    }
}

}  // namespace

void audio_start(AudioMixFn mix) { std::thread(run, mix).detach(); }
