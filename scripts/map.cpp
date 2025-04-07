//
// Created by Baka-tannn on 4/3/2025.
//

#include <ctime>
#include "map.h"
#include "textureLoader.h"

int Map::arr[MAP_ROWS][MAP_COLS] = {0};  // Array for map
std::set<std::pair<int, int>> Map::occupiedPositions; // Position that has object rendered

Map::Map() {
    srand(time(NULL));

    // Load texture
    tile1 = TextureLoader::loadTexture("resources/img/tile32_light.png");
    tile2 = TextureLoader::loadTexture("resources/img/tile32_dark.png");
    blockTexture = TextureLoader::loadTexture("resources/img/tile64_light.png");
    hole = TextureLoader::loadTexture("resources/img/hole.png");
    powerup = TextureLoader::loadTexture("resources/img/powerup.png");
    // Tile rect
    src = {0, 0, TILE_SIZE, TILE_SIZE};
    spawnObjects();  // Rand object
}

Map::~Map() { // Destructor
    if (ball) {
        delete ball;
        ball = nullptr;
    }
    if (tile1) {
        SDL_DestroyTexture(tile1);
        tile1 = nullptr;
    }
    if (tile2) {
        SDL_DestroyTexture(tile2);
        tile2 = nullptr;
    }
    if (blockTexture) {
        SDL_DestroyTexture(blockTexture);
        blockTexture = nullptr;
    }
    if (hole) {
        SDL_DestroyTexture(hole);
        hole = nullptr;
    }
    if (powerup) {
        SDL_DestroyTexture(powerup);
        powerup = nullptr;
    }
    resetMap();
}

// Check if position is occupied
bool Map::isOccupied(int x, int y) {
    return occupiedPositions.find({x, y}) != occupiedPositions.end();
}

// Prevent object from spawning at all 4 sides
bool Map::isBlocked(int x, int y) {
return isOccupied(x - 1, y) && isOccupied(x + 1, y) &&
       isOccupied(x, y - 1) && isOccupied(x, y + 1);
}

// Randomly spawn objects
void Map::spawnObjects() {
    occupiedPositions.clear();

    // Spawn block
    for (int i = 0; i < 15; i++) {
        int x, y;
        do {
            x = (rand() % (MAP_COLS  - 1));
            y = (rand() % (MAP_ROWS -1));  // 64x64
        } while (isOccupied(x, y) || isOccupied(x + 1, y) ||
                 isOccupied(x, y + 1) || isOccupied(x + 1, y + 1)); // Check if 4 tiles are occupied

        // Mark as occupied
        occupiedPositions.insert({x, y});
        occupiedPositions.insert({x + 1, y});
        occupiedPositions.insert({x, y + 1});
        occupiedPositions.insert({x + 1, y + 1});

        arr[y][x] = 1;
    }

    // Spawn holes
    int holeX, holeY;
    do {
        holeX = 1 + rand() % (MAP_COLS - 2); // Not spawn at the edge
        holeY = 1 + rand() % (MAP_ROWS - 2);
    } while (isOccupied(holeX, holeY) || isBlocked(holeX, holeY));

    // Mark as occupied
    occupiedPositions.insert({holeX, holeY});
    arr[holeY][holeX] = 2;

    // Spawn ball
    int ballX, ballY;
    do {
        ballX = 1 + rand() % (MAP_COLS - 2); // Not spawn at the edge
        ballY = 1 + rand() % (MAP_ROWS - 2);
    } while (isOccupied(ballX, ballY) || isBlocked(ballX, ballY));
    // Mark as occupied
    occupiedPositions.insert({ballX, ballY});
    // Create ball
    ball = new Ball(Vector(ballX * TILE_SIZE, ballY * TILE_SIZE));

    if (!(rand() % 5)){ // 20% spawn rate per map
        // Spawn powerup
        int powerupX, powerupY;
        do {
            powerupX = 1 + rand() % (MAP_COLS - 2); // Not spawn at the edge
            powerupY = 1 + rand() % (MAP_ROWS - 2);
        } while (isOccupied(powerupX, powerupY) || isBlocked(powerupX, powerupY));

        // Mark as occupied
        occupiedPositions.insert({powerupX, powerupY});
        arr[powerupY][powerupX] = 3;
    }


}

// Draw map
void Map::drawMap() {
    // Draw tiles

    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            dist = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if ((i + j) % 2 == 0) {
                TextureLoader::DrawMapObject(tile1, src, dist);
            } else {
                TextureLoader::DrawMapObject(tile2, src, dist);
            }

        }
    }

    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            dist.x = j * TILE_SIZE;
            dist.y = i * TILE_SIZE;

            if (arr[i][j] == 1) { // Draw blocks
                src.w = BLOCK_SIZE;
                src.h = BLOCK_SIZE;
                dist.w = BLOCK_SIZE;
                dist.h = BLOCK_SIZE;
                TextureLoader::DrawMapObject(blockTexture, src, dist);
            } else if (arr[i][j] == 2) { // Draw hole
                src.w = TILE_SIZE;
                src.h = TILE_SIZE;
                dist.w = TILE_SIZE;
                dist.h = TILE_SIZE;
                TextureLoader::DrawMapObject(hole, src, dist);
            } else if (arr[i][j] == 3) { // Draw powerup
                src.w = TILE_SIZE;
                src.h = TILE_SIZE;
                dist.w = TILE_SIZE;
                dist.h = TILE_SIZE;
                TextureLoader::DrawMapObject(powerup, src, dist);
            }
        }
    }
}

void Map::resetMap() { // Reset map
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            arr[i][j] = 0;
        }
    }
    occupiedPositions.clear();
}