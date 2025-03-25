//
// Created by Baka-tannn on 22/2/2025.
//

#include <iostream>
#include <cmath>
#include "game.h"
#include "textureLoader.h"
#include "textRenderer.h"
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

void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH ,SCREEN_HEIGHT , 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 132, 171, 60, 255);
        }
        running = true;
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

        case SDL_MOUSEBUTTONDOWN:
            if (map->getBall() && map->getBall()->velocity.x == 0 && map->getBall()->velocity.y == 0) {
                SDL_GetMouseState(&startX, &startY);
                isDragging = true;
            }
        break;

        case SDL_MOUSEMOTION:
            if (isDragging) {
                SDL_GetMouseState(&endX, &endY);
            }
        break;

        case SDL_MOUSEBUTTONUP:
            if (isDragging) {
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
    if (map) {
        map->drawTile();
        map->getBall()->drawBall();
    }


    // Vẽ mũi tên chỉ hướng
    if (isDragging && map->getBall() && map->getBall()->velocity.x == 0 && map->getBall()->velocity.y == 0) {
        float dx = map->getBall()->dist.x + BALL_SIZE / 2 - endX;
        float dy = map->getBall()->dist.y + BALL_SIZE / 2 - endY;

        // Tính góc quay của mũi tên
        float angle = atan2(dy, dx) * 180 / M_PI + 90;

        // Tính hệ số độ dài mũi tên
        float multiplier = std::min(sqrt(dx * dx + dy * dy) / 4, 30.0) / 10.0;
        SDL_Rect arrowRect = {
            static_cast<int>(map->getBall()->dist.x + BALL_SIZE / 2 - 8),  // Căn giữa theo chiều ngang
            static_cast<int>(map->getBall()->dist.y + BALL_SIZE / 2 - 32 * multiplier),  // Căn chỉnh dọc
            16, static_cast<int>(64 * multiplier)   // Điều chỉnh chiều dài theo lực kéo
        };

        // Load texture mũi tên
        SDL_Texture* arrowTexture = TextureLoader::loadTexture("resources/img/point.png");
        if (arrowTexture) {
            SDL_RenderCopyEx(renderer, arrowTexture, nullptr, &arrowRect, angle, nullptr, SDL_FLIP_NONE);
            SDL_DestroyTexture(arrowTexture);
        }
    }

    std::string mapText = "Map: " + std::to_string(mapCount);
    textRenderer.renderText(renderer, mapText, 10, 10, 24, WHITE);

    std::string strokeText = "Stroke: " + std::to_string(stroke);
    textRenderer.renderTextCenter(renderer, strokeText, SCREEN_WIDTH / 2, 10, 24, WHITE);

    // round to 2 decimal places
    avgStroke = totalStroke / (double)mapCount;
    std::string avgStrokeText = "Avg. Stroke: " + std::to_string(avgStroke);
    textRenderer.renderText(renderer, avgStrokeText, SCREEN_WIDTH - 200, 10, 24, WHITE);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    if (map) {
        delete map;
        map = nullptr;
    }
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
