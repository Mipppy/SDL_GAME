#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <vector>
#include <cstring>
#include <SDL2/SDL.h>
#include <type_traits>
namespace utils
{
    struct hitboxBounds;
    extern void screenDemensions(int &p_screenWidth, int &p_screenHeight);
    extern bool collidingWithPlayer(SDL_Rect p_hitbox, double angle = 0);
    extern double getPlayerAngleFromPoint(int p_x, int p_y);
    extern double getPlayerAngleFromPoint(SDL_Rect p_rect);
    extern hitboxBounds getHitboxPositionData(SDL_Rect);
};

#endif