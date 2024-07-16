
#include "GameManager.hpp"

GameManager::GameManager()
{
    // 初始化
    // 顺序不能变
    mss = new MessageSystem();

    gi = new GraphInterface(mss);
    lib = new Library();
    game = new Game(mss, gi, lib);

    // Initialize the game
    Say("Game Manager Created", WIN_COLOR_GRAY);
}

GameManager::~GameManager()
{
    // 退出，释放资源
    // 顺序不能变
    delete game;
    delete lib;
    delete gi;

    delete mss;
    Say("Game Manager Exit", WIN_COLOR_GRAY);
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
