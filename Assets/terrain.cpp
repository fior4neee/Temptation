#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include <string>
#include <string.h>
#include "terrain.h"


Terrain::Terrain (Graphic& graphics) : graphics(graphics), x(0), y(0), terrain_sprite(nullptr) {}

SDL_Texture* Terrain::getSprite() {
    return this->terrain_sprite;
}

void Terrain::setSprite(SDL_Texture* sprite) {
    this->terrain_sprite = sprite;
}

Terrain Terrain::setTerrain(int newX, int newY, const std::string& filePath) {
    this->x = newX;
    this->y = newY;
    this->terrain_sprite = loadTexture(filePath);
}

void Terrain::setPos(int newX, int newY) {
    this->x = newX;
    this->y = newY;
}

void Terrain::deleteTerrain() {
    
}

