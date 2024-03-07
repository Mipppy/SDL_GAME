#include <SDL2/SDL.h>
#include <SDL2/sdl_image.h>
#include "entity.hpp"
#include "gameData/const.hpp"

Entity::Entity() {}

void Entity::initEntity(char* p_path, int p_x, int p_y, SDL_Renderer* o_renderer ) {
    p_renderer = o_renderer;
    g_texture = IMG_LoadTexture(o_renderer, p_path);
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
    SDL_RenderCopy(p_renderer, g_texture, &src, &dst);
}
void Entity::setTexture(char * p_path)
{
    g_texture = IMG_LoadTexture(p_renderer, p_path);
}

Entity::~Entity() {
    SDL_DestroyTexture(g_texture);
}