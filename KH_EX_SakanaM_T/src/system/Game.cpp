
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
    mss = ms;

    std::cout << "Game Init Success" << std::endl;
    return 0;
}

short Game::Exit()
{
    // Exit the game
    std::cout << "Game Exit" << std::endl;

    // Exit Game...

    std::cout << "Game Exit Success" << std::endl;
    return 0;
}

// 只有返回值为0时才会继续运行，为1时正常退出，其他情况表示运行失败
short Game::Update()
{
    // Update the game
    // std::cout << "Game Update..." << std::endl;
    mss->Say("\nGame Update...", WIN_COLOR_WHITE);
    mss->Say("Enter a command: ", WIN_COLOR_WHITE);

    char ch = _getch();
    char m = 0;
    std::string str = "";
    short flag = 0;

    // 设置文字颜色为亮绿色
    SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    switch (ch)
    {
    case 'q':
        mss->Say("Game Exit", WIN_COLOR_WHITE);
        flag = 1;
        break;

    case 'r':
        m = mss->Send_Message();
        str = "Read message from system: ";
        str += m;
        mss->Say(str, WIN_COLOR_WHITE);
        break;

    default:
        str = "Send message to system: ";
        str += ch;
        mss->Say(str, WIN_COLOR_WHITE);
        mss->Receive_Message(ch);
        break;
    }
    // 重置为默认颜色
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    return flag;
}
