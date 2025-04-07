//
// Created by Baka-tannn on 1/4/2025.
//

#include <cmath>
#include "eventHandler.h"
#include "game.h"
#include "audio.h"

void EventHandler::handleEvent(Game* game)
{
    while (SDL_PollEvent(&Game::event)) {
        switch (Game::event.type) {
            case SDL_QUIT:
                Game::running = false;
                break;

            case SDL_KEYDOWN:
                handleKeyDown(game, Game::event.key.keysym.sym);
                break;

            case SDL_MOUSEBUTTONDOWN:
                handleMouseButtonDown(game);
                break;

            case SDL_MOUSEMOTION:
                handleMouseMotion(game);
                break;

            case SDL_MOUSEBUTTONUP:
                handleMouseButtonUp(game);
                break;

            default:
                break;
        }
    }
}

void EventHandler::handleKeyDown(Game* game, SDL_Keycode key)
{
    switch (key) {
        case SDLK_ESCAPE:  // ESC
            if (game->getState() == PLAYING) {
                game->setState(PAUSE);
            }
            else if (game->getState() == PAUSE) {
                game->setState(PLAYING);
            }
            else if (game->getState() == START_SCREEN) {
                game->setState(EXIT);
            }
            else if (game->getState() == INSTRUCTIONS) {
                game->setState(START_SCREEN);
            }
            break;

        case SDLK_RETURN:  // ENTER
            if (game->getState() == START_SCREEN) {
                Game::map = new Map();
                game->setState(PLAYING);
            }
            else if (game->getState() == GAME_OVER) {
                game->resetStat();
                game->setState(START_SCREEN);
            }
            else if (game->getState() == PAUSE) {
                game->setState(GAME_OVER);
            }
            break;

        case SDLK_m:  // Mute/Unmute BGM
            muteBG = !muteBG;
            if (muteBG) {
                Audio::PauseAudio();
            }
            else {
                Audio::ResumeAudio();
            }
            break;

        case SDLK_p:  // Toggle power-up
            if (game->getState() == PLAYING &&
                havePowerUp &&
                Game::map->getBall()->getVelocity() == Vector(0, 0)) {
                isPowerUp = !isPowerUp;
                Audio::PlaySFX("resources/sfx/powerup.mp3", 15);
            }
            break;

        case SDLK_i:  // Instructions
            if (game->getState() == START_SCREEN) {
                game->setState(INSTRUCTIONS);
            }
            break;

        default:
            break;
    }
}

void EventHandler::handleMouseButtonDown(Game* game)
{
    if (game->getState() == PLAYING &&
        Game::map->getBall() &&
        Game::map->getBall()->getVelocity() == Vector(0, 0)) {
        SDL_GetMouseState(&game->startX, &game->startY);
        game->setDragging(true);
    }

    if (game->getState() == PLAYING && isPowerUp && !havePowerUp) {
        isPowerUp = false;
    }
}

void EventHandler::handleMouseMotion(Game* game)
{
    if (game->getState() == PLAYING && game->getDragging()) {
        SDL_GetMouseState(&game->endX, &game->endY);
    }
}

void EventHandler::handleMouseButtonUp(Game* game)
{
    if (game->getState() == PLAYING && game->getDragging()) {
        game->setDragging(false);
        SDL_GetMouseState(&game->endX, &game->endY);

        Ball* ball = Game::map->getBall();
        if (ball->getVelocity() == Vector(0, 0)) {
            // Ball position
            int posX = ball->getDist().x + BALL_SIZE / 2;
            int posY = ball->getDist().y + BALL_SIZE / 2;

            // Calculate direction and force
            double dx = posX - game->endX;
            double dy = posY - game->endY;
            double distance = std::sqrt(dx * dx + dy * dy);
            double maxForce = 30.0;
            double force = std::min(distance / 4, maxForce);
            double angle = std::atan2(dy, dx);

            // Apply force
            ball->setVelocity(Vector(cos(angle) * force, sin(angle) * force));

            // Update game state
            stroke++;
            totalStroke++;
            Audio::PlaySFX("resources/sfx/swing.mp3", 10);

            if (isPowerUp) {
                havePowerUp = false;
            }
        }
    }
}