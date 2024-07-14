
#include "GameManager.hpp"

GameManager::GameManager() : game(nullptr), lib(nullptr), gi(nullptr), mss(nullptr)
{
    Say("Game Manager", WIN_COLOR_GRAY);

    // 初始化
    // 顺序不能变
    gi = new GraphInterface();
    mss = new MessageSystem();
    lib = new Library();
    game = new Game(gi, mss);

    // Initialize the game
    Say("Game Manager Created", WIN_COLOR_GRAY);
}

GameManager::~GameManager()
{
    Say("Game Manager Over", WIN_COLOR_GRAY);
    // 退出，释放资源
    // 顺序不能变
    delete game;
    delete lib;
    delete mss;
    delete gi;

    // Destroy the game
    Say("Game Manager Destroyed", WIN_COLOR_GRAY);
}

// 返回值：0正常退出，1初始化失败，2运行失败，3退出失败
short GameManager::RUN()
{
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
        if (del_time < RATE_SLEEP)
        {
            Sleep(RATE_SLEEP - del_time);
        }
        str_time = clock();
    } while (game->Update() == 0);
    Say("Game Manager Stop", WIN_COLOR_GREEN);
    EndBatchDraw();

    return 0;
}
