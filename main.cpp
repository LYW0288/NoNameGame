#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow *NoName = new GameWindow();

    NoName->game_play();

    delete NoName;
    return 0;
}
