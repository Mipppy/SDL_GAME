#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <map>
#include <vector>
#include <variant>
#include <string>
#include "sub/renderer.hpp"
#include "sub/entity.hpp"

bool running = true;
void EventHandler();

int main(int argc, char *argv[])
{
	Renderer rend;
	rend.initRenderer();
    std::map<const char*, const char*> mappings;
	std::map<const char*, std::pair<const char*, const char*>> mappings2;
	mappings.insert(std::make_pair("1", "resources/rock.png"));
    mappings2.emplace("1", std::make_pair("resources/rock.png", "ge"));
	char path[] = "resources/test.csv";
	char path2[] = "resources/teste.csv";
	std::vector<std::vector<std::string>> mapData = rend.loadFromCSV(path);
	std::vector<std::vector<std::string>> entityMapData = rend.loadFromCSV(path2);
	rend.renderCSVEntities(entityMapData, mappings2);
	while (running)
	{
		EventHandler();
		rend.clearRenderer();
		rend.renderCSVStaticObjects(mapData, mappings);
		rend.updateEntities();
		rend.displayRenderedObjects();
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
		}
	}
}