//
// Created by Baka-tannn on 23/2/2025.
//

#ifndef BALL_H
#define BALL_H
#pragma once
#include "vector.h"
#include "entity.h"
class Ball : public Entity
{
private:
    SDL_Texture *ball;


public:

    bool win = false;
    Ball(Vector position, SDL_Texture *texture);
    ~Ball();
    void drawBall();
    void update();
    Vector velocity, position;
    SDL_Rect src, dist;



};

#endif //BALL_H
