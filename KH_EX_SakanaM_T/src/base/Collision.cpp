
#include "base.hpp"

Collision::Collision(Position *p, ushort w, ushort h) : Position(p)
{
    for (ushort i = 0; i < TESTPOINTCOUNT; i++)
    {
        test_points[i] = new Position(this);
    }
    CollResetTestPoints(w, h);
}

Collision::~Collision()
{
    for (ushort i = 0; i < TESTPOINTCOUNT; i++)
    {
        delete test_points[i];
    }
}

void Collision::CollTest(Area *area)
{
    // 遍历检测点
    for (short i = 0; i < TESTPOINTCOUNT; i++)
    {
        test_points_value[i] = area->Area_in(test_points[i]);
    }
}

void Collision::CollResetTestPoints(ushort w, ushort h)
{
    test_points[0]->Position_set(w / 3, 0);
    test_points[1]->Position_set(2 * w / 3, 0);
    test_points[2]->Position_set(w, h / 3);
    test_points[3]->Position_set(w, 2 * h / 3);
    test_points[4]->Position_set(2 * w / 3, h);
    test_points[5]->Position_set(w / 3, h);
    test_points[6]->Position_set(0, 2 * h / 3);
    test_points[7]->Position_set(0, h / 3);

    Position_set(-w / 2, -h / 2);
}
