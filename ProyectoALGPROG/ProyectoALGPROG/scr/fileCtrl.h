#pragma once

#include <fstream>
#include <iostream>
#include <string>

void gen_map(int n, int m, std::string dir);
void read_data(char map[30][30], std::string dir, int(&ppos)[2]);
int getint(std::string str, bool sec = false);