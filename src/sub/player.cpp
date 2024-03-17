#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.hpp"
#include "gameData/const.hpp"
#include "entity.hpp"
#include "npc.hpp"
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
    if (wPress)
    {
        g_velY = g_velY - speed;
    }
    if (lonePlayerInstance->sPress)
    {
        g_velY = g_velY + speed;
    }
    if (lonePlayerInstance->aPress)
    {
        g_velX = g_velX - speed;
    }
    if (lonePlayerInstance->dPress)
    {
        g_velX = g_velX + speed;
    }
    // Nerf Diaganol Movement, as it's faster than walking
    if ((aPress || dPress) && (wPress || sPress))
    {
        if (g_velX >= speedCap - int_DIAGONAL_MOVEMENT_PENATLY)
            g_velX = speedCap - int_DIAGONAL_MOVEMENT_PENATLY;
        if (g_velX <= -speedCap + int_DIAGONAL_MOVEMENT_PENATLY)
            g_velX = -speedCap + int_DIAGONAL_MOVEMENT_PENATLY;
        if (g_velY >= speedCap - int_DIAGONAL_MOVEMENT_PENATLY)
            g_velY = speedCap - int_DIAGONAL_MOVEMENT_PENATLY;
        if (g_velY <= -speedCap + int_DIAGONAL_MOVEMENT_PENATLY)
            g_velY = -speedCap + int_DIAGONAL_MOVEMENT_PENATLY;
    }
    if (g_velX >= speedCap)
    {
        g_velX = speedCap;
    }
    if (g_velX <= -speedCap)
    {
        g_velX = -speedCap;
    }
    if (g_velY >= speedCap)
    {
        g_velY = speedCap;
    }
    if (g_velY <= -speedCap)
    {
        g_velY = -speedCap;
    }
    if (!wPress && !sPress)
    {
        g_velY = g_velY * traction;
    }
    if (!aPress && !dPress)
    {
        g_velX = g_velX * traction;
    }
    if (currentInteractingNPC != nullptr)
    {
        if (!currentInteractingNPC->isCloseToPlayer())
        {
            currentInteractingNPC->finishInteracting();
        }
    }
}