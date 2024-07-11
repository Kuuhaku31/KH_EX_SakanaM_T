
#include "Game.h"

#include <iostream>

Game::Game()
{
    // Initialize the game
    std::cout << "Game Created" << std::endl;
}

Game::~Game()
{
    // Destroy the game
    std::cout << "Game Destroyed" << std::endl;
}

short Game::Init()
{
    // Initialize the game
    std::cout << "Game Init" << std::endl;

    // Initialize Game...

    std::cout << "Game Init Success" << std::endl;
    return 0;
}

// 只有返回值为0时才会继续运行，为1时正常退出，其他情况表示运行失败
short Game::Update()
{
    return 1;
}

short Game::Exit()
{
    // Exit the game
    std::cout << "Game Exit" << std::endl;

    // Exit Game...

    std::cout << "Game Exit Success" << std::endl;
    return 0;
}
