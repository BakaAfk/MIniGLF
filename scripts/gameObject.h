//
// Created by Baka-tannn on 23/2/2025.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once
#include "game.h"

class GameObject {
public:
    GameObject(const char *textureSheet, int x, int y, int w, int h);
    ~GameObject();
    void update();
    void render();

private:
    int x, y, w, h;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Rect src, dist;
};


#endif //GAMEOBJECT_H
