#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector>
#include <string>
#include "entity.hpp"
class Renderer {
    public:
        Renderer();
        SDL_Window* g_window;
        SDL_Renderer* g_renderer;
        void initRenderer();
        std::vector<std::vector<std::string>> loadFromCSV(char p_path[]);
        //renderCSVStaticObjects is a constant job, being run constantly, taking care of static rendering
        void renderCSVStaticObjects(std::vector<std::vector<std::string>> p_mapData, std::map<const char*, const char*> p_mappings);
        //renderCSVEntities is a one and done job, initalizing the Entity and that's it.
        void renderCSVEntities(std::vector<std::vector<std::string>> p_mapData, std::map<const char*, const char*> p_mappings);
        void updateEntities();
        void rendererCleanup();
        void clearRenderer();
        void render(const char* p_path, int p_x, int p_y, int p_h, int p_w);
        void displayRenderedObjects();
};
#endif