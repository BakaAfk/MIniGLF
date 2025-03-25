//
// Created by Baka-tannn on 23/2/2025.
//
#include "physics.h"

bool Physics::isCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
    // ABBA algorithm
    return (rect1.x < rect2.x + rect2.w &&
            rect1.x + rect1.w > rect2.x &&
            rect1.y < rect2.y + rect2.h &&
            rect1.y + rect1.h > rect2.y);
}

void Physics::reflect(SDL_Rect& rect, double& veloX, double& veloY, const SDL_Rect& boundary) {
    // Đảo ngược velo theo 2 trục
    if (rect.x < boundary.x || rect.x + rect.w > boundary.x + boundary.w) {
        veloX = -veloX;
    }
    if (rect.y < boundary.y || rect.y + rect.h > boundary.y + boundary.h) {
        veloY = -veloY;
    }

    // Gán lại vị trí cho bóng
    if (rect.x < boundary.x) rect.x = boundary.x;
    if (rect.x + rect.w > boundary.x + boundary.w) rect.x = boundary.x + boundary.w - rect.w;
    if (rect.y < boundary.y) rect.y = boundary.y;
    if (rect.y + rect.h > boundary.y + boundary.h) rect.y = boundary.y + boundary.h - rect.h;
}

void Physics::reflectObject(SDL_Rect& rect, double& veloX, double& veloY, const SDL_Rect& object) {
    // Tính khoảng cách từ tâm của object đến tâm của bóng
    int deltaX = rect.x + rect.w / 2 - object.x - object.w / 2;
    int deltaY = rect.y + rect.h / 2 - object.y - object.h / 2;

    // Nếu bóng chạm vào object
    if (std::abs(deltaX) > std::abs(deltaY)) {
        if (deltaX > 0) {
            rect.x = object.x + object.w;
        } else {
            rect.x = object.x - rect.w;
        }
        veloX = -veloX;
    } else {
        if (deltaY > 0) {
            rect.y = object.y + object.h;
        } else {
            rect.y = object.y - rect.h;
        }
        veloY = -veloY;
    }

}