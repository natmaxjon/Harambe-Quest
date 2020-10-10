#include "Configuration.h"
#include "GameLoop.h"

int main()
{
    GameLoop game{GAME_WIDTH, GAME_HEIGHT, GAME_TITLE, WINDOW_STYLE};
    game.run();
    return EXIT_SUCCESS;
}
