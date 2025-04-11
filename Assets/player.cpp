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

void Player::setParticleTexture(const std::string& filePath) {
    particleTexture = graphic.loadTexture(filePath);
}

void Player::render() {
    if (character_sprite) {
<<<<<<< Updated upstream
        SDL_Rect dst = {velocityX, velocityY, 50, 50}; // Example size
        SDL_RenderCopy(graphic.getRenderer(), character_sprite, NULL, &dst);
    }
=======
        SDL_Rect srcRect = {currentFrame * frameWidth, 0, frameWidth, frameHeight};
        // SDL_Rect dstRect = {(int)position.x, (int)position.y, frameWidth, frameHeight}; // Example size
        // SDL_RenderCopy(graphic.getRenderer(), character_sprite, &src, &dst);
        graphic.renderTexture(character_sprite, &srcRect, (int)position.x, (int)position.y, frameWidth, frameHeight, true);

        // Optional: Draw collision box
        SDL_Rect playerRect = this->getPlayerRect();
        const SDL_Rect& camera = graphic.getCameraRect();

        SDL_Rect playerScreenRect = {
            playerRect.x - camera.x,
            playerRect.y - camera.y,
            playerRect.w,
            playerRect.h
        };

        SDL_SetRenderDrawBlendMode(graphic.getRenderer(), SDL_BLENDMODE_BLEND); // Enable alpha blending
        SDL_SetRenderDrawColor(graphic.getRenderer(), hitboxColor.r, hitboxColor.g, hitboxColor.b, hitboxColor.a); // Yellow to Green, Semi-transparent
        SDL_RenderDrawRect(graphic.getRenderer(), &playerScreenRect);
        SDL_SetRenderDrawBlendMode(graphic.getRenderer(), SDL_BLENDMODE_NONE); // Disable alpha blending
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

void Player::handlePlayerDeath(float playerX, float playerY, SDL_Texture* particleTexture, std::vector<Particle>& particles,
    float minParticleSize, float maxParticleSize, int numParticles) {
    for (int i = 0; i < numParticles; ++i) {
        particles.push_back(createParticle(playerX, playerY, particleTexture, minParticleSize, maxParticleSize));
    }
}

void Player::dustExplosion() {
    SDL_Rect camera = graphic.getCameraRect();
    float correctX = position.x - camera.x + 25,
          correctY = position.y - camera.y + 25;

    handlePlayerDeath(correctX, correctY, particleTexture, particles, minParticleSize, maxParticleSize, numParticles);
}

void Player::applyGravity(float deltaTime) {
    if (velocity.y < 0.01f) {
        // If jumping up
        velocity.y += gravity * deltaTime;
    } else if (velocity.y > 0.01f ) {
        // If falling down, increased gravity
        velocity.y += gravity * deltaTime * 1.5f;
    } else {
        velocity.y = 0.0f; // Snap it cleanly
    }
}

static int frameCounter = 0;
void Player::update(float deltaTime) {
    // Update particles
    for (auto it = particles.begin(); it != particles.end();) {
        updateParticle(*it);
        if (it->lifetime <= 0 || it->size <= (it->originalSize * minSizeFactor)) {
            it = particles.erase(it);
        } else {
            drawParticle(graphic.getRenderer(), *it);
            ++it;
        }
    }

    if (isWin && onGround) {
        // std::cout << "Have won" << std::endl;
        if (!particles.empty()) {
            // wait
        } else {
            graphic.setGameState(MENU);
            isWin = false;
        }
        return;
    }

    // bool grounded = false;
    frameCounter++;
    if (isRespawning) {
        respawnCooldown -= deltaTime;
        if (respawnCooldown <= 0.0f) {
            isRespawning = false;
            respawnCooldown = 0.0f;
            this->setPos(0, 445);
            std::cout << "Respawn complete!\n";
        }
        return;
    }

    applyGravity(deltaTime);

    position.x += static_cast<int>(velocity.x * deltaTime);
    position.y += static_cast<int>(velocity.y * deltaTime);

    // if (onGround) {
    //     std::cout << "ON GROUND!\n";
    // } else {
    //     std::cout << "IN AIR! Velocity Y: " << velocity.y << "\n";
    // }

    SDL_Rect playerRect = this->getPlayerRect();

    Checkpoint* checkpointPtr = this->getCheckpoint();

    // SDL_Rect camera = graphic.getCameraRect();
    // if (&camera) {
    //     std::cout << playerRect.x << " " << playerRect.y << " " << camera.x << " " << camera.y << std::endl;
    // }

    if (checkpointPtr) {
        SDL_Rect checkpointRect = checkpointPtr->getCollisionRect();
        if (checkCollision(playerRect, checkpointRect)) {
            // IF CODITION FULFILLED THEN PLAYER HAVE WON
            // DO WHATEVER YOU WANT WHEN PLAYER WON
            //
            if (!isWin) {
                dustExplosion();
            }
            this->handleWin();
            //
            // std::cout << "Touched flag" << std::endl;
            hitboxColor.r = 0;
        } else {
            hitboxColor.r = 255;
        }
    } else {
        std::cerr << "Failed to fetch checkpoint" << std::endl;
    }
    
    if (position.y > 1000.0f) {
        std::cout << "Player fell out of bounds! Respawning...\n";
        respawn();
        return;
    }

    // Check vertical collision
    for (auto& terrain : graphic.getTerrains()) {
        SDL_Rect terrainRect = terrain->getRect();
        SDL_Rect groundCheckRect = this->getGroundcheckRect();
        // Check next frame
        SDL_Rect nextGroundCheckRect = groundCheckRect;
        SDL_Rect nextHeadbuttRect = groundCheckRect;
        nextGroundCheckRect.y += static_cast<int>(velocity.y * deltaTime);
        nextHeadbuttRect.y -= frameHeight + 1;

        // If collide next frame, velocity = 0
        if (checkCollision(nextGroundCheckRect, terrainRect)) {
            if (terrain->getCanKill()) {
                dustExplosion();
                std::cout << "Player hit spike and died!" << std::endl;
                respawn();
                break;
            }
            // std::cout << "Colliding with " << terrainRect.x << " " << terrainRect.y << "\n!";
            if (velocity.y > 0.1f) {
                velocity.y /= 2.0f;
            } else {
                velocity.y = 0;
            }
        }

        if (checkCollision(nextHeadbuttRect, terrainRect)) {
            if (terrain->getCanKill()) {
                dustExplosion();
                std::cout << "Player hit spike and died!" << std::endl;
                respawn();
                break;
            }
            position.y = terrainRect.y + frameHeight + 1;
            velocity.y = 50;
        }

        // Check if grounded
        if (checkCollision(groundCheckRect, terrainRect)) {
            // if (terrain->getCanKill()) {
            //     dustExplosion();
            //     std::cout << "Player hit spike and died!" << std::endl;
            //     respawn();
            //     break;
            // }

            float newY = terrainRect.y - frameHeight;
            onGround = true;

            // if stuck then snap up
            if (position.y > newY - 0.5f && position.y < newY + 12.0f) {
                position.y = newY;
            }
            break;
        } else {
            onGround = false;
        }
    }

    // Check horizontal collision
    for (auto& terrain : graphic.getTerrains()) {
        SDL_Rect terrainRect = terrain->getRect();
        SDL_Rect nextFrameRect = {playerRect.x + 9, playerRect.y + 5, playerRect.w - 18, playerRect.h - 10};
        nextFrameRect.x += static_cast<int>(velocity.x * deltaTime);

        if (checkCollision(nextFrameRect, terrainRect)) {
            if (terrain->getCanKill()) {
                dustExplosion();     
                std::cout << "Player hit spike and died!" << std::endl;
                respawn();
                break;
            }
            // std::cout << "Colliding with " << terrainRect.x << " " << terrainRect.y << "\n!";
            if (velocity.x > 0) {
                // If collide to the left of terrain
                position.x = terrainRect.x - frameWidth + 4;
            } else if (velocity.x < 0) {
                // If collide to the right of terrain
                position.x = terrainRect.x + frameWidth - 4;
            }
            velocity.x = 0;
            break;
        } 
    }

    // if (frameCounter % 200 == 0) {
    //     std::cout << "Player Y: " << position.y << " | Velocity Y: " << velocity.y << " X: " << position.x << " | Velocity X: " << velocity.x << "\n!";
    // }
    // onGround = grounded;
}

bool Player::checkCollision(const SDL_Rect& playerRect, const SDL_Rect& terrainRect) {
    return SDL_HasIntersection(&playerRect, &terrainRect);
}

void Player::respawn() {
    this->setPos(position.x,-100);
    velocity.x = 0;
    velocity.y = 0;
    isRespawning = true;
    respawnCooldown = RESPAWN_DURATION;
}

void Player::handleWin() {
    isWin = true;
>>>>>>> Stashed changes
}