#include <SDL2/SDL.h>
#include <SDL2/sdl_image.h>
#include <vector>
#include <memory>
#include <iostream>
#include "entity.hpp"
#include "player.hpp"
#include "gameData/const.hpp"

std::vector<std::unique_ptr<Entity>> allEntities;

Entity::Entity() {}

void Entity::initEntity(const char *p_path, int p_x, int p_y, SDL_Renderer *o_renderer)
{
    g_x = p_x;
    g_y = p_y;
    p_renderer = o_renderer;
    g_texture = IMG_LoadTexture(o_renderer, p_path);
    allEntities.push_back(std::make_unique<Entity>(*this));
}
void Entity::update()
{
    g_x = (g_x + g_velX);
    g_y = (g_y + g_velY);
    g_velX = g_velX *.6;
    g_velY = g_velY*.6;
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(g_texture, NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
    dst.x = g_x;
    dst.y = g_y;
    dst.w = int_DEFAULT_TEXTURE_SIZE;
    dst.h = int_DEFAULT_TEXTURE_SIZE;
    SDL_RenderCopy(p_renderer, g_texture, &src, &dst);

}
void Entity::setTexture(char *p_path)
{
    g_texture = IMG_LoadTexture(p_renderer, p_path);
}

Entity::~Entity()
{
}

Entity* createEntity(const char* p_type) {
    std::cout << p_type << std::endl;
    if (strcmp(p_type, "p") == 0) {
        return new Player;
    }
    else if (strcmp(p_type, "ge") == 0) {
        return new Entity;
    }
    return nullptr;
}