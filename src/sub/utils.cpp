#include "utils.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <cstring>
void utils::screenDemensions(int &p_screenWidth, int &p_screenHeight)
{
    SDL_DisplayMode dm;

    SDL_GetDesktopDisplayMode(0, &dm);

    p_screenWidth = 1820;
    p_screenHeight = 720;
}
std::vector<const char*> splitString(const std::string& str, char delimiter) {
    std::vector<const char*> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start).c_str());
        start = end + 1;
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start).c_str());
    return tokens;
}