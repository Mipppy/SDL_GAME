#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "gui.hpp"
#include "gameData/const.hpp"
#include <vector>
#include <iostream>
#include <cmath>
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

GUI_DIALOGUE_AREA::GUI_DIALOGUE_AREA(int p_x, int p_y, int p_w, int p_h, const char *p_path)
{
    g_x = p_x;
    g_y = p_y;
    g_hitbox = {p_x, p_y, p_w, p_h};
    g_path = p_path;
    shouldRender = false;
}
GUI_DIALOGUE_TEXT::GUI_DIALOGUE_TEXT(GUI_DIALOGUE_AREA *p_baseArea)
{
    TTF_Init();
    SDL_Color White = {0, 0, 0};
    shouldRender = false;
    TTF_Font *Sans = TTF_OpenFont("resources/sans.ttf", 24);
    g_rect.x = p_baseArea->g_x + 10;
    g_rect.y = p_baseArea->g_y + 10;
    g_rect.w = p_baseArea->g_hitbox.w * 0.8;
    g_rect.h = p_baseArea->g_hitbox.h * 0.8;
    g_backupRect = g_rect;
    g_surface = TTF_RenderText_Blended_Wrapped(Sans, p_baseArea->dialogue, White,g_rect.w);
    TTF_CloseFont(Sans);
}
GUI_DIALOGUE_TEXT::~GUI_DIALOGUE_TEXT()
{
    SDL_FreeSurface(g_surface);
}
void GUI_DIALOGUE_TEXT::updateSurface(char *p_dialogue)
{
    SDL_Color White = {0, 0, 0};
    shouldRender = true;
    TTF_Font *Sans = TTF_OpenFont("resources/sans.ttf", 24);
    SDL_FreeSurface(g_surface);
    TTF_SizeText(Sans, p_dialogue, &g_rect.w, &g_rect.h);
    int timesToScale = round(g_rect.w/(g_backupRect.w)) + 1;
    g_rect.h *= timesToScale;
    g_rect.w = (g_rect.w/timesToScale) * 1.15;
    g_surface = TTF_RenderText_Blended_Wrapped(Sans, p_dialogue, White, g_backupRect.w);
    TTF_CloseFont(Sans);
}