
#include "base.hpp"

Shape::Shape(int w, int h, int v)
{
    if(0 >= w || 0 >= h)
    {
        shape_buffer = nullptr;
        shape_wide   = 0;
        shape_high   = 0;
        shape_long   = 0;
    }
    else
    {
        shape_buffer = new unsigned int[w * h];
        shape_wide   = w;
        shape_high   = h;
        shape_long   = w * h;

        for(int i = 0; i < shape_long; i++)
        {
            shape_buffer[i] = v;
        }
    }
}

Shape::Shape(const unsigned int* b, int w, int h)
{
    if(!b || 0 >= w || 0 >= h)
    {
        shape_buffer = nullptr;
        shape_wide   = 0;
        shape_high   = 0;
        shape_long   = 0;
    }
    else
    {
        shape_buffer = new unsigned int[w * h];
        shape_wide   = w;
        shape_high   = h;
        shape_long   = w * h;

        for(int i = 0; i < shape_long; i++)
        {
            shape_buffer[i] = b[i];
        }
    }
}

Shape::~Shape()
{
    if(shape_buffer)
    {
        delete[] shape_buffer;
    }
}

int
Shape::Shape_wide() const
{
    return shape_wide;
}

int
Shape::Shape_high() const
{
    return shape_high;
}

int
Shape::Shape_long() const
{
    return shape_long;
}

unsigned int*
Shape::Shape_buffer()
{
    return shape_buffer;
}

int
Shape::Shape_in(int n) const
{
    if(Limit(n, 0, shape_long) && shape_long)
    {
        return shape_buffer[n];
    }
    else
    {
        return 0;
    }
}

int
Shape::Shape_in(Point p) const
{
    if(Limit(p, ZEROPOINT, Point{shape_wide, shape_high}) && shape_long)
    {
        return shape_buffer[p.py * shape_wide + p.px];
    }
    else
    {
        return 0;
    }
}

bool
Shape::Shape_in(int n, int b) const
{
    if(Limit(n, 0, shape_long) && Limit<0, 31>(b) && shape_long)
    {
        return shape_buffer[n] & (1 << b);
    }
    else
    {
        return false;
    }
}

// 获取某个bit位的值，第三个参数为0-31
bool
Shape::Shape_in(Point p, int b) const
{
    if(Limit(p, ZEROPOINT, Point{shape_wide, shape_high}) && Limit<0, 31>(b) && shape_long)
    {
        return shape_buffer[p.py * shape_wide + p.px] & (1 << b);
    }
    else
    {
        return false;
    }
}

void
Shape::Shape_draw_point(int n, int v)
{
    if(n >= 0 && n < shape_long)
    {
        shape_buffer[n] = v;
    }
}

void
Shape::Shape_draw_point(int x, int y, int v)
{
    if(x >= 0 && x < shape_wide && y >= 0 && y < shape_high)
    {
        shape_buffer[y * shape_wide + x] = v;
    }
}

inline int
abs(int x)
{
    return x < 0 ? -x : x;
}

inline void
swap(int& a, int& b)
{
    int t = a;
    a     = b;
    b     = t;
}

void
Shape::Shape_draw_line(int x1, int y1, int x2, int y2, int v)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    if(dx == 0 && dy == 0)
    {
        Shape_draw_point(x1, y1, v);
    }
    else if(dx == 0)
    {
        for(int y = y1; y <= y2; y++)
        {
            Shape_draw_point(x1, y, v);
        }
    }
    else if(dy == 0)
    {
        for(int x = x1; x <= x2; x++)
        {
            Shape_draw_point(x, y1, v);
        }
    }
    else
    {
        if(abs(dx) > abs(dy))
        {
            if(x1 > x2)
            {
                swap(x1, x2);
                swap(y1, y2);
            }
            for(int x = x1; x <= x2; x++)
            {
                int y = y1 + dy * (x - x1) / dx;
                Shape_draw_point(x, y, v);
            }
        }
        else
        {
            if(y1 > y2)
            {
                swap(x1, x2);
                swap(y1, y2);
            }
            for(int y = y1; y <= y2; y++)
            {
                int x = x1 + dx * (y - y1) / dy;
                Shape_draw_point(x, y, v);
            }
        }
    }
}

void
Shape::Shape_draw_rectangle(int, int, int, int, int)
{
    // ...
}

void
Shape::Shape_draw_circle(int centerX, int centerY, int radius, int value)
{
    for(int y = -radius; y <= radius; y++)
    {
        for(int x = -radius; x <= radius; x++)
        {
            if(x * x + y * y <= radius * radius)
            {
                int drawX = centerX + x;
                int drawY = centerY + y;
                int p     = drawY * shape_wide + drawX;
                if(p >= 0 && p < shape_long)
                {
                    shape_buffer[p] = value;
                }
            }
        }
    }
}

void
Shape::Shape_reset(int w, int h, int v)
{
    if(0 >= w || 0 >= h)
    {
        delete[] shape_buffer;
        shape_buffer = nullptr;
        shape_wide   = 0;
        shape_high   = 0;
        shape_long   = 0;
    }
    else
    {
        delete[] shape_buffer;
        shape_buffer = new unsigned int[w * h];
        shape_wide   = w;
        shape_high   = h;
        shape_long   = w * h;

        for(int i = 0; i < shape_long; i++)
        {
            shape_buffer[i] = v;
        }
    }
}

// **这个函数无法处理数组越界！**
void
Shape::Shape_reset(const int* b, int w, int h)
{
    if(!b || 0 >= w || 0 >= h)
    {
        delete[] shape_buffer;
        shape_buffer = nullptr;
        shape_wide   = 0;
        shape_high   = 0;
        shape_long   = 0;
    }
    else
    {
        delete[] shape_buffer;
        shape_buffer = new unsigned int[w * h];
        shape_wide   = w;
        shape_high   = h;
        shape_long   = w * h;

        for(int i = 0; i < shape_long; i++)
        {
            shape_buffer[i] = b[i];
        }
    }
}

void
Shape::Shape_copy(Shape* s)
{
    shape_wide = s->shape_wide;
    shape_high = s->shape_high;
    shape_long = s->shape_long;
    delete[] shape_buffer;
    shape_buffer = new unsigned int[shape_long];
    for(int i = 0; i < shape_long; i++)
    {
        shape_buffer[i] = s->shape_buffer[i];
    }
}

void
Shape::Shape_clear(int v)
{
    for(int i = 0; i < shape_long; i++)
    {
        shape_buffer[i] = v;
    }
}

void
Shape::Shape_clear(int t, int f)
{
    for(int i = 0; i < shape_long; i++)
    {
        if(shape_buffer[i])
        {
            shape_buffer[i] = t;
        }
        else
        {
            shape_buffer[i] = f;
        }
    }
}

void
Shape::Shape_not()
{
    for(int i = 0; i < shape_long; i++)
    {
        shape_buffer[i] = ~shape_buffer[i];
    }
}
