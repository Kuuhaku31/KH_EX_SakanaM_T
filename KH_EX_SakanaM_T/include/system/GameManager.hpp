
#pragma once

#include "Game.hpp"

// 引入库
class GameManager
{
public:
    GameManager();
    ~GameManager();

    // 返回值：0正常退出，1初始化失败，2运行失败，3退出失败
    short RUN();

private:
    Game *game;

    Library *lib;
    GraphInterface *gi;
    MessageSystem *mss;
};
