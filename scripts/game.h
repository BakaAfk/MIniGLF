//
// Created by Baka-tannn on 21/2/2025.
//
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>

class Game {
private:
    SDL_Window *window;
    int cnt = 0;
    int mouseX, mouseY;
    double angle = 0;


public:
    Game();
    ~Game();
    void init(const char* title, int width, int height);
    void handleEvent();
    void update();
    bool isRunning();
    void render();
    void clean();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool running;
};