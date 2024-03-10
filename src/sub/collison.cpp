#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "collison.hpp"
#include <vector>
#include <iostream>
#include "entity.hpp"

std::vector<SDL_Rect *> g_staticHitboxes;

void Collison::checkCollisons()
{
    for (auto &p_entity : allEntities)
    {
        int leftA = p_entity->g_hitbox.x;
        int rightA = p_entity->g_hitbox.x + p_entity->g_hitbox.w;
        int topA = p_entity->g_hitbox.y;
        int bottomA = p_entity->g_hitbox.y + p_entity->g_hitbox.h;
        for (auto &p_static : g_staticHitboxes)
        {
            std::cout << "static x,y: " << p_static->x << ", " << p_static->y << " : " << p_entity->g_hitbox.x << "," << p_entity->g_hitbox.y <<std::endl;
            int leftB = p_static->x;
            int rightB = p_static->x + p_static->w;
            int topB = p_static->y;
            int bottomB = p_static->y + p_static->h;
            if (bottomA <= topB || leftA >= rightB || topA >= bottomB || rightA <= leftB)
            {
                std::cout << "no collison" << std::endl;
            }
            else
            {
                std::cout << p_entity->currentXDirection << ", " << p_entity->currentYDirection << std::endl;
                if (p_entity->currentXDirection == 0) {
                    p_entity->g_velX *= -1;
                }         
            }
        }
    }
}

Collison::Collison()
{
}

Collison::~Collison()
{
}