
#include "Collision.h"

Collision::Collision(Movement *m) : movement(m) {}

Collision::Collision(Movement *m, ushort w, ushort h) : movement(m) { Reset_test_points(w, h); }

Collision::~Collision() {}

void Collision::Update(Area *area)
{
    // 先将检测点值清零
    for (int i = 0; i < 8; i++)
    {
        test_points_value[i] = 0;
    }

    // 赋值
    if (area)
    {
        for (int i = 0; i < 8; i++)
        {
            test_points_value[i] = area->Area_in(test_points[i]);
        }
    }

    // 碰撞处理
    if (test_points_value[1])
    {
        movement->ResetVelocity_y();
        movement->AddForce(Vector{0, -COLLFORCE});
    }
    if (test_points_value[3])
    {
        movement->ResetVelocity_x();
        movement->AddForce(Vector{-COLLFORCE, 0});
    }
    if (test_points_value[5])
    {
        movement->ResetVelocity_y();
        movement->AddForce(Vector{0, COLLFORCE});
    }
    if (test_points_value[7])
    {
        movement->ResetVelocity_x();
        movement->AddForce(Vector{COLLFORCE, 0});
    }
}

void Collision::Reset_test_points(ushort w, ushort h)
{
    test_points[0].SetPosition(-w / 2, -h / 2);
    test_points[1].SetPosition(0, -h / 2);
    test_points[2].SetPosition(w / 2, -h / 2);
    test_points[3].SetPosition(w / 2, 0);
    test_points[4].SetPosition(w / 2, h / 2);
    test_points[5].SetPosition(0, h / 2);
    test_points[6].SetPosition(-w / 2, h / 2);
    test_points[7].SetPosition(-w / 2, 0);
}

uint Collision::Get_test_points_value(short i)
{
    return test_points_value[i];
}
