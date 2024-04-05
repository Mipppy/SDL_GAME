#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include "entity.hpp"
#include "collison.hpp"
class Renderer
{
public:
    Renderer();
    SDL_Window *g_window;
    SDL_Renderer *g_renderer;
    Collison collisons;
    std::vector<std::pair<int, int>> staticObjectsNotToRender;
    std::vector<std::pair<SDL_Texture *, const char *>> lastTexturesLoaded;
    long long unsigned int maxTexturesCached = 3;
    void initRenderer();
    std::vector<std::vector<std::string>> loadFromCSV(char p_path[]);
    void renderCSVStaticObjects(std::vector<std::vector<std::string>> p_mapData, std::map<const char *, const char *> p_mappings, double ticks);
    void renderCSVEntities(std::vector<std::vector<std::string>> p_mapData, std::map<const char *, std::pair<const char *, const char *>> p_mappings);
    void renderGUIElements();
    void updateEntities();
    void rendererCleanup();
    void cleanUpStaticHitboxes();
    void clearRenderer();
    void render(const char *p_path, int p_x, int p_y, int p_h, int p_w, bool p_shouldOffset);
    void displayRenderedObjects();
    void renderText();
};
#endif