#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//String Prefixes (Used to avoid potentially overriding other libraries constants)
/*
    str_ : Generic string.  
    path_ : File path.  ALL PATHS START AT ROOT DIRECTORY
    int_ : Generic int.
*/

const int int_DEFAULT_TEXTURE_SIZE = 64;
const int int_DEFAULT_TEXTURE_OFFSET = 64;
const int int_DEFAULT_TEXTURE_MULTIPLIER = 64;
const char* str_WINDOW_NAME = "Referencetopia";