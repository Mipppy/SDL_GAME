#ifndef GUI_HPP
#define GUI_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class GUI_BUTTON;  // Forward declaration

class GUI {
public:
    GUI();
    ~GUI();
    void createButton(int p_x, int p_y, int p_w, int p_h, const char *p_path);
    void destroyButton(GUI_BUTTON *p_button);
    void destroyAllButtons();
    void checkIfButtonClicked(int p_mouseX, int p_mouseY);
};

class GUI_BUTTON {
public:
    SDL_Rect g_hitbox;
    SDL_Texture *g_texture;
    int g_x = 0, g_y = 0;
    GUI_BUTTON(int p_x, int p_y, int p_w, int p_h, const char *p_path);
    ~GUI_BUTTON();
    void onClick();
    void checkClick();
};
extern std::vector<GUI_BUTTON *> allButtons;

#endif
