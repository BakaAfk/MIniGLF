//
// Created by Baka-tannn on 21/2/2025.
//

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#pragma once

#include <SDL.h>

#include "game.h"


class TextureLoader {
public:
    static SDL_Texture *loadTexture(const char *fileName);
    static void Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dist);
};
#endif //TEXTURELOADER_H
