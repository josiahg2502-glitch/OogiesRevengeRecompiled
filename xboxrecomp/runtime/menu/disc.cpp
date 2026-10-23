// Disc setup (see disc.h), as the old WinForms launcher did it (launcher/XboxDisc.cs). The image is untrusted input:
// names are checked before any file is written and every read against the image's size.
#include "disc.h"

#include <windows.h>
#include <bcrypt.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <set>
#include <stdexcept>
#include <vector>

namespace fs = std::filesystem;

namespace {

// The executable this port was recompiled from: Oogie's Revenge, USA (title 42560004, version 1). Only its exact bytes run.
const char* const kWantedXbe = "9a8319c7b1cb5ee29781bf641a0cf549c221fdc57effb8f72085608019f41548";
const char* const kWrongGame = "This is not The Nightmare Before Christmas: Oogie's Revenge for the Xbox (USA). Only that version "
                               "runs, because the port was built from its exact game code.";
const char* const kCutShort = "The image is cut short (a damaged or incomplete dump).";
constexpr long long kSector = 2048;

struct Problem : std::runtime_error {  // a sentence for the player
    using std::runtime_error::runtime_error;
};

std::string sha256(const std::vector<uint8_t>& data) {
    uint8_t h[32];
    BCRYPT_ALG_HANDLE alg = nullptr;
    BCRYPT_HASH_HANDLE hash = nullptr;
    bool ok = BCryptOpenAlgorithmProvider(&alg, BCRYPT_SHA256_ALGORITHM, nullptr, 0) == 0 &&
              BCryptCreateHash(alg, &hash, nullptr, 0, nullptr, 0, 0) == 0 &&
              BCryptHashData(hash, const_cast<uint8_t*>(data.data()), ULONG(data.size()), 0) == 0 && BCryptFinishHash(hash, h, 32, 0) == 0;
    if (hash) BCryptDestroyHash(hash);
    if (alg) BCryptCloseAlgorithmProvider(alg, 0);
    if (!ok) throw Problem("The game executable could not be checked.");
    char hex[65];
    for (int i = 0; i < 32; ++i) std::snprintf(hex + 2 * i, 3, "%02x", h[i]);
    return hex;
}

struct Image {
    FILE* f = nullptr;
    long long size = 0, partition = 0;
    struct Entry {
        fs::path path;
        long long offset, length;
    };
    std::vector<Entry> files;
    std::set<std::pair<uint32_t, uint32_t>> seen;

    explicit Image(const std::wstring& path) {
        f = _wfopen(path.c_str(), L"rb");
        if (!f) throw Problem("The disc image could not be opened.");
        _fseeki64(f, 0, SEEK_END);
        size = _ftelli64(f);
        for (long long p : {0x18300000LL, 0xFD90000LL, 0x2080000LL, 0LL}) {  // XGD1, XGD2, XGD3, xiso
            if (p + 33 * kSector > size) continue;
            std::vector<uint8_t> m = read(p + 32 * kSector, 20);
            if (std::memcmp(m.data(), "MICROSOFT*XBOX*MEDIA", 20) != 0) continue;
            partition = p;
            std::vector<uint8_t> head = read(p + 32 * kSector + 20, 8);
            uint32_t root, root_size;
            std::memcpy(&root, &head[0], 4), std::memcpy(&root_size, &head[4], 4);
            walk(root, root_size, {}, 0);
            return;
        }
        throw Problem("This is not an Xbox disc image (no Xbox file system found).");
    }
    ~Image() { std::fclose(f); }

    std::vector<uint8_t> read(long long at, long long count) {
        if (at < 0 || count < 0 || at + count > size) throw Problem(kCutShort);
        std::vector<uint8_t> b(static_cast<size_t>(count));
        _fseeki64(f, at, SEEK_SET);
        if (count && std::fread(b.data(), 1, b.size(), f) != b.size()) throw Problem(kCutShort);
        return b;
    }

