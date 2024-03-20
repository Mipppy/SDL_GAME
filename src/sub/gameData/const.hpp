#ifndef CONST_HPP
#define CONST_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
// String Prefixes (Used to avoid potentially overriding other libraries constants)
/*
    str_ : Generic string.
    path_ : File path.  ALL PATHS START AT ROOT DIRECTORY
    int_ : Generic int.
*/

inline const int int_DEFAULT_TEXTURE_SIZE = 64;
inline const int int_DEFAULT_TEXTURE_OFFSET = 64;
inline const int int_DEFAULT_TEXTURE_MULTIPLIER = 64;
inline const char *str_WINDOW_NAME = "undefined";
inline const int int_DIAGONAL_MOVEMENT_PENATLY = 1;
inline const SDL_Color color_White = {0,0,0};
inline const SDL_Color color_Black = {255,255,255};
inline const SDL_Color color_darkGrey = {179,179,179};
inline const SDL_Color color_lightGrey = {100,100,100};
inline const SDL_Color color_Grey = {129,129,129};
#endif