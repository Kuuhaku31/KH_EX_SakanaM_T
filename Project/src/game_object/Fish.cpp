
#include "GameObjects.hpp"


Fish::Fish() {}
Fish::~Fish() {}

void
Fish::Update()
{
    // 如果HP为0，立即死亡
    if(fish_HP <= 0) { fish_alive = false; }


    // 根据碰撞情况更新Movement
#define tpv objectColls[main_coll].test_points_value

    Vector force_vector = ZEROVECTOR;
    int    maxforce     = 1000000;
    int    force        = 0;

    // 上方受到碰撞
    if(force = tpv[0] + tpv[1] + tpv[2])
    {
        if(force > maxforce) // 如果受到的力过大，则视为碰到墙壁，立即停止
        {
            movement_velocity.vy = 0;
            px += 1;
        }
        else
        {
            force_vector.vy += force / 3;
        }
    }

    // 右方受到碰撞
    if(force = tpv[2] + tpv[3] + tpv[4])
    {
        if(force > maxforce)
        {
            movement_velocity.vx = 0;
            px -= 1;
        }
        else
        {
            force_vector.vx -= force / 3;
        }
    }

    // 下方受到碰撞
    if(force = tpv[4] + tpv[5] + tpv[6])
    {
        if(force > maxforce)
        {
            movement_velocity.vy = 0;
            px -= 1;
        }
        else
        {
            force_vector.vy -= force / 3;
        }
    }

    // 左方受到碰撞
    if(force = tpv[6] + tpv[7] + tpv[0])
    {
        if(force > maxforce)
        {
            movement_velocity.vx = 0;
            px += 1;
        }
        else
        {
            force_vector.vx += force / 3;
        }
    }
    ObjectAddForce(force_vector);

#undef tpv

    // 更新
    Object::Update();
}

int
Fish::FishGetHP()
{
    return fish_HP;
}
int
Fish::FishGetPower()
{
    return fish_power;
}

void
Fish::FishSetHP(int hp)
{
    fish_HP = hp;
    Limit(fish_HP, 0, fish_HP_MAX);
}

void
Fish::FishSetPower(int p)
{
    fish_power = p;
    Limit(fish_power, 0, fish_power_MAX);
}

void
Fish::FishSetHP_d(int hp)
{
    fish_HP += hp;
    Limit(fish_HP, 0, fish_HP_MAX);
}

void
Fish::FishSetPower_d(int p)
{
    fish_power += p;
    Limit(fish_power, 0, fish_power_MAX);
}