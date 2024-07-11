
#include "GameManager.h"

#include <iostream>
#include <ctime>

#include <graphics.h>

GameManager::GameManager()
{
    // Initialize the game
    std::cout << "Game Manager Created" << std::endl;
}

GameManager::~GameManager()
{
    // Destroy the game
    std::cout << "Game Manager Destroyed" << std::endl;
}

// 返回值：0正常退出，1初始化失败，2运行失败，3退出失败
short GameManager::RUN()
{
    std::cout << "Game Manager Running" << std::endl;

    // 初始化
    try
    {
        // 初始化窗口
        HWND h = initgraph(GRAPHWIDE, GRAPHHIGH, 1);
        SetWindowPos(h, nullptr, GRAPH_X, GRAPH_Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        SetWindowText(h, _T(GAME_NAME));

        // 初始化资源
        library.Init();

        // 初始化game
        game.Init();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << "Game Manager Init Failed" << std::endl;

        return 1;
    }
    std::cout << "Game Manager Init Success" << std::endl;

    unsigned long str_time = clock();
    unsigned long end_time = 0;
    unsigned long del_time = 0;

    BeginBatchDraw();
    std::cout << "Game Manager Running" << std::endl;
    do
    { // 开始游戏主循环
        FlushBatchDraw();
        end_time = clock();
        del_time = end_time - str_time;
        std::cout << del_time << std::endl; // 输出帧间隔时间，用于调试
        if (del_time < RATE_SLEEP)
        {
            Sleep(RATE_SLEEP - del_time);
        }
        str_time = clock();
    } while (game.Update() == 0);
    std::cout << "Game Manager Stop" << std::endl;
    EndBatchDraw();

    // 退出，释放资源
    {
        // 将来一些退出时的操作，如释放资源等……
        closegraph();
    }

    std::cout << "Game Manager Over" << std::endl;
    return 0;
}
