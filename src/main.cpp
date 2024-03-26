#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "sub/renderer.hpp"
#include "sub/entity.hpp"
#include "sub/player.hpp"
#include "sub/collison.hpp"
#include "sub/gui.hpp"
#include "sub/npc.hpp"
#include "sub/console.hpp"
#include "sub/globals.hpp"
#include "sub/utils.hpp"
unsigned int a = SDL_GetTicks();
unsigned int b = SDL_GetTicks();
double delta = 0;
bool running = true;
void EventHandler();
Renderer rend;
GUI gui;
int main(int argc, char *argv[])
{
	rend.initRenderer();
	std::map<const char *, const char *> mappings;
	std::map<const char *, std::pair<const char *, const char *>> mappings2;
	mappings.insert(std::make_pair("1", "resources/rock.png"));
	mappings2.emplace("1", std::make_pair("resources/player/player_", "p"));
	mappings2.emplace("2", std::make_pair("resources/rock.png", "npc"));
	char path[] = "resources/test.csv";
	char path2[] = "resources/teste.csv";
	allGUIelements.clear();
	allButtons.clear();
	rend.staticObjectsNotToRender.clear();
	std::vector<std::vector<std::string>> mapData = rend.loadFromCSV(path);
	std::vector<std::vector<std::string>> entityMapData = rend.loadFromCSV(path2);
	rend.renderCSVEntities(entityMapData, mappings2);
	gui.createButton(1000, 500, 64, 64, "resources/button.png");
	while (running)
	{
		a = SDL_GetTicks();
		delta += a - b;
		if (delta > 1000 / 500.0)
		{
			/*
				Render Order:
				GUI
				HUD
				ENTITIES
				COLLIDABLE OBJECTS
				BACKGROUND OBJECTS
			*/
			rend.cleanUpStaticHitboxes();
			EventHandler();
			rend.clearRenderer();
			rend.renderCSVStaticObjects(mapData, mappings, a);
			rend.updateEntities();
			rend.renderGUIElements();
			rend.renderText();
			rend.displayRenderedObjects();
			delta = 0;
		}
		b = SDL_GetTicks();
	}
	return 0;
}

void EventHandler()
{
	SDL_Event event;

	/* Process events */
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				lonePlayerInstance->wPress = true;
				break;
			case SDLK_d:
				lonePlayerInstance->dPress = true;
				break;
			case SDLK_a:
				lonePlayerInstance->aPress = true;
				break;
			case SDLK_s:
				lonePlayerInstance->sPress = true;
				break;
			case SDLK_e:
				checkIfShouldInteract();
				break;
			case SDLK_BACKQUOTE:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				lonePlayerInstance->wPress = false;
				break;
			case SDLK_s:
				lonePlayerInstance->sPress = false;
				break;
			case SDLK_a:
				lonePlayerInstance->aPress = false;
				break;
			case SDLK_d:
				lonePlayerInstance->dPress = false;
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			int x, y;
			SDL_GetMouseState(&x, &y);
			gui.checkIfButtonClicked(x, y);
		}
	}
}
