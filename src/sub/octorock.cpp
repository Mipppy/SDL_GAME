#include "octorock.hpp"
#include "player.hpp"
#include "utils.hpp"
#include "projectile.hpp"
#include "globals.hpp"
#include <cmath>
#include <cstdlib>
#include <random>
#include <iostream>
void OctorockProjectile::update()
{
    g_x = (g_x + g_velX);
    g_y = (g_y + g_velY);
    g_hitbox.x = g_x - lonePlayerInstance->g_x;
    g_hitbox.y = g_y - lonePlayerInstance->g_y;
    sampleCollison();
    if (hitStatic || (g_hitEntity != nullptr && g_hitEntity != dummyEntity))
    {
        shouldRender = false;
        g_x = g_owner->g_x;
        g_y = g_owner->g_y;
    }
}
OctorockProjectile::OctorockProjectile() {}
OctorockProjectile::~OctorockProjectile() {}

Octorock::Octorock()
{
    allEntities.push_back(this);
    angle = 180;
    pathfinder->enabled = true;
    degreesOfFreedom = 90;
    pathfinder->pushBackPointOperation(700, 100);
    currentProjectile.initProjectile(this, 32, 32, g_x + 32, g_y + 32, "resources/octorock_rock.png", {32, 32, 32, 32});
}
Octorock::~Octorock()
{
    delete pathfinder;
}

void Octorock::tickUpdate()
{
    playerXDistance = g_hitbox.x - lonePlayerInstance->g_hitbox.x;
    playerYDistance = g_hitbox.y - lonePlayerInstance->g_hitbox.y;
    double ticks = globals::ticks / 7;
    if ((int)ticks % 10 == 0)
    {
        double playerAngle = utils::getPlayerAngleFromPoint(g_hitbox);
        int calcAngle = std::round(static_cast<double>(playerAngle) / 90) * 90;
        angle = calcAngle < 0 ? 270: calcAngle;
        g_velX = 0;
        g_velY = 0;
        if (angle == 90)
        {
            g_velX = -speed;
        }
        else if (angle == 0)
        {
            g_velY = speed;
        }
        else if (angle == 180)
        {
            g_velY = -speed;
        }
        else if (angle == 270)
        {
            g_velX = speed;
        }
    }
    if ((int)ticks % 100 == 0)
    {
        currentProjectile.g_x = g_x+32;
        currentProjectile.g_y = g_y+32;
        currentProjectile.g_velX = 0;
        currentProjectile.g_velY = 0;
        currentProjectile.shouldRender = true;
        if (angle == 90)
        {
            currentProjectile.g_velX = -projectileSpeed;
        }
        else if (angle == 0)
        {
            currentProjectile.g_velY = projectileSpeed;
        }
        else if (angle == 180)
        {
            currentProjectile.g_velY = -projectileSpeed;
        }
        else if (angle == 270)
        {
            currentProjectile.g_velX = projectileSpeed;
        }
    }
    // pathfinder->pathfind();
}