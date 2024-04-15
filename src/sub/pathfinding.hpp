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
    virtual ~PathfindingOperation();
    virtual void pathfind(Entity* p_ownerEntity);
};

class PathfindingPointOperation : public PathfindingOperation
{
public:
    PathfindingPointOperation(int p_x, int p_y);
    ~PathfindingPointOperation();
    void pathfind(Entity* p_ownerEntity) override;
    int g_x;
    int g_y;
};

class PathfindingEntityOperation : public PathfindingOperation
{
public:
    PathfindingEntityOperation(Entity *p_entity);
    ~PathfindingEntityOperation();
    void pathfind(Entity* p_ownerEntity) override;
    Entity *targetEntity;
};

class Pathfinder
{
public:
    Entity *g_entity;
    std::vector<PathfindingOperation*> operations;
    int maxQueueSize = 10;
    bool enabled = false;
    PathfindingOperation* lastOperation;
    Pathfinder(Entity *p_entity);
    ~Pathfinder();
    void pushBackPointOperation(int p_x, int p_y);
    void pushBackEntityOperation(Entity *p_targetEntity);
    void clearOperations();
    void removeOperation(int p_index);
    void pathfind();
    void cancelPathfindingOperation();
};

#endif