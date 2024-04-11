#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"
#include <vector>

class PathfindingOperation
{
public:
    PathfindingOperation();
    ~PathfindingOperation();
};

class PathfindingPointOperation : public PathfindingOperation
{
public:
    PathfindingPointOperation(int p_x, int p_y);
    ~PathfindingPointOperation();
    int g_x;
    int g_y;
};

class PathfindingEntityOperation : public PathfindingOperation
{
public:
    PathfindingEntityOperation(Entity *p_entity);
    ~PathfindingEntityOperation();
    Entity *targetEntity;
};

class Pathfinder
{
public:
    Entity *g_entity;
    std::vector<PathfindingOperation> operations;
    bool currentlyPathfinding = false;
    Pathfinder(Entity *p_entity);
    ~Pathfinder();
    void pushBackPointOperation(int p_x, int p_y);
    void pushBackEntityPathfind(Entity *p_targetEntity);
    void clearOperations();
    void removeOperation(int p_index);
    void pathfind();
};

#endif