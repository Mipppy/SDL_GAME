#include "entity.hpp"
#include "pathfinding.hpp"

PathfindingOperation::PathfindingOperation() {};
PathfindingOperation::~PathfindingOperation() {};

PathfindingPointOperation::PathfindingPointOperation(int p_x, int p_y) {
    g_x = p_x;
    g_y = p_y;    
}
PathfindingPointOperation::~PathfindingPointOperation() {};

PathfindingEntityOperation::PathfindingEntityOperation(Entity* p_entity) {
    targetEntity = p_entity;
}
PathfindingEntityOperation::~PathfindingEntityOperation() {};



Pathfinder::Pathfinder(Entity* p_entity) {
    g_entity = p_entity;
}

Pathfinder::~Pathfinder() {}

void Pathfinder::clearOperations() {
    operations.clear();
}
void Pathfinder::pushBackPointOperation(int p_x, int p_y) {
    PathfindingPointOperation op = PathfindingPointOperation(p_x, p_y);
    operations.push_back(op);
};