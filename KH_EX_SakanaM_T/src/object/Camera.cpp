
#include "Camera.hpp"

// 用于混合两个颜色
static inline void
mix_color(unsigned int *c1, unsigned int *c2)
{
    int a2 = (*c2 & 0xff000000) >> 24;
    if (!a2)
    {
        return;
    }
    int a1 = (*c1 & 0xff000000) >> 24;

    int r1 = (*c1 & 0x00ff0000) >> 16;
    int r2 = (*c2 & 0x00ff0000) >> 16;

    int g1 = (*c1 & 0x0000ff00) >> 8;
    int g2 = (*c2 & 0x0000ff00) >> 8;

    int b1 = (*c1 & 0x000000ff);
    int b2 = (*c2 & 0x000000ff);

    int a = a1 + a2;
    int r = (r1 * (0xff - a2) + r2 * a2) / 0xff;
    int g = (g1 * (0xff - a2) + g2 * a2) / 0xff;
    int b = (b1 * (0xff - a2) + b2 * a2) / 0xff;

    *c1 = (a << 24) | (r << 16) | (g << 8) | b;
}

static inline void
fun_add_AH(unsigned int *a, unsigned int *b)
{
    if (*b)
    {
        unsigned int d = ((*b * 0xff) / 40000) << 24;
        mix_color(a, &d);
    }
}

static inline void
fun_add_AC(unsigned int *a, unsigned int *b)
{
    if (*b)
    {
        unsigned int d = ((*b * 0xff) / 800) << 24;
        unsigned int c = 0x00000000 | d;
        mix_color(a, &c);
    }
}

Camera::Camera()
{
}

Camera::~Camera()
{
}

// 调整视野大小
void Camera::Tweaks_sight(int dw, int dh)
{
    int w = shape_wide + dw;
    int h = shape_high + dh;
    if (0 < w && 0 < h)
    {
        Shape_reset(w, h);

        // kx = sight_wide / 1.0 / graph_wide;
        // ky = sight_high / 1.0 / graph_high;
    }
}

void Camera::Rending(Renderer *ren)
{
    Compute(ren, mix_color);
}

int Camera::Mouse_X(int x)
{
    return x * kx + Get_x() - shape_wide / 2;
}

int Camera::Mouse_Y(int y)
{
    return y * ky + Get_y() - shape_high / 2;
}
