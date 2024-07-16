
#pragma once

// 对接用的头文件

#include <math.h>
#include <string>
#include <iostream>
#include <ctime>

// 宏定义
//  定义了一些基本的数据类型
#define uint unsigned int
#define ushort unsigned short
#define uchar unsigned char
#define schar signed char

#define OXF 0xffffffff

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

// 定义一些需要的函数
namespace kh
{
    float sqrt(float);
} // namespace kh
