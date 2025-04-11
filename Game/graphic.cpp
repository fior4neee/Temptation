#include "graphic.h"
#include <SDL.h>
#include <SDL_image.h>
#include "button.h"
#include "terrain.h"
#include "player.h"
#include "checkpoint.h"
#include <fstream>

std::string getAssetPath(const std::string& filename) {
    std::string basePath = SDL_GetBasePath();
    return basePath + filename;
}

void Graphic::initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE) {
    this->screenWidth = SCREEN_WIDTH;
    this->screenHeight = SCREEN_HEIGHT;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logErrorAndExit("Error at Init: ", SDL_GetError());
    }
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        logErrorAndExit("SDL_Image Error: ", IMG_GetError());
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        logErrorAndExit("CreateWindow Error: ", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    std::cout << "Yo bro u just created a new renderer " << renderer << std::endl;
    if(renderer == nullptr){
        std::cout << "Error creating renderer" << SDL_GetError() << std::endl;
        return;
    }

    cameraRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void Graphic::quitSDL() {
<<<<<<< Updated upstream
    if(texture) {
        SDL_DestroyTexture(texture);
        std::cout << "Texture destroyed successfully.\n";
        texture = nullptr;
=======
    if (player) {
        delete player;
        player = nullptr;
        std::cout << "Player successfully deleted.\n";
    } else {
        // std::cout << "Player was null.\n";
>>>>>>> Stashed changes
    }

    if (player->getCheckpoint()) {
        player->getCheckpoint()->free();
        checkpoint = nullptr;
        std::cout << "Checkpoint destroyed successfully.\n";
    } else {
        // std::cout << "Checkpoint was null.\n";
    }

    if (!buttons.empty()) {
        for (auto& button : buttons) { 
            delete button;
            button = nullptr; 
        }
        buttons.clear();
        std::cout << "Buttons destroyed successfully.\n";
    } else {
        // std::cout << "Buttons was null.\n";
    }

    if (!terrains.empty()) {
        for (auto& terrain : terrains) {
            delete terrain;
            terrain = nullptr;
        }
        terrains.clear();
        std::cout << "Terrains destroyed successfully.\n";
    } else {
        // std::cout << "Terrains was null.\n";
    }

    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        std::cout << "General texture destroyed successfully.\n";
    }
    if (background_texture) {
        SDL_DestroyTexture(background_texture);
        background_texture = nullptr;
        std::cout << "Menu background texture destroyed successfully.\n";
    }
     if (newBGTexture) {
        SDL_DestroyTexture(newBGTexture);
        newBGTexture = nullptr;
        std::cout << "Level background texture destroyed successfully.\n";
    }
 
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
        std::cout << "Renderer destroyed successfully.\n";
    } else {
        // std::cout << "Renderer was already null.\n"; 
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
        std::cout << "Window destroyed successfully.\n";
    } else { 
        // std::cout << "Window pointer was already null.\n"; 
    }
    
    IMG_Quit();
    SDL_Quit();

    std::cout << "SDL Quit completed.\n";
}

SDL_Texture* Graphic::loadTexture(const std::string& filepath) {
    SDL_Surface* loadedSurface = IMG_Load(filepath.c_str());
    // std::cout << "Renderer in loadTexture: " << renderer << std::endl;
    if (!loadedSurface) {
        logErrorAndExit("Loaded Surface Error: ", IMG_GetError());
        return nullptr;
    }

    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (!newTexture) {
        // logErrorAndExit("Texture Error: ", SDL_GetError());
        std::cerr << "Texture Error: " << SDL_GetError() << "!\n";
        return nullptr;
    }

    return newTexture;
}

