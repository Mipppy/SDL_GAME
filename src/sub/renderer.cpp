#include <SDL2/SDL.h>
#include <map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include "renderer.hpp"
#include "entity.hpp"
#include "gameData/const.hpp"
#include "collison.hpp"
#include "player.hpp"
#include "npc.hpp"
#include "gui.hpp"
#include "globals.hpp"
#include "utils.hpp"
Renderer::Renderer(){};

void Renderer::initRenderer()
{

    SDL_Init(SDL_INIT_EVERYTHING);
    utils::screenDemensions(globals::GLOBAL_userScreenWidth, globals::GLOBAL_userScreenHeight);
    g_window = SDL_CreateWindow(str_WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, globals::GLOBAL_userScreenWidth, globals::GLOBAL_userScreenHeight, SDL_WINDOW_SHOWN);
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Renderer::rendererCleanup()
{
    SDL_DestroyWindow(g_window);
    SDL_DestroyRenderer(g_renderer);
    SDL_Quit();
    TTF_Quit();
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

void Renderer::render(const char *p_path, int p_x, int p_y, int p_w, int p_h, bool p_shouldOffset)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(g_renderer, p_path);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
    if (p_shouldOffset)
    {
        dst.x = p_x - lonePlayerInstance->g_x;
        dst.y = p_y - lonePlayerInstance->g_y;
    }
    else
    {
        dst.x = p_x;
        dst.y = p_y;
    }
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

    // Gets the first line of the file so a little binary isn't read.
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

void Renderer::renderCSVStaticObjects(std::vector<std::vector<std::string>> p_mapData, std::map<const char *, const char *> p_mappings)
{
    int cellcounter = 0;
    int rowcounter = 0;

    // Loop through 2d vector array
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
                    SDL_Rect *p_hitbox = new SDL_Rect{((cellcounter * int_DEFAULT_TEXTURE_MULTIPLIER) - int_DEFAULT_TEXTURE_OFFSET) - lonePlayerInstance->g_x, ((rowcounter * int_DEFAULT_TEXTURE_MULTIPLIER) - int_DEFAULT_TEXTURE_OFFSET) - lonePlayerInstance->g_y, int_DEFAULT_TEXTURE_SIZE, int_DEFAULT_TEXTURE_SIZE};
                    g_staticHitboxes.push_back(p_hitbox);
                    render(mappingData.second, (cellcounter * int_DEFAULT_TEXTURE_MULTIPLIER) - int_DEFAULT_TEXTURE_OFFSET, (rowcounter * int_DEFAULT_TEXTURE_MULTIPLIER) - int_DEFAULT_TEXTURE_OFFSET, int_DEFAULT_TEXTURE_SIZE, int_DEFAULT_TEXTURE_SIZE, true);
                }
            }
        }
    }
}
void Renderer::renderCSVEntities(std::vector<std::vector<std::string>> p_mapData, std::map<const char *, std::pair<const char *, const char *>> p_mappings)
{
    int cellcounter = 0;
    int rowcounter = 0;

    // Loop through 2d vector array
    for (const auto &row : p_mapData)
    {
        rowcounter++;
        cellcounter = 0;
        std::vector<std::string> rowCells;
        for (const auto &cell : row)
        {
            rowCells.push_back(cell);
            cellcounter++;
        }

        for (const auto &mappingData : p_mappings)
        {
            if (strcmp(rowCells.front().c_str(), mappingData.second.second) == 0)
            {
                Entity *worthlessEntity = createEntity(mappingData.second.second, rowCells);
                try {
                    worthlessEntity->initEntity(mappingData.second.first,  std::stoi(rowCells[1]), std::stoi(rowCells[2]), g_renderer);
                }
                catch (std::length_error) {
                    std::cout << "failed to init entity of type " << typeid(*worthlessEntity).name() << std::endl;
                }
            }
        }
        rowCells.clear();
    }
}
void Renderer::updateEntities()
{
    for (auto p_entity : allEntities)
    {
        p_entity->tickUpdate();
        collisons.checkCollisons(p_entity);
        p_entity->update();
    }
}
void Renderer::cleanUpStaticHitboxes()
{
    // Whoops! Removing this causes a memory leak!
    for (SDL_Rect *p_staticHitbox : g_staticHitboxes)
    {
        delete p_staticHitbox;
    }
    g_staticHitboxes.clear();
}

void Renderer::renderGUIElements()
{
    for (auto p_guiElement : allGUIelements)
    {
        if (p_guiElement->shouldRender)
        {
            render(p_guiElement->g_path, p_guiElement->g_x, p_guiElement->g_y, p_guiElement->g_hitbox.w, p_guiElement->g_hitbox.h, false);
        }
    }
}
void Renderer::renderText()
{
    if (npcTextArea->shouldRender)
    {
        npcTextArea->updateSurface(npcDialogueArea->dialogue);
        SDL_Texture *message = SDL_CreateTextureFromSurface(g_renderer, npcTextArea->g_surface);
        SDL_RenderCopy(g_renderer, message, NULL, &npcTextArea->g_rect);
        SDL_DestroyTexture(message);
    }
};