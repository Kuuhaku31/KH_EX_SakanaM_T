
#include "GameObjects.hpp"

Bullet::Bullet()
{
    ObjectResetAreas(BULLET_AREA_COUNT);
    ObjectResetColls(BULLET_TEST_POINTS_COUNT);
}

Bullet::Bullet(Position* pos, Point poi, Vector vec)
    : Object(pos, poi)
{
    ObjectResetAreas(BULLET_AREA_COUNT);
    ObjectResetColls(BULLET_TEST_POINTS_COUNT);

    movement_velocity = vec;
}

Bullet::~Bullet()
{}

void
Bullet::BulletExplode(Area* damage_area)
{
    AREA_COMPUTE(damage_area, (&object_areas[bullet_explode_range]), a += b;);
}
