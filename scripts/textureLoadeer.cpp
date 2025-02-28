//
// Created by Baka-tannn on 21/2/2025.
//
#include "textureLoader.h"

SDL_Texture *TextureLoader::loadTexture(const char *fileName)
{
    SDL_Surface *surface = IMG_Load(fileName);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureLoader::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dist)
{
    SDL_RenderCopy(Game::renderer, texture, &src, &dist);
}