<<<<<<< Updated upstream
void Graphic::renderTexture(SDL_Texture* texture, int x, int y, int w, int h) {
    if (!texture) {
        logErrorAndExit("Couldn't load texture: ", SDL_GetError());
    }

    SDL_Rect destRect = { x,y,w,h }; // positioning tool
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
=======
void Graphic::renderTexture(SDL_Texture* texture, int x, int y, int w, int h, bool useCamera) {
    renderTexture(texture, nullptr, x, y, w, h, useCamera);
>>>>>>> Stashed changes
}

void Graphic::renderTexture(SDL_Texture* texture, const SDL_Rect* srcRect, int x, int y, int w, int h, bool useCamera) {
    if (!texture) {
        std::cerr << "Attempted to render null texture!" << std::endl;
        return;
    }
    if (!renderer) {
        std::cerr << "Attempted to render with null renderer!" << std::endl;
       return;
    }
    
    SDL_Rect destRect;
    if (useCamera) {
        destRect = {x - cameraRect.x, y - cameraRect.y, w, h};
    } else {
        destRect = {x, y, w, h};
    }

    SDL_RenderCopy(renderer, texture, srcRect, &destRect);
}

void Graphic::updateCamera(int playerX, int screenWidth, int levelWidth) {
    cameraRect.x = playerX - screenWidth / 2;

    if (cameraRect.x < 0) {
        cameraRect.x = 0;
    }
    if (cameraRect.x > levelWidth - screenWidth) {
        cameraRect.x = levelWidth - screenWidth;
    }

    cameraRect.y = 0;
    // cameraRect.w = screenWidth;
    // cameraRect.h = screenHeight;
}

void Graphic::logErrorAndExit(const char* msg, const char* error){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    quitSDL();
}

void Graphic::deleteTexture() {
    if (texture) {
        SDL_DestroyTexture(this->texture);
        texture = nullptr;
    }
}

void Graphic::freeTextures() {
<<<<<<< Updated upstream
    for (auto& terrain : terrains) {
        if (terrain->getSprite()) {
            SDL_DestroyTexture(terrain->getSprite());
        }
    }
    terrains.clear(); 
    for (auto& button : buttons) {
        delete button;
    }
    buttons.clear();
=======
    // if (!terrains.empty()) {
    //     for (auto& terrain : terrains) {
    //         delete terrain;
    //     }
        terrains.clear();
    // }
    // if (!buttons.empty()) {
    //     for (auto& button : buttons) {
    //         delete button;
    //     }
        buttons.clear();
    // }

    // std::cout << "Cleared level-specific vectors (freeTextures called)." << std::endl;
>>>>>>> Stashed changes
}


void Graphic::handleEvents(const SDL_Event& e) {
    for (auto button : buttons) {
        button->handleEvent(e);    
    }
}

void Graphic::initMenu() {
    int horizontal = 150;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    std::string backgroundIMG = "Imgs/Background/7481714.jpg";
    SDL_Texture* background_texture = loadTexture(backgroundIMG.c_str());
    renderTexture(background_texture, 0, 0, 1200, 800);
    buttons.clear();

    for (int i = 1; i <= 5; i++) {
        std::string filePath = "Imgs/Menu/Levels/0" + std::to_string(i) + ".png";
        Button* temp_button = new Button(*this, filePath, horizontal, 100, 100, 100, static_cast<GameState>(LEVEL_1 + (i - 1)));
        buttons.push_back(temp_button);
        horizontal += 200;
    }

    buttons.push_back(new Button(*this, "Imgs/Menu/Buttons/Close.png", screenWidth - 50, 0, 50, 50, QUIT));
}

void Graphic::renderMenu(SDL_Renderer* renderer) {
    // std::cout << "Render Menu called. \n";
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
<<<<<<< Updated upstream
    std::string backgroundIMG = "Imgs/Background/7481714.jpg";
    SDL_Texture* background_texture = loadTexture(backgroundIMG.c_str());
    renderTexture(background_texture, 0, 0, 1200, 800);
=======
    // std::string backgroundIMG = "Imgs/Background/7481714.jpg";
    // SDL_Texture* background_texture = loadTexture(backgroundIMG.c_str());
    if (background_texture){
        renderTexture(background_texture, nullptr, 0, 0, screenWidth, screenHeight, false);
    }
>>>>>>> Stashed changes
    for (auto button : buttons) {
        button->render(false);
    }
    // SDL_RenderPresent(renderer);
}

bool Graphic::initLevel(GameState gameState) {
    GameState initialGameState = this->getGameState();
    try {
        // std::cout << "Calling initLevel on Graphic instance: " << this << " with Renderer: " << this->getRenderer() << std::endl;
        // std::cout << "Init Level activated\n";
        switch(gameState) {
            case LEVEL_1:
                if (!loadTerrain("Assets/Terrain_Files/level1.txt")) {
                    this->setGameState(initialGameState); 
                    return false;
                }
                break;
            case LEVEL_2:
                if (!loadTerrain("Assets/Terrain_Files/level2.txt")) {
                    this->setGameState(initialGameState); 
                    return false;
                }
                break;
            case LEVEL_3:
                if (!loadTerrain("Assets/Terrain_Files/level3.txt")) {
                    this->setGameState(initialGameState); 
                    return false;
                }
                break;
            case LEVEL_4:
                if (!loadTerrain("Assets/Terrain_Files/level4.txt")) {
                    this->setGameState(initialGameState); 
                    return false;
                }
                break;
            case LEVEL_5:
                if (!loadTerrain("Assets/Terrain_Files/level5.txt")) {
                    this->setGameState(initialGameState); 
                    return false;
                }
                break;
            case MENU:
            case QUIT:
                this->initMenu();
                break;
        }
        buttons.clear();
        buttons.push_back(new Button(*this, "Imgs/Menu/Buttons/Back.png", 10, 10, 48, 48, MENU));
        return true;  // Level loaded successfully
    } catch (const std::exception& e) {
        std::cerr << "Error in initLevel: " << e.what() << std::endl;
        this->setGameState(initialGameState);
    } catch (...) {
        std::cerr << "Unknown error in initLevel!" << std::endl;
    }
    
    return false;  // Return failure if anything breaks
}

void Graphic::renderLevel(SDL_Renderer* renderer, GameState gameState) {
    // std::cout << "Render level called.\n";
    // std::cout << "Renderer in renderLevel: " << this->renderer << std::endl;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
<<<<<<< Updated upstream
    std::string newBGTest = "Imgs/Background/yrkGs9.png";
    SDL_Texture* newBGTexture = loadTexture(newBGTest.c_str());
    renderTexture(newBGTexture, 0, 0, 1200, 800);
=======
    if (newBGTexture && newBGTexture != background_texture) {
        // int bgWidth, bgHeight;
        // SDL_QueryTexture(newBGTexture, NULL, NULL, &bgWidth, &bgHeight);

        // renderTexture(newBGTexture, nullptr, 0, 0, bgWidth, bgHeight, true);

        renderTexture(newBGTexture, nullptr, 0, 0, 1200, 800, false);
    } else {
        SDL_RenderClear(renderer);
    }

>>>>>>> Stashed changes
    for (auto button : buttons) {
        button->render(false);
    }

    for (auto terrain : terrains) {
        terrain->render();
    }
}

void Graphic::createTerrain(const std::string& filePath, float x, float y, Vector2 offset, Vector2 collisionBox, bool canKill) {
    // std::cout << "createTerrain called\n";
    // std::cout << "Renderer being passed into createTerrain: " << this->getRenderer() << std::endl;
    SDL_Texture* temp_terrain = loadTexture(filePath);
    terrains.emplace_back(new Terrain(*this, x, y, temp_terrain, offset, collisionBox, canKill));
}

bool Graphic::loadTerrain(const std::string& filePath) {
    GameState initialGameState = this->getGameState();
    // std::cout << "Load terrain called with renderer: " << this->getRenderer() << std::endl;
    std::ifstream myfile(filePath);
    std::string terrainFilePath;
    float tempX, tempY;
    Vector2 offset;
    Vector2 collisionBox;
    bool canKill;
    if (!myfile.is_open()) {
        std::cerr << "Problem opening terrain file: " << filePath << std::endl;
        this->setGameState(initialGameState);
        buttons.clear();
        buttons.push_back(new Button(*this, "Imgs/Menu/Buttons/Back.png", 10, 10, 48, 48, MENU));
        return false; 
    }
    while (myfile >> terrainFilePath >> tempX >> tempY >> offset.x >> offset.y >> collisionBox.x >> collisionBox.y >> canKill) {
        createTerrain(terrainFilePath, tempX, tempY, offset, collisionBox, canKill);
    }
    myfile.close();
    return true; 
}

Graphic::~Graphic() {
    quitSDL();
}

void Graphic::modulateTextureColor(SDL_Texture* texture, Uint8 red, Uint8 green, Uint8 blue) {
    if (texture) {
        SDL_SetTextureColorMod(texture, red, green, blue);
    } else {
        std::cout << "Texture Color Modulation Failed: " << SDL_GetError() << std::endl;
    }    
}