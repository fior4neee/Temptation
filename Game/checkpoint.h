#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "graphic.h"

const int NUM_FRAMES = 10;
const int ANIMATION_SPEED = 6;

class Checkpoint : public Graphic {
    private:
        SDL_Rect rect;
        SDL_Texture* texture = nullptr;
        Graphic& graphic;
        GameState gameState;

        SDL_Rect collisionBox;
        SDL_Rect animationFrames[NUM_FRAMES];
        int currentFrame = 0;
        int frameCounter = 0;

    public:
        Checkpoint(Graphic& graphic, const std::string& imagePath, Vector2 position, SDL_Rect collisionBox);
        ~Checkpoint() {};
        void render();
        Graphic& getGraphic() { return graphic; }   
        SDL_Texture* getTexture();

        void update(float deltaTime);

        const SDL_Rect& getCollisionRect() const;
        void setGameState(GameState newState);
        GameState getGameState() const;

        // Function to clean up texture
        void free() {
            if (texture) {
                SDL_DestroyTexture(texture);
                texture = nullptr;
            }
        }
};

#endif