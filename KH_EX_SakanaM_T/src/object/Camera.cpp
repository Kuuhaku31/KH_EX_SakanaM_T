
#include "GameObjects.hpp"

// 用于混合两个颜色
inline void
mix_color(int &c1, int &c2)
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

inline void
fun_add_AH(int &a, int &b)
{
    if (b)
    {
        int d = ((b * 0xff) / 40000) << 24;
        mix_color(a, d);
    }
}

inline void
fun_add_AC(int &a, int &b)
{
    if (b)
    {
        int d = ((b * 0xff) / 800) << 24;
        int c = 0x00000000 | d;
        mix_color(a, c);
    }
}

template <int bit, int color>
inline void
fun_rend_zone(int &a, int &b)
{
    int c = b >> bit;
    (c & 0x1) ? c = color : c = 0x0;

    mix_color(a, c);
}

// 定义一个宏，方便调用
#define CAMERASIGHT Object::objectAreas[ObjectAreaType::skin01]

// 构造、析构函数
Camera::Camera(MessageSystem *mss, Zone *z, Point poi, int w, int h) : GameObject(mss, z, poi)
{
    CAMERASIGHT->Shape_reset(w, h);
}

Camera::~Camera() {}

void Camera::Rending(Area *area)
{
    AREA_COMPUTE(CAMERASIGHT, area, (mix_color(a, b)));
}

void Camera::RendingObject(Object *obj, ObjectAreaType t)
{
    AREA_COMPUTE(CAMERASIGHT, obj->ObjectGetArea(t), (mix_color(a, b)));
}

void Camera::RendingZone(Zone *zone, ZoneAreaType t)
{
    AREA_COMPUTE(CAMERASIGHT, zone,
                 ({
                     int c = b >> t;
                     (c & 0x1) ? c = zone->ZoneGetColor(t) : c = 0x0;

                     mix_color(a, c);
                 }));
}

void Camera::Clearsight()
{
    CAMERASIGHT->Shape_clear();
}

void Camera::Sight_size(int w, int h)
{
    CAMERASIGHT->Shape_reset(w, h);
}

void Camera::Sight_align(bool b)
{
    if (b)
    {
        CAMERASIGHT->Area_align();
    }
    else
    {
        CAMERASIGHT->Position_set(ZEROPOINT);
    }
}

void Camera::SendToMessageSystem(ShapeType t)
{
    message_system->Receive_Shapes(CAMERASIGHT, t);
}

// 取消宏
#undef CAMERASIGHT
