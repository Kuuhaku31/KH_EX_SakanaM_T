
#include "GameObjects.hpp"

// 线性插值函数
static int
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

    int output = 0x88000000;
    output |= (r << 16);
    output |= (g << 8);
    output |= b;

    return output;
}

// 用于混合两个颜色
static void
mix_color(int& c1, int& c2)
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

// 构造、析构函数
Camera::Camera()
{
    camera_sight.parent_pos = this;
}

Camera::Camera(Position* p, int w, int h)
{
    parent_pos              = p;
    camera_sight.parent_pos = this;
    camera_sight.Shape_reset(w, h);
}

Camera::~Camera() {}

static void
action_mixcolor(int& a, int& b, int v)
{
    mix_color(a, b);
}

void
Camera::CameraRending(Area* area, CameraRendingType t)
{
    camera_sight.Shape_merge(area, *area - camera_sight, action_mixcolor);
}

static void
action_rend_matter(int& a, int& b, int zt)
{
    int c = 0;
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
}

void
Camera::CameraRending(GameObject* obj, CameraRendingType t)
{
    Shape* skin = obj->animation_list->AnimationList_getFrame(obj->animation_timer.Timer_getTime());
    camera_sight.Shape_merge(skin, (*obj - camera_sight) + obj->animation_point, action_mixcolor);

    CameraRending(obj->test_points, obj->test_point_count, 0x88ff0000, t);
}

void
Camera::CameraRending(Zone* zone, CameraRendingType t)
{
    Area* area = nullptr;
    switch(t)
    {
    case camera_rending_zone_data:
        area = &zone->zone_data;
        break;
    case camera_rending_zone_matter:
        area = &zone->zone_matter;
        break;
    case camera_rending_zone_damage:
        area = &zone->zone_damage;
        break;
    default:
        break;
    }

    camera_sight.Area_merge(area, action_rend_matter);
}

// 渲染碰撞检测
void
Camera::CameraRending(Position* ps, int pc, int c, CameraRendingType t)
{
    for(int i = 0; i < pc; i++)
    {
        Point p  = ps[i].Position_root_xy();
        Point lp = camera_sight.Area_local_xy(p);
        int   b  = camera_sight.Shape_in(lp);

        mix_color(b, c);

        camera_sight.Shape_draw_point(lp.px, lp.py, b);
    }
}

void
Camera::CameraClearSight()
{
    camera_sight.Shape_clear();
}

void
Camera::CameraSight_size(int w, int h)
{
    camera_sight.Shape_reset(w, h);
}

void
Camera::CameraSight_size_d(int dw, int dh)
{
    camera_sight.Shape_reset(camera_sight.Shape_wide() + dw, camera_sight.Shape_high() + dh);
}

void
Camera::CameraSight_align()
{
    camera_sight.Area_align();
}
