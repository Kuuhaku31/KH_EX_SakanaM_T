
#include "Game.h"

#include <windows.h>
#include <iostream>
#include <conio.h>

#include "MessageSystem.h"

// 设置控制台文字颜色的函数
void SetConsoleColor(WORD color)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台输出的句柄
    SetConsoleTextAttribute(hConsoleOutput, color);          // 设置文字和背景颜色
}

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

short Game::Init(MessageSystem *ms)
{
    // Initialize the game
    std::cout << "Game Init" << std::endl;

    // Initialize Game...
    message_system = ms;

    std::cout << "Game Init Success" << std::endl;
    return 0;
}

// 只有返回值为0时才会继续运行，为1时正常退出，其他情况表示运行失败
short Game::Update()
{
    // Update the game
    std::cout << "Game Update..." << std::endl;

    char ch = _getch();
    short flag = 0;
    int m = 0;

    // 设置文字颜色为亮绿色
    SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    switch (ch)
    {
    case 'w':
        std::cout << "Move Up" << std::endl;
        break;

    case 's':
        std::cout << "Move Down" << std::endl;
        break;

    case 'a':
        std::cout << "Move Left" << std::endl;
        break;

    case 'd':
        std::cout << "Move Right" << std::endl;
        break;

    case 'q':
        std::cout << "Game Exit" << std::endl;
        flag = 1;
        break;

    case 'r':
        m = message_system->Send_Message();
        std::cout << "Read message from system:" << m << std::endl;
        break;

    default:
        std::cout << "Send message to system:" << int(ch) << std::endl;
        message_system->Receive_Message(int(ch));
        break;
    }
    // 重置为默认颜色
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    return flag;
}

short Game::Exit()
{
    // Exit the game
    std::cout << "Game Exit" << std::endl;

    // Exit Game...

    std::cout << "Game Exit Success" << std::endl;
    return 0;
}
