
#include "base.hpp"

Object::Object() {}

Object::Object(Position* pos, Point poi)
    : Position{poi, pos}
{}

Object::~Object() {}


// 更新运动状态
void
Object::Update()
{
    // 更新速度、加速度
    movement_velocity += movement_acceleration * movement_DT;
    movement_acceleration = {0.0f, 0.0f};

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
    Point  int_dp   = {(int)float_dp.vx, (int)float_dp.vy};
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
Object::ObjectAddForce(Vector f)
{
    if(movement_mass)
    {
        movement_acceleration += f * (1.0 / movement_mass);
    }
}

void
Object::ObjectCollTest(Area* a)
{
    for(int i = 0; i < object_test_point_count; i++)
    {
        object_test_points_value[i] = a->Area_in(&object_test_points[i]);
        // std::cout << "\nobject_test_points[" << i << "].x: " << object_test_points[i].px << std::endl;
        // std::cout << "object_test_points[" << i << "].y: " << object_test_points[i].py << std::endl;
        // std::cout << "object_test_points[" << i << "].parent: " << object_test_points[i].parent_pos << std::endl;
        // std::cout << "object_test_points_value[" << i << "]: " << object_test_points_value[i] << std::endl;
    }
    object_test_points_value_main = a->Area_in(this);
}

// 返回
bool
Object::ObjectGetArea(Area** a, int t)
{
    if(Limit(t, 0, object_area_count - 1))
    {
        *a = &object_areas[t];
        return true;
    }
    else
    {
        return false;
    }
}

bool
Object::ObjectGetColl(Position** p, int t)
{
    if(Limit(t, 0, object_test_point_count - 1))
    {
        *p = &object_test_points[t];
        return true;
    }
    else
    {
        return false;
    }
}

void
Object::ObjectResetAreas(int count)
{
    if(object_areas)
    {
        delete[] object_areas;
    }

    object_area_count = count;
    object_areas      = new Area[count];
    for(int i = 0; i < object_area_count; i++)
    {
        object_areas[i].parent_pos = this;
    }
}

void
Object::ObjectResetColls(int count)
{
    if(object_test_points)
    {
        delete[] object_test_points;
    }

    if(object_test_points_value)
    {
        delete[] object_test_points_value;
    }

    object_test_point_count  = count;
    object_test_points       = new Position[count];
    object_test_points_value = new unsigned int[count];

    for(int i = 0; i < object_test_point_count; i++)
    {
        object_test_points[i].parent_pos = this;
    }
}

Area*
Object::ObjectGetArea()
{
    return object_areas;
}

Position*
Object::ObjectGetColl()
{
    return object_test_points;
}

int
Object::ObjectGetAreaCount()
{
    return object_area_count;
}

int
Object::ObjectGetCollCount()
{
    return object_test_point_count;
}
