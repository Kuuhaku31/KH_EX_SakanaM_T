
#include "GameObjects.hpp"

// 线性插值函数
inline unsigned int
interpolateColor(int value, int max_value)
{
    // 起点颜色 (黑色)
    int r1 = 0, g1 = 0, b1 = 0;
    // 终点颜色 (白色)
    int r2 = 255, g2 = 255, b2 = 255;

    // 计算插值
    int r = r1 + (r2 - r1) * value / max_value;
    int g = g1 + (g2 - g1) * value / max_value;
    int b = b1 + (b2 - b1) * value / max_value;

    unsigned int output = 0x88000000;
    output |= (r << 16);
    output |= (g << 8);
    output |= b;

    return output;
}

// 用于混合两个颜色
inline void
mix_color(unsigned int& c1, unsigned int& c2)
{
    int a2 = (c2 & 0xff000000) >> 24;
    if(!a2)
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
fun_add_AH(unsigned int& a, unsigned int& b)
{
    if(b)
    {
        unsigned int d = ((b * 0xff) / 40000) << 24;
        mix_color(a, d);
    }
}

inline void
fun_add_AC(unsigned int& a, unsigned int& b)
{
    if(b)
    {
        unsigned int d = ((b * 0xff) / 800) << 24;
        unsigned int c = 0x00000000 | d;
        mix_color(a, c);
    }
}

template<int bit, int color>
inline void
fun_rend_zone(unsigned int& a, unsigned int& b)
{
    unsigned int c = b >> bit;
    (c & 0x1) ? c = color : c = 0x0;

    mix_color(a, c);
}


// 构造、析构函数
Camera::Camera()
{}

Camera::Camera(Position* p, int w, int h)
    : Object(p)
{
    objectAreas[0].Shape_reset(w, h);
}

Camera::~Camera() {}

void
Camera::CameraRending(Area* area, int t)
{
    AREA_COMPUTE((&objectAreas[t]), area, (mix_color(a, b)));
}

void
Camera::CameraRending(Zone* zone, ZoneAreaType zt, int t)
{
    AREA_COMPUTE((&objectAreas[t]), zone,
                 ({
                     unsigned int c = b >> zt;
                     (c & 0x1) ? c = zone->ZoneGetColor(zt) : c = 0x0;

                     mix_color(a, c);
                 }));
}

// 渲染碰撞检测
void
Camera::CameraRending(Collision* coll, unsigned int c, int t)
{
    Position* tem = nullptr;
    int       i   = 0;
    while(coll->CollGetTestPoint(tem, i))
    {
        Point        p  = tem->Position_root_xy();
        Point        lp = objectAreas[t].Area_local_xy(p);
        unsigned int b  = objectAreas[t].Area_in(p);

        mix_color(b, c);

        objectAreas[t].Shape_draw_point(lp.px, lp.py, b);

        i++;
    }
}

void
Camera::CameraRendingMatter(Area* area, int t)
{
    AREA_COMPUTE((&objectAreas[t]), area,
                 ({
                     unsigned int c = 0;
                     if(b > 0xff)
                     {
                         c = 0x88ff88ff;
                     }
                     else
                     {
                         c = 0x88000000;
                         c |= (b << 16);
                         c |= (b << 8);
                         c |= b;
                     }

                     mix_color(a, c);
                 }));
}

void
Camera::CameraClearSight(int t)
{
    objectAreas[t].Shape_clear();
}

void
Camera::CameraSight_size(int w, int h, int t)
{
    objectAreas[t].Shape_reset(w, h);
}

void
Camera::CameraSight_size_d(int dw, int dh, int t)
{
    objectAreas[t].Shape_reset(objectAreas[t].Shape_wide() + dw, objectAreas[t].Shape_high() + dh);
}

void
Camera::CameraSight_align(int t)
{
    objectAreas[t].Area_align();
}
