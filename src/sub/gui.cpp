#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gui.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

std::vector<GUI_BUTTON *> allButtons;
std::vector<GUI_BASE *> allGUIelements;

GUI::GUI()
{
}
GUI::~GUI() {}
void GUI::createButton(int p_x, int p_y, int p_w, int p_h, const char *p_path)
{
    GUI_BUTTON *newButton = new GUI_BUTTON(p_x, p_y, p_w, p_h, p_path);
    allGUIelements.push_back(newButton);
    allButtons.push_back(newButton);
}
void GUI::destroyAllButtons()
{
    for (GUI_BUTTON *p_button : allButtons)
    {
        this->destroyButton(p_button);
    }
}
void GUI::destroyButton(GUI_BUTTON *p_button)
{
    allButtons.erase(std::remove(allButtons.begin(), allButtons.end(), p_button), allButtons.end());
    delete p_button;
}

void GUI::checkIfButtonClicked(int p_mouseX, int p_mouseY)
{
    for (GUI_BUTTON *p_button : allButtons)
    {
        p_button->checkClick(p_mouseX, p_mouseY);
    }
}

GUI_BUTTON::GUI_BUTTON(int p_x, int p_y, int p_w, int p_h, const char *p_path)
{
    g_x = p_x;
    g_y = p_y;
    g_hitbox = {p_x, p_y, p_w, p_h};
    g_path = p_path;
}
GUI_BUTTON::~GUI_BUTTON()
{
}

void GUI_BUTTON::onClick()
{
    std::cout << "clicked button: " << this << std::endl;
}
void GUI_BUTTON::checkClick(int p_x, int p_y)
{
    if ((p_x > g_hitbox.x) && (p_x < g_hitbox.x + g_hitbox.w) && (p_y > g_hitbox.y) && (p_y < g_hitbox.y + g_hitbox.h))
    {
        this->onClick();
    }
}