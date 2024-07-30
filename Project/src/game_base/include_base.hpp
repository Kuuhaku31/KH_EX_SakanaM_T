
#pragma once

// 对接用的头文件

#include <math.h>
#include <string>
#include <iostream>
#include <ctime>

// 宏定义

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

#define KHCOLOR_BLACK 0xff000000
#define KHCOLOR_BLUE 0xff0000ff
#define KHCOLOR_GREEN 0xff00ff00
#define KHCOLOR_CYAN 0xff00ffff
#define KHCOLOR_RED 0xffff0000
#define KHCOLOR_PINK 0xffff00ff
#define KHCOLOR_YELLOW 0xffffff00
#define KHCOLOR_WHITE 0xffffffff
#define KHCOLOR_GRAY 0xffc0c0c0
#define KHCOLOR_BROWN 0xffc0c000
#define KHCOLOR_LIGHT_BLUE 0xff8080ff
#define KHCOLOR_LIGHT_GREEN 0xff80ff80
#define KHCOLOR_LIGHT_CYAN 0xff80ffff
#define KHCOLOR_LIGHT_RED 0xffff8080
#define KHCOLOR_LIGHT_PINK 0xffff80ff
#define KHCOLOR_LIGHT_YELLOW 0xffffff80
#define KHCOLOR_LIGHT_WHITE 0xffc0c0c0
#define KHCOLOR_LIGHT_BROWN 0xffc0c000

// 定义一些需要的函数
namespace kh
{
float sqrt(float);
} // namespace kh

// 对于所有大于
// 0x 00 00 00 ff (225)
// 的值
// 认为是墙壁
#define WALL_LIM 0xff
