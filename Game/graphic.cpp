#include "graphic.h"
#include <SDL.h>
#include <SDL_image.h>
#include "button.h"

void Graphic::initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logErrorAndExit("Error at Init: ", SDL_GetError());
    }
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        logErrorAndExit("SDL_Image Error: ", IMG_GetError());
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

SDL_Texture* Graphic::loadTexture(const std::string& filepath) {
    SDL_Surface* loadedSurface = IMG_Load(filepath.c_str());
    if (!loadedSurface) {
        logErrorAndExit("Loaded Surface Error: ", IMG_GetError());
        return nullptr;
    }

    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (!newTexture) {
        logErrorAndExit("Texture Error: ", SDL_GetError());
        return nullptr;
    }

    return newTexture;
}

void Graphic::renderTexture(SDL_Texture* texture, int x, int y, int w, int h) {
    if (!texture) {
        logErrorAndExit("Couldn't load texture: ", SDL_GetError());
    }

    SDL_Rect destRect = { x,y,w,h }; // positioning tool
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}


void Graphic::logErrorAndExit(const char* msg, const char* error){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphic::deleteTexture() {
    if (texture) {
        SDL_DestroyTexture(this->texture);
        texture = nullptr;
    }
}

void Graphic::handleEvents() {
    GameState gameState = MENU;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameState = QUIT;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_1: gameState = LEVEL_1; break;  // Press 1 to start Level 1
                // case SDLK_2: gameState = LEVEL_2; break;  // Press 2 to start Level 2
                case SDLK_ESCAPE: gameState = QUIT; break;
            }
        }
    }
}

void Graphic::renderMenu(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    SDL_RenderPresent(renderer);
}

void Graphic::renderLevel(SDL_Renderer* renderer, int levelNumber) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    std::string filePath = "Imgs/Menu/Levels/0" + std::to_string(levelNumber) + ".png";
    SDL_Texture* levelNumberImg = loadTexture(filePath.c_str());
    renderTexture(levelNumberImg, 100, 100, 64, 64);
    buttons.push_back(new Button(this, "Imgs/Menu/Buttons/Play.png", 500, 500, 64, 64));
    for (auto button : buttons) {
        button->render();
    }
}

void Graphic::renderButtons() {
    for (auto button: buttons) {
        button->render();
    }
}

Graphic::~Graphic() {
    quitSDL();
    for (auto& button : buttons) {
        delete button;
    }
}
