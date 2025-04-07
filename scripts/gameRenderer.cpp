//
// Created by Baka-tannn on 25/3/2025.
//

#include <cmath>
#include "gameRenderer.h"
#include "textureLoader.h"
#include "globalVar.h"

// Global variables
int GameRenderer::baseY = 200;
double GameRenderer::time = 0;
int GameRenderer::aniSpeed = 10;

void GameRenderer::renderMainScreen() { // Render main screen
    int titleY;
    // Draw background
    SDL_Texture *bgTexture = TextureLoader::loadTexture("resources/img/bg1.png");
    SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    TextureLoader::DrawAsset(bgTexture, bgRect, 0);
    // Draw title and animation
    titleY = baseY + std::sin(time/M_PI) * 20;
    time += 0.5;
    SDL_Texture *titleTexture = TextureLoader::loadTexture("resources/img/title.png");
    SDL_Rect titleRect = {SCREEN_WIDTH / 2 - 200, titleY, 400, 100};
    TextureLoader::DrawAsset(titleTexture, titleRect, 0);

    // Draw text
    renderTextBackground(SCREEN_WIDTH/2 - 200, 350 - 5, 400, TEXTH + 10, GRAY_BG);
    TextRenderer::renderTextCenter(Game::renderer, "Press ENTER to Start", SCREEN_WIDTH/2, 350, DEFAULT_FONT_SIZE, WHITE);

    renderTextBackground(SCREEN_WIDTH/2 - 200, 400 - 5, 400, TEXTH + 10, GRAY_BG);
    TextRenderer::renderTextCenter(Game::renderer, "Press ESC to Quit", SCREEN_WIDTH/2, 400, DEFAULT_FONT_SIZE, WHITE);

    renderTextBackground(SCREEN_WIDTH/2 - 200, 450 - 5, 400, TEXTH + 10, GRAY_BG);
    TextRenderer::renderTextCenter(Game::renderer, "Press I for Instructions", SCREEN_WIDTH/2, 450, DEFAULT_FONT_SIZE, WHITE);
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

void GameRenderer::renderInstructions() {
    SDL_Texture *bgTexture = TextureLoader::loadTexture("resources/img/bg1.png");
    SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    TextureLoader::DrawAsset(bgTexture, bgRect, 0);

    SDL_Texture *titleTexture = TextureLoader::loadTexture("resources/img/instructions.png");
    SDL_Rect titleRect = {SCREEN_WIDTH / 2 - 200, 200, 400, 100};
    TextureLoader::DrawAsset(titleTexture, titleRect, 0);

    int y = 300;
    for (const std::string& line : instructions) {
        TextRenderer::renderTextCenter(Game::renderer, line, SCREEN_WIDTH / 2, y, DEFAULT_FONT_SIZE, BLACK);
        y += 30;
    }
}


void GameRenderer::renderPauseScreen() { // Render pause screen
    // Load bg
    SDL_Texture *bgTexture = TextureLoader::loadTexture("resources/img/bg1.png");
    SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    TextureLoader::DrawAsset(bgTexture, bgRect, 0);

    // Load pause title
    SDL_Texture *pauseTexture = TextureLoader::loadTexture("resources/img/pause.png");
    SDL_Rect pauseRect = {SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 100, 400, 100};
    TextureLoader::DrawAsset(pauseTexture, pauseRect, 0);

    // Render text
    GameRenderer::renderTextBackground(SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 + 50 - 5, 400, TEXTH + 10, GRAY_BG);
    TextRenderer::renderTextCenter(Game::renderer, "Press ESC to Resume", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 50, DEFAULT_FONT_SIZE, WHITE);
    GameRenderer::renderTextBackground(SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 + 100 - 5, 400, TEXTH + 10, GRAY_BG);
    TextRenderer::renderTextCenter(Game::renderer, "Press ENTER to Exit", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 100, DEFAULT_FONT_SIZE, WHITE);
}

void GameRenderer::renderGameOver() {
    // Load bg
    SDL_Texture *bgTexture = TextureLoader::loadTexture("resources/img/bg_end.png");
    SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    TextureLoader::DrawAsset(bgTexture, bgRect, 0);

    // Load title
    SDL_Texture *gameOverTexture = TextureLoader::loadTexture("resources/img/gameover.png");
    SDL_Rect gameOverRect = {SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 175, 400, 100};
    TextureLoader::DrawAsset(gameOverTexture, gameOverRect, 0);

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
    if (isPowerUp) {
        SDL_Texture* PUarrowTexture = TextureLoader::loadTexture("resources/img/pointPU.png");
        TextureLoader::DrawAsset(PUarrowTexture, arrowRect, angle);
    } else {
        SDL_Texture* arrowTexture = TextureLoader::loadTexture("resources/img/point.png");
        TextureLoader::DrawAsset(arrowTexture, arrowRect, angle);
    }
}

// Render transparent background for text
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

    std::string powerUpText = "Power Up: " + std::to_string(havePowerUp);
    TTF_SizeText(TextRenderer::getFont(), powerUpText.c_str(), &textW, &textH);
    renderTextBackground(SCREEN_WIDTH - 115 - 5, SCREEN_HEIGHT - 50 - 5, textW + 10, textH + 10, GRAY_BG);
    TextRenderer::renderText(Game::renderer, powerUpText, SCREEN_WIDTH - 115,SCREEN_HEIGHT - 50 , DEFAULT_FONT_SIZE, WHITE);
}

