//
// Created by Baka-tannn on 21/2/2025.
//

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SDL.h>

class TextureLoader {
public:
    static SDL_Texture *loadTexture(const char *fileName);
    static void DrawMapObject(SDL_Texture *texture, SDL_Rect src, SDL_Rect dist);
    static void DrawAsset(SDL_Texture *texture, SDL_Rect dist, double angle, SDL_RendererFlip flip = SDL_FLIP_NONE);
};
#endif //TEXTURELOADER_H
