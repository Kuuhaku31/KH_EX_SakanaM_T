
// 全局消息系统
// 用于全局消息的发送和接收

#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

#include "Input.hpp"

#define MESSAGE_MAX 100
#define GAME_MESSAGE_MAX 100
#define SYSTEM_MESSAGE_MAX 100

/*

在Windows控制台中，可以通过SetConsoleTextAttribute函数设置的颜色包括前景色（文字颜色）和背景色。每种颜色都可以通过组合以下基本颜色常量来表示：

FOREGROUND_BLUE（前景蓝色）
FOREGROUND_GREEN（前景绿色）
FOREGROUND_RED（前景红色）
FOREGROUND_INTENSITY（增加前景颜色的亮度）
BACKGROUND_BLUE（背景蓝色）
BACKGROUND_GREEN（背景绿色）
BACKGROUND_RED（背景红色）
BACKGROUND_INTENSITY（增加背景颜色的亮度）

通过组合这些常量，可以创建不同的颜色。例如，将FOREGROUND_RED | FOREGROUND_GREEN组合可以得到黄色文字。以下是一些可能的组合示例：

纯色（不带亮度增强）:

黑色: 无（默认）
蓝色: FOREGROUND_BLUE
绿色: FOREGROUND_GREEN
青色: FOREGROUND_GREEN | FOREGROUND_BLUE
红色: FOREGROUND_RED
紫色: FOREGROUND_RED | FOREGROUND_BLUE
黄色: FOREGROUND_RED | FOREGROUND_GREEN
白色: FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

增强亮度的颜色:

亮蓝色: FOREGROUND_BLUE | FOREGROUND_INTENSITY
亮绿色: FOREGROUND_GREEN | FOREGROUND_INTENSITY
亮青色: FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
亮红色: FOREGROUND_RED | FOREGROUND_INTENSITY
亮紫色: FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
亮黄色: FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
亮白色: FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY

同样的规则也适用于背景颜色，只是使用BACKGROUND_*常量而不是FOREGROUND_*常量。通过这种方式，可以在Windows控制台中表示多种颜色组合。

void test_output()
    {
        Say("Test Output:\n", WIN_COLOR_LIGHT_WHITE);

        Say("Red", WIN_COLOR_RED);
        Say("Yellow", WIN_COLOR_YELLOW);
        Say("Green", WIN_COLOR_GREEN);
        Say("Cyan", WIN_COLOR_CYAN);
        Say("Blue", WIN_COLOR_BLUE);
        Say("Pink", WIN_COLOR_PINK);
        Say("Black", WIN_COLOR_BLACK);
        Say("White", WIN_COLOR_WHITE);
        Say("Gray", WIN_COLOR_GRAY);

        Say("Light Red", WIN_COLOR_LIGHT_RED);
        Say("Light Yellow", WIN_COLOR_LIGHT_YELLOW);
        Say("Light Green", WIN_COLOR_LIGHT_GREEN);
        Say("Light Cyan", WIN_COLOR_LIGHT_CYAN);
        Say("Light Blue", WIN_COLOR_LIGHT_BLUE, WIN_COLOR_RED);
        Say("Light Pink", WIN_COLOR_LIGHT_PINK);
        Say("Light White", WIN_COLOR_LIGHT_WHITE);

        Say("Test Output End\n", WIN_COLOR_LIGHT_WHITE);

        for (int k = 1; k < 255; k++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
            std::cout << "\n  " << std::hex << k << " -- I want to be nice today!";
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

*/

#define WIN_COLOR_BLACK 0x0
#define WIN_COLOR_BLUE 0x1
#define WIN_COLOR_GREEN 0x2
#define WIN_COLOR_CYAN 0x3
#define WIN_COLOR_RED 0x4
#define WIN_COLOR_PINK 0x5
#define WIN_COLOR_YELLOW 0x6
#define WIN_COLOR_WHITE 0x7
#define WIN_COLOR_GRAY 0x8
#define WIN_COLOR_LIGHT_BLUE 0x9
#define WIN_COLOR_LIGHT_GREEN 0xA
#define WIN_COLOR_LIGHT_CYAN 0xB
#define WIN_COLOR_LIGHT_RED 0xC
#define WIN_COLOR_LIGHT_PINK 0xD
#define WIN_COLOR_LIGHT_YELLOW 0xE
#define WIN_COLOR_LIGHT_WHITE 0xF

// 消息系统
#define KEY_W input.key_W
#define KEY_S input.key_S
#define KEY_A input.key_A
#define KEY_D input.key_D

#define KEY_I input.key_I
#define KEY_K input.key_K
#define KEY_J input.key_J
#define KEY_L input.key_L

#define KEY_Q input.key_Q
#define KEY_E input.key_E
#define KEY_R input.key_R
#define KEY_F input.key_F

#define ARR_U input.arr_U
#define ARR_D input.arr_D
#define ARR_L input.arr_L
#define ARR_R input.arr_R

#define SPACE input.space
#define SHIFT input.shift
#define ESC__ input.esc__
#define ENTER input.enter

#define MOUSE_X input.mouse_X
#define MOUSE_Y input.mouse_Y
#define MOUSE_DX input.mouseDX
#define MOUSE_DY input.mouseDY
#define MOUSE_V input.mouse_V
#define MOUSE_L input.mouse_L
#define MOUSE_R input.mouse_R
#define MOUSE_M input.mouse_M
#define MOUSE_W input.mouse_W

struct graph_data
{
    HWND graph_HWND = nullptr;
    HDC graph_HDC = nullptr;
    unsigned int *graph_buffer = nullptr;
    int graph_wide = 0;
    int graph_high = 0;
    int graph_long = 0;

    int graph_half_wide = 0;
    int graph_half_high = 0;
};

class MessageSystem
{
public:
    MessageSystem();
    ~MessageSystem();

    // 初始化和退出
    short Init();
    short Exit();

    // 用于在控制台打印消息
    // 第二个参数表示消息的颜色
    void Say(std::string, int = WIN_COLOR_WHITE, int = WIN_COLOR_BLACK);

    // 清屏
    void ClearGraph();
    void ClearScreen();
    // 用于在窗口中打印消息
    void Photographed();
    // 设置输出格式
    void Photographed_format();
    void Photographed_format(int, int, int, int);

    // 发送消息
    int
    Send_Message();
    int Send_Message_to_Game();
    int Send_Message_to_GameManager();

    // 接收消息
    void Receive_Message(char);
    void Receive_Message_from_Game(char);
    void Receive_Message_from_GameManager(char);

    // 启用、停用消息队列
    // 先不写
    void Enable_Message();
    void Enable_Message_to_Game();
    void Enable_Message_to_GameManager();

    void Disable_Message();
    void Disable_Message_to_Game();
    void Disable_Message_to_GameManager();

    void Set_graph_data(graph_data);

    Input input;
    // 要输出的图像
    IMAGE screen;

private:
    // 窗口信息
    graph_data gd;

    // 输出格式
    struct
    {
        int output_x1 = 0;
        int output_y1 = 0;
        int output_x2 = 0;
        int output_y2 = 0;
    };

    // 消息队列
    // 不同的消息类型分别存储
    int message_count = 0;
    char message_queue[MESSAGE_MAX] = {0};

    int game_message_count = 0;
    char game_message_queue[GAME_MESSAGE_MAX] = {0};

    int system_message_count = 0;
    char system_message_queue[SYSTEM_MESSAGE_MAX] = {0};
};
