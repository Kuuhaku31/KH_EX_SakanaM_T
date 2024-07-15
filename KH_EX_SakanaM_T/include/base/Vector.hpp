
#pragma once

#include <math.h>

#include "Position.hpp"

#define ZEROVECTOR \
    Vector { 0.0f, 0.0f }

// 向量
struct Vector
{
    float vx = 0.0f;
    float vy = 0.0f;
};

// 计算模长
float moudle(Point);
float module(Vector);

// 数乘
Vector operator*(const Vector &, float);

// 重载==操作符
bool operator==(const Vector &, const Vector &);
// 重载!=操作符
bool operator!=(const Vector &, const Vector &);

// 重载加法操作符
Point operator+(const Point &, const Point &);
Vector operator+(const Vector &, const Vector &);
Vector operator+(const Vector &, const Point &);
Vector operator+(const Point &, const Vector &);

// 重载+=操作符
Point &operator+=(Point &, const Point &);
Vector &operator+=(Vector &, const Vector &);
Vector &operator+=(Vector &, const Point &);
Vector &operator+=(Point &, const Vector &);

// 重载减法操作符
Point operator-(const Point &, const Point &);
Vector operator-(const Vector &, const Vector &);
Vector operator-(const Vector &, const Point &);

// 重载-=操作符
Point &operator-=(Point &, const Point &);
Vector &operator-=(Vector &, const Vector &);
Vector &operator-=(Vector &, const Point &);
