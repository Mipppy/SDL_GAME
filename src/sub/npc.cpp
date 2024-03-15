#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "npc.hpp"
#include "entity.hpp"
#include "player.hpp"

NPC *currentInteractingNPC;
std::vector<NPC *> allNPCs;

NPC::NPC(std::vector<const char *> p_dialogueVector, double p_interactDistance, bool p_autoInteract)
{
    dialogue = p_dialogueVector;
    g_autoInteract = p_autoInteract;
    g_interactDistance = p_interactDistance;
    allEntities.push_back(this);
    allNPCs.push_back(this);
}
NPC::~NPC() {}

void NPC::tickUpdate()
{
}
void NPC::displayDialogue()
{
    lonePlayerInstance->interacting = true;
    g_interacting = true;
    currentInteractingNPC = this;
}
void NPC::finishInteracting()
{
    g_interacting = false;
    lonePlayerInstance->interacting = false;
    currentInteractingNPC = nullptr;
    dialogueIndex = 0;
}
bool NPC::isCloseToPlayer()
{
    double x = lonePlayerInstance->g_x - g_x;
    double y = lonePlayerInstance->g_y - g_y;
    double distance = std::sqrt(x * x + y * y);
    if (distance <= g_interactDistance)
    {
        displayDialogue();
        return true;
    }
    return false;
}
bool NPC::shouldFinishInteracting()
{
    if (dialogueIndex + 1 > static_cast<int>(dialogue.size()))
    {
        return true;
    }
    return false;
}
void checkIfShouldInteract()
{
    if (currentInteractingNPC != nullptr && lonePlayerInstance->interacting == true && currentInteractingNPC->isCloseToPlayer())
    {
        if (currentInteractingNPC->shouldFinishInteracting())
        {
            currentInteractingNPC->finishInteracting();
            return;
        }
        else
        {
            std::cout << currentInteractingNPC->dialogue.at(currentInteractingNPC->dialogueIndex) << std::endl;
            currentInteractingNPC->dialogueIndex += 1;
        }
    }
    else
    {
        for (auto &p_npc : allNPCs)
        {
            if (p_npc->g_autoInteract == true)
            {
                p_npc->displayDialogue();
            }
            if (p_npc->isCloseToPlayer())
            {
                //Google "recursion" !
                checkIfShouldInteract();
                break;
            }
        }
    }
}