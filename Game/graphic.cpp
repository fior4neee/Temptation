#include "graphic.h"
#include <SDL.h>
#include <SDL_image.h>

void Graphic::initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logErrorAndExit("Error at Init: ", SDL_GetError());
    }
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        logErrorAndExit("SDL_Image Error: ", IMG_GetError());
    }

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        logErrorAndExit("CreateWindow Error: ", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == nullptr){

        std::cout << "Error creating renderer" << SDL_GetError() << std::endl;
        return;
    }
}

void Graphic::quitSDL() {
    if(texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* Graphic::loadTexture( const std::string filepath) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(filepath.c_str());
    if (!loadedSurface) {
        logErrorAndExit("Loaded Surface Error: ", IMG_GetError());
    }
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!newTexture) {
        logErrorAndExit("Texture Error: ", SDL_GetError());

        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void Graphic :: logErrorAndExit(const char* msg, const char* error){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}
