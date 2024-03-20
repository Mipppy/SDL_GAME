#include "utils.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void utils::screenDemensions(int &p_screenWidth, int &p_screenHeight)
{
    SDL_DisplayMode dm;

    SDL_GetDesktopDisplayMode(0, &dm);

    p_screenWidth = dm.w;
    p_screenHeight = dm.h;
}