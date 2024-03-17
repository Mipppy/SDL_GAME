#ifndef GUI_HPP
#define GUI_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class GUI_BASE;
class GUI_BUTTON;
class GUI_DIALOGUE_AREA;
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
    bool shouldRender = true;
};
class GUI_BUTTON : public GUI_BASE
{
public:
    GUI_BUTTON(int p_x, int p_y, int p_w, int p_h, const char *p_path);
    virtual ~GUI_BUTTON();
    virtual void onClick();
    virtual void checkClick(int p_x, int p_y);
};

class GUI_DIALOGUE_AREA : public GUI_BASE
{
public:
    char *dialogue = "";
    GUI_DIALOGUE_AREA(int p_x, int p_y, int p_w, int p_h, const char *p_path);
};
class GUI_DIALOGUE_TEXT : public GUI_BASE
{
public:
    SDL_Surface *g_surface;
    SDL_Rect g_rect;
    GUI_DIALOGUE_TEXT(GUI_DIALOGUE_AREA *);
    ~GUI_DIALOGUE_TEXT();
    void updateSurface(char *);
};

extern GUI_DIALOGUE_AREA *npcDialogue;
extern std::vector<GUI_BUTTON *> allButtons;
extern std::vector<GUI_BASE *> allGUIelements;
#endif
