#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "entity.hpp"
#include <memory>
class Entity {
    public:
        SDL_Texture* g_texture;
        int g_x = 0,g_y = 0, g_velX = 0, g_velY = 0;
        SDL_Renderer* p_renderer;
        void initEntity(const char* p_path, int p_x, int p_y, SDL_Renderer* o_renderer);
        void setTexture(char* p_path);
        void update();
        void destroyEntity();
        virtual void tickUpdate();
        Entity();
        ~Entity();
}; 

Entity* createEntity(const char* p_type);

extern std::vector<std::unique_ptr<Entity>> allEntities;

#endif