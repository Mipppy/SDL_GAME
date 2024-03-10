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
}
Player::~Player() {}


void Player::Entity::tickUpdate()
{
    if (lonePlayerInstance->wPress == true)
    {
        g_velY = g_velY - lonePlayerInstance->speed;
    }
    if (lonePlayerInstance->sPress == true)
    {
        g_velY = g_velY + lonePlayerInstance->speed;
    }
    if (lonePlayerInstance->aPress == true)
    {
        g_velX = g_velX - lonePlayerInstance->speed;
    }
    if (lonePlayerInstance->dPress == true)
    {
        g_velX = g_velX + lonePlayerInstance->speed;
    }
    if (g_velX > lonePlayerInstance->speedCap) {
        g_velX = lonePlayerInstance->speedCap;
    }
    if (g_velX < -lonePlayerInstance->speedCap) {
        g_velX = -lonePlayerInstance->speedCap;
    }
    if (g_velY > lonePlayerInstance->speedCap) {
        g_velY = lonePlayerInstance->speedCap;
    }
    if (g_velY < -lonePlayerInstance->speedCap) {
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