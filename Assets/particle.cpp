#include "particle.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

// Function to generate a random float within a range
float randomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

// Function to generate a random integer within a range
int randomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// Function to create a particle
Particle createParticle(float x, float y, SDL_Texture* texture, float minSize, float maxSize) {
    Particle p;
    p.x = x;
    p.y = y;
    p.vx = randomFloat(-2.0f, 2.0f); // Initial velocity
    p.vy = randomFloat(-2.0f, 2.0f);
    p.lifetime = randomInt(60, 120); // Lifetime of the particle (in frames)
    p.texture = texture;
    p.size = randomFloat(minSize, maxSize); // Random size
    p.originalSize = p.size;
    p.alpha = 255;
    return p;
}

// Function to update a particle
void updateParticle(Particle& p) {
    p.x += p.vx;
    p.y += p.vy;
    p.lifetime--;
    p.size -= p.originalSize / 60.0f; // Example shrinking over 60 frames
    p.alpha = (p.lifetime > 60) ? 255 : (p.lifetime * 255 / 60); // Fade out
    if (p.size < 0) p.size = 0;
}

// Function to draw a particle
void drawParticle(SDL_Renderer* renderer, const Particle& p) {
    if (p.lifetime <= 0 || p.size <= 0) return; // Don't draw dead particles

    SDL_Rect destRect;
    destRect.x = static_cast<int>(p.x - p.size / 2); // Center the particle
    destRect.y = static_cast<int>(p.y - p.size / 2);
    destRect.w = static_cast<int>(p.size);
    destRect.h = static_cast<int>(p.size);

    SDL_SetTextureAlphaMod(p.texture, static_cast<Uint8>(p.alpha));
    SDL_RenderCopy(renderer, p.texture, NULL, &destRect);
    SDL_SetTextureAlphaMod(p.texture, 255); // Reset
}