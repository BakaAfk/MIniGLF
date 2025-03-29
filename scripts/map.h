//
// Created by Baka-tannn on 4/3/2025.
//

#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "ball.h"

class Map {
public:
    Map();
    ~Map();
    Ball* getBall() { return ball; }
    void removeBall() { delete ball; ball = nullptr; }
    void drawTile();
    void spawnObjects();
    static void checkCollisionWithObject(SDL_Rect& ballRect, double veloX, double veloY);
    static int arr[MAP_ROWS][MAP_COLS];
    static void resetOccupiedPositions();
    static void resetMap();
    static std::set<std::pair<int, int>> occupiedPositions;
    static bool isOccupied(int x, int y);
private:
    SDL_Texture *blockTexture, *tile1, *tile2, *hole;
    Ball *ball;

    SDL_Rect src, dist;
};

#endif // MAP_H

