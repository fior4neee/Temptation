#include <iostream>
#include <SDL.h>
#include "graphic.h"
<<<<<<< Updated upstream

int main(int argc, char* argv[]) {
    Graphic game;
    game.initSDL(1200, 800, "Temptation");
    std::cout << "New Graphic: " << &game << "\n";
    SDL_Renderer* renderer = game.getRenderer(); 
    game.initMenu();

=======
#include "player.h"
#include "checkpoint.h"

const int TARGET_FPS = 60;
const float TARGET_FRAMETIME = 1000.0f / TARGET_FPS;
const float FIXED_DELTATIME = 1.0f / TARGET_FPS;

const int CHECKPOINT_OFFSET_X = -8;
const int CHECKPOINT_OFFSET_Y = -14;
const SDL_Rect CHECKPOINT_COLLISION_BOX = {7, 0, 36, 50};

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int LEVEL_WIDTH = 3000;

int main(int argc, char* argv[]) {
    Graphic game;
    game.initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, "Temptation");
    // std::cout << "New Graphic: " << &game << "\n";
    SDL_Renderer* renderer = game.getRenderer(); 
    game.initMenu();

    SDL_Texture* playerTexture = nullptr;
    Player* player = new Player(game, 50, 450, playerTexture);
    player->setSprite("Imgs/Main Characters/Mask Dude/Idle (32x32).png");
    player->setParticleTexture("Imgs/Other/Dust Particle.png");
    game.setPlayer(player);

    Checkpoint* checkpoint = new Checkpoint(game, "Imgs/Items/Checkpoints/Checkpoint/Checkpoint (Flag Idle)(64x64).png", {550 + CHECKPOINT_OFFSET_X, 700 + CHECKPOINT_OFFSET_Y}, CHECKPOINT_COLLISION_BOX);
    player->setCheckpoint(checkpoint);

>>>>>>> Stashed changes
    // Start with the MENU state
    GameState currentState = MENU; 
    bool running = true;
    bool levelInitialized = false;
    SDL_Event e;

    while (running) {
<<<<<<< Updated upstream
=======
        Uint32 frameStartTicks = SDL_GetTicks();

>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======

                if (player) {
                    player->render();
                    player->update(FIXED_DELTATIME);
                } else {
                    std::cerr << "Player not found!\n";
                }

                if (checkpoint) {
                    checkpoint->render();
                    checkpoint->update(FIXED_DELTATIME);
                } else {
                    std::cerr << "Checkpoint not found!\n";
                }

                game.updateCamera(player->getPos().x, SCREEN_WIDTH, LEVEL_WIDTH);

>>>>>>> Stashed changes
                break;
            case QUIT:
                running = false;
                break;
        }

        SDL_RenderPresent(renderer);

        Uint32 frameEndTicks = SDL_GetTicks();
        Uint32 frameDurationMs = frameEndTicks - frameStartTicks;

        if (frameDurationMs < TARGET_FRAMETIME) {
            Uint32 delayTime = static_cast<Uint32>(TARGET_FRAMETIME - frameDurationMs);
            SDL_Delay(delayTime);
        }

        lastTicks = SDL_GetTicks();
    }

    game.quitSDL();
    return 0;
}
