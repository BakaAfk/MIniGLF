    //
    // Created by Baka-tannn on 25/3/2025.
    //

#include "gameRenderer.h"
#include "textureLoader.h"


void GameRenderer::renderMainScreen() {
    // Draw background
    SDL_SetRenderDrawColor(Game::renderer, 132, 171, 60, 100);
    SDL_RenderClear(Game::renderer);
    SDL_Texture *bgTexture = TextureLoader::loadTexture("resources/img/bg.png");
    if (bgTexture) {
        SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(Game::renderer, bgTexture, nullptr, &bgRect);
        SDL_DestroyTexture(bgTexture);
    }

    // Draw title and instructions
    TextRenderer::renderTextCenter(Game::renderer, "TUI DEP TRAI ", SCREEN_WIDTH/2, 100, 48, {0, 0, 0, 255});
    TextRenderer::renderTextCenter(Game::renderer, "Press ENTER to Start", SCREEN_WIDTH/2, 300, 24, {0, 0, 0, 255});
    TextRenderer::renderTextCenter(Game::renderer, "Press ESC to Quit", SCREEN_WIDTH/2, 350, 24, {0, 0, 0, 255});
    SDL_RenderPresent(Game::renderer);
}

void GameRenderer::renderPlayingScreen(bool isDragging, Map *map, Ball* ball, int endX, int endY) {
    if (map) {
        map->drawTile();
        if (ball) {
            ball->drawBall();
        }
    }

    // Draw arrow when dragging
    if (isDragging && ball && ball->velocity.x == 0 && ball->velocity.y == 0) {
        renderArrow(ball, endX, endY);
    }

    // Draw game stats
    renderStats();
    SDL_RenderPresent(Game::renderer);
}

void GameRenderer::renderPauseScreen() {
    // Semi-transparent overlay
    SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 150);
    SDL_Rect overlay = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(Game::renderer, &overlay);

    // Pause text
    TextRenderer::renderTextCenter(Game::renderer, "PAUSED", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 50, 48, WHITE);
    TextRenderer::renderTextCenter(Game::renderer, "Press ESC to Resume", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 50, 24, WHITE);
    TextRenderer::renderTextCenter(Game::renderer, "Press ENTER to The endgame gg", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 100, 24, WHITE);
    SDL_RenderPresent(Game::renderer);
}

void GameRenderer::renderGameOver() {
    // Semi-transparent overlay
    SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 150);
    SDL_Rect overlay = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(Game::renderer, &overlay);

    // Game over text
    TextRenderer::renderTextCenter(Game::renderer, "GAME COMPLETE!", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 100, 48, WHITE);
    TextRenderer::renderTextCenter(Game::renderer, "Maps: " + std::to_string(mapCount), SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 50, 36, WHITE);
    TextRenderer::renderTextCenter(Game::renderer, "Strokes: " + std::to_string(totalStroke), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 36, WHITE);
    TextRenderer::renderTextCenter(Game::renderer, "Avg. Stroke: " + std::to_string(avgStroke), SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 50, 36, WHITE);
    TextRenderer::renderTextCenter(Game::renderer, "Press ENTER to Continue", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 100, 24, WHITE);
    SDL_RenderPresent(Game::renderer);
}

void GameRenderer::renderArrow(Ball* ball, int endX, int endY) {
    float dx = ball->dist.x + BALL_SIZE / 2 - endX;
    float dy = ball->dist.y + BALL_SIZE / 2 - endY;

    // Calculate arrow rotation angle
    float angle = atan2(dy, dx) * 180 / M_PI + 90;

    // Calculate arrow length multiplier
    float multiplier = std::min(sqrt(dx * dx + dy * dy) / 4, 30.0) / 10.0;
    SDL_Rect arrowRect = {
        static_cast<int>(ball->dist.x + BALL_SIZE / 2 - 8),
        static_cast<int>(ball->dist.y + BALL_SIZE / 2 - 32 * multiplier),
        16, static_cast<int>(64 * multiplier)
    };

    // Load and render arrow texture
    SDL_Texture* arrowTexture = TextureLoader::loadTexture("resources/img/point.png");
    if (arrowTexture) {
        SDL_RenderCopyEx(Game::renderer, arrowTexture, nullptr, &arrowRect, angle, nullptr, SDL_FLIP_NONE);
        SDL_DestroyTexture(arrowTexture);
    }
    SDL_RenderPresent(Game::renderer);
}

void GameRenderer::renderStats() {
    std::string mapText = "Map: " + std::to_string(mapCount - 1);
    TextRenderer::renderText(Game::renderer, mapText, 10, 10, 24, WHITE);

    std::string strokeText = "Stroke: " + std::to_string(stroke);
    TextRenderer::renderTextCenter(Game::renderer, strokeText, SCREEN_WIDTH / 2, 10, 24, WHITE);

    avgStroke = (double)totalStroke / mapCount;
    std::string avgStrokeText = "Avg. Stroke: " + std::to_string(avgStroke);
    TextRenderer::renderText(Game::renderer, avgStrokeText, SCREEN_WIDTH - 200, 10, 24, WHITE);
    SDL_RenderPresent(Game::renderer);
}