#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL_image.h>

class player {
    private:
        int x;
        int y;
        SDL_Texture* character_sprite;
        Terrain playerTerrain;
    public:
        SDL_Texture* getSprite();
        void setSprite(SDL_Texture* sprite);
        Terrain setTerrain();
        void updatePosition(int x, int y);
        std::pair<int, int> getPos();
        void setPos(int x, int y);
};

#endif