    // A directory is a binary tree of entries: left/right subtree offsets (in dwords), sector, size, attributes, name.
    void walk(uint32_t sector, uint32_t bytes, const fs::path& prefix, int depth) {
        if (depth > 32 || bytes == 0 || bytes > (64u << 20) || !seen.insert({sector, bytes}).second) return;
        std::vector<uint8_t> t = read(partition + sector * kSector, bytes);
        std::vector<size_t> stack = {0};
        for (int guard = 0; !stack.empty() && guard < 100000; ++guard) {
            size_t off = stack.back();
            stack.pop_back();
            if (off + 14 > t.size() || (t[off] == 0xFF && t[off + 1] == 0xFF)) continue;
            uint16_t left, right;
            uint32_t start, length;
            std::memcpy(&left, &t[off], 2), std::memcpy(&right, &t[off + 2], 2);
            std::memcpy(&start, &t[off + 4], 4), std::memcpy(&length, &t[off + 8], 4);
            uint8_t attr = t[off + 12], len = t[off + 13];
            if (off + 14 + len > t.size()) continue;
            std::string name(reinterpret_cast<const char*>(&t[off + 14]), len);
            bool safe = !name.empty() && name != "." && name != "..";
            for (unsigned char ch : name) safe &= ch >= 32 && ch < 127 && !std::strchr("<>:\"/\\|?*", ch);
            if (!safe) throw Problem("The image holds an unsafe file name.");
            if (left) stack.push_back(left * 4u);
            if (right) stack.push_back(right * 4u);
            fs::path path = prefix / name;
            if (attr & 0x10) walk(start, length, path, depth + 1);
            else files.push_back({path, partition + start * kSector, length});
        }
    }
};

void check_xbe(const std::vector<uint8_t>& xbe) {
    if (sha256(xbe) != kWantedXbe) throw Problem(kWrongGame);
}

}  // namespace

bool disc_ready() { return GetFileAttributesA("Disc\\files\\default.xbe") != INVALID_FILE_ATTRIBUTES; }

std::string disc_setup(const std::wstring& chosen, std::atomic<int>& done, std::atomic<int>& total) {
    const fs::path staging = "Disc\\files.new", target = "Disc\\files";
    std::error_code ec;
    try {
        fs::remove_all(staging, ec);
        fs::create_directories(staging);
        fs::path from = chosen;
        if (_wcsicmp(from.filename().c_str(), L"default.xbe") == 0) {  // a folder extracted by another tool
            std::vector<fs::path> files;
            for (auto& e : fs::recursive_directory_iterator(from.parent_path()))
                if (e.is_regular_file()) files.push_back(e.path());
            total = int(files.size());
            FILE* x = _wfopen(chosen.c_str(), L"rb");
            if (!x) throw Problem("The game executable could not be opened.");
            std::vector<uint8_t> xbe(size_t(fs::file_size(from)));
            size_t got = std::fread(xbe.data(), 1, xbe.size(), x);
            std::fclose(x);
            if (got != xbe.size()) throw Problem("The game executable could not be read.");
            check_xbe(xbe);
            for (auto& p : files) {
                fs::path to = staging / fs::relative(p, from.parent_path());
                fs::create_directories(to.parent_path());
                fs::copy_file(p, to, fs::copy_options::overwrite_existing);
                ++done;
            }
        } else {
            Image img(chosen);
            total = int(img.files.size());
            const Image::Entry* xbe = nullptr;
            for (auto& e : img.files)
                if (_wcsicmp(e.path.c_str(), L"default.xbe") == 0) xbe = &e;
            if (!xbe) throw Problem("This Xbox disc has no game executable (default.xbe).");
            if (xbe->length > (64 << 20)) throw Problem(kWrongGame);
            check_xbe(img.read(xbe->offset, xbe->length));
            std::vector<uint8_t> buf(4 << 20);
            for (auto& e : img.files) {
                if (e.offset + e.length > img.size) throw Problem(kCutShort);
                fs::path to = staging / e.path;
                fs::create_directories(to.parent_path());
                FILE* o = _wfopen(to.c_str(), L"wb");
                if (!o) throw Problem("The game files could not be written (is the folder read-only or the disk full?).");
                _fseeki64(img.f, e.offset, SEEK_SET);
                for (long long left = e.length; left > 0;) {
                    size_t n = std::fread(buf.data(), 1, size_t(std::min<long long>(left, buf.size())), img.f);
                    if (!n || std::fwrite(buf.data(), 1, n, o) != n) {
                        std::fclose(o);
                        throw Problem(n ? "The game files could not be written (is the disk full?)." : kCutShort);
                    }
                    left -= (long long)n;
                }
                std::fclose(o);
                ++done;
            }
        }
        fs::remove_all(target, ec);
        fs::rename(staging, target);
        return "";
    } catch (const Problem& p) {
        fs::remove_all(staging, ec);
        return p.what();
    } catch (const std::exception& e) {
        fs::remove_all(staging, ec);
        return std::string("The game files could not be copied: ") + e.what();
    }
}
