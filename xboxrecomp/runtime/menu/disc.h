// Setting the game up from the player's own disc: an Xbox disc image (Redump .iso of XGD1/2/3, or an xiso) or the
// default.xbe of a folder extracted from one. Its files are copied into Disc\files once; only the USA game runs.
#pragma once
#include <atomic>
#include <string>

bool disc_ready();  // Disc\files\default.xbe is there
// Copies the chosen image's (or folder's) files into Disc\files, counting them in done/total as it goes.
// Returns "" when done, else a sentence for the player (Disc\files is then left as it was).
std::string disc_setup(const std::wstring& chosen, std::atomic<int>& done, std::atomic<int>& total);
