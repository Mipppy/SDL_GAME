#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <vector>
#include <cstring>
#include <SDL2/SDL.h>
namespace utils
{
    extern void screenDemensions(int &p_screenWidth, int &p_screenHeight);
    extern bool collidingWithPlayer(SDL_Rect p_hitbox, double angle = 0);
};

#endif