
#include "base.hpp"

// 设置点的分布位置
inline void
setpoints(Position* p, int count, int w, int h)
{
    if(count == 1)
    {
        (Point) p[0] = Point{0, 0};
    }
    else if(count == 4)
    {
        (Point) p[0] = Point{w / 2, 0};
        (Point) p[1] = Point{w, h / 2};
        (Point) p[2] = Point{w / 2, h};
        (Point) p[3] = Point{0, h / 2};
    }
    else if(count == 8)
    {
        (Point) p[0] = Point{w / 4, 0};
        (Point) p[1] = Point{w / 2, 0};
        (Point) p[2] = Point{3 * w / 4, 0};
        (Point) p[3] = Point{w, h / 4};
        (Point) p[4] = Point{w, h / 2};
        (Point) p[5] = Point{w, 3 * h / 4};
        (Point) p[6] = Point{3 * w / 4, h};
        (Point) p[7] = Point{w / 2, h};
    }
    else if(count = 12)
    {
        (Point) p[0]  = Point{w / 4, 0};
        (Point) p[1]  = Point{w / 2, 0};
        (Point) p[2]  = Point{3 * w / 4, 0};
        (Point) p[3]  = Point{w, h / 4};
        (Point) p[4]  = Point{w, h / 2};
        (Point) p[5]  = Point{w, 3 * h / 4};
        (Point) p[6]  = Point{3 * w / 4, h};
        (Point) p[7]  = Point{w / 2, h};
        (Point) p[8]  = Point{w / 4, h};
        (Point) p[9]  = Point{0, 3 * h / 4};
        (Point) p[10] = Point{0, h / 2};
        (Point) p[11] = Point{0, h / 4};
    }
    else
    {
        for(int i = 0; i < count; i++)
        {
            (Point) p[i] = Point{w / 2, h / 2};
        }
    }
}

Collision::Collision(Position* p, int w, int h)
{
    parent_pos = p;
    for(int i = 0; i < TESTPOINTCOUNT; i++)
    {
        test_points[i].parent_pos = this;
    }
    CollResetTestPoints(w, h);
}

Collision::~Collision()
{}

void
Collision::CollTest(Area* area)
{
    // 遍历检测点
    for(int i = 0; i < TESTPOINTCOUNT; i++)
    {
        test_points_value[i] = area->Area_in(test_points[i]);
    }
}

int
Collision::CollTestPointValue(int n) const
{
    Limit(n, 0, TESTPOINTCOUNT - 1);
    return test_points_value[n];
}

void
Collision::CollResetTestPoints(int w, int h)
{
    // 设置检测点的位置
    setpoints(test_points, TESTPOINTCOUNT, w, h);

    *(Point*)this = Point{-w / 2, -h / 2};
}
