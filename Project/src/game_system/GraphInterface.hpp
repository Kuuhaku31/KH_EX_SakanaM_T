
// 游戏窗口的接口
// 用于初始化窗口，输出图像等操作
// 接收按键信息

#pragma once

#include "MessageSystem.hpp"

class GraphInterface
{
public:
    GraphInterface(MessageSystem *);
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

    // 获取鼠标在世界坐标系中的位置
    Point Mouse_World_Point();
    // 获取鼠标在Shape坐标系中的位置
    Point Mouse_Shape_Point();

    // 清屏
    void ClearScreen();

    // 从MessageSystem获取图像，并处理
    void ReceiveFromMessageSystem();
    // 输出图像
    void Photographed();

    // 设置输出格式，先不写
    void Photographed_format();

private:
    //^
    MessageSystem *message_system;

    // 需要处理的图像
    Shape shapes[SHAPE_QUEUE_MAX];
    // 要输出的图像
    IMAGE screen;

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
        int *graph_buffer;
        int graph_wide;
        int graph_high;
        int graph_long;

        int graph_half_wide;
        int graph_half_high;

        // 窗口输出参数
        int output_x1;
        int output_y1;
        int output_x2;
        int output_y2;

        int output_wide;
        int output_high;
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
