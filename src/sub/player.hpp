#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"

class Player : public Entity
{
public:
    float speed = 1;
    float traction = 0.6;
    float speedCap = 3;
    bool interacting = false;
    bool wPress = false, dPress = false, aPress = false, sPress = false;
    Player();
    ~Player();
    void keyEventHandler();
    void tickUpdate() override;
};
extern Player *lonePlayerInstance;
#endif