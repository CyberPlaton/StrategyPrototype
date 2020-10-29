#pragma once

#include<omp.h>
#include<sstream>
#include<memory>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<thread>
#include<random>
#include<stdexcept>
#include<stdarg.h> // for custom printf function.
#include<array>
#include<random>

#include<fstream>


#define SPRITES_WIDTH_AND_HEIGHT 128

#define COMPARE_STRINGS(x, y) strcmp(x.c_str(), y) // Utility.
#define COMPARE_STRINGS_2(x, y) strcmp(x.c_str(), y.c_str()) // Utility.