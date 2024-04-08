#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "collison.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include "entity.hpp"
#include "projectile.hpp"
std::vector<std::tuple<SDL_Rect *, int, int>> g_staticHitboxes;

void Collison::checkCollisons(Entity *p_entity)
{
    int leftA = p_entity->g_hitbox.x;
    int rightA = p_entity->g_hitbox.x + p_entity->g_hitbox.w;
    int topA = p_entity->g_hitbox.y;
    int bottomA = p_entity->g_hitbox.y + p_entity->g_hitbox.h;
    for (auto &p_static : g_staticHitboxes)
    {
        SDL_Rect *hitbox = std::get<0>(p_static);
        int leftB = hitbox->x;
        int rightB = hitbox->x + hitbox->w;
        int topB = hitbox->y;
        int bottomB = hitbox->y + hitbox->h;
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

Entity* Collison::rectCollison(SDL_Rect p_rect)
{
    int leftA = p_rect.x;
    int rightA = p_rect.x + p_rect.w;
    int topA = p_rect.y;
    int bottomA = p_rect.y + p_rect.h;

    // Check collision with static hitboxes
    for (auto& p_static : g_staticHitboxes)
    {
        SDL_Rect *hitbox = std::get<0>(p_static);
        int leftB = hitbox->x;
        int rightB = hitbox->x + hitbox->w;
        int topB = hitbox->y;
        int bottomB = hitbox->y + hitbox->h;

        if (!(bottomA <= topB || leftA >= rightB || topA >= bottomB || rightA <= leftB))
        {
            // Collision detected with static hitbox
            std::cout << "static" << std::endl;
            return nullptr; // You might want to return a pointer to the hitbox itself
        }
    }

    // Check collision with entities
    for (auto& p_entity : allEntities)
    {
        SDL_Rect entityRect = p_entity->g_hitbox;
        int leftB = entityRect.x;
        int rightB = entityRect.x + entityRect.w;
        int topB = entityRect.y;
        int bottomB = entityRect.y + entityRect.h;

        if (!(bottomA <= topB || leftA >= rightB || topA >= bottomB || rightA <= leftB))
        {
            // Collision detected with entity
            std::cout << "Entity" << std::endl;
            return p_entity;
        }
    }

    // No collision detected
    return nullptr;
}


Collison::Collison()
{
}

Collison::~Collison()
{
}