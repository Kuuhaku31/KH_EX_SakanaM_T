
#include "Movement.hpp"

Movement::Movement(Position *p)
    : position(p),
      DT(0.1f),
      mass(0.0f),
      buf_p(ZEROVECTOR),
      mov_v(ZEROVECTOR),
      mov_a(ZEROVECTOR) {}

Movement::Movement(Position *p, float m, Vector v)
    : position(p),
      DT(0.1f),
      mass(m),
      buf_p(ZEROVECTOR),
      mov_v(v),
      mov_a(ZEROVECTOR) {}

Movement::~Movement() {}

// 更新运动状态
void Movement::Update(drag_data dd)
{
    if (mov_v != ZEROVECTOR)
    {
        // 根据阻力参数改变运动状态
        float v_mod = module(mov_v);

        float fforce_1 = dd.drag_u;
        float fforce_2 = v_mod * v_mod * dd.drag_c;

        if (mass > 0.0f)
        {
            fforce_1 *= (dd.drag_f / mass);
            fforce_2 *= (dd.drag_r / mass);
        }
        float v_mod_ = v_mod - (fforce_1 + fforce_2) * dd.area_drag;

        if (v_mod_ < 0.0f)
        {
            mov_v.vx = 0;
            mov_v.vy = 0;
        }
        else
        {
            mov_v.vx *= v_mod_ / v_mod;
            mov_v.vy *= v_mod_ / v_mod;
        }
    }

    Vector float_dp = mov_v * DT;

    Point int_dp = {(int)float_dp.vx, (int)float_dp.vy};

    buf_p += float_dp - int_dp;

    if (buf_p.vx > 1.0f)
    {
        int_dp.px++;
        buf_p.vx -= 1.0f;
    }
    else if (buf_p.vx < -1.0f)
    {
        int_dp.px--;
        buf_p.vx += 1.0f;
    }

    if (buf_p.vy > 1.0f)
    {
        int_dp.py++;
        buf_p.vy -= 1.0f;
    }
    else if (buf_p.vy < -1.0f)
    {
        int_dp.py--;
        buf_p.vy += 1.0f;
    }

    // 更新位置
    position->Position_move(int_dp);

    // 更新速度、加速度
    mov_v += mov_a * DT;
    mov_a = {0.0f, 0.0f};
}

void Movement::ResetDT(float dt) { DT = dt; }
void Movement::ResetMass(float m) { mass = m; }
void Movement::ResetVelocity(Vector v) { mov_v = v; }
void Movement::AddVelocity(Vector v) { mov_v += v; }

void Movement::ResetAcceleration(Vector a) { mov_a = a; }
void Movement::ResetForce(Vector f) { mov_a = f; }
void Movement::AddForce(Vector f) { mov_a += f; }

float Movement::GetDT() { return DT; }
float Movement::GetMass() { return mass; }
Vector Movement::GetVelocity() { return mov_v; }
Vector Movement::GetAcceleration() { return mov_a; }
