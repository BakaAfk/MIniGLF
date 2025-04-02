//
// Created by Baka-tannn on 21/2/2025.
//

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "globalVar.h"
#include "textRenderer.h"
#include "map.h"
class Map;
class EventHandler;
class Game {
private:
    SDL_Window *window;
    double angle = 0;
    bool isDragging = false;
    TextRenderer textRenderer;
    GameState gameState;

public:
    Game();
    ~Game();
    void init();
    void handleEvent();
    void update();
    bool isRunning();
    void render();
    void clean();
    GameState getState() const;
    void setState(GameState state);
    void resetStat();
    void setDragging(bool dragging) { isDragging = dragging; }
    bool getDragging() { return isDragging; }

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool running;
    static Map* map;
    int startX, startY, endX, endY;
};

#endif //GAME_H
