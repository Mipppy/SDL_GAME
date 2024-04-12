#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "entity.hpp"
#include "collison.hpp"

class Projectile
{
public: 
    const char *g_path;
    int g_w = 0;
    int g_h = 0;
    int g_x = 0;
    int g_velX = 0;
    int g_velY = 0;
    bool wasInit = false;
    bool shouldRender = true;
    int g_y = 0;
    Entity *g_owner = nullptr;
    Projectile* thisPtr = this;
    Entity *g_hitEntity = nullptr;
    bool hitStatic = false;
    SDL_Rect g_hitbox = {0, 0, 0, 0};
    Projectile();
    void initProjectile(Entity *p_owner, int p_w, int p_h, int p_x, int p_y, const char *p_path, SDL_Rect p_hitbox);
    void sampleCollison();
    Entity* checkCollison();
    virtual void update();
    virtual ~Projectile();
};

extern std::vector<Projectile *> activeProjectiles;

#endif