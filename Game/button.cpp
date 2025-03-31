#include <string>
#include "button.h"

Button::Button(Graphic& graphic, const std::string& imagePath, int x, int y, int w, int h, GameState gameState)
        : graphic(graphic), renderer(graphic.getRenderer()), rect{x,y,w,h}, gameState(gameState) {
            texture = graphic.loadTexture(imagePath); this->x = x; this->y = y; this->w = w; this->h = h; 
        }

GameState Button::getGameState() {
    return this->gameState;
}

SDL_Texture* Button::getTexture() {
    return this->texture;
}

void Button::render() {
    if (texture) {
        graphic.renderTexture(texture, rect.x, rect.y, rect.w, rect.h);
        // std::cout << "Rendering successful: " << texture << "\n";
    } else {
        std::cout << "Button Error: " << SDL_GetError();
    }
}

void Button::handleEvent(const SDL_Event& e) {
    // std::cout << "Button Event: " << e.type << std::endl;
    if (e.type == SDL_MOUSEMOTION) {
        handleMouseMotion(e);
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        handleMouseClick(e);
    } else {
        // std::cout << "At Button: " << this->getGameState() << " ";
        // logErrorAndExit("Button Event Error: ", SDL_GetError());
    }
}

void Button::handleMouseMotion(const SDL_Event& e) {
    if (isWithinBounds(e.motion.x, e.motion.y)) {
        modulateTextureColor(this->texture, 255, 0, 0);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        
    } else {
        modulateTextureColor(this->texture, 255, 255, 255);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
}

void Button::handleMouseClick(const SDL_Event& e) {
    if (isWithinBounds(e.button.x, e.button.y)) {
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.clicks == 2) {
            std::cout << "Double click detected at Button " << this->getGameState() << "!\n";
            try {
                initLevel(this->getGameState());
            } catch (std::exception& e) {
                std::cout << "Error found with initLevel " << e.what() << "!\n"; 
            } 
        }
    }
}

// void Button::changeLevel(GameState gameState) {
//     switch (gameState) {
//         case MENU:
//             std::cout << "Switching to Menu\n";
//             graphic.renderMenu(renderer);
//             break;
//         case LEVEL_1:
//         case LEVEL_2:
//         case LEVEL_3:
//         case LEVEL_4:
//         case LEVEL_5:
//             std::cout << "Switching to Level " << (gameState - LEVEL_1 + 1) << "\n";
//             graphic.initLevel(gameState);
//             graphic.renderLevel(renderer, (int)(gameState - LEVEL_1 + 1));
//             break;
//         case QUIT:
//             std::cout << "Quitting Game...\n";
//             SDL_Quit();
//             break;
//         default:
//             std::cout << "Unknown button type\n";
//     }
// }