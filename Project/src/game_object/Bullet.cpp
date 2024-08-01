
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
{}

void
Bullet::Update()
{
    if(is_timer)
    {
        if(timer)
        {
            timer--;
        }
        else
        {
            BulletExplodeDel();
            bullet_alive = false;
        }
    }
    else
    {
        if(object_test_points_value_main)
        {
            BulletExplode();
            is_timer = true;
        }

        Object::Update();
    }
}

void
Bullet::BulletExplode()
{
    movement_velocity = ZEROVECTOR;
    if(explode_area)
    {
        AREA_COMPUTE(explode_area, (&object_areas[bullet_explode_range]), a += b;);
    }
}

void
Bullet::BulletExplodeDel()
{
    if(explode_area)
    {
        AREA_COMPUTE(explode_area, (&object_areas[bullet_explode_range]), a -= b;);
    }
}
