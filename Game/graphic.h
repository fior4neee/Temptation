#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class Graphic {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

public:
    Graphic() : window(nullptr), renderer(nullptr) {} // Constructor initializing pointers to nullptr
    ~Graphic() { quitSDL(); }  // Destructor to clean up resources

    void initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE = "Temptation");
    void quitSDL();
    void renderTexture(SDL_Texture* texture, int x, int y, int w, int h);
    void logErrorAndExit(const char* msg, const char* error);

    SDL_Texture* loadTexture(const std::string filePath);
};

class Move {
    private:
        int x;
        int y;
    public:
};

#endif
