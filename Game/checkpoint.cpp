#include <string>
#include <iostream>
#include "checkpoint.h"

Checkpoint::Checkpoint(Graphic& graphic, const std::string& imagePath, Vector2 position, SDL_Rect collisionBox) : graphic(graphic) {
    texture = graphic.loadTexture(imagePath);
    if (texture == nullptr) {
        // Handle error loading texture
        SDL_Log("Failed to load checkpoint texture: %s", SDL_GetError());
    }
    this->rect = { static_cast<int>(position.x), static_cast<int>(position.y), 64, 64 };
    this->collisionBox = collisionBox;
    this->collisionBox.x = static_cast<int>(position.x + collisionBox.x) + 10;
    this->collisionBox.y = static_cast<int>(position.y + collisionBox.y) + 16;

    // Define the individual frames within the texture
    for (int i = 0; i < NUM_FRAMES; ++i) {
        animationFrames[i].x = i * rect.w;
        animationFrames[i].y = 0;
        animationFrames[i].w = rect.w;
        animationFrames[i].h = rect.h;
    }
}

SDL_Texture* Checkpoint::getTexture() {
    return this->texture;
}

void Checkpoint::render() {
    if (texture) {
        SDL_Rect sourceRect = animationFrames[currentFrame];
        // SDL_Rect destRect = this->rect;
        // SDL_RenderCopy(graphic.getRenderer(), texture, &sourceRect, &destRect);
        graphic.renderTexture(texture, &sourceRect, this->rect.x, this->rect.y, this->rect.w, this->rect.h, true);

        // Optional: Draw collision box
        const SDL_Rect& camera = graphic.getCameraRect();
        SDL_Rect collisionScreenRect = {
            collisionBox.x - camera.x,
            collisionBox.y - camera.y,
            collisionBox.w,
            collisionBox.h
        };

        SDL_SetRenderDrawBlendMode(graphic.getRenderer(), SDL_BLENDMODE_BLEND); // Enable alpha blending
        SDL_SetRenderDrawColor(graphic.getRenderer(), 255, 0, 0, 100); // Red, semi-transparent
        // SDL_RenderDrawRect(graphic.getRenderer(), &collisionBox);
        SDL_RenderDrawRect(graphic.getRenderer(), &collisionScreenRect);
        SDL_SetRenderDrawBlendMode(graphic.getRenderer(), SDL_BLENDMODE_NONE); // Disable alpha blending
    }
}

void Checkpoint::update(float deltaTime) {
    frameCounter++;
    if (frameCounter >= ANIMATION_SPEED) {
        currentFrame = (currentFrame + 1) % NUM_FRAMES;
        frameCounter = 0;
    }
}

const SDL_Rect& Checkpoint::getCollisionRect() const {
    return collisionBox;
};

void Checkpoint::setGameState(GameState newState) {
    gameState = newState;
}

GameState Checkpoint::getGameState() const {
    return gameState;
}