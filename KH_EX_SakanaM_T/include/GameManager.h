
#pragma once

#include <iostream>
#include <ctime>

#include <graphics.h>

#include "Input.h"
#include "Library.h"
#include "Game.h"

// 总管
class GameManager
{
public:
    GameManager();
    ~GameManager();

    // 基础循环
    void
    RUN()
    {
        init();

        unsigned long start_time = 0;
        unsigned long end___time = 0;
        unsigned long delta_time = 0;

        BeginBatchDraw();
        do
        {
            FlushBatchDraw();
            end___time = clock();
            delta_time = end___time - start_time;
            std::cout << delta_time << std::endl;
            if (delta_time < SLEEP)
            {
                Sleep(SLEEP - delta_time);
            }
            start_time = clock();
        } while (update());
        EndBatchDraw();

        over();
    }

private:
    // 窗口句柄
    HWND graph_HWND = nullptr;

    Library library;
    Input input;
    Game game;

    // 各项参数
    const int FRAME_RATE = 60;
    const int SLEEP = 1000 / FRAME_RATE;

    const int GRAPHWIDE = 1600;
    const int GRAPHHIGH = 900;
    const int GRAPHLONG = 1600 * 900;

    const int wx = 1176;
    const int wy = 1569;

    // 初始化
    inline void
    init()
    {
        // 初始化窗口
        graph_HWND = initgraph(GRAPHWIDE, GRAPHHIGH, 1);
        SetWindowPos(graph_HWND, nullptr, -1374, 793, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        SetWindowText(graph_HWND, _T("Sakana"));

        // 初始化资源
        library.Init();

        // 初始化game
        game.Init();
    }

    inline bool
    update()
    {
        return game.Update();
    }

    // 释放内存
    inline void
    over()
    {
        closegraph();
    }
};
