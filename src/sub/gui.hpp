#ifndef GUI_HPP
#define GUI_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class GUI_BASE;
class GUI_BUTTON;

class GUI
{
public:
    GUI();
    ~GUI();
    void createButton(int p_x, int p_y, int p_w, int p_h, const char *p_path);
    void destroyButton(GUI_BUTTON *p_button);
    void destroyAllButtons();
    void checkIfButtonClicked(int p_mouseX, int p_mouseY);
};
class GUI_BASE
{
public:
    int g_x = 0, g_y = 0;
    SDL_Rect g_hitbox = {0, 0, 0, 0};
    const char *g_path;
};
class GUI_BUTTON : public GUI_BASE
{
public:
    GUI_BUTTON(int p_x, int p_y, int p_w, int p_h, const char *p_path);
    ~GUI_BUTTON();
    void onClick();
    void checkClick(int p_x, int p_y);
};

extern std::vector<GUI_BUTTON *> allButtons;
extern std::vector<GUI_BASE *> allGUIelements;
#endif
