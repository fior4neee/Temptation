#include <string>
#include "button.h"

Button::Button(Graphic* graphic, const std::string& imagePath, int x, int y, int w, int h)
        : graphic(graphic), renderer(graphic->getRenderer()), rect{x,y,w,h} {
            texture = graphic->loadTexture(imagePath);
        }

void Button::render() {
    if (texture) {
        graphic->renderTexture(texture, rect.x, rect.y, rect.w, rect.h);
    } else {
        std::cout << "Button Error: " << SDL_GetError();
    }
}

bool Button::isClicked(int mouseX, int mouseY) {
    return mouseX >= rect.x && mouseX <= rect.x + rect.w &&
           mouseY >= rect.y && mouseY <= rect.y + rect.h;
}
