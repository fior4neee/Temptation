#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include <string>
#include <string.h>
#include "terrain.h"
#include <fstream>

Terrain::Terrain (Graphic& graphic, float positionX, float positionY, SDL_Texture* sprite) : graphic(graphic), renderer(graphic.getRenderer()), position(positionX, positionY), terrain_sprite(sprite) {
    rect = { (int) positionX, (int)positionY, 50, 50 };
}

SDL_Texture* Terrain::getSprite() {
    return terrain_sprite;
}

Terrain::~Terrain() {
    if (terrain_sprite) {
        SDL_DestroyTexture(terrain_sprite);
        terrain_sprite = nullptr;
    }
}

void Terrain::setSprite(SDL_Texture* sprite) {
    this->terrain_sprite = sprite;
}

void Terrain::render() {
    if (terrain_sprite) {
        std::cout << "Rendering terrain " << terrain_sprite << "!\n"; 
        graphic.renderTexture(terrain_sprite, rect.x, rect.y, rect.w, rect.h);
    } else {
        std::cerr << "Terrain Render() Error: " << SDL_GetError() << " " << IMG_GetError();
    }
}

void Graphic::saveTerrain(const std::string& terrainFilePath) {
    std::ofstream myfile(terrainFilePath);
    for (auto terrain : terrains) {
        myfile << terrain->getTexturePath() << " " << terrain->position.x << " " << terrain->position.y << "\n";
    }
    myfile.close();
    // std::cout << "All terrain saved successfully!";
}

// void Graphic::createTerrain(const std::string& filePath, float x, float y) {
//     std::cout << "createTerrain called\n";
//     std::cout << this << std::endl;
//     SDL_Texture* temp_terrain = loadTexture(filePath.c_str());
//     terrains.emplace_back(new Terrain(*this, x, y, temp_terrain));
// }