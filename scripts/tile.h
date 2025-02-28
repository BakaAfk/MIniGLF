//
// Created by Baka-tannn on 23/2/2025.
//

#ifndef TILE_H
#define TILE_H
#pragma once

#include "game.h"

class Tile{
private:
    SDL_Rect src, dist;
    SDL_Texture *tile1, *tile2;
    int tiles[20][30];
public:
    Tile();
    ~Tile();
    void loadTiles();
    void drawTile();
};
#endif //TILE_H
