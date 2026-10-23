// The game's own menu, shown in the game window before it starts (like the Mother 3 port's): Play, Settings,
// Controls, Mods, Quit, drawn with the game's art read from the player's disc and driven by pad or keyboard.
#pragma once

// Returns when the player chooses Play; Quit ends the process. A display setting changed here restarts the program
// (the window and device are made with those settings), and the restarted one skips the menu (--play).
// Without the game's files (the first start) or with `setup` (--setup), it first asks for the player's disc.
void menu_run(bool setup = false);
// The same menu during play (F1): over the frame just shown, with the game and its sound held. Resume (or F1, Esc,
// the pad's B) goes back. Settings apply at once, except resolution, picture shape and frame rate (next start).
void menu_overlay();
