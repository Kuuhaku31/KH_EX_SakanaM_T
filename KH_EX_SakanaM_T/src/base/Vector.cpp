
#include "base.hpp"

// 计算模长
float moudle(Point p)
{
    return kh::sqrt(p.px * p.px + p.py * p.py);
}

float module(Vector v)
{
    return kh::sqrt(v.vx * v.vx + v.vy * v.vy);
}

Vector operator*(const Vector &v, float f)
{
    Vector res;
    res.vx = v.vx * f;
    res.vy = v.vy * f;
    return res;
}

bool operator==(const Vector &v1, const Vector &v2)
{
    return v1.vx == v2.vx && v1.vy == v2.vy;
}

bool operator!=(const Vector &v1, const Vector &v2)
{
    return v1.vx != v2.vx || v1.vy != v2.vy;
}

// 重载加法操作符
Point operator+(const Point &p1, const Point &p2)
{
    Point p;
    p.px = p1.px + p2.px;
    p.py = p1.py + p2.py;
    return p;
}

Vector operator+(const Vector &v1, const Vector &v2)
{
    Vector v;
    v.vx = v1.vx + v2.vx;
    v.vy = v1.vy + v2.vy;
    return v;
}

Vector operator+(const Vector &v, const Point &p)
{
    Vector v1;
    v1.vx = v.vx + p.px;
    v1.vy = v.vy + p.py;
    return v1;
}

Vector operator+(const Point &p, const Vector &v)
{
    Vector v1;
    v1.vx = p.px + v.vx;
    v1.vy = p.py + v.vy;
    return v1;
}

// 重载+=操作符
Point &operator+=(Point &p1, const Point &p2)
{
    p1.px += p2.px;
    p1.py += p2.py;
    return p1;
}

Vector &operator+=(Vector &v1, const Vector &v2)
{
    v1.vx += v2.vx;
    v1.vy += v2.vy;
    return v1;
}

Vector &operator+=(Vector &v, const Point &p)
{
    v.vx += p.px;
    v.vy += p.py;
    return v;
}

// 重载减法操作符
Point operator-(const Point &p1, const Point &p2)
{
    Point p;
    p.px = p1.px - p2.px;
    p.py = p1.py - p2.py;
    return p;
}

Vector operator-(const Vector &v1, const Vector &v2)
{
    Vector v;
    v.vx = v1.vx - v2.vx;
    v.vy = v1.vy - v2.vy;
    return v;
}

Vector operator-(const Vector &v, const Point &p)
{
    Vector v1;
    v1.vx = v.vx - p.px;
    v1.vy = v.vy - p.py;
    return v1;
}

Vector operator-(const Point &p, const Vector &v)
{
    Vector v1;
    v1.vx = p.px - v.vx;
    v1.vy = p.py - v.vy;
    return v1;
}

// 重载-=操作符
Point &operator-=(Point &p1, const Point &p2)
{
    p1.px -= p2.px;
    p1.py -= p2.py;
    return p1;
}

Vector &operator-=(Vector &v1, const Vector &v2)
{
    v1.vx -= v2.vx;
    v1.vy -= v2.vy;
    return v1;
}

Vector &operator-=(Vector &v, const Point &p)
{
    v.vx -= p.px;
    v.vy -= p.py;
    return v;
}
