
#include "GameObjects.hpp"

Bullet::Bullet(Zone* z)
    : GameObject(z)
{
    explode_area.parent_pos = this;
}


Bullet::~Bullet()
{
    explodeDel();
}

void
Bullet::Update()
{
    if(!is_alive) return;

    if(explode_timer_del.is_timing)
    {
        if(explode_timer_del.Timer_getTime())
        {
            explode_timer_del.Timer_update();
        }
        else
        {
            explodeDel();
            is_alive = false;
        }
    }
    else
    {
        if(test_points_value_main)
        {
            explode();
            return;
        }

        GameObject::Update();
    }
}


void
Bullet::explode()
{
    if(explode_timer_del.is_timing)
    {
        // 如果已经爆炸，直接返回
        return;
    }
    else
    {
        explode_timer_del.is_timing = true;
        movement_velocity           = ZEROVECTOR; // 立刻停止运动，添加爆炸影响
        zone->zone_damage += explode_area;
    }
}

// 清除爆炸影响
void
Bullet::explodeDel()
{
    if(explode_timer_del.is_timing)
    {
        explode_timer_del.is_timing = false;
        zone->zone_damage -= explode_area;
    }
}


// Marble::Marble()
// {
//     ObjectResetAreas(MARBLE_AREA_COUNT);
//     ObjectResetColls(MARBLE_TEST_POINTS_COUNT);

//     init();
// }

// Marble::Marble(Position* pos, Point poi, Vector vec)
//     : GameObject(pos, poi)
// {
//     ObjectResetAreas(MARBLE_AREA_COUNT);
//     ObjectResetColls(MARBLE_TEST_POINTS_COUNT);

//     movement_velocity = vec;

//     init();
// }

// Marble::~Marble()
// {
// }

// void
// Marble::init()
// {
//     object_test_points[0] = Point{ 0, -5 };
//     object_test_points[1] = Point{ 5, 0 };
//     object_test_points[2] = Point{ 0, 5 };
//     object_test_points[3] = Point{ -5, 0 };
// }

// void
// Marble::Update()
// {
//     const int dhp = -5;
//     const int dmp = 1;

//     if(!marble_alive) return;
//     if(marble_HP <= 0)
//     {
//         marble_alive = false;
//         return;
//     }

//     if(object_test_points_value[0])
//     {
//         movement_velocity.vy = -movement_velocity.vy;
//         marble_HP += dhp;
//         py += dmp;
//     }
//     if(object_test_points_value[1])
//     {
//         movement_velocity.vx = -movement_velocity.vx;
//         marble_HP += dhp;
//         px -= dmp;
//     }
//     if(object_test_points_value[2])
//     {
//         movement_velocity.vy = -movement_velocity.vy;
//         marble_HP += dhp;
//         py -= dmp;
//     }
//     if(object_test_points_value[3])
//     {
//         movement_velocity.vx = -movement_velocity.vx;
//         marble_HP += dhp;
//         px += dmp;
//     }

//     GameObject::Update();
// }

// bool
// Marble::MarbleIsAlive() const
// {
//     return marble_alive;
// }

// void
// Marble::MarbleKill()
// {
//     marble_alive = false;
// }
