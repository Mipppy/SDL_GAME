#ifndef OCTOROCK_HPP
#define OCTOROCK_HPP
#include "projectile.hpp"
#include "pathfinding.hpp"
#include "entity.hpp"
#include <SDL2/SDL.h>
#include <memory>
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
    int projectileSpeed = 7.5;
    int playerYDistance = 0;
    Pathfinder* pathfinder = new Pathfinder(this);
    double rad = 0;
    OctorockProjectile currentProjectile = OctorockProjectile();
    double speed = 1;
    Octorock();
    ~Octorock();
    void tickUpdate() override;
};

#endif