
#include "GameManager.hpp"

#include <iostream>
#include <ctime>

#include <graphics.h>

GameManager::GameManager()
{
    // Initialize the game
    mss.Say("Game Manager Created", WIN_COLOR_GRAY);
}

GameManager::~GameManager()
{
    // Destroy the game
    mss.Say("Game Manager Destroyed", WIN_COLOR_GRAY);
}

// 返回值：0正常退出，1初始化失败，2运行失败，3退出失败
short GameManager::RUN()
{
    mss.Say("Game Manager Running", WIN_COLOR_GRAY);

    // 初始化
    // 初始化窗口
    HWND h = initgraph(GRAPHWIDE, GRAPHHIGH, 1);
    SetWindowPos(h, nullptr, GRAPH_X, GRAPH_Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    SetWindowText(h, _T(GAME_NAME));

    graph_data gd = {h, GetImageHDC(nullptr), (unsigned int *)GetImageBuffer(nullptr), GRAPHWIDE, GRAPHHIGH, GRAPHLONG, GRAPHWIDE / 2, GRAPHHIGH / 2};
    mss.Set_graph_data(gd);

    // 初始化资源
    lib.Init();

    // 初始化game
    game.Init(&mss);

    unsigned long str_time = clock();
    unsigned long end_time = 0;
    unsigned long del_time = 0;

    BeginBatchDraw();
    mss.Say("Game Manager Running", WIN_COLOR_GREEN);
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
    } while (game.Update() == 0);
    mss.Say("Game Manager Stop", WIN_COLOR_GREEN);
    EndBatchDraw();

    // 退出，释放资源
    {
        // 将来一些退出时的操作，如释放资源等……
        closegraph();
    }

    mss.Say("Game Manager Over", WIN_COLOR_GRAY);
    return 0;
}
