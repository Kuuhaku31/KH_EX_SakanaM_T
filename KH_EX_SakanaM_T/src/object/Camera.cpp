
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
    CAMERASIGHT->Area_compute(area, mix_color);
}

void Camera::RendingObject(Object *obj, ObjectAreaType t)
{
    CAMERASIGHT->Area_compute(obj->ObjectGetArea(t), mix_color);
}

void Camera::RendingZone(Zone *zone, ZoneAreaType t)
{
    typedef void (*FunPtr)(int &, int &);
    FunPtr fun = nullptr;

    switch (t)
    {
    case main_area:
        fun = fun_rend_zone<main_area, 0xffc0c0c0>;
        break;

    case relative_area_01:
        fun = fun_rend_zone<relative_area_01, KHCOLOR_BROWN>;
        break;
    case relative_area_02:
        fun = fun_rend_zone<relative_area_02, KHCOLOR_LIGHT_BROWN>;
        break;

    case wall_area_01:
        fun = fun_rend_zone<wall_area_01, KHCOLOR_GREEN & 0x88ffffff>;
        break;
    case wall_area_02:
        fun = fun_rend_zone<wall_area_02, KHCOLOR_LIGHT_GREEN>;
        break;

    case coll_area_01:
        fun = fun_rend_zone<coll_area_01, KHCOLOR_YELLOW>;
        break;
    case coll_area_02:
        fun = fun_rend_zone<coll_area_02, KHCOLOR_LIGHT_YELLOW>;
        break;

    case DHP_area_01:
        fun = fun_rend_zone<DHP_area_01, KHCOLOR_RED>;
        break;
    case DHP_area_02:
        fun = fun_rend_zone<DHP_area_02, KHCOLOR_LIGHT_RED>;
        break;

    default:
        break;
    }

    CAMERASIGHT->Area_compute(zone, fun);
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
