#include "audio.h"
#include "game.h"

int main(int argc , char* argv[])
{
    Game *game = new Game();
    game->init();
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
