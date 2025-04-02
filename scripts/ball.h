//
// Created by Baka-tannn on 23/2/2025.
//

#ifndef BALL_H
#define BALL_H
#include "vector.h"
class Ball
{
private:
    SDL_Texture *ball;
    Vector velocity, position;
    SDL_Rect src, dist;
    bool win = false;

public:
    Ball(Vector pos);
    ~Ball();
    void drawBall();
    void update();
    void setVelocity(const Vector& v) { velocity = v; }

    const Vector& getPosition() const { return position; }
    const Vector& getVelocity() const { return velocity; }
    const SDL_Rect& getDist() const { return dist; }
    bool isWin() const { return win; }
};

#endif //BALL_H
