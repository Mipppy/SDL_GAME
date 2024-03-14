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
            // nothing
        }
        else
        {
            // Calculate overlap and pick side based on greatest
            int overlapLeft = rightA - leftB;
            int overlapRight = rightB - leftA;
            int overlapTop = bottomA - topB;
            int overlapBottom = bottomB - topA;
            int minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});
            if (minOverlap == overlapLeft)
            {
                p_entity->g_x -= overlapLeft;
            }
            else if (minOverlap == overlapRight)
            {
                p_entity->g_x += overlapRight;
            }
            if (minOverlap == overlapTop)
            {
                p_entity->g_y -= overlapTop;
            }
            else if (minOverlap == overlapBottom)
            {
                p_entity->g_y += overlapBottom;
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