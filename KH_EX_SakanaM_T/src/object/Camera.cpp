
#include "Object.hpp"

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

// 构造、析构函数
Camera::Camera(MessageSystem *mss, Position *pos, Point poi, uint w, uint h) : Object(mss, pos, poi)
{
    sight = new Area(this, poi, w, h);
}

Camera::~Camera()
{
    delete sight;
}

//
void Camera::Rending(Area *area)
{
    sight->Area_compute(area, mix_color);
}

void Camera::RendingObject(Object *obj)
{
    sight->Area_compute(obj->main_skin, mix_color);
}

void Camera::Clearsight()
{
    sight->Shape_clear();
}

void Camera::Sight_size(uint w, uint h)
{
    sight->Shape_reset(w, h);
}

void Camera::Sight_align(bool b)
{
    if (b)
    {
        sight->Area_align();
    }
    else
    {
        sight->Position_set(0, 0);
    }
}

void Camera::SendToMessageSystem(ShapeType t)
{
    message_system->Receive_Shapes(sight, t);
}
