//
// Created by Baka-tannn on 25/3/2025.
//

#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "map.h"

class GameRenderer {
private:
    static int baseY;
    static double time;
    static int aniSpeed;

public:
    static void renderMainScreen();
    static void renderPlayingScreen(bool isDragging, Map* map, Ball *ball, int endX, int endY);
    static void renderPauseScreen();
    static void renderGameOver();
    static void renderArrow(Ball* ball, int endX, int endY);
    static void renderStats();
    static void renderTextBackground(int x, int y, int w, int h, SDL_Color color);
};

#endif //GAMERENDERER_H
