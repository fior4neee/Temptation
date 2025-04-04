#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "graphic.h"

class Button : public Graphic {
    private:
        SDL_Rect rect;
        SDL_Texture* texture;
        Graphic& graphic;
        int x,y,w,h;
        GameState gameState;
    public: 
        Button(Graphic& graphic, const std::string& filePath, int x, int y, int w, int h, GameState gameState );
        ~Button() {};
        void render();
        Graphic& getGraphic() { return graphic; }        
        bool isWithinBounds(int x, int y) const {
            if (x < rect.x) return false;
            if (x > rect.x + rect.w) return false;
            if (y < rect.y) return false;
            if (y > rect.y + rect.h) return false;
            return true;
        }
        void handleEvent(const SDL_Event& e);
        void handleMouseMotion(const SDL_Event& e);
        void handleMouseClick(const SDL_Event& e);
        GameState getGameState();
        // void handleClick(); 
        // void changeLevel(GameState gameState);
        //debug:
        SDL_Texture* getTexture();
}; 

#endif