
#include "GameObjects.hpp"

Bullet::Bullet()
{
    ObjectResetAreas(BULLET_AREA_COUNT);
    ObjectResetColls(BULLET_TEST_POINTS_COUNT);
}

Bullet::Bullet(Position* pos, Point poi, Vector vec, Area* ea)
    : Object(pos, poi)
    , explode_area(ea)
{
    ObjectResetAreas(BULLET_AREA_COUNT);
    ObjectResetColls(BULLET_TEST_POINTS_COUNT);

    movement_velocity = vec;
}

Bullet::~Bullet()
{
}

void
Bullet::Update()
{
    if(!bullet_alive) return;

    if(is_timer)
    {
        if(timer < 0)
        {
            timer--;
        }
        else
        {
            explodeDel();
            bullet_alive = false;
        }
    }
    else
    {
        if(object_test_points_value_main)
        {
            explode();
            is_timer = true;
            return;
        }

        Object::Update();
    }
}

bool
Bullet::BulletIsAlive() const
{
    return bullet_alive;
}

void
Bullet::BulletKill()
{
    bullet_alive = false;
}

void
Bullet::explode()
{
    if(explode_area)
    {
        // 立刻停止运动，添加爆炸影响
        movement_velocity = ZEROVECTOR;
        AREA_COMPUTE(explode_area, (&object_areas[bullet_explode_range]), a -= b;);
    }
    else
    {
        bullet_alive = false;
    }
}

// 清除爆炸影响
void
Bullet::explodeDel()
{
    AREA_COMPUTE(explode_area, (&object_areas[bullet_explode_range]), a += b;);
}
