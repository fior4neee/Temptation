#include <iostream>
#include <SDL.h>
#include "graphic.h"

int main(int argc, char* argv[]) {
    Graphic game;
    game.initSDL(1200, 800, "Temptation");

    SDL_Renderer* renderer = game.getRenderer(); 
    game.initMenu();
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            // std::cout << "Event Type: " << e.type << std::endl;
            game.handleEvents(e);
            if (e.type == SDL_QUIT) {
                running = false; break;
            }
            // if (e.type == SDL_MOUSEMOTION) {
            //     std::cout << e.motion.x << " " << e.motion.y << std::endl;
            // }
        }
        
        SDL_RenderClear(renderer); 
        game.renderMenu(renderer);
        SDL_RenderPresent(renderer);
    }

    game.quitSDL();
    return 0;
}
