#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <vector>
#include <cstring>
namespace utils
{
    extern void screenDemensions(int &p_screenWidth, int &p_screenHeight);
    extern std::vector<const char*> split(const char* s, char delimiter);
};

#endif