
#include "base.hpp"

Collision::Collision(ushort w, ushort h) { CollResetTestPoints(w, h); }
Collision::~Collision() {}

void Collision::CollUpdate(Position *pos, Area *area, uint *b)
{
    if (pos && area && b)
    {
        parent_pos = pos;

        // 赋值
        for (int i = 0; i < TESTPOINTCOUNT; i++)
        {
            b[i] = area->Area_in(&test_points[i]);
        }
    }
}

void Collision::CollResetTestPoints(ushort w, ushort h)
{
    test_points[0].Position_set(-w, -h);
    test_points[1].Position_set(+0, -h);
    test_points[2].Position_set(+w, -h);
    test_points[3].Position_set(+w, +0);
    test_points[4].Position_set(+w, +h);
    test_points[5].Position_set(+0, +h);
    test_points[6].Position_set(-w, +h);
    test_points[7].Position_set(-w, +0);
}
