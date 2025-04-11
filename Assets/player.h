#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL_image.h>
#include <string.h>
#include <string>
#include "graphic.h"
#include "checkpoint.h"
#include "vector2.h"
#include "terrain.h"
#include "particle.h"

class Player {
    protected:
        int velocityX;
        int velocityY;
        SDL_Texture* character_sprite;
        SDL_Texture* particleTexture;
        Graphic& graphic;
<<<<<<< Updated upstream
=======

        int frameWidth = 50;
        int frameHeight = 50;
        int currentFrame = 0;
        int frameCount = 4; // 	Total number of frames in animation
        int frameDelay = 8;
        int delayCounter = 0;

        bool onGround = false;
        float gravity = 980.0f;
        float jumpForce = -500.0f;
        bool wantsToDrop = false;//

        bool isRespawning = false;
        float respawnCooldown = 0.0f;
        const float RESPAWN_DURATION = 2.0f;

        bool isWin = false;

        Vector2 groundCheckSize = Vector2(24, 2);
        SDL_Color hitboxColor = { 255, 255, 0, 100 };

        // Player death particles
        std::vector<Particle> particles;
        float minParticleSize = 5.0f;
        float maxParticleSize = 15.0f;
        int numParticles = 100;
        float minSizeFactor = 0.1f;
>>>>>>> Stashed changes
    public:
        Vector2 position;
        Vector2 velocity;
        Player(Graphic& graphic, float startX, float startY, SDL_Texture* character_sprite);
        ~Player();

        void update(float deltaTime) {
            position += velocity * deltaTime;
        }
        void setPos(Vector2 position) {
            this->position = position;
        }

        Vector2 getPos() {
            return this->position;
        }

        SDL_Texture* getSprite(Player player);
        void setSprite(const std::string& filePath);
        // Terrain setTerrain(int newX, int newY, SDL_Texture* sprite);
        SDL_Texture* getSprite();
        void render();
<<<<<<< Updated upstream
=======
        void setParticleTexture(const std::string& filePath);

        void handleInput(const SDL_Event& e);
        void applyGravity(float deltaTime);
        bool checkCollision(const SDL_Rect& playerRect, const SDL_Rect& terrainRect);
        void handlePlayerDeath(float playerX, float playerY, SDL_Texture* particleTexture, std::vector<Particle>& particles, float minParticleSize, float maxParticleSize, int numParticles);
        void dustExplosion();

        SDL_Rect getPlayerRect() {
            SDL_Rect playerRect = {static_cast<int>(position.x), static_cast<int>(position.y), frameWidth, frameHeight};
            return playerRect;
        }

        SDL_Rect getGroundcheckRect() {
            SDL_Rect groundCheckRect = {static_cast<int>(position.x + 15), static_cast<int>(position.y + frameHeight - 1), static_cast<int>(groundCheckSize.x), static_cast<int>(groundCheckSize.y)};
            return groundCheckRect;
        }
        void respawn();
        void handleWin();
>>>>>>> Stashed changes
};      

#endif