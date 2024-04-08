#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "projectile.hpp"
#include "entity.hpp"
#include "collison.hpp"
#include "globals.hpp"
std::vector<Projectile *> activeProjectiles;
Projectile::Projectile(){};
Projectile::~Projectile()
{
    if (id >= 0 && id < activeProjectiles.size())
    {
        activeProjectiles.erase(activeProjectiles.begin() + id);
    }
};

void Projectile::initProjectile(Entity *p_owner, int p_w, int p_h, int p_x, int p_y, const char *p_path, SDL_Rect p_hitbox)
{
    g_owner = p_owner;
    g_w = p_w;
    g_h = p_h;
    g_x = p_x;
    g_y = p_y;
    g_path = p_path;
    g_hitbox = p_hitbox;
    activeProjectiles.push_back(this);
    id = activeProjectiles.size();
}

Entity* Projectile::checkCollison()
{
    Entity *possibleEntity = collison.rectCollison(g_hitbox);
    if (possibleEntity != nullptr )
    {
            std::cout << possibleEntity << std::endl;

        return possibleEntity;
    }
    return nullptr;
}

void Projectile::update()
{
}