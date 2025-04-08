#include <iostream>
#include <SDL.h>
#include "graphic.h"
#include "player.h"

int main(int argc, char* argv[]) {
    Graphic game;
    game.initSDL(1200, 800, "Temptation");
    // std::cout << "New Graphic: " << &game << "\n";
    SDL_Renderer* renderer = game.getRenderer(); 
    game.initMenu();

    SDL_Texture* playerTexture = nullptr;
    Player* player = new Player(game, 50, 450, playerTexture);
    player->setSprite("Imgs/Main Characters/Mask Dude/Idle (32x32).png");
    game.setPlayer(player);

    // Start with the MENU state
    GameState currentState = MENU; 
    bool running = true;
    bool levelInitialized = false;
    SDL_Event e;
    Uint32 lastTicks = SDL_GetTicks();

    while (running) {
        Uint32 currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - lastTicks) / 1000.0f;
        lastTicks = currentTicks;
        while (SDL_PollEvent(&e)) {
            game.handleEvents(e);
            if (e.type == SDL_QUIT) {
                running = false; 
                break;
            }
            if (currentState >= LEVEL_1 && currentState <= LEVEL_5 && player) {
                player->handleInput(e);
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
                    player->setPos(0, 400);
                    levelInitialized = true;
                }
                game.renderLevel(renderer, currentState);
                if (player) {
                    player->render();
                    player->update(deltaTime);
                } else {
                    std::cerr << "Player not found!\n";
                }
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
