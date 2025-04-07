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

Ball::Ball(Vector pos) // Ball initialization
{
    position = pos;
    ball = TextureLoader::loadTexture("resources/img/ball.png");
    src.x = src.y = 0;
    src.w = src.h = dist.w = dist.h = BALL_SIZE;
    dist.x = static_cast<int>(position.x);
    dist.y = static_cast<int>(position.y);
    velocity = {0, 0};
}

Ball::~Ball() // Delete ball and free texture
{
    if (ball) {
        SDL_DestroyTexture(ball);
        ball = nullptr;
    }
}

void Ball::drawBall() // Draw ball to screen
{
    dist.x = static_cast<int>(position.x);
    dist.y = static_cast<int>(position.y);
    TextureLoader::DrawMapObject(ball, src, dist);
}

void Ball::update() // Update ball position and velocity
{
    Vector prevPos = position; // Save current position

    // Update position
    position = position + velocity;
    dist.x = std::round(position.x);
    dist.y = std::round(position.y);

    Vector currPos = {
        position.x + velocity.x,
        position.y + velocity.y
    };

    // Apply friction
    velocity = velocity * FRICTION;

    // Stop ball if speed is too low
    double speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (speed < 1) {
        velocity = {0, 0};
    }

    // Handle hole collision
    if (Physics::isHole(dist, prevPos, currPos) || win) {
        win = true;

        // Get hole center position
        int holeX = dist.x + HOLE_SIZE / 2;
        int holeY = dist.y + HOLE_SIZE / 2;

        // Set velocity to move into hole
        velocity = {
            (holeX - currPos.x) / 4,
            (holeY - currPos.y) / 4
        };

        // Shrink ball
        if (dist.w > 2 && dist.h > 2) {
            dist.w -= 4;
            dist.h -= 4;
        }

        // Destroy ball when small enough
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

    // Check boundary collision
    if (Physics::isCollision(dist, BOUNDARY)) {
        Physics::reflect(dist, velocity, BOUNDARY);
        position = {
            static_cast<double>(dist.x),
            static_cast<double>(dist.y)
        };
    }

    // Check collisions with blocks and power-ups
    SDL_Rect ballPos = {
        static_cast<int>(currPos.x),
        static_cast<int>(currPos.y),
        dist.w,
        dist.h
    };

    int ballGridX = dist.x / TILE_SIZE;
    int ballGridY = dist.y / TILE_SIZE;

    // Check 3x3 grid around ball
    for (int i = std::max(0, ballGridY - 1); i <= std::min(MAP_ROWS - 1, ballGridY + 1); i++) {
        for (int j = std::max(0, ballGridX - 1); j <= std::min(MAP_COLS - 1, ballGridX + 1); j++) {
            if (Map::arr[i][j] == 1) { // Block collision
                SDL_Rect blockRect = {
                    j * TILE_SIZE,
                    i * TILE_SIZE,
                    BLOCK_SIZE,
                    BLOCK_SIZE
                };

                if (Physics::isCollision(ballPos, blockRect)) {
                    if (!isPowerUp) {
                        Physics::reflectObject(dist, velocity, blockRect);
                        position = {
                            static_cast<double>(dist.x),
                            static_cast<double>(dist.y)
                        };
                    } else {
                        Map::arr[i][j] = 0; // Destroy block
                    }
                }
            }
            else if (Map::arr[i][j] == 3) { // Power-up collision
                SDL_Rect powerupRect = {
                    j * TILE_SIZE,
                    i * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE
                };

                if (Physics::isCollision(ballPos, powerupRect)) {
                    Audio::PlaySFX("resources/sfx/powerup.mp3", 15);
                    havePowerUp = true;
                    Map::arr[i][j] = 0; // Collect power-up
                    return;
                }
            }
        }
    }
}