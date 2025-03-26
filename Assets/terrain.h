#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL_image.h>
#include "Game/graphic.h"
#include <string>

class Terrain : public Graphic {
    private:
        int x;
        int y;
        SDL_Texture* terrain_sprite;
        Graphic& graphics;
    public:
        Terrain(Graphic& graphics);
        SDL_Texture* getSprite();
        void setSprite(SDL_Texture* sprite);
        Terrain setTerrain(int x, int y, const std::string& filePath);
        std::pair<int, int> getPos();
        void setPos(int x, int y);
        void deleteTerrain();
};

#endif