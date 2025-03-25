#include "audio.h"
#include "entity.h"
#include "game.h"
#include <cmath>

int main(int argc , char* argv[])
{
    Game *game = new Game();
    game->init();
    // Load bgm
    Audio("resources/sfx/bg.mp3", -1, 10);

    while (game->isRunning())
    {
        game->handleEvent();
        game->update();
        game->render();

        SDL_Delay(1000 / 60);
    }
    game->clean();
    delete game;
    return 0;
}
