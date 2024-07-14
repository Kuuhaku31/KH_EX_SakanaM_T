
// 游戏窗口的接口
// 用于初始化窗口，输出图像等操作
// 接收按键信息

#pragma once

#define GAME_RATE 60
#define RATE_SLEEP 1000 / GAME_RATE

#define GRAPHWIDE 1600
#define GRAPHHIGH 900
#define GRAPHLONG 1600 * 900

#define GRAPH_X 40
#define GRAPH_Y 30

#define GAME_NAME "Sakana"

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

#include <iostream>
#include <string>
#include <ctime>

#include <graphics.h>
#include "Area.hpp"

// 用于在控制台打印消息
// 第二个参数表示消息的颜色
void Say(std::string str, int txtCode = OXF, int bakcgroudCode = 0);

// 实现IMAGE类和Shape类的互相转化
void conversion_IMAGE_Area(IMAGE *img, Shape *area);
void conversion_IMAGE_Area(Shape *area, IMAGE *img);
void get_resources(Shape *shape, std::string path);
// 清屏
void clearGraph();

/*

int Camera::Mouse_X(int x)
{
    return x * kx + Get_x() - shape_wide / 2;
}

int Camera::Mouse_Y(int y)
{
    return y * ky + Get_y() - shape_high / 2;
}

*/

class GraphInterface
{
public:
    GraphInterface();
    ~GraphInterface();

    // 获取键盘鼠标信息
    short GetInput();

    // 访问键盘鼠标信息
    int Key_W();
    int Key_S();
    int Key_A();
    int Key_D();

    int Key_I();
    int Key_K();
    int Key_J();
    int Key_L();

    int Key_Q();
    int Key_E();
    int Key_R();
    int Key_F();

    int Arr_U();
    int Arr_D();
    int Arr_L();
    int Arr_R();

    int Space();
    int Shift();
    int Esc__();
    int Enter();

    int Mouse_X();
    int Mouse_Y();
    int MouseDX();
    int MouseDY();
    int Mouse_V();
    int Mouse_L();
    int Mouse_R();
    int Mouse_M();
    int Mouse_W();

    // 要输出的图像
    IMAGE screen;

    // 清屏
    void ClearScreen();
    void Photographed();

    // 设置输出格式，先不写
    void Photographed_format() {};

private:
    // 键盘鼠标信息
    struct
    {
        ExMessage msg;

        int key_W = 0;
        int key_S = 0;
        int key_A = 0;
        int key_D = 0;

        int key_I = 0;
        int key_K = 0;
        int key_J = 0;
        int key_L = 0;

        int key_Q = 0;
        int key_E = 0;
        int key_R = 0;
        int key_F = 0;

        int arr_U = 0;
        int arr_D = 0;
        int arr_L = 0;
        int arr_R = 0;

        int space = 0;
        int shift = 0;
        int esc__ = 0;
        int enter = 0;

        int mouse_X = 0;
        int mouse_Y = 0;
        int mouseDX = 0;
        int mouseDY = 0;
        int mouse_V = 0;
        int mouse_L = 0;
        int mouse_R = 0;
        int mouse_M = 0;
        int mouse_W = 0;
    };

    // 窗口信息
    struct
    {
        HWND graph_HWND;
        HDC graph_HDC;
        uint *graph_buffer;
        int graph_wide;
        int graph_high;
        int graph_long;

        int graph_half_wide;
        int graph_half_high;
    };
};

/*

void MessageSystem::Photographed()
{
    StretchBlt(
        gd.graph_HDC,
        output_x1,
        output_y1,
        output_x2,
        output_y2,

        GetImageHDC(&screen),
        0,
        0,
        screen.getwidth(),
        screen.getheight(),

        SRCCOPY);
}

void MessageSystem::Photographed_format()
{
    output_x1 = -16;
    output_y1 = -9;
    output_x2 = gd.graph_wide + 32;
    output_y2 = gd.graph_high + 18;
}

void MessageSystem::Photographed_format(int x1, int y1, int x2, int y2)
{
    output_x1 = x1 - 16;
    output_y1 = y1 - 9;
    output_x2 = x2 + 32;
    output_y2 = y2 + 18;
}

*/
