//
// Created by Baka-tannn on 4/3/2025.
//


#include "map.h"
#include "textureLoader.h"
#include "game.h"
#include "ball.h"

int Map::arr[MAP_ROWS][MAP_COLS] = {0};  // Khởi tạo tất cả các ô với giá trị 0
std::set<std::pair<int, int>> Map::occupiedPositions; // Tập hợp các vị trí đã render object


Map::Map() {
    srand(time(nullptr));

    // Load texture
    tile1 = TextureLoader::loadTexture("resources/img/tile32_light.png");
    tile2 = TextureLoader::loadTexture("resources/img/tile32_dark.png");
    blockTexture = TextureLoader::loadTexture("resources/img/tile64_light.png");
    hole = TextureLoader::loadTexture("resources/img/hole.png");

    // Tile rect
    src.x = 0;
    src.y = 0;
    src.w = TILE_SIZE;
    src.h = TILE_SIZE;

    spawnObjects();  // Rand object
}

Map::~Map() {
    if (ball) {
        delete ball;
        ball = nullptr;
    }
    SDL_DestroyTexture(tile1);
    SDL_DestroyTexture(tile2);
    SDL_DestroyTexture(blockTexture);
    SDL_DestroyTexture(hole);
    resetMap();
}

// Kiểm tra vị trí đã có object nào chưa
bool Map::isOccupied(int x, int y) {
    return Map::occupiedPositions.find({x, y}) != Map::occupiedPositions.end();
}


bool isBlocked(int arr[][30], int x, int y) { // Tránh bóng / lỗ bị bao 4 phía bởi block
    return Map::isOccupied(x - 1, y) && Map::isOccupied(x + 1, y) &&
           Map::isOccupied(x, y - 1) && Map::isOccupied(x, y + 1);

}

// Hàm spawn block, hole và ball
void Map::spawnObjects() {
    occupiedPositions.clear();

    // Spawn block
    for (int i = 0; i < 15; i++) {
        int x, y;
        do {
            x = (rand() % (MAP_COLS  - 1));  // Rand tọa độ
            y = (rand() % (MAP_ROWS -1));  // Vì block 64x64 nên -1 để không tràn ra khỏi màn hình
        } while (isOccupied(x, y) || isOccupied(x + 1, y) ||
                 isOccupied(x, y + 1) || isOccupied(x + 1, y + 1)); // Kiểm tra xem đã có object nào tại 4 ô hình vuông chưa

        // Đánh dấu 4 ô đã có object
        occupiedPositions.insert({x, y});
        occupiedPositions.insert({x + 1, y});
        occupiedPositions.insert({x, y + 1});
        occupiedPositions.insert({x + 1, y + 1});

        arr[y][x] = 1;  // Lưu vào map
    }

    // Spawn lỗ
    int holeX, holeY;
    do {
        holeX = rand() % MAP_COLS;
        holeY = rand() % MAP_ROWS;
    } while (isOccupied(holeX, holeY) || isBlocked(arr, holeX, holeY) || holeX == 0 || holeY == 0 || holeX == MAP_COLS - 1 || holeY == MAP_ROWS - 1);
    // Không spawn đè lên object khác / không bị block 4 hướng // không spawn ở biên
    occupiedPositions.insert({holeX, holeY});
    arr[holeY][holeX] = 2;  //

    // Spawn ball
    int ballX, ballY;
    do {
        ballX = rand() % MAP_COLS;
        ballY = rand() % MAP_ROWS;
    } while (isOccupied(ballX, ballY) || isBlocked(arr, ballX, ballY) || ballX == 0 || ballY == 0 || ballX == MAP_COLS - 1 || ballY == MAP_ROWS - 1); // Như hole
    occupiedPositions.insert({ballX, ballY});

    ball = new Ball(Vector(ballX * TILE_SIZE, ballY * TILE_SIZE));
}

// Vẽ map
void Map::drawTile() {
    // Vẽ nền
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            dist.x = j * TILE_SIZE;
            dist.y = i * TILE_SIZE;
            dist.w = TILE_SIZE;
            dist.h = TILE_SIZE;

            // Ô cờ caro
            if ((i + j) % 2 == 0) {
                TextureLoader::Draw(tile1, src, dist);
            } else {
                TextureLoader::Draw(tile2, src, dist);
            }
        }
    }

    // Vẽ block và hole
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            dist.x = j * TILE_SIZE;
            dist.y = i * TILE_SIZE;

            if (arr[i][j] == 1) { // Vẽ block
                src.w = BLOCK_SIZE;
                src.h = BLOCK_SIZE;
                dist.w = BLOCK_SIZE;
                dist.h = BLOCK_SIZE;
                TextureLoader::Draw(blockTexture, src, dist);
            } else if (arr[i][j] == 2) { // Vẽ hole
                src.w = TILE_SIZE;
                src.h = TILE_SIZE;
                dist.w = TILE_SIZE;
                dist.h = TILE_SIZE;
                TextureLoader::Draw(hole, src, dist);
            }
        }
    }
}



void resetOccupiedPositions() {
    Map::occupiedPositions.clear();
}

void Map::resetMap() {
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            arr[i][j] = 0;
        }
    }

    occupiedPositions.clear();

}