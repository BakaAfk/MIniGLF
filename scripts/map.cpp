//
// Created by Baka-tannn on 4/3/2025.
//


#include "map.h"
#include "textureLoader.h"
#include "game.h"
#include "ball.h"

int Map::arr[MAP_ROWS][MAP_COLS] = {0};  // Khởi tạo tất cả các ô với giá trị 0
std::set<std::pair<int, int>> Map::occupiedPositions;


std::set<std::pair<int, int>> occupiedPositions;

Map::Map() {
    srand(time(nullptr));

    // Load texture
    tile1 = TextureLoader::loadTexture("resources/img/tile32_light.png");
    tile2 = TextureLoader::loadTexture("resources/img/tile32_dark.png");
    blockTexture = TextureLoader::loadTexture("resources/img/tile64_light.png");
    hole = TextureLoader::loadTexture("resources/img/hole.png");

    src.x = 0;
    src.y = 0;
    src.w = TILE_SIZE;
    src.h = TILE_SIZE;

    spawnObjects();  // Tạo block, hole và ball ngẫu nhiên
}

Map::~Map() {
    if (ball) {
        delete ball;
        ball = nullptr;
    }
    resetMap();
}

// Kiểm tra vị trí đã bị chiếm chưa
bool Map::isOccupied(int x, int y) {
    return occupiedPositions.find({x, y}) != occupiedPositions.end();
}


bool isBlocked(int arr[][30], int x, int y) {
    return arr[y][x] == 1 ||
             (x > 0 && arr[y][x - 1] == 1) ||
             (x < MAP_COLS - 1 && arr[y][x + 1] == 1) ||
             (y > 0 && arr[y - 1][x] == 1) ||
             (y < MAP_ROWS - 1 && arr[y + 1][x] == 1);

}

// Hàm spawn block, hole và ball
void Map::spawnObjects() {
    occupiedPositions.clear();

    // Spawn block (15 block ngẫu nhiên, mỗi block 64px)
    for (int i = 0; i < 15; i++) {
        int x, y;
        do {
            x = (rand() % (MAP_COLS / 2)) * 2;  // Block chiếm 2 ô ngang
            y = (rand() % (MAP_ROWS / 2)) * 2;  // Block chiếm 2 ô dọc
        } while (isOccupied(x, y) || isOccupied(x + 1, y) ||
                 isOccupied(x, y + 1) || isOccupied(x + 1, y + 1));

        occupiedPositions.insert({x, y});
        occupiedPositions.insert({x + 1, y});
        occupiedPositions.insert({x, y + 1});
        occupiedPositions.insert({x + 1, y + 1});
        arr[y][x] = 1;  // 1 = Block
    }

    // Spawn hole (1 holes ngẫu nhiên)
    int holeX, holeY;
    do {
        holeX = rand() % MAP_COLS;
        holeY = rand() % MAP_ROWS;
    } while (isOccupied(holeX, holeY) || isBlocked(arr, holeX, holeY));
    occupiedPositions.insert({holeX, holeY});
    arr[holeY][holeX] = 2;  // 2 = Hole

    // Spawn ball (1 ball, đảm bảo không trùng với block hoặc hole hoặc không bị block bao kín xung quanh)
    int ballX, ballY;
    do {
        ballX = rand() % MAP_COLS - 1;
        ballY = rand() % MAP_ROWS - 1;
    } while (isOccupied(ballX, ballY) || isBlocked(arr, ballX, ballY));
    occupiedPositions.insert({ballX, ballY});
    arr[ballY][ballX] = 0;  // 0 = Ball]

    ball = new Ball(Vector(ballX * TILE_SIZE, ballY * TILE_SIZE),
                    TextureLoader::loadTexture("resources/img/ball.png"));
}

// Vẽ map
void Map::drawTile() {
    /*// 1. Vẽ nền trước (tile1, tile2)
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
    */
    // 2. Vẽ block và hole sau cùng để không bị đè
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            dist.x = j * TILE_SIZE;
            dist.y = i * TILE_SIZE;

            if (arr[i][j] == 1 && j % 2 == 0 && i % 2 == 0) {
                // Block 64x64 (Chỉ vẽ ở góc trên bên trái)*src.w = BLOCK_SIZE;
                src.w = BLOCK_SIZE;
                src.h = BLOCK_SIZE;
                dist.w = BLOCK_SIZE;
                dist.h = BLOCK_SIZE;
                TextureLoader::Draw(blockTexture, src, dist);
            } else if (arr[i][j] == 2) {
                // Hole 32x32
                src.w = TILE_SIZE;
                src.h = TILE_SIZE;
                dist.w = TILE_SIZE;
                dist.h = TILE_SIZE;
                TextureLoader::Draw(hole, src, dist);
            }
        }
    }
}


bool Map::isHole(const SDL_Rect& ballRect, const Vector& prevPos, const Vector& currPos) {
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            if (arr[i][j] == 2) {  // 2 = Hole
                SDL_Rect holeRect = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                // Tọa độ tâm của lỗ
                float holeX = holeRect.x + holeRect.w / 2;
                float holeY = holeRect.y + holeRect.h / 2;

                // Tọa độ di chuyển của bóng
                float x1 = prevPos.x + ballRect.w / 2;
                float y1 = prevPos.y + ballRect.h / 2;
                float x2 = currPos.x + ballRect.w / 2;
                float y2 = currPos.y + ballRect.h / 2;

                // Khoảng cách từ lỗ đến đường di chuyển của bóng
                float A = y2 - y1;
                float B = x1 - x2;
                float C = x2 * y1 - x1 * y2;

                float distance = std::abs(A * holeX + B * holeY + C) / sqrt(A * A + B * B);

                // Nếu khoảng cách từ đường đi của bóng đến tâm lỗ nhỏ hơn bán kính lỗ, coi như vào lỗ
                if (distance <= TILE_SIZE / 2 && Physics::isCollision(ballRect, holeRect)) {
                    return true;
                }
            }
        }
    }
    return false;
}
void resetOccupiedPositions() {
    occupiedPositions.clear();
}

void Map::resetMap() {
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            arr[i][j] = 0;
        }
    }
    occupiedPositions.clear();

}