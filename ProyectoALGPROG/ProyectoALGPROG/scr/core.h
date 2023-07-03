#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <algorithm>

#include "fileCtrl.h"
#include "graphics.h"

void main_menu();
void game(int n, int m, std::string data);
void skip_level(char(&map)[30][30], int n, int m, std::string data);
bool retry_level(char map[30][30], std::string data, enum STA res);
bool next_level(char(&map)[30][30], int n, int m, std::string data);
enum STA move_player(char(&map)[30][30], enum DIR dir, int ppos[2], int n, int m);
void change_dif(int& n, int& m);