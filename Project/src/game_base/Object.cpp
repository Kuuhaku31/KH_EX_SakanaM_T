
#include "base.hpp"

Object::Object()
{
    for(short i = 0; i < OBJECTAREASCOUNT; i++)
    {
        objectAreas[i].parent_pos = this;
    }

    for(short i = 0; i < OBJECTCOLLCOUNT; i++)
    {
        objectColls[i].parent_pos = this;
    }
}

Object::Object(Position* pos, Point poi)
    : Position{poi, pos}
{
    for(short i = 0; i < OBJECTAREASCOUNT; i++)
    {
        objectAreas[i].parent_pos = this;
    }

    for(short i = 0; i < OBJECTCOLLCOUNT; i++)
    {
        objectColls[i].parent_pos = this;
    }
}

Object::~Object() {}

// 返回
Area*
Object::ObjectGetArea(int t)
{
    Limit<0, OBJECTAREASCOUNT - 1>(t);
    return &objectAreas[t];
}

Collision*
Object::ObjectGetCollision(int t)
{
    Limit<0, OBJECTCOLLCOUNT - 1>(t);
    return &objectColls[t];
}

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
