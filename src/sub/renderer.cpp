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

void Renderer::loadFromCSV(char p_path[], std::map<const char*, std::variant<const char*, Entity>> p_mappings)
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
    
    //Used for object positioning
    int cellcounter = 0;
    int rowcounter = 0;

    //Loop through 2d vector array
    for (const auto &row : csvData)
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
                    if (typeid(mappingData.second) == typeid(Entity)) {

                    }
                    else {
                        render(mappingData.second, (cellcounter * int_DEFAULT_TEXTURE_MULTIPLIER) - int_DEFAULT_TEXTURE_OFFSET, (rowcounter * int_DEFAULT_TEXTURE_MULTIPLIER) - int_DEFAULT_TEXTURE_OFFSET, int_DEFAULT_TEXTURE_SIZE, int_DEFAULT_TEXTURE_SIZE);
                    }
                }
            }
        }
    }
    file.close();
}