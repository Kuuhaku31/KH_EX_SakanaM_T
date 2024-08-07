
#include "GameObjects.hpp"


GameObject::~GameObject()
{
    free();
}

// 更新运动状态
void
GameObject::Update()
{
    if(!is_alive) return;

    updateTimer();
    updateTestValue();
    updateMovement();
}

void
GameObject::Force(Vector f)
{
    if(movement_mass)
    {
        movement_acceleration += f * (1.0 / movement_mass);
    }
}

void
GameObject::init()
{
    if(zone == nullptr)
    {
        is_alive = false;
        return;
    }
    animation_timer.Timer_setLoop(true);
}

void
GameObject::free()
{
    if(test_point_count)
    {
        test_point_count = 0;

        delete[] test_points;
        delete[] test_points_value;

        test_points       = nullptr;
        test_points_value = nullptr;
    }
}

void
GameObject::updateTimer()
{
    animation_timer.Timer_update();
}

void
GameObject::updateMovement()
{
    // 更新速度、加速度
    movement_velocity += movement_acceleration * movement_DT;
    movement_acceleration = { 0.0f, 0.0f };

    if(movement_mass && movement_velocity != ZEROVECTOR && movement_resistance != ZEROVECTOR)
    {
        // 根据阻力参数改变运动状态
        float v_mod  = module(movement_velocity);
        float v_mod_ = v_mod - (movement_resistance.vx + v_mod * v_mod * movement_resistance.vy) / movement_mass;

        if(v_mod_ < 0.0f)
        {
            movement_velocity = ZEROVECTOR;
        }
        else
        {
            movement_velocity *= v_mod_ / v_mod;
        }
    }

    Vector float_dp = movement_velocity * movement_DT;
    Point  int_dp   = { (int)float_dp.vx, (int)float_dp.vy };
    movement_buffer += float_dp - int_dp;

    if(movement_buffer.vx > 1.0f)
    {
        int_dp.px++;
        movement_buffer.vx -= 1.0f;
    }
    else if(movement_buffer.vx < -1.0f)
    {
        int_dp.px--;
        movement_buffer.vx += 1.0f;
    }

    if(movement_buffer.vy > 1.0f)
    {
        int_dp.py++;
        movement_buffer.vy -= 1.0f;
    }
    else if(movement_buffer.vy < -1.0f)
    {
        int_dp.py--;
        movement_buffer.vy += 1.0f;
    }

    // 更新位置
    *this += int_dp;
}

void
GameObject::updateTestValue()
{
    for(int i = 0; i < test_point_count; i++)
    {
        test_points_value[i] = zone->zone_matter.Area_in(&test_points[i]);
        // std::cout << "\nobject_test_points[" << i << "].x: " << object_test_points[i].px << std::endl;
        // std::cout << "object_test_points[" << i << "].y: " << object_test_points[i].py << std::endl;
        // std::cout << "object_test_points[" << i << "].parent: " << object_test_points[i].parent_pos << std::endl;
        // std::cout << "object_test_points_value[" << i << "]: " << object_test_points_value[i] << std::endl;
    }
    test_points_value_main = zone->zone_matter.Area_in(this);
}
