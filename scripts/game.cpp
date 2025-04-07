//
// Created by Baka-tannn on 22/2/2025.
//

#include <SDL.h>
#include <cmath>
#include <fstream>
#include "game.h"
#include "globalVar.h"
#include "gameRenderer.h"
#include "map.h"
#include "audio.h"
#include "eventHandler.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Map* Game::map = nullptr;
bool Game::running = false;

Game::Game() {}

Game::~Game() {
    clean();
}

GameState Game::getState() const { // Get game state
    return gameState;
}

void Game::setState(GameState state) { // Set game state
    gameState = state;
}

void Game::resetStat() { // Reset game stats after game completion
    stroke = 0;
    totalStroke = 0;
    avgStroke = 0;
    mapCount = 1;
    havePowerUp = false;
    isPowerUp = false;
    if (map) {
        delete map;
        map = nullptr;
    }
}

void Game::init() { // Game initialization
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(
            TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0
        );
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (TTF_Init() == -1) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Khong the khoi tao TTF", nullptr);
        }

        if (!window) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Khong the khoi tao window", nullptr);
        }

        if (!renderer) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Khong the khoi tao renderer", nullptr);
        }

        std::ifstream fileInstructions("resources/instructions.txt"); // Open instructions text file
        if (!fileInstructions.is_open()) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Khong the mo file instructions", nullptr);
        }

        std::string line;
        while (std::getline(fileInstructions, line)) { // Read instructions line by line
            instructions.push_back(line);
        }
        fileInstructions.close();

        running = true;
        gameState = START_SCREEN; // Set game state to start screen
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); // Initialize audio channel for BGM
    Audio("resources/sfx/bg.mp3", -1, 10); // Play BGM
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

        case INSTRUCTIONS:
            GameRenderer::renderInstructions();
            break;

        case EXIT:
            running = false;
            break;
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() { // Clean up resources
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

bool Game::isRunning() { // Check if game is running
    return running;
}