#ifndef NPC_HPP
#define NPC_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "entity.hpp"
#include "gui.hpp"
#include "gameData/const.hpp"

class NPC : public Entity {
    public:
    std::vector<const char*> dialogue;
    bool g_interacting = false;
    double g_interactDistance = 0;
    int dialogueIndex = 0;
    bool g_autoInteract = false;
    NPC(std::vector<const char *> p_dialogueVector, double p_interactDistance, bool p_autoInteract);
    ~NPC();
    void tickUpdate() override;
    bool isCloseToPlayer();
    void displayDialogue();
    void finishInteracting();
    bool shouldFinishInteracting();
    void displayTextBox(const char *);
};

void checkIfShouldInteract();
extern GUI_DIALOGUE_AREA* npcDialogueArea;
extern GUI_DIALOGUE_TEXT* npcTextArea;
extern std::vector<NPC*> allNPCs;
extern NPC* currentInteractingNPC;
#endif