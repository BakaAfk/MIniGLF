//
// Created by Baka-tannn on 23/2/2025.
//

#ifndef BALL_H
#define BALL_H
#pragma once
#include "game.h"
#include "vector.h"
#include "entity.h"

class Ball : public Entity
{
private:
    SDL_Texture *ball, *fire;
    SDL_Rect src, dist;
    Vector velocity{20, 20};
    int stroke = 0;
    bool win = false;
    double friction = 0.1;
    bool isOnfire = false;
    int fireTimer;
    int fireX, fireY;
    Mix_Chunk *bounce;
public:
    Ball(Vector position, SDL_Texture *texture);
    ~Ball();
    void drawBall();
    void update();


};

#endif //BALL_H
