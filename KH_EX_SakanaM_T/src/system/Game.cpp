
#include "Game.hpp"

#include <windows.h>
#include <iostream>
#include <conio.h>

// 设置控制台文字颜色的函数
void SetConsoleColor(WORD color)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台输出的句柄
    SetConsoleTextAttribute(hConsoleOutput, color);          // 设置文字和背景颜色
}

Game::Game()
{
    // Initialize the game
    std::cout << "\nGame Created";
}

Game::~Game()
{
    // Destroy the game
    std::cout << "\nGame Destroyed";
}

short Game::Init(MessageSystem *ms)
{
    // Initialize Game...
    mss = ms;

    mss->Say("\nGame Init Success", WIN_COLOR_GRAY);
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

short game_update_01(MessageSystem *mss)
{
    mss->Say("\nGame Update...", WIN_COLOR_WHITE);
    mss->Say("Enter a command: ", WIN_COLOR_WHITE);

    char ch = _getch();
    char m = 0;
    std::string str = "";
    short flag = 0;

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

    return flag;
}

short game_update_02(MessageSystem *mss)
{
    short flag = 0;
    mss->input.GetInput();

    if (mss->KEY_Q)
    {
        mss->Say("You Pressed Q", WIN_COLOR_WHITE);
    }
    if (mss->KEY_R)
    {
        mss->Say("You Pressed R", WIN_COLOR_WHITE);
    }
    if (mss->ENTER)
    {
        mss->Say("Game Exit", WIN_COLOR_WHITE);
        flag = 1;
    }

    return flag;
}

// 只有返回值为0时才会继续运行，为1时正常退出，其他情况表示运行失败
short Game::Update()
{
    // Update the game
    return game_update_02(mss);
}
