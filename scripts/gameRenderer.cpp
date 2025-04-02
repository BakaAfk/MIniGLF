//
// Created by Baka-tannn on 25/3/2025.
//

#include <cmath>
#include "gameRenderer.h"
#include "textureLoader.h"
#include "globalVar.h"

// Tilte animation thingy
int GameRenderer::baseY = 200;
double GameRenderer::time = 0;
int GameRenderer::aniSpeed = 10;

void GameRenderer::renderMainScreen() { // Render main screen
    int textH, titleY;
    // Draw background
    SDL_Texture *bgTexture = TextureLoader::loadTexture("resources/img/bg1.png");
    if (bgTexture) {
        SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(Game::renderer, bgTexture, nullptr, &bgRect);
        SDL_DestroyTexture(bgTexture);
    }
    // Draw title and animation
    titleY = baseY + std::sin(time/M_PI) * 20;
    time += 0.5;
    SDL_Texture *titleTexture = TextureLoader::loadTexture("resources/img/title.png");
    if (titleTexture) {
        SDL_Rect titleRect = {SCREEN_WIDTH / 2 - 200, titleY, 400, 100};
        SDL_RenderCopy(Game::renderer, titleTexture, nullptr, &titleRect);
        SDL_DestroyTexture(titleTexture);
    }

    // Draw text
    renderTextBackground(SCREEN_WIDTH/2 - 200, 350 - 5, 400, TEXTH + 10, GRAY_BG);
    TextRenderer::renderTextCenter(Game::renderer, "Press ENTER to Start", SCREEN_WIDTH/2, 350, 24, WHITE);

    renderTextBackground(SCREEN_WIDTH/2 - 200, 400 - 5, 400, TEXTH + 10, GRAY_BG);
    TextRenderer::renderTextCenter(Game::renderer, "Press ESC to Quit", SCREEN_WIDTH/2, 400, DEFAULT_FONT_SIZE, WHITE);

    TextRenderer::renderText(Game::renderer, "Press M to mute/unmute BG music", SCREEN_WIDTH - 235, SCREEN_HEIGHT - 50, 15, BLACK);
}

void GameRenderer::renderPlayingScreen(bool isDragging, Map *map, Ball* ball, int endX, int endY) { // Render playing screen
    // Draw ball and map
    if (map) {
        map->drawMap();
        if (ball) {
            ball->drawBall();
        }
    }

    // Draw arrow when dragging
    if (isDragging && ball && ball->getVelocity().x == 0 && ball->getVelocity().y == 0) {
        renderArrow(ball, endX, endY);
    }

    // Draw game stats
    renderStats();
}

void GameRenderer::renderPauseScreen() { // Render pause screen
    // Load bg
    SDL_Texture *bgTexture = TextureLoader::loadTexture("resources/img/bg1.png");
    if (bgTexture) {
        SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(Game::renderer, bgTexture, nullptr, &bgRect);
        SDL_DestroyTexture(bgTexture);
    }

    // Load pause title
    SDL_Texture *pauseTexture = TextureLoader::loadTexture("resources/img/pause.png");
    if (pauseTexture) {
        SDL_Rect pauseRect = {SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 100, 400, 100};
        SDL_RenderCopy(Game::renderer, pauseTexture, nullptr, &pauseRect);
        SDL_DestroyTexture(pauseTexture);
    }

    // Render text
    GameRenderer::renderTextBackground(SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 + 50 - 5, 400, TEXTH + 10, GRAY_BG);
    TextRenderer::renderTextCenter(Game::renderer, "Press ESC to Resume", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 50, DEFAULT_FONT_SIZE, WHITE);
    GameRenderer::renderTextBackground(SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 + 100 - 5, 400, TEXTH + 10, GRAY_BG);
    TextRenderer::renderTextCenter(Game::renderer, "Press ENTER to Exit", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 100, DEFAULT_FONT_SIZE, WHITE);
}

