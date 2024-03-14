#ifndef NPC_HPP
#define NPC_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "entity.hpp"


class NPC : public Entity {
    public:
    std::vector<char*> dialogue;
    bool interacting;
    NPC(std::vector<char *> p_dialogueVector);
    ~NPC();
    void tickUpdate() override;
    void isCloseToPlayer();
    void displayDialogue();
    void finishInteracting();
};

void checkIfShouldInteract() {
    for (auto& p_npc : allNPCs) {
        
    }
}

extern std::vector<NPC*> allNPCs;

#endif