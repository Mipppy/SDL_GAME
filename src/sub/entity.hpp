#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity {
    SDL_Texture* g_texture;
    int g_x,g_y, g_velX, g_velY;
    SDL_Renderer* p_renderer;
    void initEntity(char* p_path, int p_x, int p_y, SDL_Renderer* o_renderer);
    void setTexture(char* p_path);
    void update();
    void destroyEntity();
    Entity();
    ~Entity();
}; 