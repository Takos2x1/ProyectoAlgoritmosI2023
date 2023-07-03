#pragma once

#include <string>

void draw(std::string img_dir, int color);
void draw_map(char map[30][30], std::string dir, int ppos[2]);
void draw_menu(int sel, int n);
void play_intro(int n);