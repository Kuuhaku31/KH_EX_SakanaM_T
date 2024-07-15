
#include "Camera.hpp"

// 用于混合两个颜色
static inline void
mix_color(uint &c1, uint &c2)
{
    int a2 = (c2 & 0xff000000) >> 24;
    if (!a2)
    {
        return;
    }
    int a1 = (c1 & 0xff000000) >> 24;

    int r1 = (c1 & 0x00ff0000) >> 16;
    int r2 = (c2 & 0x00ff0000) >> 16;

    int g1 = (c1 & 0x0000ff00) >> 8;
    int g2 = (c2 & 0x0000ff00) >> 8;

    int b1 = (c1 & 0x000000ff);
    int b2 = (c2 & 0x000000ff);

    int a = a1 + a2;
    int r = (r1 * (0xff - a2) + r2 * a2) / 0xff;
    int g = (g1 * (0xff - a2) + g2 * a2) / 0xff;
    int b = (b1 * (0xff - a2) + b2 * a2) / 0xff;

    c1 = (a << 24) | (r << 16) | (g << 8) | b;
}

static inline void
fun_add_AH(uint &a, uint &b)
{
    if (b)
    {
        uint d = ((b * 0xff) / 40000) << 24;
        mix_color(a, d);
    }
}

static inline void
fun_add_AC(uint &a, uint &b)
{
    if (b)
    {
        uint d = ((b * 0xff) / 800) << 24;
        uint c = 0x00000000 | d;
        mix_color(a, c);
    }
}

Camera::Camera()
{
    sight.Position_set(this);
}

Camera::Camera(int x, int y, uint w, uint h) : Position(x, y)
{
    sight.Position_set(this);
    sight.Shape_reset(w, h);
}

Camera::Camera(Point p, uint w, uint h) : Position(p)
{
    sight.Position_set(this);
    sight.Shape_reset(w, h);
}

Camera::Camera(Position *p, int x, int y, uint w, uint h) : Position(p, x, y)
{
    sight.Position_set(this);
    sight.Shape_reset(w, h);
}

Camera::Camera(Position *pos, Point poi, uint w, uint h) : Position(pos, poi)
{
    sight.Position_set(this);
    sight.Shape_reset(w, h);
}

Camera::~Camera()
{
}

void Camera::Rending(Area *area)
{
    sight.Area_compute(area, mix_color);
}

void Camera::Clearsight()
{
    sight.Shape_clear();
}

void Camera::Sight_size(uint w, uint h)
{
    sight.Shape_reset(w, h);
}

void Camera::Sight_align(bool b)
{
    if (b)
    {
        sight.Area_align();
    }
    else
    {
        sight.Position_set(0, 0);
    }
}
