#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"

class Player : public Entity
{
public:
    float speed = 150;
    float traction = 0.6;
    float speedCap = 3;
    bool interacting = false;
    char *fileDirectionExtension = "down.png";
    bool wPress = false, dPress = false, aPress = false, sPress = false;
    Player();
    ~Player();
    void keyEventHandler();
    void tickUpdate() override;
    void updateDirection();
};
extern Player *lonePlayerInstance;
#endif