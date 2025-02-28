//
// Created by Baka-tannn on 22/2/2025.
//

#include <iostream>
#include <cmath>
#include "game.h"
#include "textureLoader.h"
#include "gameObject.h"
#include "tile.h"
#include "ball.h"
#include "vector.h"


SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

GameObject *player;
Tile *tile;
Ball *ball;



bool Game::running = false;
Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 132, 171, 60, 255);
        }
        running = true;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "Loi khi khoi tao SDL_TTF" << std::endl;
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    tile = new Tile();
    player = new GameObject("resources/img/cube.png", 480 - 32, 320 - 32, 64, 64);
    ball = new Ball(Vector(0,0), TextureLoader::loadTexture("resources/img/ball.png"));
}
    void Game::handleEvent()
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                running = false;
            break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mouseX, &mouseY);
            break;
            default:
                break;
        }
    }

    void Game::update()
    {
        ball->update();
        player->update();
    }

    void Game::render()
    {
        SDL_RenderClear(renderer);
        tile->drawTile();
        ball->drawBall();
        SDL_RenderPresent(renderer);
    }

    void Game::clean()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        TTF_Quit();
    }

    bool Game::isRunning()
    {
        return running;
    }
