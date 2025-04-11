#include "particle.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

float randomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

int randomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

Particle createParticle(float x, float y, SDL_Texture* texture, float minSize, float maxSize) {
    Particle p;
    p.x = x;
    p.y = y;
    p.vx = randomFloat(-2.0f, 2.0f); 
    p.vy = randomFloat(-2.0f, 2.0f);
    p.lifetime = randomInt(60, 120); 
    p.texture = texture;
    p.size = randomFloat(minSize, maxSize); 
    p.originalSize = p.size;
    p.alpha = 255;
    return p;
}

void updateParticle(Particle& p) {
    p.x += p.vx;
    p.y += p.vy;
    p.lifetime--;
    p.size -= p.originalSize / 60.0f; 
    p.alpha = (p.lifetime > 60) ? 255 : (p.lifetime * 255 / 60); 
    if (p.size < 0) p.size = 0;
}

void drawParticle(SDL_Renderer* renderer, const Particle& p) {
    if (p.lifetime <= 0 || p.size <= 0) return; 

    SDL_Rect destRect;
    destRect.x = static_cast<int>(p.x - p.size / 2); 
    destRect.y = static_cast<int>(p.y - p.size / 2);
    destRect.w = static_cast<int>(p.size);
    destRect.h = static_cast<int>(p.size);

    SDL_SetTextureAlphaMod(p.texture, static_cast<Uint8>(p.alpha));
    SDL_RenderCopy(renderer, p.texture, NULL, &destRect);
    SDL_SetTextureAlphaMod(p.texture, 255); 
}