#ifndef COLLISON_HPP
#define COLLISON_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <tuple>
#include "entity.hpp"

extern std::vector<std::tuple<SDL_Rect*, int,int>> g_staticHitboxes;
class Collison
{
public:
    Collison();
    ~Collison();
    void checkCollisons(Entity *p_entity);
    void rectCollison();
};
Entity* rectCollison(SDL_Rect);
#endif