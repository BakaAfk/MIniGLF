//
// Created by Baka-tannn on 22/2/2025.
//

#include <SDL.h>
#include <cmath>
#include "game.h"
#include "globalVar.h"
#include "gameRenderer.h"
#include "map.h"
#include "vector.h"
#include "audio.h"
#include "textureLoader.h"
#include "eventHandler.h"


SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;


Map* Game::map = nullptr;
bool Game::running = false;

Game::Game() {}

Game::~Game() {
    clean();
}

GameState Game::getState() const { // Get state
    return gameState;
}

void Game::setState(GameState state) { // Set state
    gameState = state;
}

void Game::resetStat() { // Reset stat after game over
    stroke = 0;
    totalStroke = 0;
    avgStroke = 0;
    mapCount = 1;
    if (map) {
        delete map;
        map = nullptr;
    }
    map = new Map();
}
void Game::init() { // Initialize game
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH ,SCREEN_HEIGHT , 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (TTF_Init() == -1) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Khong the khoi tao TTF", nullptr);
        }
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 132, 171, 60, 255);
        }
        running = true;
        gameState = START_SCREEN;
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Audio("resources/sfx/bg.mp3", -1, 10);
}

void Game::handleEvent() { // Event handler
    EventHandler::handleEvent(this);

}

void Game::update() { // Game updater
    if (map && map->getBall()) {
        map->getBall()->update();
    }
}

void Game::render() { // Game renderer
    SDL_RenderClear(renderer);
    switch (gameState) {
        case START_SCREEN:
            GameRenderer::renderMainScreen();
            break;
        case PLAYING:
            GameRenderer::renderPlayingScreen(isDragging, map, map->getBall(), endX, endY);
            break;
        case PAUSE:
            GameRenderer::renderPauseScreen();
            break;
        case GAME_OVER:
            GameRenderer::renderGameOver();
            break;
        case EXIT:
            running = false;
            break;
    }
    SDL_RenderPresent(renderer);
}

void Game::clean() { // Clean before exit
    TextureLoader::clearCache();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    if (map) {
        delete map;
        map = nullptr;
    }
    Mix_CloseAudio();
    SDL_Quit();
    TTF_Quit();

}

bool Game::isRunning() {
    return running;
}


