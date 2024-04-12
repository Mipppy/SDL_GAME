#include "entity.hpp"
#include "pathfinding.hpp"

PathfindingOperation::PathfindingOperation(){};
void PathfindingOperation::pathfind() {};
PathfindingOperation::~PathfindingOperation(){};

PathfindingPointOperation::PathfindingPointOperation(int p_x, int p_y) : g_x(p_x), g_y(p_y) {}
void PathfindingPointOperation::pathfind() {
    
}
PathfindingPointOperation::~PathfindingPointOperation(){};

PathfindingEntityOperation::PathfindingEntityOperation(Entity *p_entity) : targetEntity(p_entity) {}
void PathfindingEntityOperation::pathfind() {};
PathfindingEntityOperation::~PathfindingEntityOperation(){};

Pathfinder::Pathfinder(Entity *p_entity)
{
    g_entity = p_entity;
}

Pathfinder::~Pathfinder() {}

void Pathfinder::clearOperations()
{
    operations.clear();
}
void Pathfinder::pushBackPointOperation(int p_x, int p_y)
{
    PathfindingPointOperation op = PathfindingPointOperation(p_x, p_y);
    operations.push_back(op);
};
void Pathfinder::pushBackEntityPathfind(Entity *p_entity)
{
    PathfindingEntityOperation op = PathfindingEntityOperation(p_entity);
    operations.push_back(op);
}
void Pathfinder::removeOperation(int p_index)
{
    operations.erase(operations.begin() + p_index);
}

void Pathfinder::cancelPathfindingOperation()
{
    operations.erase(operations.begin());
}

void Pathfinder::pathfind()
{
}