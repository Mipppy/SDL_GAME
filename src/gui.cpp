#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gui.hpp"
#include <vector>

std::vector<GUI_BUTTON*> allButtons; 

GUI::GUI() {}
GUI::~GUI() {}
void GUI::createButton(int p_x, int p_y, int p_w, int p_h, const char * p_path) {
    GUI_BUTTON* newButton = new GUI_BUTTON(p_x, p_y, p_w, p_h, p_path);
    allButtons.push_back(newButton);
}
void GUI::destroyAllButtons() {
    for (GUI_BUTTON* p_button : allButtons) {
        this->destroyButton(p_button);
    }
}
void GUI::destroyButton(GUI_BUTTON* p_button) {
    auto iterator = std::find(allButtons.begin(), allButtons.end(), p_button);
    delete p_button;
    allButtons.erase(iterator);
}
void GUI::checkIfButtonClicked(int p_mouseX, int p_mouseY) {

}

GUI_BUTTON::GUI_BUTTON(int p_x, int p_y, int p_w, int p_h, const char * p_path) {
    
}
GUI_BUTTON::~GUI_BUTTON() {}

void GUI_BUTTON::onClick() {

}
void GUI_BUTTON::checkClick() {

}