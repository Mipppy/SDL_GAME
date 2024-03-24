#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// all global variables will reside here, such as vectors of all entities an etc, to avoid having to import that entire header just to use one variable
namespace globals
{
    extern int GLOBAL_userScreenWidth;
    extern int GLOBAL_userScreenHeight;
};
#endif