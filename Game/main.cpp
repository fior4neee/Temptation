#include <iostream>
#include <SDL.h>
#include "graphic.h"

int main(int argc, char* argv[]) {
    Graphic game;
    game.initSDL(1000, 800, "Temptation");

    SDL_Renderer* renderer = game.getRenderer(); 

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        SDL_RenderClear(renderer); 
        game.renderLevel(renderer, 1);
        SDL_Texture* hello = game.loadTexture("Imgs/Hello.png");
        game.renderTexture(hello, 110, 200, 630, 500);
        SDL_RenderPresent(renderer);
    }

    game.quitSDL();
    return 0;
}
