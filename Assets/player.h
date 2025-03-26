#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL_image.h>
#include <string.h>
#include <string>
#include "Game/graphic.h"
#include "terrain.h"

class Player {
    private:
        int x;
        int y;
        SDL_Texture* character_sprite;
        Graphic& graphics;
    public:
        Player(Graphic& graphics);
        ~Player();

        SDL_Texture* getSprite(Player player);
        void setSprite(SDL_Texture* sprite);
        void setPlayer(int x, int y, const std::string& filePath);
        Terrain setTerrain(int newX, int newY, SDL_Texture* sprite);
        void updatePosition(int x, int y);
        std::pair<int, int> getPos();
        void setPos(int x, int y);
        SDL_Texture* getSprite();
        void Player::render(SDL_Renderer* renderer);
};      

#endif