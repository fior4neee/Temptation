#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "graphic.h"

class Button {
    private:
        SDL_Rect rect;
        SDL_Texture* texture;
        SDL_Renderer* renderer;
        Graphic* graphic;

    public: 
        Button(Graphic* graphic, const std::string& filePath, int x, int y, int w, int h );
        ~Button() { graphic->quitSDL(); };
        void render();
        bool isClicked(int mouseX, int mouseY);
};

#endif