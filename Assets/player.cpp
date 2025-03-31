#include <iostream>
#include <SDL_image.h>
#include "player.h"

Player::Player(Graphic& graphic, float startX, float startY, SDL_Texture* character_sprite) : graphic(graphic), position(startX, startY), character_sprite(nullptr) {}

Player::~Player() {
    if (character_sprite) {
        SDL_DestroyTexture(character_sprite);
        character_sprite = nullptr;
    }
}

SDL_Texture* Player::getSprite() {
    return this->character_sprite;
}

void Player::setSprite(const std::string& filePath) {
    SDL_Texture* sprite = graphic.loadTexture(filePath);
    this->character_sprite = sprite;
}

void Player::render() {
    if (character_sprite) {
        SDL_Rect dst = {velocityX, velocityY, 50, 50}; // Example size
        SDL_RenderCopy(graphic.getRenderer(), character_sprite, NULL, &dst);
    }
}