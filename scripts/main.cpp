#include "audio.h"
#include "entity.h"
#include "game.h"
#include <iostream>
#include <cmath>
#include <vector>

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const int midX = SCREEN_WIDTH / 2, midY = SCREEN_HEIGHT / 2, veloY = 5;




int main(int argc , char* argv[])
{
    Game *game = new Game();
    game->init("mmb", SCREEN_WIDTH, SCREEN_HEIGHT);
    // Load bgm
    Audio("resources/sfx/bg.mp3", -1, 10);

    while (game->isRunning())
    {
        game->handleEvent();
        game->update();
        game->render();

        SDL_Delay(20);
    }
    game->clean();
    return 0;
}
