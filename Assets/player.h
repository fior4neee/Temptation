#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL_image.h>
#include <string.h>
#include <string>
#include "graphic.h"
#include "vector2.h"
#include "terrain.h"

class Player {
    protected:
        int velocityX;
        int velocityY;
        SDL_Texture* character_sprite;
        Graphic& graphic;
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
};      

#endif