//
// Created by Baka-tannn on 21/2/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "vector.h"

class Entity {
private:
    Vector pos;
    double angle = 0;
    double scaleW = 1, scaleH = 1;
    SDL_Texture *texture;
    SDL_Rect rect;
public:
    Entity(Vector pos, SDL_Texture *texture);
    void setPos(double x, double y);
    void setAngle(double angle);
    void setScale(float w, float h);
    void update();
};





#endif //ENTITY_H
