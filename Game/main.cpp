#include <iostream>
#include <SDL.h>
#include "graphic.h"

int main(int argc, char* argv[]) {
    Graphic game;
    game.initSDL(1200, 800, "Temptation");
    std::cout << "New Graphic: " << &game << "\n";
    SDL_Renderer* renderer = game.getRenderer(); 
    game.initMenu();

    // Start with the MENU state
    GameState currentState = MENU; 
    bool running = true;
    bool levelInitialized = false;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            game.handleEvents(e);
            if (e.type == SDL_QUIT) {
                running = false; 
                break;
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);
        GameState nextState = game.getGameState();
        if (nextState != currentState) {
            currentState = nextState;
            levelInitialized = false;
        }
        switch (currentState) {
            case MENU:
            if (!levelInitialized) {
                game.initMenu();
                levelInitialized = true;
            }
                game.renderMenu(renderer); // Render menu
                break;
            case LEVEL_1:
            case LEVEL_2:
            case LEVEL_3:
            case LEVEL_4:
            case LEVEL_5:
                if (!levelInitialized) {
                    game.initLevel(currentState); // Render the level
                    levelInitialized = true;
                }
                game.renderLevel(renderer, currentState);
                break;
            case QUIT:
                running = false;
                break;
        }

        SDL_RenderPresent(renderer);
    }

    game.quitSDL();
    return 0;
}
