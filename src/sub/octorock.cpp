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
    g_hitbox.x = g_x;
    g_hitbox.y = g_y;
    Entity *p_entityHit = checkCollison();
    if (p_entityHit != nullptr)
    {
        std::cout << "Hit entity: " << p_entityHit << std::endl;
        p_entityHit->g_x = 0;
        p_entityHit->g_y = 0;
    }
}
OctorockProjectile::OctorockProjectile() {}
OctorockProjectile::~OctorockProjectile()
{

    std::cout << "uh oh, destroyed " << std::endl;
}

Octorock::Octorock()
{
    allEntities.push_back(this);
    angle = 180;
}
Octorock::~Octorock() {}

double Octorock::facePlayer()
{
    rad = std::atan2(playerYDistance, playerXDistance);
    return rad * (180.0 / M_PI) + 90;
}

void Octorock::tickUpdate()
{
    playerXDistance = g_hitbox.x - lonePlayerInstance->g_hitbox.x;
    playerYDistance = g_hitbox.y - lonePlayerInstance->g_hitbox.y;
    double ticks = globals::ticks / 7;
    if ((int)ticks % 100 == 0)
    {

        double playerAngle = facePlayer();
        int calcAngle = std::round(static_cast<double>(playerAngle) / 90) * 90;
        angle = (calcAngle > 180) ? 180 : calcAngle;
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
        else if (angle == -90)
        {
            g_velX = speed;
        }
    }
    if (utils::collidingWithPlayer(g_hitbox, 0))
    {
        lonePlayerInstance->angle = angle;
    }
    if ((int)ticks % 200 == 0)
    {
        currentProjectile = OctorockProjectile();

        currentProjectile.initProjectile(this, 32, 32, g_x + 32, g_y + 32, "resources/octorock_rock.png", {32, 32, 32, 32});
        if (angle == 90)
        {
            currentProjectile.g_velX = -2;
        }
        else if (angle == 0)
        {
            currentProjectile.g_velY = 2;
        }
        else if (angle == 180)
        {
            currentProjectile.g_velY = -2;
        }
        else if (angle == -90)
        {
            currentProjectile.g_velX = 2;
        }
    }
}