
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

    if(is_exploding)
    {
        if(timer < 0)
        {
            timer--;
        }
        else
        {
            explodeDel();
        }
    }
    else
    {
        if(object_test_points_value_main)
        {
            explode();
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
    if(is_exploding)
    {
        explodeDel();
    }
}

void
Bullet::explode()
{
    if(is_exploding)
    {
        // 如果已经爆炸，直接返回
        return;
    }
    else if(explode_area)
    {
        is_exploding      = true;
        movement_velocity = ZEROVECTOR; // 立刻停止运动，添加爆炸影响
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
    bullet_alive = false;
    AREA_COMPUTE(explode_area, (&object_areas[bullet_explode_range]), a += b;);
}


Marble::Marble()
{
    ObjectResetAreas(MARBLE_AREA_COUNT);
    ObjectResetColls(MARBLE_TEST_POINTS_COUNT);

    init();
}

Marble::Marble(Position* pos, Point poi, Vector vec)
    : Object(pos, poi)
{
    ObjectResetAreas(MARBLE_AREA_COUNT);
    ObjectResetColls(MARBLE_TEST_POINTS_COUNT);

    movement_velocity = vec;

    init();
}

Marble::~Marble()
{
}

void
Marble::init()
{
    object_test_points[0] = Point{ 0, -5 };
    object_test_points[1] = Point{ 5, 0 };
    object_test_points[2] = Point{ 0, 5 };
    object_test_points[3] = Point{ -5, 0 };
}

void
Marble::Update()
{
    const int dhp = -5;
    const int dmp = 1;

    if(!marble_alive) return;
    if(marble_HP <= 0)
    {
        marble_alive = false;
        return;
    }

    if(object_test_points_value[0])
    {
        movement_velocity.vy = -movement_velocity.vy;
        marble_HP += dhp;
        py += dmp;
    }
    if(object_test_points_value[1])
    {
        movement_velocity.vx = -movement_velocity.vx;
        marble_HP += dhp;
        px -= dmp;
    }
    if(object_test_points_value[2])
    {
        movement_velocity.vy = -movement_velocity.vy;
        marble_HP += dhp;
        py -= dmp;
    }
    if(object_test_points_value[3])
    {
        movement_velocity.vx = -movement_velocity.vx;
        marble_HP += dhp;
        px += dmp;
    }

    Object::Update();
}

bool
Marble::MarbleIsAlive() const
{
    return marble_alive;
}

void
Marble::MarbleKill()
{
    marble_alive = false;
}
