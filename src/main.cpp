
#include "game_systems.hpp"

int
main()
{
    Say("START", WIN_COLOR_WHITE, KHCOLOR_BLACK);

    GameManager g;
    g.RUN();

    Say("OVER", WIN_COLOR_WHITE, KHCOLOR_BLACK);

    return 0;
}
