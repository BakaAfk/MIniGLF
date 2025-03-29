//
// Created by Baka-tannn on 22/2/2025.
//

#include <iostream>
#include <cmath>
#include "game.h"
#include "textureLoader.h"
#include "textRenderer.h"
#include "globalVar.h"
#include "gameRenderer.h"
#include "map.h"
#include "vector.h"
#include "audio.h"


SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;


Map* Game::map = nullptr;
bool Game::running = false;

Game::Game() {}

Game::~Game() {
    clean();
}

GameState Game::getState() {
    return gameState;
}

void Game::setState(GameState state) {
    gameState = state;
}

void Game::resetStat() {
    stroke = 0;
    totalStroke = 0;
    avgStroke = 0;
    mapCount = 1;
    delete map;
    map = new Map();
}
void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH ,SCREEN_HEIGHT , 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (TTF_Init() == -1) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to initialize TTF", nullptr);
        }
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 132, 171, 60, 255);
        }
        running = true;
        gameState = START_SCREEN;
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    map = new Map();
    Audio("resources/sfx/bg.mp3", -1, 10);
}

void Game::handleEvent() {
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            running = false;
        break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    if (getState() == PLAYING) {
                        setState(PAUSE);
                    } else if (getState() == PAUSE) {
                        setState(PLAYING);
                    } else if (getState() == START_SCREEN) {
                        setState(EXIT);
                    }
                break;

                case SDLK_RETURN:
                    if (getState() == START_SCREEN) {
                        setState(PLAYING);
                    } else if (getState() == GAME_OVER) {
                        resetStat();
                        setState(START_SCREEN);
                    } else if (getState() == PAUSE) {
                        setState(GAME_OVER);
                    }
                break;
            }
        break;

        case SDL_MOUSEBUTTONDOWN:
            if (getState() == PLAYING && map->getBall() && map->getBall()->velocity.x == 0 && map->getBall()->velocity.y == 0) {
                SDL_GetMouseState(&startX, &startY);
                isDragging = true;
            }
        break;

        case SDL_MOUSEMOTION:
            if (getState() == PLAYING && isDragging) {
                SDL_GetMouseState(&endX, &endY);
            }
        break;

        case SDL_MOUSEBUTTONUP:
            if (getState() == PLAYING && isDragging) {
                isDragging = false;
                SDL_GetMouseState(&endX, &endY);

                // Lấy vị trí bóng
                int posX = map->getBall()->dist.x + BALL_SIZE / 2;
                int posY = map->getBall()->dist.y + BALL_SIZE / 2;


                // Tính toán góc và lực
                double dx = posX - endX;
                double dy = posY - endY;
                double distance = sqrt(dx * dx + dy * dy);  // Độ dài lực
                double maxForce = 30.0;  // Giới hạn lực tối đa

                // Chuẩn hóa lực
                double force = std::min(distance / 4, maxForce);

                // Tính góc và vận tốc
                double angle = atan2(dy, dx);
                map->getBall()->velocity.x = cos(angle) * force;
                map->getBall()->velocity.y = sin(angle) * force;

                // Cập nhật số gậy
                stroke++;
                totalStroke++;
                Audio::PlaySFX("resources/sfx/swing.mp3", 10);
            }
        break;

        default:
            break;
    }
}

void Game::update() {
    if (map && map->getBall()) {
        map->getBall()->update();
    }
}

void Game::render() {
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
}

void Game::clean() {
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
/*
void Game::resetDragging() {
    isDragging = false;
} */
