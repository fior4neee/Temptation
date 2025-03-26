#include <iostream>
#include <SDL_image.h>
#include "player.h"

Player::Player(Graphic& graphics) : graphics(graphics), x(0), y(0), character_sprite(nullptr) {}

Player::~Player() {
    if (character_sprite) {
        SDL_DestroyTexture(character_sprite);
    }
}

void Player::setPos(int newX, int newY) {
    this->x = newX;
    this->y = newY;
}

void Player::updatePosition(int dx, int dy) {
    x += dx;
    x += dy;
}

std::pair<int, int> Player::getPos() {
    return {x,y};
}

SDL_Texture* Player::getSprite() {
    return this->character_sprite;
}

void Player::setSprite(SDL_Texture* sprite) {
    this->character_sprite = sprite;
}

void Player::setPlayer(int newX, int newY, const std::string& filePath) {
    x = newX;
    y = newY;
    character_sprite = graphics.loadTexture(filePath);
}

void Player::render(SDL_Renderer* renderer) {
    if (character_sprite) {
        SDL_Rect dst = {x, y, 50, 50}; // Example size
        SDL_RenderCopy(renderer, character_sprite, NULL, &dst);
    }
}