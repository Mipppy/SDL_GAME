#ifndef COLLISON_HPP
#define COLLISON_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "entity.hpp"

extern std::vector<SDL_Rect*> g_staticHitboxes; 

class Collison {
    public:
        Collison();
        ~Collison();
        void checkCollisons(Entity* p_entity);
};
#endif