
#include "base.hpp"

// 设置点的分布位置
inline void
setpoints(Position* p, int count, int w, int h)
{
    //如果count不是4的倍数
    if(count % 4)
    {
        for(int i = 0; i < count; i++)
        {
            (Point) p[i] = Point{w / 2, h / 2};
        }
    }
    else
    {
        int side     = count / 4;
        int spaced_w = w / (side + 1);
        int spaced_h = h / (side + 1);

        for(int i = 0; i < side; i++)
        {
            p[i]            = Point{spaced_w * (i + 1), 0};
            p[i + side]     = Point{w, spaced_h * (i + 1)};
            p[i + 2 * side] = Point{w - spaced_w * (i + 1), h};
            p[i + 3 * side] = Point{0, h - spaced_h * (i + 1)};
        }
    }
}

Collision::Collision() {}

Collision::Collision(int count, int w, int h)
{
    CollResetTestPoints(test_point_count, w, h);
}

Collision::~Collision()
{
    if(test_points) { delete[] test_points; }
    if(test_points_value) { delete[] test_points_value; }
}

void
Collision::CollTest(Area* area)
{
    // 遍历检测点
    for(int i = 0; i < test_point_count; i++)
    {
        test_points_value[i] = area->Area_in(&test_points[i]);
    }

    // 设置主检测点
    test_point_main = area->Area_in(this);
}

void
Collision::CollClearValue()
{
    for(int i = 0; i < test_point_count; i++) { test_points_value[i] = 0; }
    test_point_main = 0;
}

void
Collision::CollResetTestPoints(int count, int w, int h)
{
    // 先释放原来的检测点
    if(test_points) { delete[] test_points; }
    if(test_points_value) { delete[] test_points_value; }

    // 重新设置检测点
    test_point_count  = count;
    test_points       = new Position[test_point_count];
    test_points_value = new unsigned int[test_point_count];

    // 设置检测点的父位置
    for(int i = 0; i < test_point_count; i++) { test_points[i].parent_pos = this; }
    // 设置检测点的位置
    setpoints(test_points, test_point_count, w, h);

    px = -w / 2;
    py = -h / 2;
}

bool
Collision::CollGetTestPoint(Position*& p, int i)
{
    if(Limit(i, 0, test_point_count - 1))
    {
        p = &test_points[i];
        return true;
    }
    else
    {
        return false;
    }
}

int
Collision::CollGetTestPointCount() const
{
    return test_point_count;
}

unsigned int
Collision::CollGetTestPointValue(int index) const
{
    if(index == -1)
    {
        return test_point_main;
    }
    else if(Limit(index, 0, test_point_count - 1))
    {
        return test_points_value[index];
    }
    else
    {
        return 0;
    }
}
