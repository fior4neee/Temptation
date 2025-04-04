#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <SDL_image.h>
#include "graphic.h"
#include "vector2.h"
#include <string>

class Terrain : public Graphic {
    protected:
        SDL_Rect rect;
        SDL_Texture* terrain_sprite;
        Graphic& graphic;
        SDL_Renderer* renderer;
        std::string texturePath;
    public:
        Vector2 position;
        // Vector2 velocity; maybe in the future blocks are meant to move. not right now though. i am dead
        Terrain(Graphic& graphic, float positionX, float positionY, SDL_Texture* sprite);
        ~Terrain();
        SDL_Texture* getSprite();
        void setSprite(SDL_Texture* sprite);
        void render();
        std::string getTexturePath() { return texturePath;}
};

#endif