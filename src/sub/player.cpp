#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.hpp"
#include "gameData/const.hpp"
#include "entity.hpp"
#include "npc.hpp"
#include "globals.hpp"
#include <cstring>
#include <iostream>
#include <vector>

Player *lonePlayerInstance = nullptr;

Player::Player()
{
    lonePlayerInstance = this;
    allEntities.push_back(this);
}
Player::~Player() {}

void Player::updateDirection()
{
    const char* oldDirection = fileDirectionExtension;
    if (currentXDirection == 1 && currentYDirection == -1)
    {
        fileDirectionExtension = "right.png";
    }
    else if (currentXDirection == -1 && currentYDirection == 0)
    {
        fileDirectionExtension = "up.png";
    }
    else if (currentXDirection == 0 && currentYDirection == -1)
    {
        fileDirectionExtension = "left.png";
    }
    else if (currentXDirection == -1 && currentYDirection == 1)
    {
        fileDirectionExtension = "down.png";
    }
    if (strcmp(fileDirectionExtension, oldDirection) != 0) {
        spriteSheetInstance = 0;
        char newPath[150];
        strncpy(newPath, g_path, sizeof(newPath) - 1);
        newPath[sizeof(newPath) - 1] = '\0';
        strncat(newPath, fileDirectionExtension, sizeof(newPath) - strlen(newPath) - 1);
        setTexture(newPath);
    }
}

void Player::tickUpdate()
{
    if (wPress)
    {
        g_velY = g_velY - speed;
        globals::random += 5;
    }
    if (lonePlayerInstance->sPress)
    {
        g_velY = g_velY + speed;
        globals::random -= 5;
    }
    if (lonePlayerInstance->aPress)
    {
        g_velX = g_velX - speed;
        globals::random += 10;
    }
    if (lonePlayerInstance->dPress)
    {
        g_velX = g_velX + speed;
        globals::random -= 10;
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
    updateDirection();
}