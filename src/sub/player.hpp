#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"
class Player : Entity {
    public: 
        bool wPress = false, dPress = false, aPress = false, sPress = false;
        Player();
        ~Player();
        void playerKeyhandler();
        void movementHandler();
};
#endif