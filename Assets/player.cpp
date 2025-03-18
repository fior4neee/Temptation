#include <iostream>
#include <SDL_image.h>

class player {
    private:
        int x;
        int y;
        SDL_Texture* character_sprite;
    public:
        SDL_Texture* getSprite(player player);
        SDL_Texture* setSprite(player player);
        Terrain setTerrain();
        void updatePosition(int x, int y);
        player() 
        ?? getPos();
        ?? setPos();
};