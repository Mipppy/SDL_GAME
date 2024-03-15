#include <SDL2/SDL.h>
#include <SDL2/sdl_image.h>
#include <vector>
#include <memory>
#include <iostream>
#include "entity.hpp"
#include "player.hpp"
#include "npc.hpp"
#include "gameData/const.hpp"

std::vector<Entity*> allEntities;
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
    dst.x = g_x;
    dst.y = g_y;
    dst.w = int_DEFAULT_TEXTURE_SIZE;
    dst.h = int_DEFAULT_TEXTURE_SIZE;
    g_hitbox = dst;
    SDL_RenderCopy(p_renderer, g_texture, &src, &dst);

    if (g_velY < 0) {
        currentYDirection = 0;
    }
    else {
        currentYDirection = 1;
    }
    if (g_velX < 0){
        currentXDirection = 0;
    }
    else {
        currentXDirection = 1;
    }
}
void Entity::setTexture(char *p_path)
{
    g_texture = IMG_LoadTexture(p_renderer, p_path);
}

Entity* createEntity(const char* p_type) {
    if (strcmp(p_type, "p") == 0) {
        return new Player;
    }
    else if (strcmp(p_type, "npc") == 0) {
        std::vector<const char *> dialogue;
        dialogue.push_back("test dialogue #1 !");
        dialogue.push_back("test dialogue #2 !");
        dialogue.push_back("test dialogue #3 !");
        dialogue.push_back("test dialogue #4 !");
        dialogue.push_back("test dialogue #5 !");
        dialogue.push_back("test dialogue #6 !");
        return new NPC(dialogue, 100, false);
    }
    return nullptr;
}

void Entity::tickUpdate() {
}