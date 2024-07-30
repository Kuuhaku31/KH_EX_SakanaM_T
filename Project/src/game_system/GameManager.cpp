
#include "game_systems.hpp"

#define GAME_RATE 60
#define RATE_SLEEP 1000 / GAME_RATE

// 返回值：0正常退出，1初始化失败，2运行失败，3退出失败
int
GameManager::RUN()
{
    init();

    unsigned long str_time = clock();
    unsigned long end_time = 0;
    unsigned long del_time = 0;

    BeginBatchDraw();
    Say("Game Manager Running", WIN_COLOR_GREEN);
    do
    { // 开始游戏主循环
        FlushBatchDraw();
        end_time = clock();
        del_time = end_time - str_time;
        if(del_time < RATE_SLEEP)
        {
            Sleep(RATE_SLEEP - del_time);
        }
        str_time = clock();
    } while(game->Update());
    Say("Game Manager Stop", WIN_COLOR_GREEN);
    EndBatchDraw();

    exit();

    return 0;
}

void
GameManager::init()
{
    // 初始化
    gi   = new GraphInterface;
    lib  = new Library;
    game = new Game(gi, lib);

    char name[] = "Game";
    gi->NewGraph(GRAPHWIDE, GRAPHHIGH, GRAPH_X, GRAPH_Y, name);

    // Initialize the game
    Say("Game Manager Created", WIN_COLOR_GRAY);
}

void
GameManager::exit()
{
    gi->CloseGraph();

    // 退出，释放资源
    // 顺序不能变
    delete game;
    delete lib;
    delete gi;

    Say("Game Manager Exit", WIN_COLOR_GRAY);
}
