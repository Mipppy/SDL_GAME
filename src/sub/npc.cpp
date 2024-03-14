#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "npc.hpp"
#include "entity.hpp"

std::vector<NPC*> allNPCs;

NPC::NPC(std::vector<char *> p_dialogueVector) {
    dialogue = p_dialogueVector;
    allEntities.push_back(this);
}
NPC::~NPC() {}

void NPC::tickUpdate() {
    
}
void NPC::displayDialogue() {

}
void NPC::finishInteracting() {

}
void NPC::isCloseToPlayer() {
    
}