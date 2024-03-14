#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.hpp"
#include "gameData/const.hpp"
#include "entity.hpp"
#include <iostream>
#include <vector>

Player *lonePlayerInstance = nullptr;

Player::Player()
{
    lonePlayerInstance = this;
    allEntities.push_back(this);
}
Player::~Player() {}

void Player::tickUpdate()
{
    if (lonePlayerInstance->wPress)
    {
        g_velY = g_velY - lonePlayerInstance->speed;
    }
    if (lonePlayerInstance->sPress)
    {
        g_velY = g_velY + lonePlayerInstance->speed;
    }
    if (lonePlayerInstance->aPress)
    {
        g_velX = g_velX - lonePlayerInstance->speed;
    }
    if (lonePlayerInstance->dPress)
    {
        g_velX = g_velX + lonePlayerInstance->speed;
    }
    // Nerf Diaganol Movement, as it's faster than walking
    if ((lonePlayerInstance->aPress || lonePlayerInstance->dPress) && (lonePlayerInstance->wPress || lonePlayerInstance->sPress))
    {
        if (g_velX >= lonePlayerInstance->speedCap - int_DIAGONAL_MOVEMENT_PENATLY)
            g_velX = lonePlayerInstance->speedCap - int_DIAGONAL_MOVEMENT_PENATLY;
        if (g_velX <= -lonePlayerInstance->speedCap + int_DIAGONAL_MOVEMENT_PENATLY)
            g_velX = -lonePlayerInstance->speedCap + int_DIAGONAL_MOVEMENT_PENATLY;
        if (g_velY >= lonePlayerInstance->speedCap - int_DIAGONAL_MOVEMENT_PENATLY)
            g_velY = lonePlayerInstance->speedCap - int_DIAGONAL_MOVEMENT_PENATLY;
        if (g_velY <= -lonePlayerInstance->speedCap + int_DIAGONAL_MOVEMENT_PENATLY)
            g_velY = -lonePlayerInstance->speedCap + int_DIAGONAL_MOVEMENT_PENATLY;
    }
    if (g_velX >= lonePlayerInstance->speedCap)
    {
        g_velX = lonePlayerInstance->speedCap;
    }
    if (g_velX <= -lonePlayerInstance->speedCap)
    {
        g_velX = -lonePlayerInstance->speedCap;
    }
    if (g_velY >= lonePlayerInstance->speedCap)
    {
        g_velY = lonePlayerInstance->speedCap;
    }
    if (g_velY <= -lonePlayerInstance->speedCap)
    {
        g_velY = -lonePlayerInstance->speedCap;
    }
    if (!lonePlayerInstance->wPress && !lonePlayerInstance->sPress)
    {
        g_velY = g_velY * lonePlayerInstance->traction;
    }
    if (!lonePlayerInstance->aPress && !lonePlayerInstance->dPress)
    {
        g_velX = g_velX * lonePlayerInstance->traction;
    }
}