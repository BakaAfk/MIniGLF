//
// Created by Baka-tannn on 13/3/2025.
//

#ifndef GLOBALVAR_H
#define GLOBALVAR_H
#include <SDL.h>
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const int MAP_ROWS = 20;
const int MAP_COLS = 30;
const int TILE_SIZE = 32;
const int BLOCK_SIZE = 64;
const int BALL_SIZE = 32;
const int HOLE_SIZE = 32;
const int midX = SCREEN_WIDTH / 2, midY = SCREEN_HEIGHT / 2, veloY = 5;
extern const char *TITLE;
const SDL_Color WHITE = {255, 255, 255, 255};
const float FRICTION = 0.97f;

extern int stroke;
extern int totalStroke;
extern double avgStroke;
extern int mapCount;
enum GameState {
    START_SCREEN,
    PLAYING,
    PAUSE,
    EXIT
};
#endif //GLOBALVAR_H
