//
// Created by Baka-tannn on 1/4/2025.
//

#include <cmath>
#include "eventHandler.h"
#include "game.h"
#include "audio.h"

void EventHandler::handleEvent(Game* game) { // Get event
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

void EventHandler::handleKeyDown(Game* game, SDL_Keycode key) { // Key down
    switch (key) {
        case SDLK_ESCAPE: // ESC
            if (game->getState() == PLAYING) {
                game->setState(PAUSE);
            } else if (game->getState() == PAUSE) {
                game->setState(PLAYING);
            } else if (game->getState() == START_SCREEN) {
                game->setState(EXIT);
            }
            break;

        case SDLK_RETURN: //ENTER
            if (game->getState() == START_SCREEN) {
                if (Game::map) {
                    delete Game::map;
                    Game::map = nullptr;
                }
                Game::map = new Map();
                game->setState(PLAYING);
            } else if (game->getState() == GAME_OVER) {
                game->resetStat();
                game->setState(START_SCREEN);
            } else if (game->getState() == PAUSE) {
                game->setState(GAME_OVER);
            }
            break;
        case SDLK_m: // MuteBG
            muteBG = !muteBG;
            if (muteBG) {
                Audio::PauseAudio();
            } else {
                Audio::ResumeAudio();
            }


            break;
        default:
            break;
    }
}

void EventHandler::handleMouseButtonDown(Game* game) { // Mouse click down
    if (game->getState() == PLAYING && Game::map->getBall() && Game::map->getBall()->getVelocity().x == 0 && Game::map->getBall()->getVelocity().y == 0) {
        SDL_GetMouseState(&game->startX, &game->startY);
        game->setDragging(true);
    }
}

void EventHandler::handleMouseMotion(Game* game) { // Mouse movement
    if (game->getState() == PLAYING && game->getDragging()) {
        SDL_GetMouseState(&game->endX, &game->endY);

    }
}

void EventHandler::handleMouseButtonUp(Game* game) { // Mouse click release
    if (game->getState() == PLAYING && game->getDragging()) {
        game->setDragging(false);
        SDL_GetMouseState(&game->endX, &game->endY);
        Ball* ball = Game::map->getBall();
        if (ball->getVelocity().x == 0 && ball->getVelocity().y == 0) {
            int posX = ball->getDist().x + BALL_SIZE / 2;
            int posY = ball->getDist().y + BALL_SIZE / 2;

            double dx = posX - game->endX;
            double dy = posY - game->endY;
            double distance = std::sqrt(dx * dx + dy * dy);
            double maxForce = 30.0;
            double force = std::min(distance / 4, maxForce);
            double angle = std::atan2(dy, dx);

            ball->setVelocity(Vector(cos(angle) * force, sin(angle) * force));

            stroke++;
            totalStroke++;
            Audio::PlaySFX("resources/sfx/swing.mp3", 10);
        }
    }
}
