//
// Created by Baka-tannn on 4/3/2025.
//

#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "ball.h"
#include <set>

class Map {
private:
    SDL_Texture *blockTexture, *tile1, *tile2, *hole;
    Ball *ball;
    SDL_Rect src, dist;
public:
    Map();
    ~Map();
    Ball* getBall() { return ball; }
    void removeBall() { delete ball; ball = nullptr; }
    void drawMap();
    void spawnObjects();
    static int arr[MAP_ROWS][MAP_COLS];
    static void resetMap();
    static std::set<std::pair<int, int>> occupiedPositions;
    bool isOccupied(int x, int y);
    bool isBlocked(int x, int y);

};
#endif // MAP_H

