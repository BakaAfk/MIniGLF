//
// Created by Baka-tannn on 23/2/2025.
//
#include "ball.h"
#include "textureLoader.h"
#include "game.h"
#include "audio.h"

Ball::Ball(Vector position, SDL_Texture *texture): Entity(position, texture)
{
    ball = TextureLoader::loadTexture("resources/img/ball.png");
    fire = TextureLoader::loadTexture("resources/img/boom.jpg");
    bounce = Mix_LoadWAV("resources/sfx/boom.mp3");
    src.x = src.y = 0;
    src.w = dist.w = src.h = dist.h = 32;
    dist.x = position.x;
    dist.y = position.y;
}

Ball::~Ball()
{
    if (ball)
    {
        SDL_DestroyTexture(ball);
    }
    if (fire)
    {
        SDL_DestroyTexture(fire);
    }
    if (bounce)
    {
        Mix_FreeChunk(bounce);
    }
}

void Ball::drawBall()
{
    TextureLoader::Draw(ball, src, dist);
    if (isOnfire) {
        int texW, texH;
        SDL_QueryTexture(fire, NULL, NULL, &texW, &texH);
        SDL_Rect temp1, temp2;
        temp1.x = 0;
        temp1.y = 0;
        temp1.w = texW;
        temp1.h = texH;
        temp2.x = fireX;
        temp2.y = fireY;
        temp2.w = 32;
        temp2.h = 32;
        TextureLoader::Draw(fire, temp1, temp2);

    }
}

void Ball::update() {
    int veloX = std::abs(velocity.x);
    int veloY = std::abs(velocity.y);
    if (veloX > 0) {
        velocity.x -= (velocity.x / veloX) * friction;
    }
    if (veloY > 0) {
        velocity.y -= (velocity.y / veloY) * friction;
    }
    if (SDL_GetTicks() - fireTimer > 3000) {
        isOnfire = false;
    }
    dist.x += velocity.x;
    dist.y += velocity.y;

    if (dist.x < 0 || dist.x > 960 - 32) {
        velocity.x = -velocity.x;
        isOnfire = true;
        fireTimer = SDL_GetTicks();
        fireX = dist.x;
        fireY = dist.y;
        Mix_PlayChannel(-1, bounce, 0);

    }
    if (dist.y < 0 || dist.y > 640 - 32) {
        velocity.y = -velocity.y;
        TextureLoader::Draw(fire, src, dist);
        isOnfire = true;
        fireTimer = SDL_GetTicks();
        fireX = dist.x;
        fireY = dist.y;
        Mix_PlayChannel(-1, bounce, 0);
    }

}