void GameRenderer::renderGameOver() {
    // Load bg
    SDL_Texture *bgTexture = TextureLoader::loadTexture("resources/img/bg_end.png");
    if (bgTexture) {
        SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(Game::renderer, bgTexture, nullptr, &bgRect);
        SDL_DestroyTexture(bgTexture);
    }

    // Load title
    SDL_Texture *gameOverTexture = TextureLoader::loadTexture("resources/img/gameover.png");
    if (gameOverTexture) {
        SDL_Rect gameOverRect = {SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 175, 400, 100};
        SDL_RenderCopy(Game::renderer, gameOverTexture, nullptr, &gameOverRect);
        SDL_DestroyTexture(gameOverTexture);
    }

    // Game over text
    int textW, textH;
    std::string mapText = "Maps: " + std::to_string(mapCount - 1);
    TTF_SizeText(TextRenderer::getFont(), mapText.c_str(), &textW, &textH);
    TextRenderer::renderTextCenter(Game::renderer, "Maps: " + std::to_string(mapCount - 1), SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 45, 36, BLACK);
    TextRenderer::renderTextCenter(Game::renderer, "Strokes: " + std::to_string(totalStroke), SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 5, 36, BLACK);
    TextRenderer::renderTextCenter(Game::renderer, "Avg. Stroke: " + std::to_string(avgStroke), SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 45, 36, BLACK);
    TextRenderer::renderTextCenter(Game::renderer, "Press ENTER to Continue", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 95, DEFAULT_FONT_SIZE, BLACK);
}

void GameRenderer::renderArrow(Ball* ball, int endX, int endY) { // Render arrow
    // Arrow lengths
    double dx = ball->getDist().x + BALL_SIZE / 2 - endX;
    double dy = ball->getDist().y + BALL_SIZE / 2 - endY;
    // Arrow rotation angle
    double angle = atan2(dy, dx) * 180 / M_PI + 90;

    // Arrow length multiplier
    double multiplier = std::min(sqrt(dx * dx + dy * dy) / 4, 30.0) / 10.0; // Max multiplier = 3
    SDL_Rect arrowRect = {
        static_cast<int>(ball->getDist().x + BALL_SIZE / 2 - 8), // Move arrow to the center of the ball
        static_cast<int>(ball->getDist().y + BALL_SIZE / 2 - 32 * multiplier),
        16, static_cast<int>(64 * multiplier)
    };

    // Draw arrow texture
    SDL_Texture* arrowTexture = TextureLoader::loadTexture("resources/img/point.png");
    if (arrowTexture) {
        SDL_RenderCopyEx(Game::renderer, arrowTexture, nullptr, &arrowRect, angle, nullptr, SDL_FLIP_NONE);
        SDL_DestroyTexture(arrowTexture);
    }
}

// render transparent background for text
void GameRenderer::renderTextBackground(int x, int y, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer, color.r, color.g, color.b, color.a);
    SDL_Rect bgRect = {x, y, w, h};
    SDL_RenderFillRect(Game::renderer, &bgRect);
}

void GameRenderer::renderStats() { // Render game stats
    int textW, textH;
    std::string mapText = "Map: " + std::to_string(mapCount - 1);
    TTF_SizeText(TextRenderer::getFont(), mapText.c_str(), &textW, &textH);
    renderTextBackground(5, 5, textW + 10, textH + 10, GRAY_BG);
    TextRenderer::renderText(Game::renderer, mapText, 10, 10, DEFAULT_FONT_SIZE, WHITE);

    std::string strokeText = "Stroke: " + std::to_string(stroke);
    TTF_SizeText(TextRenderer::getFont(), strokeText.c_str(), &textW, &textH);
    renderTextBackground(SCREEN_WIDTH / 2 - textW / 2 - 5, 5, textW + 10, textH + 10, GRAY_BG);
    TextRenderer::renderTextCenter(Game::renderer, strokeText, SCREEN_WIDTH / 2, 10, DEFAULT_FONT_SIZE, WHITE);

    avgStroke = static_cast<double>(totalStroke) / std::max(mapCount - 1, 1);
    std::string avgStrokeText = "Avg. Stroke: " + std::to_string(avgStroke);
    TTF_SizeText(TextRenderer::getFont(), avgStrokeText.c_str(), &textW, &textH);
    renderTextBackground(SCREEN_WIDTH - 200 - 5, 5, textW + 10, textH + 10, GRAY_BG);
    TextRenderer::renderText(Game::renderer, avgStrokeText, SCREEN_WIDTH - 200, 10, DEFAULT_FONT_SIZE, WHITE);
}

