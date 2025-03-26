#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

class Button;

class Graphic {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Surface* loadedSurface;
    enum GameState {
        MENU,
        LEVEL_1,
        QUIT
    };
    std::vector<Button*> buttons;

public:
    Graphic() : window(nullptr), renderer(nullptr), texture(nullptr), loadedSurface(nullptr) {} // Constructor initializing pointers to nullptr
    ~Graphic(); // Destructor to clean up resources

    void initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE = "Temptation");
    void quitSDL();
    void logErrorAndExit(const char* msg, const char* error);
    
    SDL_Texture* loadTexture(const std::string& filepath);
    SDL_Renderer* getRenderer() {return renderer;};

    void renderMenu(SDL_Renderer* renderer);
    void renderLevel(SDL_Renderer* renderer, int levelNumber);
    void renderTexture(SDL_Texture* texture, int x, int y, int w, int h);
    void renderButtons();
    void deleteTexture();
    void handleEvents();
};

#endif
