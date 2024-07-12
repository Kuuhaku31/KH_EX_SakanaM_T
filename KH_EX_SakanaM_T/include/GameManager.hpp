
#pragma once

#include "Game.hpp"
#include "Library.hpp"
#include "MessageSystem.hpp"

#define GAME_RATE 60
#define RATE_SLEEP 1000 / GAME_RATE

#define GRAPHWIDE 1600
#define GRAPHHIGH 900
#define GRAPHLONG 1600 * 900

#define GRAPH_X 40
#define GRAPH_Y 30

#define GAME_NAME "Sakana"

// 引入库
class GameManager
{
public:
    GameManager();
    ~GameManager();

    // 返回值：0正常退出，1初始化失败，2运行失败，3退出失败
    short RUN();

private:
    Game game;
    Library lib;
    MessageSystem mss;
};
