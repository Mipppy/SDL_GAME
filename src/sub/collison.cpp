#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "collison.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include "entity.hpp"

std::vector<SDL_Rect *> g_staticHitboxes;

void Collison::checkCollisons(Entity *p_entity)
{
    int leftA = p_entity->g_hitbox.x;
    int rightA = p_entity->g_hitbox.x + p_entity->g_hitbox.w;
    int topA = p_entity->g_hitbox.y;
    int bottomA = p_entity->g_hitbox.y + p_entity->g_hitbox.h;
    for (auto &p_static : g_staticHitboxes)
    {
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
            int overlapLeft = rightA - leftB;
            int overlapRight = rightB - leftA;
            int overlapTop = bottomA - topB;
            int overlapBottom = bottomB - topA;
            int maxOverlap = std::max({overlapLeft, overlapRight, overlapTop, overlapBottom});

            if (maxOverlap == overlapLeft)
            {
                std::cout << "Collided with right side" << std::endl;
            }
            else if (maxOverlap == overlapRight)
            {
                std::cout << "Collided with left side" << std::endl;
            }
            else if (maxOverlap == overlapTop)
            {
                std::cout << "Collided with bottom side" << std::endl;
            }
            else if (maxOverlap == overlapBottom)
            {
                std::cout << "Collided with top side" << std::endl;
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