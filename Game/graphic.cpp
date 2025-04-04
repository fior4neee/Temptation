#include "graphic.h"
#include <SDL.h>
#include <SDL_image.h>
#include "button.h"
#include "terrain.h"
#include "player.h"
#include <fstream>

std::string getAssetPath(const std::string& filename) {
    std::string basePath = SDL_GetBasePath();
    return basePath + filename;
}

void Graphic::initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE) {
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
}

void Graphic::quitSDL() {
    if(texture) {
        SDL_DestroyTexture(texture);
        std::cout << "Texture destroyed successfully.\n";
        texture = nullptr;
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        std::cout << "Renderer destroyed successfully.\n";
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        std::cout << "Window destroyed successfully.\n";
        window = nullptr;
    }

    if (!buttons.empty()) {
        for (auto& button : buttons) {
            delete button;
        }
        std::cout << "Buttons destroyed successfully.\n";
    }
    IMG_Quit();
    SDL_Quit();
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

void Graphic::renderTexture(SDL_Texture* texture, int x, int y, int w, int h) {
    if (!texture) {
        logErrorAndExit("Couldn't load texture: ", SDL_GetError());
    }

    SDL_Rect destRect = { x,y,w,h }; // positioning tool
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
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
}

void Graphic::renderMenu(SDL_Renderer* renderer) {
    // std::cout << "Render Menu called. \n";
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    std::string backgroundIMG = "Imgs/Background/7481714.jpg";
    SDL_Texture* background_texture = loadTexture(backgroundIMG.c_str());
    renderTexture(background_texture, 0, 0, 1200, 800);
    for (auto button : buttons) {
        button->render();
    }
    // SDL_RenderPresent(renderer);
}

bool Graphic::initLevel(GameState gameState) {
    GameState initialGameState = this->getGameState();
    try {
        std::cout << "Calling initLevel on Graphic instance: " << this << " with Renderer: " << this->getRenderer() << std::endl;
        std::cout << "Init Level activated\n";
        switch(gameState) {
            case LEVEL_1:
                if (!loadTerrain("Assets/Terrain_Files/level1.txt")) return false;
                break;
            case LEVEL_2:
                if (!loadTerrain("Assets/Terrain_Files/level2.txt")) return false;
                break;
            case LEVEL_3:
                if (!loadTerrain("Assets/Terrain_Files/level3.txt")) return false;
                break;
            case LEVEL_4:
                if (!loadTerrain("Assets/Terrain_Files/level4.txt")) return false;
                break;
            case LEVEL_5:
                if (!loadTerrain("Assets/Terrain_Files/level5.txt")) return false;
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
    std::string newBGTest = "Imgs/Background/yrkGs9.png";
    SDL_Texture* newBGTexture = loadTexture(newBGTest.c_str());
    renderTexture(newBGTexture, 0, 0, 1200, 800);
    for (auto button : buttons) {
        button->render();
    }
}

void Graphic::createTerrain(const std::string& filePath, float x, float y) {
    // std::cout << "createTerrain called\n";
    // std::cout << "Renderer being passed into createTerrain: " << this->getRenderer() << std::endl;
    SDL_Texture* temp_terrain = loadTexture(filePath);
    terrains.emplace_back(new Terrain(*this, x, y, temp_terrain));
}

bool Graphic::loadTerrain(const std::string& filePath) {
    GameState initialGameState = this->getGameState();
    // std::cout << "Load terrain called with renderer: " << this->getRenderer() << std::endl;
    terrains.clear();
    std::ifstream myfile(filePath);
    std::string terrainFilePath;
    float tempX, tempY;
    if (!myfile.is_open()) {
        std::cerr << "Problem opening terrain file: " << filePath << std::endl;
        this->setGameState(initialGameState);
        return false; 
    }
    while (myfile >> terrainFilePath >> tempX >> tempY) {
        createTerrain(terrainFilePath, tempX, tempY);
    }
    myfile.close();
    for (auto terrain : terrains) {
        terrain->render();
    }
    return true; 
}

Graphic::~Graphic() {
    quitSDL();
    for (auto& button : buttons) {
        delete button;
    }
    for (auto& terrain : terrains) {
        delete terrain;
    }
}

void Graphic::modulateTextureColor(SDL_Texture* texture, Uint8 red, Uint8 green, Uint8 blue) {
    if (texture) {
        SDL_SetTextureColorMod(texture, red, green, blue);
    } else {
        std::cout << "Texture Color Modulation Failed: " << SDL_GetError() << std::endl;
    }    
}