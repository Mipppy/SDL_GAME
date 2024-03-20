#include <SDL2/SDL.h>
#include <SDL2/sdl_image.h>
#include <vector>
#include <memory>
#include <iostream>
#include "entity.hpp"
#include "player.hpp"
#include "globals.hpp"
#include "npc.hpp"
#include "gameData/const.hpp"

std::vector<Entity *> allEntities;
Entity::Entity() {}

void Entity::initEntity(const char *p_path, int p_x, int p_y, SDL_Renderer *o_renderer)
{
    g_x = p_x;
    g_y = p_y;
    p_renderer = o_renderer;
    g_texture = IMG_LoadTexture(o_renderer, p_path);
    // MUST BE IN **EVERY** CONSTRUCTOR!
    // allEntities.push_back(std::make_unique<Entity>(*this));
}
void Entity::update()
{
    g_x = (g_x + g_velX);
    g_y = (g_y + g_velY);
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(g_texture, NULL, NULL, &src.w, &src.h);
    SDL_Rect dst;
    if (typeid(*this).hash_code() == typeid(Player).hash_code())
    {
        dst.x = globals::GLOBAL_userScreenWidth / 2 - 32;
        dst.y = globals::GLOBAL_userScreenHeight / 2 - 32;
    }
    else
    {
        dst.x = g_x - lonePlayerInstance->g_x;
        dst.y = g_y - lonePlayerInstance->g_y;
    }
    dst.w = int_DEFAULT_TEXTURE_SIZE;
    dst.h = int_DEFAULT_TEXTURE_SIZE;
    g_hitbox = dst;
    SDL_RenderCopy(p_renderer, g_texture, &src, &dst);
    if (g_velY < 0)
    {
        currentYDirection = 0;
    }
    else
    {
        currentYDirection = 1;
    }
    if (g_velX < 0)
    {
        currentXDirection = 0;
    }
    else
    {
        currentXDirection = 1;
    }
}
void Entity::setTexture(char *p_path)
{
    g_texture = IMG_LoadTexture(p_renderer, p_path);
}

Entity *createEntity(const char *p_type)
{
    if (strcmp(p_type, "p") == 0)
    {
        return new Player;
    }
    else if (strcmp(p_type, "npc") == 0)
    {
        std::vector<const char *> dialogue;
        dialogue.push_back("test dialogue #1 !");
        dialogue.push_back("test dialogue #2 !");
        dialogue.push_back("test dialogue #3 !");
        dialogue.push_back("test dialogue #4 ! wow the word wrapping algorithm actually works, that took longer than expected!");
        dialogue.push_back("test dialogue #5 ! lots of random words because 4 rows seems to be just a little, tiny, miniscule bit broken at the moment ");
        dialogue.push_back("test dialogue #6 ! and a bunch more of useless trash! ooh!  what's that, more trash! wow! even more useless text for testing!  I hate this!  and it goes on and on and on, forever, this has no bonds or limits");
        return new NPC(dialogue, 100, false);
    }
    return nullptr;
}

void Entity::tickUpdate()
{
}