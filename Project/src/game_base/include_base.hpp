
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

//限制器模板函数
// 如果value不在范围内，则调整并返回false
template<int MIN, int MAX>
inline bool
Limit(int& value)
{
    if(value < MIN)
    {
        value = MIN;
        return false;
    }
    if(value > MAX)
    {
        value = MAX;
        return false;
    }
    return true;
}

inline bool
Limit(int& value, int min, int max)
{
    if(value < min)
    {
        value = min;
        return false;
    }
    if(value > max)
    {
        value = max;
        return false;
    }
    return true;
}

inline void
transformat(int* m) // 长度为6
{
    /*
	A的宽度
	A的高度
	B的宽度
	B的高度
	B的左上角相对于A的左上角的x坐标
	B的左上角相对于A的左上角的y坐标

		||
		\/

	A的起始点
	A的间隔
	B的起始点
	B的间隔
	宽度
	次数
	*/

    int A_start = 0;
    int A_skip  = 0;
    int B_start = 0;
    int B_skip  = 0;

    int wide = m[2];
    int high = m[3];

    int R = m[4] + m[2] - m[0];
    int L = m[4];
    int T = m[5];
    int B = m[5] + m[3] - m[1];

    if(R > 0)
    {
        wide -= R;
        B_skip += R;
    }
    if(R < 0)
    {
        A_skip -= R;
    }
    if(L > 0)
    {
        A_skip += L;
        A_start += L;
    }
    if(L < 0)
    {
        wide += L;
        B_skip -= L;
        B_start -= L;
    }
    if(B > 0)
    {
        high -= B;
    }
    if(T > 0)
    {
        A_start += m[0] * T;
    }
    if(T < 0)
    {
        high += T;
        B_start -= m[2] * T;
    }

    m[0] = A_start;
    m[1] = A_skip;
    m[2] = B_start;
    m[3] = B_skip;
    m[4] = wide;
    m[5] = high;
}

// 数对（点）
struct Point
{
    int px = 0;
    int py = 0;

    inline Point&
    operator=(const Point& p)
    {
        px = p.px;
        py = p.py;
        return *this;
    }
};

// 向量
struct Vector
{
    float vx = 0.0f;
    float vy = 0.0f;

    inline Vector&
    operator=(const Vector& v)
    {
        vx = v.vx;
        vy = v.vy;
        return *this;
    }
};

#define ZEROPOINT \
    Point { 0, 0 }
#define ZEROVECTOR \
    Vector { 0.0f, 0.0f }
//


// 重载操作符

inline bool
operator==(const Vector& v1, const Vector& v2)
{
    return v1.vx == v2.vx && v1.vy == v2.vy;
}

inline bool
operator!=(const Vector& v1, const Vector& v2)
{
    return !(v1 == v2);
}

inline bool
operator>(const Vector& v1, const Vector& v2)
{
    return v1.vx > v2.vx && v1.vy > v2.vy;
}

inline bool
operator<(const Vector& v1, const Vector& v2)
{
    return v1.vx < v2.vx && v1.vy < v2.vy;
}

inline bool
operator>=(const Vector& v1, const Vector& v2)
{
    return v1.vx >= v2.vx && v1.vy >= v2.vy;
}

inline bool
operator<=(const Vector& v1, const Vector& v2)
{
    return v1.vx <= v2.vx && v1.vy <= v2.vy;
}

inline bool
operator==(const Point& p1, const Point& p2)
{
    return p1.px == p2.px && p1.py == p2.py;
}

inline bool
operator!=(const Point& p1, const Point& p2)
{
    return !(p1 == p2);
}

inline bool
operator>(const Point& p1, const Point& p2)
{
    return p1.px > p2.px && p1.py > p2.py;
}

inline bool
operator<(const Point& p1, const Point& p2)
{
    return p1.px < p2.px && p1.py < p2.py;
}

inline bool
operator>=(const Point& p1, const Point& p2)
{
    return p1.px >= p2.px && p1.py >= p2.py;
}

inline bool
operator<=(const Point& p1, const Point& p2)
{
    return p1.px <= p2.px && p1.py <= p2.py;
}

inline Point
operator+(const Point& p1, const Point& p2)
{
    return Point{p1.px + p2.px, p1.py + p2.py};
}

inline Vector
operator+(const Vector& v1, const Vector& v2)
{
    return Vector{v1.vx + v2.vx, v1.vy + v2.vy};
}

inline Vector
operator+(const Vector& v, const Point& p)
{
    return Vector{v.vx + p.px, v.vy + p.py};
}

inline Vector
operator+(const Point& p, const Vector& v)
{
    return Vector{p.px + v.vx, p.py + v.vy};
}

inline Point&
operator+=(Point& p1, const Point& p2)
{
    p1.px += p2.px;
    p1.py += p2.py;
    return p1;
}

inline Vector&
operator+=(Vector& v1, const Vector& v2)
{
    v1.vx += v2.vx;
    v1.vy += v2.vy;
    return v1;
}

inline Vector&
operator+=(Vector& v, const Point& p)
{
    v.vx += p.px;
    v.vy += p.py;
    return v;
}

inline Point
operator-(const Point& p1, const Point& p2)
{
    return Point{p1.px - p2.px, p1.py - p2.py};
}

inline Vector
operator-(const Vector& v1, const Vector& v2)
{
    return Vector{v1.vx - v2.vx, v1.vy - v2.vy};
}

inline Vector
operator-(const Vector& v, const Point& p)
{
    return Vector{v.vx - p.px, v.vy - p.py};
}

inline Vector
operator-(const Point& p, const Vector& v)
{
    return Vector{p.px - v.vx, p.py - v.vy};
}

inline Point&
operator-=(Point& p1, const Point& p2)
{
    p1.px -= p2.px;
    p1.py -= p2.py;
    return p1;
}

inline Vector&
operator-=(Vector& v1, const Vector& v2)
{
    v1.vx -= v2.vx;
    v1.vy -= v2.vy;
    return v1;
}

inline Vector&
operator-=(Vector& v, const Point& p)
{
    v.vx -= p.px;
    v.vy -= p.py;
    return v;
}

inline Vector
operator*(const Vector& v, float f)
{
    return Vector{v.vx * f, v.vy * f};
}

inline Vector
operator*(const Point& p, float f)
{
    return Vector{p.px * f, p.py * f};
}

inline Vector&
operator*=(Vector& v, float f)
{
    v.vx *= f;
    v.vy *= f;
    return v;
}


// 计算模长
inline float
moudle(Point p)
{
    return kh::sqrt(p.px * p.px + p.py * p.py);
}

inline float
module(Vector v)
{
    return kh::sqrt(v.vx * v.vx + v.vy * v.vy);
}

// 化为单位向量
inline Vector
unit(Point p)
{
    float  m = moudle(p);
    Vector v;
    v.vx = p.px / m;
    v.vy = p.py / m;
    return v;
}

inline Vector
unit(Vector v)
{
    Vector v1;
    if(v != ZEROVECTOR)
    {
        float m = module(v);
        v1.vx   = v.vx / m;
        v1.vy   = v.vy / m;
    }
    return v1;
}
