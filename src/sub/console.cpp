// #include "console.hpp"
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>

// Console::Console() {}
// Console::~Console() {
//     SDL_DestroyRenderer(consoleRenderer);
//     SDL_DestroyWindow(consoleWindow);
// }
// void Console::loadConsole()
// {
//     if (!loaded)
//     {
//         loaded = true;
//         consoleWindow = SDL_CreateWindow("Debug Console", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1800 / 2, 720 / 2, SDL_WINDOW_SHOWN);
//         consoleRenderer = SDL_CreateRenderer(consoleWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//         SDL_SetRenderDrawColor(consoleRenderer, 169, 169, 169, 255);
//         hideConsole();
//     }
// }
// void Console::showConsole()
// {
//     if (loaded && !displayed)
//     {
//         displayed = true;
//         SDL_ShowWindow(consoleWindow);
//         SDL_RaiseWindow(consoleWindow);
//     }
// }
// void Console::printToConsole(const char *p_text, SDL_Color p_colorHex)
// {
//     if (loaded)
//     {
//         SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, p_text, p_colorHex);
//         SDL_Texture *Message = SDL_CreateTextureFromSurface(consoleRenderer, surfaceMessage);
//         SDL_Rect Message_rect;
//         Message_rect.x = 10;
//         Message_rect.y = 10 + (messagesDisplayed * 100);
//         Message_rect.w = 880;
//         Message_rect.h = 100;
//     }
// }
// void Console::hideConsole()
// {
//     if (loaded && displayed)
//     {
//         displayed = false;
//         SDL_HideWindow(consoleWindow);
//     }
// }
// void Console::shouldShowOrHide()
// {
//     if (loaded && !displayed)
//     {
//         showConsole();
//     }
//     else if (loaded && displayed)
//     {
//         hideConsole();
//     }
// }
// void Console::whileOpen()
// {
//     if (loaded)
//     {

//     }
// }