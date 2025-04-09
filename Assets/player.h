#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL_image.h>
#include <string.h>
#include <string>
#include "graphic.h"
#include "vector2.h"
#include "terrain.h"

class Player : public Graphic{
    protected:
        SDL_Texture* character_sprite;
        Graphic& graphic;

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
        const float RESPAWN_DURATION = 5.0f;

        Vector2 sideCheckSize = Vector2(50, 4);
        Vector2 groundCheckSize = Vector2(20, 2);
    public:
        Vector2 position;
        Vector2 velocity;
        Player(Graphic& graphic, float startX, float startY, SDL_Texture* character_sprite);
        ~Player();

        void update(float deltaTime);
        void setPos(float x, float y) {this->position = {x,y};};
        Vector2 getPos() {
            return this->position;
        }

        void setSprite(const std::string& filePath);
        // Terrain setTerrain(int newX, int newY, SDL_Texture* sprite);
        SDL_Texture* getSprite();
        void render();

        void handleInput(const SDL_Event& e);
        void applyGravity(float deltaTime);
        bool checkCollision(const SDL_Rect& playerRect, const SDL_Rect& terrainRect);

        SDL_Rect getPlayerRect() {
            SDL_Rect playerRect = {static_cast<int>(position.x), static_cast<int>(position.y), frameWidth, frameHeight};
            return playerRect;
        }

        SDL_Rect getsidecheckRect() {
            SDL_Rect sideCheckRect = {static_cast<int>(position.x + 9), static_cast<int>(position.y + 22), static_cast<int>(sideCheckSize.x), static_cast<int>(sideCheckSize.y)};
            return sideCheckRect;
        }

        SDL_Rect getGroundcheckRect() {
            SDL_Rect groundCheckRect = {static_cast<int>(position.x + 15), static_cast<int>(position.y + frameHeight - 1), static_cast<int>(groundCheckSize.x), static_cast<int>(groundCheckSize.y)};
            return groundCheckRect;
        }
        void respawn();
};      

#endif