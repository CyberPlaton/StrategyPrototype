#pragma once
// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


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
#include<ctime>

#include<fstream>


#define TURN_TIME_MODIFIER 1
#define SPRITES_WIDTH_AND_HEIGHT 64
#define MAP_SIZE 20 // Defines the size of the map. Would be convenient to set it dynamically.
#define TECH_TREE_COUNT 4 // civilian, military, magick and technical.
#define JOBLESS_CITIZENS_COUNT 15

#define VISIBLE_MAP_WIDTH 14
#define VISIBLE_MAP_HEIGHT 11

#define COMPARE_STRINGS(x, y) strcmp(x.c_str(), y) // Utility.
#define COMPARE_STRINGS_2(x, y) strcmp(x.c_str(), y.c_str()) // Utility.

int StringToInt(std::string s);
int Random();

template<typename T>
void pop_front(std::vector<T>& v)
{
    if (v.size() > 0) {
        v.erase(v.begin());
    }
}