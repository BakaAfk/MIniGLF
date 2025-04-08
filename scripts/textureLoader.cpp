//
// Created by Baka-tannn on 21/2/2025.
//

#include <SDL_image.h>
#include "textureLoader.h"
#include "game.h"

SDL_Texture *TextureLoader::loadTexture(const char *fileName)
{
    SDL_Surface* surface = IMG_Load(fileName); // Load image
    if (!surface) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Khong the khoi tao surface", nullptr);
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface); // Free surface
    if (!texture) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Khong the khoi tao texture", nullptr);
        return nullptr;
    }
    return texture;
}

void TextureLoader::DrawMapObject(SDL_Texture *texture, SDL_Rect src, SDL_Rect dist) // Draw map object
{
    SDL_RenderCopy(Game::renderer, texture, &src, &dist);
    // Not destroying texture here because it will re-use in Map spawn
    // Will be destroyed in Map destructor
}

void TextureLoader::DrawAsset(SDL_Texture *texture, SDL_Rect dist, double angle, SDL_RendererFlip flip) // Draw asset
{
    SDL_RenderCopyEx(Game::renderer, texture, nullptr, &dist, angle, nullptr, flip);
    SDL_DestroyTexture(texture);
}

