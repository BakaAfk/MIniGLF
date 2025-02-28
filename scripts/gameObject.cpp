//
// Created by Baka-tannn on 23/2/2025.
//
#include "gameObject.h"
#include "textureLoader.h"
#include "game.h"

GameObject::GameObject(const char *textureSheet, int x, int y, int w, int h)
{
    this->texture = TextureLoader::loadTexture(textureSheet);
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

GameObject::~GameObject()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

void GameObject::update() {
    int texW, texH;
    SDL_QueryTexture(this->texture, NULL, NULL, &texW, &texH);

    src.x = 0;
    src.y = 0;
    src.w = texW;
    src.h = texH;

    dist.x = x;
    dist.y = y;
    dist.w = w;
    dist.h = h;

}

void GameObject::render() {
    SDL_RenderCopy(Game::renderer, texture, &src, &dist);
}
