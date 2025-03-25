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
    void spawnObjects();  // Hàm spawn block, hole, ball
    static void checkCollisionWithObject(SDL_Rect& ballRect, double veloX, double veloY);
    static bool isHole(const SDL_Rect& ballRect, const Vector& prevPos, const Vector& currPos);
    static int arr[20][30];  // Biến mảng thành static
    static void resetOccupiedPositions();
    static void resetMap();
private:
    SDL_Texture *blockTexture, *tile1, *tile2, *hole;
    Ball *ball;


    static std::set<std::pair<int, int>> occupiedPositions;
    static bool isOccupied(int x, int y); // Chuyển thành static

    SDL_Rect src, dist;
};

#endif // MAP_H

