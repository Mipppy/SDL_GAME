#ifndef OCTOROCK_HPP
#define OCTOROCK_HPP
#include "projectile.hpp"
#include "entity.hpp"
#include <SDL2/SDL.h>

class OctorockProjectile : public Projectile
{
public:
    void update() override;
    OctorockProjectile();
    ~OctorockProjectile();
};

class Octorock : public Entity
{
public:
    int playerXDistance = 0;
    int playerYDistance = 0;
    double rad = 0;
    OctorockProjectile* currentProjectile = nullptr;
    double speed = 1;
    Octorock();
    ~Octorock();
    void tickUpdate() override;
    double facePlayer();
};

#endif