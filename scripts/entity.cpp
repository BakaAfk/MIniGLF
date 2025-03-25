//
// Created by Baka-tannn on 21/2/2025.
//
#include "entity.h"
#include <SDL.h>

Entity::Entity(Vector pos, SDL_Texture *texture): pos(pos), texture(texture)
{
    rect.x = 0;
    rect.y = 0;
    rect.w = 32;
    rect.h = 32;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}

void Entity::setPos(double x, double y)
{
    pos.x = x;
    pos.y = y;
}

void Entity::setAngle(double angle)
{
    this->angle = angle;
}

void Entity::setScale(float w, float h)
{
    scaleW = w;
    scaleH = h;
}

void Entity::update()
{
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = rect.w * scaleW;
    rect.h = rect.h * scaleH;
}