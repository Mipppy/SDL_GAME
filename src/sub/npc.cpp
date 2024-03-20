#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "npc.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "gui.hpp"
#include "gameData/const.hpp"
// Make this a global variable so we don't have to reload it every time, and just keep it loaded in the background!
GUI_DIALOGUE_AREA *npcDialogueArea = new GUI_DIALOGUE_AREA(100, 60, 500, 250, "resources/npcbox.png");
GUI_DIALOGUE_TEXT *npcTextArea = new GUI_DIALOGUE_TEXT(npcDialogueArea);
NPC *currentInteractingNPC;
std::vector<NPC *> allNPCs;

bool areaPushedBack = false;
void dialogueAreaSpecific()
{
    allGUIelements.push_back(npcDialogueArea);
    areaPushedBack = true;
}

NPC::NPC(std::vector<const char *> p_dialogueVector, double p_interactDistance, bool p_autoInteract)
{
    dialogue = p_dialogueVector;
    g_autoInteract = p_autoInteract;
    g_interactDistance = p_interactDistance;
    allEntities.push_back(this);
    allNPCs.push_back(this);
    if (!areaPushedBack)
    {
        dialogueAreaSpecific();
    }
}
NPC::~NPC()
{
}

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
    npcDialogueArea->dialogue = "";
    npcDialogueArea->shouldRender = false;
    npcTextArea->shouldRender = false;
}
bool NPC::isCloseToPlayer()
{
    double x = lonePlayerInstance->g_hitbox.x - g_hitbox.x;
    double y = lonePlayerInstance->g_hitbox.y - g_hitbox.y;
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
            currentInteractingNPC->displayTextBox(currentInteractingNPC->dialogue.at(currentInteractingNPC->dialogueIndex));
            currentInteractingNPC->dialogueIndex += 1;
        }
    }
    else
    {
        if (currentInteractingNPC != nullptr)
        {
            currentInteractingNPC->finishInteracting();
        }
        for (auto &p_npc : allNPCs)
        {
            if (p_npc->g_autoInteract == true)
            {
                p_npc->displayDialogue();
            }
            if (p_npc->isCloseToPlayer())
            {
                // Google "recursion" !
                checkIfShouldInteract();
                break;
            }
        }
    }
}

void NPC::displayTextBox(const char *dialogue)
{
    npcDialogueArea->shouldRender = true;
    npcTextArea->shouldRender = true;
    npcDialogueArea->dialogue = (char *)dialogue;
}