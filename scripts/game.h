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
#include <cmath>
#include "entity.h"
#include "physics.h"
#include "globalVar.h"
#include "textRenderer.h"
#include "audio.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>

#include "map.h"
class Map;
class Game {
private:
    SDL_Window *window;
    int startX, startY, endX, endY;
    double angle = 0;
    bool isDragging = false;
    TextRenderer textRenderer;


public:
    Game();
    ~Game();
    void init();
    void handleEvent();
    void update();
    bool isRunning();
    void render();
    void clean();
    static void resetDragging();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool running;
    static Map* map;
};
