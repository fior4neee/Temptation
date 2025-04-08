#include <iostream>
#include <SDL_image.h>
#include "player.h"
#include <math.h> // fabs

Player::Player(Graphic& graphic, float startX, float startY, SDL_Texture* character_sprite) : graphic(graphic), position(startX, startY), character_sprite(character_sprite) {
    frameWidth = 50;
    frameHeight = 50;
    currentFrame = 0;
    velocity = {0, 0};
    onGround = false;
    jumpForce = -500.0f;
    gravity = 980.0f;
    wantsToDrop = false;
}

Player::~Player() {
    if (character_sprite) {
        SDL_DestroyTexture(character_sprite);
    }
}

SDL_Texture* Player::getSprite() {
    return this->character_sprite;
}

void Player::setSprite(const std::string& filePath) {
    character_sprite = graphic.loadTexture(filePath);
}

void Player::render() {
    if (character_sprite) {
        SDL_Rect src = {currentFrame * frameWidth, 0, frameWidth, frameHeight};
        SDL_Rect dst = {(int)position.x, (int)position.y, frameWidth, frameHeight}; // Example size
        SDL_RenderCopy(graphic.getRenderer(), character_sprite, &src, &dst);
    }
}

void Player::handleInput(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                // std::cout << "Left detected!\n";
                velocity.x = -200; 
                break;
            case SDLK_RIGHT: 
                velocity.x = 200; 
                break;
            case SDLK_UP:
            case SDLK_SPACE: 
                if (onGround) {
                    std::cout << "Jumping!\n";
                    velocity.y = jumpForce;
                }
                break;
            case SDLK_DOWN:
                if (onGround) {
                    wantsToDrop = true;
                    if (position.y >= 700) wantsToDrop = false;

                }
                if (velocity.x > 0) velocity.x = std::max(velocity.x - 50, 0.0f);
                else if (velocity.x < 0) velocity.x = std::min(velocity.x + 50, 0.0f);
                break;
        }
    } else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT: case SDLK_RIGHT: velocity.x = 0; break;
        }
    }
}

void Player::applyGravity(float deltaTime) {
    if (!onGround || fabs(velocity.y) > 0.01f) {
        velocity.y += gravity * deltaTime;
    } else {
        velocity.y = 0.0f; // Snap it cleanly
    }
}//
static int frameCounter = 0;
void Player::update(float deltaTime) {
    bool grounded = false;
    frameCounter++;
    if (isRespawning) {
        respawnCooldown -= deltaTime;
        if (respawnCooldown <= 0.0f) {
            isRespawning = false;
            respawnCooldown = 0.0f;
            std::cout << "Respawn complete!\n";
        }
        return;
    }

    applyGravity(deltaTime);
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // if (onGround) {
    //     std::cout << "ON GROUND!\n";
    // } else {
    //     std::cout << "IN AIR! Velocity Y: " << velocity.y << "\n";
    // }

    SDL_Rect playerRect = this->getPlayerRect();

    if (position.y > 1000.0f) {
        std::cout << "Player fell out of bounds! Respawning...\n";
        respawn();
        return;
    }

    for (auto& terrain : graphic.getTerrains()) {
        SDL_Rect terrainRect = terrain->getRect();
        if (checkCollision(playerRect, terrainRect)) {
            float newY = terrainRect.y - frameHeight;
            if (position.y > newY - 1.0f) {
                position.y = newY;
                velocity.y = 0;
                grounded = true;
            }
            break;
        }
    }

    // if (frameCounter % 20 == 0) {
    //     std::cout << "Player Y: " << position.y << " | Velocity Y: " << velocity.y << "\n";
    // }
    onGround = grounded;
}

bool Player::checkCollision(const SDL_Rect& playerRect, const SDL_Rect& terrainRect) {
    return SDL_HasIntersection(&playerRect, &terrainRect);
}

void Player::respawn() {
    this->setPos(50,700);
    velocity.x = 0;
    velocity.y = 0;
    isRespawning = true;
    respawnCooldown = RESPAWN_DURATION;
}