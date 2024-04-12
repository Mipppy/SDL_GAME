#include "utils.hpp"
#include "player.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <cmath>
#include <cstring>
void utils::screenDemensions(int &p_screenWidth, int &p_screenHeight)
{
    SDL_DisplayMode dm;

    SDL_GetDesktopDisplayMode(0, &dm);

    p_screenWidth = 1820;
    p_screenHeight = 720;
}

bool utils::collidingWithPlayer(SDL_Rect p_hitbox, double angle)
{
    int centerX = p_hitbox.x + (p_hitbox.w / 2);
    int centerY = p_hitbox.y + (p_hitbox.h / 2);

    int halfWidth = p_hitbox.w / 2;
    int halfHeight = p_hitbox.h / 2;

    int rotatedLeft = centerX - halfWidth;
    int rotatedRight = centerX + halfWidth;
    int rotatedTop = centerY - halfHeight;
    int rotatedBottom = centerY + halfHeight;

    float angleRad = angle * (M_PI / 180);
    int tempLeft = rotatedLeft;
    rotatedLeft = centerX + (tempLeft - centerX) * std::cos(angleRad) - (rotatedTop - centerY) * std::sin(angleRad);
    int tempRight = rotatedRight;
    rotatedRight = centerX + (tempRight - centerX) * std::cos(angleRad) - (rotatedBottom - centerY) * std::sin(angleRad);
    int tempTop = rotatedTop;
    rotatedTop = centerY + (tempTop - centerY) * std::cos(angleRad) + (rotatedLeft - centerX) * std::sin(angleRad);
    int tempBottom = rotatedBottom;
    rotatedBottom = centerY + (tempBottom - centerY) * std::cos(angleRad) + (rotatedRight - centerX) * std::sin(angleRad);

    int leftA = lonePlayerInstance->g_hitbox.x;
    int rightA = lonePlayerInstance->g_hitbox.x + lonePlayerInstance->g_hitbox.w;
    int topA = lonePlayerInstance->g_hitbox.y;
    int bottomA = lonePlayerInstance->g_hitbox.y + lonePlayerInstance->g_hitbox.h;
    if (rotatedBottom <= topA || rotatedLeft >= rightA || rotatedTop >= bottomA || rotatedRight <= leftA)
    {
        return false;
    }
    else
    {
        return true;
    }
}

double utils::getPlayerAngleFromPoint(int p_x, int p_y)
{
    int playerXDistance = p_x - lonePlayerInstance->g_hitbox.x;
    int playerYDistance = p_y - lonePlayerInstance->g_hitbox.y;
    double rad = std::atan2(playerYDistance, playerXDistance);
    return rad * (180.0 / M_PI) + 90;
}
double utils::getPlayerAngleFromPoint(SDL_Rect p_rect)
{
    int playerXDistance = p_rect.x - lonePlayerInstance->g_hitbox.x;
    int playerYDistance = p_rect.y - lonePlayerInstance->g_hitbox.y;
    double rad = std::atan2(playerYDistance, playerXDistance);
    return rad * (180.0 / M_PI) + 90;
}

struct utils::hitboxBounds
{
public:
    hitboxBounds(SDL_Point tR, SDL_Point tL, SDL_Point bR, SDL_Point bL) : topRight(tR), topLeft(tL), bottomRight(bR), bottomLeft(bL) {};
    SDL_Point topRight;
    SDL_Point topLeft;
    SDL_Point bottomRight;
    SDL_Point bottomLeft;
};

utils::hitboxBounds utils::getHitboxPositionData(SDL_Rect p_rect)
{
    int leftA = p_rect.x;
    int rightA = p_rect.x + p_rect.w;
    int topA = p_rect.y;
    int bottomA = p_rect.y + p_rect.h;

    SDL_Point topLeft = {leftA, topA};
    SDL_Point topRight = {rightA, topA};
    SDL_Point bottomLeft = {leftA, bottomA};
    SDL_Point bottomRight = {rightA, bottomA};
    return utils::hitboxBounds(topRight, topLeft, bottomRight, bottomLeft);
}