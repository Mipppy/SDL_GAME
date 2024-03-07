#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>
#include "entity.hpp"
class Renderer {
    public:
        Renderer();
        SDL_Window* g_window;
        SDL_Renderer* g_renderer;
        void initRenderer();
        void loadFromCSV(char p_path[], std::map<const char*, std::variant<const char*, Entity>> p_mappings);
        void renderEntity();
        void rendererCleanup();
        void clearRenderer();
        void render(const char* p_path, int p_x, int p_y, int p_h, int p_w);
        void displayRenderedObjects();
};