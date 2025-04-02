//
// Created by Baka-tannn on 23/2/2025.
//
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "textureLoader.h"
#include "ball.h"
#include "game.h"
#include "physics.h"
#include "map.h"
#include "audio.h"

Ball::Ball(Vector pos){
    position = pos;
    ball = TextureLoader::loadTexture("resources/img/ball.png");
    src.x = src.y = 0;
    src.w = src.h = dist.w = dist.h = BALL_SIZE;
    dist.x = static_cast<int>(position.x);
    dist.y = static_cast<int>(position.y);
    velocity = {0, 0};
}
Ball::~Ball() {
    if (ball) {
        SDL_DestroyTexture(ball);
        ball = nullptr;
    }
}

void Ball::drawBall() {
    dist.x = static_cast<int>(position.x);
    dist.y = static_cast<int>(position.y);
    TextureLoader::Draw(ball, src, dist);
}

void Ball::update() {
    Vector prevPos = position;  // Lưu vị trí trước khi di chuyển

    // Cập nhật vị trí dựa trên vận tốc
    position = position + velocity;
    dist.x = std::round(position.x);
    dist.y = std::round(position.y);

    Vector currPos = {position.x + velocity.x, position.y + velocity.y};  // Lưu vị trí sau khi di chuyển

    // Nếu bóng đi qua lỗ
    if (Physics::isHole(dist, prevPos, currPos) || win == true) {
        win = true;

        // Xác định tâm của lỗ
        int holeX = dist.x + HOLE_SIZE / 2;
        int holeY = dist.y + HOLE_SIZE / 2;

        velocity = {(holeX - currPos.x) / 4, (holeY - currPos.y) / 4};

        // Thu nhỏ bóng dần
        if (dist.w > 2 && dist.h > 2) {
            dist.w -= 4;
            dist.h -= 4;

        }

        // Nếu bóng đã thu nhỏ hoàn toàn, xóa nó khỏi game
        if (dist.w <= 2 || dist.h <= 2) {
            Audio::PlaySFX("resources/sfx/hole.mp3", 10);
            mapCount++;
            stroke = 0;
            win = false;
            delete Game::map;
            Game::map = new Map();
            return;
        }
        return;
    }

    // Giảm tốc do ma sát
    velocity = velocity * FRICTION;

    // Dừng bóng (cần sửa lại để mượt hơn)
    double speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (speed < 1) {
        velocity = {0, 0};
    }

    // Kiểm tra va chạm với biên màn hình
    if (Physics::isCollision(dist, BOUNDARY)) {
        Physics::reflect(dist, velocity, BOUNDARY);
        // Cập nhật lại vị trí sau va chạm
        position = {static_cast<double>(dist.x), static_cast<double>(dist.y)};
    }

    // Kiểm tra va chạm với block
    SDL_Rect nextPos = {static_cast<int>(dist.x + velocity.x), static_cast<int>(dist.y + velocity.y), BALL_SIZE,BALL_SIZE};
    int ballGridX = dist.x / TILE_SIZE;
    int ballGridY = dist.y / TILE_SIZE;

    // Kiểm tra 8 ô xung quanh ô bóng
    for (int i = std::max(0, ballGridY - 1); i <= std::min(MAP_ROWS - 1, ballGridY + 1); i++) {
        for (int j = std::max(0, ballGridX - 1); j <= std::min(MAP_COLS - 1, ballGridX + 1); j++) {
            if (Map::arr[i][j] == 1) {  // 1 = Block
                SDL_Rect blockRect = {j * TILE_SIZE, i * TILE_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                if (Physics::isCollision(nextPos, blockRect)) {
                    Physics::reflectObject(dist, velocity, blockRect);
                    // Cập nhật lại vị trí sau va chạm
                    position = {static_cast<double>(dist.x), static_cast<double>(dist.y)};
                    return;
                }
            }
        }
    }
}