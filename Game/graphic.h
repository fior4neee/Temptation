#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include "vector2.h"

class Terrain;
class Button;
<<<<<<< Updated upstream
=======
class Player;
class Checkpoint;
>>>>>>> Stashed changes

enum GameState {
    MENU,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_4,
    LEVEL_5,
    QUIT
};

class Graphic {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Surface* loadedSurface;
<<<<<<< Updated upstream
=======

    Player* player;
>>>>>>> Stashed changes
    std::vector<Button*> buttons;
    std::vector<Terrain*> terrains;
    Checkpoint* checkpoint;
    GameState gameState;
<<<<<<< Updated upstream
=======

    SDL_Texture* background_texture;
    SDL_Texture* newBGTexture;
>>>>>>> Stashed changes

    SDL_Rect cameraRect = {0, 0, 0, 0};
    int screenWidth;
    int screenHeight;
public:
    Graphic() : window(nullptr), renderer(nullptr), texture(nullptr), loadedSurface(nullptr), gameState(MENU) {} // Constructor initializing pointers to nullptr
    ~Graphic(); // Destructor to clean up resources

    void initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE = "Temptation");
    void quitSDL();
    void logErrorAndExit(const char* msg, const char* error);
    GameState getGameState() {return gameState;};
    void setGameState(GameState state) {this -> gameState = state;};
    SDL_Texture* loadTexture(const std::string& filepath);
    SDL_Renderer* getRenderer() {return renderer;};

    void initMenu();
    void renderMenu(SDL_Renderer* renderer);
    void renderLevel(SDL_Renderer* renderer, GameState gameState);
    void renderTexture(SDL_Texture* texture, int x, int y, int w, int h, bool useCamera);
    void renderTexture(SDL_Texture* texture, const SDL_Rect* srcRect, int x, int y, int w, int h, bool useCamera);
    void deleteTexture();
    // void handleEvent(const SDL_Event& e);

    void handleEvents(const SDL_Event& e);
<<<<<<< Updated upstream
    void modulateTextureColor(SDL_Texture* texture, Uint8 red, Uint8 green, Uint8 blue);

    void createTerrain(const std::string& filePath, float x, float y);
=======
    void setPlayer(Player* player) {this->player = player;};
    void setCheckpoint(Checkpoint* checkpoint) {this->checkpoint = checkpoint;}
    Checkpoint* getCheckpoint() {return checkpoint;}
    const SDL_Rect& getCameraRect() const {return cameraRect;}
    void modulateTextureColor(SDL_Texture* texture, Uint8 red, Uint8 green, Uint8 blue);

    // update camera
    void updateCamera(int playerX, int screenWidth, int levelWidth);

    void createTerrain(const std::string& filePath, float x, float y, Vector2 offset, Vector2 collisionBox, bool canKill);
    std::vector<Terrain*> getTerrains() {return terrains;};
>>>>>>> Stashed changes
    bool loadTerrain(const std::string& filePath);
    void saveTerrain(const std::string& terrainFilePath);
    bool initLevel(GameState gameState);
    void freeTextures();
};

#endif
