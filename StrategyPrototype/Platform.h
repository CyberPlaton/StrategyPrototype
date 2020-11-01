#pragma once

#include<omp.h>
#include<sstream>
#include<memory>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<thread>
#include<Random>
#include<stdexcept>
#include<stdarg.h> // for custom printf function.
#include<array>
#include<random>
#include<cstdlib>

#include<fstream>


#define TURN_TIME_MODIFIER 4
#define SPRITES_WIDTH_AND_HEIGHT 64
#define MAP_SIZE 20 // Defines the size of the map. Would be convenient to set it dynamically.

#define VISIBLE_MAP_WIDTH 13
#define VISIBLE_MAP_HEIGHT 10


#define COMPARE_STRINGS(x, y) strcmp(x.c_str(), y) // Utility.
#define COMPARE_STRINGS_2(x, y) strcmp(x.c_str(), y.c_str()) // Utility.

int StringToInt(std::string s);
int Random();