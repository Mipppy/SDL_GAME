#include <SDL2/SDL.h>
#include <map>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <variant>
#include "renderer.hpp"
#include "entity.hpp"
#include "gameData/const.hpp"
Renderer::Renderer(){};

void Renderer::initRenderer()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    g_window = SDL_CreateWindow(str_WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1800, 720, SDL_WINDOW_SHOWN);
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // SDL_Surface * icon = IMG_Load("resources/icon.png");
    // SDL_SetWindowIcon(g_window, icon);
}

void Renderer::rendererCleanup()
{
    SDL_DestroyWindow(g_window);
    SDL_DestroyRenderer(g_renderer);
    SDL_Quit();
}

void Renderer::clearRenderer()
{
    SDL_SetRenderDrawColor(g_renderer, 90, 90, 90, 255);
    SDL_RenderClear(g_renderer);
}
void Renderer::displayRenderedObjects()
{
    SDL_RenderPresent(g_renderer);
}

void Renderer::render(const char *p_path, int p_x, int p_y, int p_w, int p_h)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(g_renderer, p_path);
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
    dst.x = p_x;
    dst.y = p_y;
    dst.w = p_w;
    dst.h = p_h;
    SDL_RenderCopy(g_renderer, texture, &src, &dst);
    SDL_DestroyTexture(texture);
}

std::vector<std::vector<std::string>> Renderer::loadFromCSV(char p_path[])
{
    std::ifstream file;
    file.open(p_path);
    std::string line;
    std::vector<std::vector<std::string>> csvData;

    //Gets the first line of the file so a little binary isn't read.
    getline(file, line);
    while (getline(file, line))
    {
        std::vector<std::string> row;
        std::istringstream lineStream(line);
        std::string cell;

        while (getline(lineStream, cell, ','))
        {
            row.push_back(cell);
        }

        csvData.push_back(row);
    };
    
    file.close();
    return csvData;
}

void Renderer::renderCSVStaticObjects(std::vector<std::vector<std::string>> p_mapData, std::map<const char*, const char*> p_mappings) {
    int cellcounter = 0;
    int rowcounter = 0;

    //Loop through 2d vector array
    for (const auto &row : p_mapData)
    {
        rowcounter++;
        cellcounter = 0;
        for (const auto &cell : row)
        {
            cellcounter++;
            for (const auto &mappingData : p_mappings)
            {
                if (cell == mappingData.first)
                {
                        render(mappingData.second, (cellcounter * int_DEFAULT_TEXTURE_MULTIPLIER) - int_DEFAULT_TEXTURE_OFFSET, (rowcounter * int_DEFAULT_TEXTURE_MULTIPLIER) - int_DEFAULT_TEXTURE_OFFSET, int_DEFAULT_TEXTURE_SIZE, int_DEFAULT_TEXTURE_SIZE);
                }
            }
        }
    }
}
void Renderer::renderCSVEntities(std::vector<std::vector<std::string>> p_mapData, std::map<const char*, std::pair<const char*, const char*>> p_mappings) {
    int cellcounter = 0;
    int rowcounter = 0;

    //Loop through 2d vector array
    for (const auto &row : p_mapData)
    {
        rowcounter++;
        cellcounter = 0;
        for (const auto &cell : row)
        {
            cellcounter++;
            for (const auto &mappingData : p_mappings)
            {
                if (cell == mappingData.first)
                {
                    Entity* worthlessEntity = createEntity(mappingData.second.second);
                    worthlessEntity->initEntity(mappingData.second.first, (cellcounter * int_DEFAULT_TEXTURE_MULTIPLIER) - int_DEFAULT_TEXTURE_OFFSET,(rowcounter * int_DEFAULT_TEXTURE_MULTIPLIER) - int_DEFAULT_TEXTURE_OFFSET, g_renderer);
                }
            }
        }
    }
}
void Renderer::updateEntities() {
    for (auto &p_entity : allEntities) {
        p_entity->tickUpdate(); // Unique class actions
        p_entity->update(); //Shared update actions 
    }
}