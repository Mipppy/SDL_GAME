// #ifndef CONSOLE_HPP
// #define CONSOLE_HPP
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
// class Console {
//   public:
//     bool loaded = false;
//     bool displayed = false;
//     int messagesDisplayed = 0;
//     TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
//     SDL_Color White = {255, 255, 255};
//     SDL_Window* consoleWindow;
//     SDL_Renderer* consoleRenderer;
//     void loadConsole();
//     void printToConsole(const char* p_text, SDL_Color p_colorHex);
//     void hideConsole();
//     void showConsole();
//     void shouldShowOrHide();
//     void whileOpen();
//     Console();
//     ~Console();
// };

// #endif