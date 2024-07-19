
#include "GameObjects.hpp"

GameObject::GameObject(MessageSystem *mss, Zone *z, Point poi, float m, Vector v) : Object(z, poi, m, v), message_system(mss), zone(z) {}

GameObject::~GameObject() {}

bool GameObject::GameObjectUpdate()
{
    // 先获取当前位置的值
    int now_point = zone->Area_in(this);

    // 如果在主区域内
    if (now_point & (0x1 << main_area))
    {
        // 如果在墙壁区域内
        ZoneAreaType collisioncode = wall_area_01;
        if (now_point & (0x1 << collisioncode))
        {
            return false;
        }

        // 检测碰撞
        objectColls[0]->CollTest(zone);

        // 获取碰撞情况
        bool v[TESTPOINTCOUNT] = {false};
        for (short i = 0; i < TESTPOINTCOUNT; i++)
        {
            v[i] = (objectColls[0]->test_points_value[i]) >> collisioncode;
        }

        // 根据碰撞情况更新Movement
        float force = zone->ZoneGetCollForce(collisioncode);
        Vector force_vector = ZEROVECTOR;
        if (v[0])
        {
            force_vector.vy += force;
            pos_y += 1;
            MovementResetAcceleration_y();
        }
        if (v[1])
        {
            force_vector.vy += force;
            MovementResetAcceleration_y();
            pos_y += 1;
        }
        if (v[2])
        {
            force_vector.vx -= force;
            MovementResetAcceleration_x();
            pos_x -= 1;
        }
        if (v[3])
        {
            force_vector.vx -= force;
            MovementResetAcceleration_x();
            pos_x -= 1;
        }
        if (v[4])
        {
            force_vector.vy -= force;
            MovementResetAcceleration_y();
            pos_y -= 1;
        }
        if (v[5])
        {
            force_vector.vy -= force;
            MovementResetAcceleration_y();
            pos_y -= 1;
        }
        if (v[6])
        {
            force_vector.vx += force;
            MovementResetAcceleration_x();
            pos_x += 1;
        }
        if (v[7])
        {
            force_vector.vx += force;
            MovementResetAcceleration_x();
            pos_x += 1;
        }

        MovementAddForce(force_vector);

        Vector relative_vector = ZEROVECTOR;
        // 如果在阻力区域内
        ZoneAreaType movementcode = relative_area_01;
        if (now_point & (0x1 << movementcode))
        {
            // 获取阻力参数
            relative_vector = zone->ZoneGetRelative(movementcode);
        }

        // 更新Movement
        MovementUpdate(relative_vector);

        return true;
    }
    else
    {
        return false;
    }
}
