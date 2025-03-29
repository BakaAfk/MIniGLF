//
// Created by Baka-tannn on 21/2/2025.
//
#include "textureLoader.h"
#include "game.h"

SDL_Texture *TextureLoader::loadTexture(const char *fileName)
{
    SDL_Surface* surface = IMG_Load(fileName);
    if (!surface) {
        std::cerr << "Loi khi load file:  " << fileName << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Loi khi tao surface " << fileName << std::endl;
        return nullptr;
    }
    return texture;
}

void TextureLoader::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dist)
{
    SDL_RenderCopy(Game::renderer, texture, &src, &dist);
}