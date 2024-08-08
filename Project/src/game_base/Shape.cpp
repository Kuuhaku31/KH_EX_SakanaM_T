
#include "base.hpp"


// 限制函数
inline bool
limit(int x, int max)
{
    return x >= 0 && x < max;
}

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
        shape_buffer = new int[w * h];
        shape_wide   = w;
        shape_high   = h;
        shape_long   = w * h;

        for(int i = 0; i < shape_long; i++)
        {
            shape_buffer[i] = v;
        }
    }
}

Shape::Shape(const int* b, int w, int h)
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
        shape_buffer = new int[w * h];
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

int*
Shape::Shape_buffer()
{
    return shape_buffer;
}

int
Shape::Shape_in(int n) const
{
    if(limit(n, shape_long))
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
    if(limit(p.px, shape_wide) && limit(p.py, shape_high))
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
    if(limit(n, shape_long) && limit(b, 32))
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
    if(limit(p.px, shape_wide) && limit(p.py, shape_high) && limit(b, 32))
    {
        return shape_buffer[p.py * shape_wide + p.px] & (1 << b);
    }
    else
    {
        return false;
    }
}

bool
Shape::Shape_in_addr(int** adr, int n)
{
    if(limit(n, shape_long))
    {
        *adr = &shape_buffer[n];
        return true;
    }
    else
    {
        return false;
    }
}


bool
Shape::Shape_in_addr(int** adr, Point p)
{
    if(limit(p.px, shape_wide) && limit(p.py, shape_high))
    {
        *adr = &shape_buffer[p.py * shape_wide + p.px];
        return true;
    }
    else
    {
        return false;
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
Shape::Shape_draw_rectangle(int x, int y, int w, int h, int color)
{
    int m[6] = { shape_wide, shape_high, w, h, x, y };
    transformat(m);

    for(int i = 0; i < m[5]; i++)
    {
        for(int j = 0; j < m[4]; j++)
        {
            shape_buffer[m[0]] = color;
            m[0]++;
            m[2]++;
        }
        m[0] += m[1];
        m[2] += m[3];
    }
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
        shape_buffer = new int[w * h];
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
        shape_buffer = new int[w * h];
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
    shape_buffer = new int[shape_long];
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

void
Shape::Shape_merge(Shape* s, Point p, void (*action)(int&, int&, int), int v)
{
    int m[6] = { this->Shape_wide(), this->Shape_high(), s->Shape_wide(), s->Shape_high(), p.px, p.py };
    transformat(m);
    int* b1 = this->Shape_buffer();
    int* b2 = s->Shape_buffer();
    for(int i = 0; i < m[5]; i++, m[0] += m[1], m[2] += m[3])
    {
        for(int j = 0; j < m[4]; j++, m[0]++, m[2]++)
        {
            action(b1[m[0]], b2[m[2]], v);
        }
    }
}
