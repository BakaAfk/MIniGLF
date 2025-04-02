//
// Created by Baka-tannn on 23/2/2025.
//
#include "physics.h"
#include <cmath>
#include "map.h"


bool Physics::isCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
    // AABB algorithm
    return (rect1.x < rect2.x + rect2.w &&
            rect1.x + rect1.w > rect2.x &&
            rect1.y < rect2.y + rect2.h &&
            rect1.y + rect1.h > rect2.y);
}

void Physics::reflect(SDL_Rect& rect, Vector& velocity, const SDL_Rect& boundary) {
    // If ball outside X-axis boundary
    if (rect.x < boundary.x || rect.x + rect.w > boundary.x + boundary.w) {
        velocity.x = -velocity.x;
    }
    // If ball outside Y-axis boundary
    if (rect.y < boundary.y || rect.y + rect.h > boundary.y + boundary.h) {
        velocity.y = -velocity.y;
    }

    // Keep ball inside boundary
    if (rect.x < boundary.x) rect.x = boundary.x;
    if (rect.x + rect.w > boundary.x + boundary.w) rect.x = boundary.x + boundary.w - rect.w;
    if (rect.y < boundary.y) rect.y = boundary.y;
    if (rect.y + rect.h > boundary.y + boundary.h) rect.y = boundary.y + boundary.h - rect.h;
}

void Physics::reflectObject(SDL_Rect& rect, Vector& velocity, const SDL_Rect& object) {
    // Distance from the center of the object to the center of the ball
    int deltaX = rect.x + rect.w / 2 - object.x - object.w / 2;
    int deltaY = rect.y + rect.h / 2 - object.y - object.h / 2;

    // Reflect the ball based on the direction of the object
    // X-axis
    if (std::abs(deltaX) > std::abs(deltaY)) {
        if (deltaX > 0) {
            rect.x = object.x + object.w; // Right side
        } else {
            rect.x = object.x - rect.w; // Left side
        }
        velocity.x = -velocity.x;
    } else { // Y-axis
        if (deltaY > 0) {
            rect.y = object.y + object.h; // Under
        } else {
            rect.y = object.y - rect.h; // Above
        }
        velocity.y = -velocity.y;
    }

}

bool Physics::isHole(const SDL_Rect& ballRect, const Vector& prevPos, const Vector& currPos) {
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            if (Map::arr[i][j] == 2) {  // 2 = Hole
                SDL_Rect holeRect = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                // Hole center position
                double holeX = holeRect.x + holeRect.w / 2;
                double holeY = holeRect.y + holeRect.h / 2;

                // Ball center position
                double x1 = prevPos.x + ballRect.w / 2;
                double y1 = prevPos.y + ballRect.h / 2;
                double x2 = currPos.x + ballRect.w / 2;
                double y2 = currPos.y + ballRect.h / 2;

                // Line equation: Ax + By + C = 0
                double A = y2 - y1;
                double B = x1 - x2;
                double C = x2 * y1 - x1 * y2;

                // Distance from the hole to the line of the ball path
                double distance = std::abs(A * holeX + B * holeY + C) / sqrt(A * A + B * B);

                // Check if the ball is close enough to the hole
                if (distance <= TILE_SIZE / 2 && Physics::isCollision(ballRect, holeRect)) {
                    return true;
                }
            }
        }
    }
    return false;
}