//
// Created by Baka-tannn on 13/3/2025.
//

#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <SDL.h>
#include <string>
#include <vector>

// Global constants
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const int MAP_ROWS = 20;
const int MAP_COLS = 30;
const int TILE_SIZE = 32;
const int BLOCK_SIZE = 64;
const int BALL_SIZE = 32;
const int HOLE_SIZE = 32;
extern const char *TITLE;
const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color GRAY_BG = {128, 128, 128, 150};
const SDL_Color BLACK = {0, 0, 0, 255};
const float FRICTION = 0.97f;
const SDL_Rect BOUNDARY = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
const int DEFAULT_FONT_SIZE = 24;
const int TEXTH = 27;

extern int stroke;
extern int totalStroke;
extern double avgStroke;
extern int mapCount;
extern bool muteBG;
extern bool havePowerUp;
extern bool isPowerUp;
extern std::vector<std::string> instructions;
typedef enum GameState {
    START_SCREEN,
    INSTRUCTIONS,
    PLAYING,
    PAUSE,
    GAME_OVER,
    EXIT
} GameState;
#endif //GLOBALVAR_H
