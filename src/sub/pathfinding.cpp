#include "entity.hpp"
#include "collison.hpp"
#include "pathfinding.hpp"
#include "utils.hpp"
#include <vector>
#include <cmath>
#include <iostream>

PathfindingOperation::PathfindingOperation(){};
void PathfindingOperation::pathfind(Entity *p_ownerEntity) {};
PathfindingOperation::~PathfindingOperation(){};

PathfindingPointOperation::PathfindingPointOperation(int p_x, int p_y) : g_x(p_x), g_y(p_y) {}
void PathfindingPointOperation::pathfind(Entity *p_ownerEntity)
{
    // std::cout << "Target XY: " << g_x << ',' << g_y << std::endl;
    // int bestDis = 0;
    // int bestXMove = p_ownerEntity->g_hitbox.x;
    // int bestYMove = p_ownerEntity->g_hitbox.y;
    // std::cout << "starting best XY: " << bestXMove << ", " << bestYMove << std::endl; 
    // for (int i = -64; i < 64; i += 64)
    // {
    //     for (int j = -64; j < 64; j += 64)
    //     {
    //         if (i == 0 && j == 0)
    //         {
    //             continue;
    //         }
    //         Entity *col = rectCollison({p_ownerEntity->g_x + i - 32, p_ownerEntity->g_y + j - 32, 1, 1});
    //         if (col != dummyEntity)
    //         {
    //             double dis = utils::distanceBetweenTwoPoints({p_ownerEntity->g_hitbox.x + i - 32, p_ownerEntity->g_hitbox.y + j - 32}, {g_x, g_y});
    //             std::cout << "dis: " << dis << std::endl;
    //             if (dis > bestDis)
    //             {
    //                 std::cout << "new best dis: " << dis << std::endl;
    //                 bestDis = dis;
    //                 bestXMove = p_ownerEntity->g_x + i - 32;
    //                 bestYMove = p_ownerEntity->g_y + j - 32;
    //             }
    //         }
    //     }
    // }
    // std::cout << "best XY: " << bestXMove << ", " << bestYMove << std::endl;  
    // double dx = bestXMove - p_ownerEntity->g_x;
    // double dy = bestYMove - p_ownerEntity->g_y;

    // double distanceToBestPoint = sqrt(dx * dx + dy * dy);

    // double unit_dx = dx / distanceToBestPoint;
    // double unit_dy = dy / distanceToBestPoint;

    // p_ownerEntity->g_velX = unit_dx * p_ownerEntity->speed;
    // p_ownerEntity->g_velY = unit_dy * p_ownerEntity->speed;
    
}
PathfindingPointOperation::~PathfindingPointOperation(){};

PathfindingEntityOperation::PathfindingEntityOperation(Entity *p_entity) : targetEntity(p_entity) {}
void PathfindingEntityOperation::pathfind(Entity *p_ownerEntity) {

};
PathfindingEntityOperation::~PathfindingEntityOperation(){};

Pathfinder::Pathfinder(Entity *p_entity)
{
    g_entity = p_entity;
    operations.reserve(maxQueueSize);
}

Pathfinder::~Pathfinder()
{
}

void Pathfinder::clearOperations()
{
    operations.clear();
}
void Pathfinder::pushBackPointOperation(int p_x, int p_y)
{
    operations.push_back(new PathfindingPointOperation(p_x, p_y));
};
void Pathfinder::pushBackEntityOperation(Entity *p_entity)
{
    operations.push_back(new PathfindingEntityOperation(p_entity));
}
void Pathfinder::removeOperation(int p_index)
{
    delete operations[p_index];
    operations.erase(operations.begin() + p_index);
}

void Pathfinder::cancelPathfindingOperation()
{
    delete operations[0];
    operations.erase(operations.begin());
}

void Pathfinder::pathfind()
{
    if (enabled)
    {
        operations[0]->pathfind(g_entity);
    }
}