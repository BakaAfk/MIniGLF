//
// Created by Baka-tannn on 31/3/2025.
//

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL.h>

class Game;
class EventHandler{
public:
    static void handleEvent(Game* game);
private:
    static void handleKeyDown(Game* game, SDL_Keycode key);
    static void handleMouseButtonDown(Game* game);
    static void handleMouseMotion(Game* game);
    static void handleMouseButtonUp(Game* game);
};

#endif //EVENTHANDLER_H

