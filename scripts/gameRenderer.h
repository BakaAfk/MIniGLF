//
// Created by Baka-tannn on 25/3/2025.
//

#ifndef GAMERENDERER_H
#define GAMERENDERER_H
#pragma once

#include "game.h"
#include "textureLoader.h"
#include "textRenderer.h"
#include "globalVar.h"
#include "map.h"

class GameRenderer {
public:
    static void renderMainScreen();
    static void renderPlayingScreen(bool isDragging, Map* map, Ball *ball, int endX, int endY);
    static void renderPauseScreen();
    static void renderGameOver();
    static void renderArrow(Ball* ball, int endX, int endY);
    static void renderStats();

};

#endif //GAMERENDERER_H
