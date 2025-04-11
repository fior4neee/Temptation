#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL.h>

struct Particle {
    float x, y;           
    float vx, vy;      
    int lifetime;      
    SDL_Texture* texture; 
    float size;        
    float originalSize; 
    float alpha;
};
float randomFloat(float min, float max);
int randomInt(int min, int max);
Particle createParticle(float x, float y, SDL_Texture* texture, float minSize, float maxSize);
void updateParticle(Particle& p);
void drawParticle(SDL_Renderer* renderer, const Particle& p);

#endif