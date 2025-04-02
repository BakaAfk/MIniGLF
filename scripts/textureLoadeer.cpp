//
// Created by Baka-tannn on 21/2/2025.
//
#include <SDL_image.h>
#include "textureLoader.h"
#include "game.h"

std::map<std::string, SDL_Texture*> TextureLoader::textureCache;

SDL_Texture *TextureLoader::loadTexture(const char *fileName)
{
    auto it = textureCache.find(fileName);
    if (it != textureCache.end()) {
        return it->second;
    }
    SDL_Surface* surface = IMG_Load(fileName);
    if (!surface) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to load image", nullptr);
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to create texture", nullptr);
        return nullptr;
    }
    return texture;
}

void TextureLoader::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dist)
{
    SDL_RenderCopy(Game::renderer, texture, &src, &dist);
}

void TextureLoader::clearCache()
{
    for (auto& texture : textureCache) {
        SDL_DestroyTexture(texture.second);
    }
    textureCache.clear();
}