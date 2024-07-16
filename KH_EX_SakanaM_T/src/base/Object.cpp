
#include "base.hpp"

Object::Object(Position *pos, Point poi, float m, Vector v) : Position(pos, poi), Movement(this, m, v)
{
    for (ushort i = 0; i < OBJECTAREASMAX; i++)
    {
        objectAreas[i] = new Area(this);
    }
    for (ushort i = 0; i < OBJECTCOLLSMAX; i++)
    {
        objectColls[i] = new Collision(this);
    }
}

Object::~Object()
{
    // 释放内存
    for (ushort i = 0; i < OBJECTAREASMAX; i++)
    {
        delete objectAreas[i];
    }
    for (ushort i = 0; i < OBJECTCOLLSMAX; i++)
    {
        delete objectColls[i];
    }
}

void Object::ObjectSetArea(Shape *s, Point p, ObjectAreaType t)
{
    objectAreas[t]->Shape_copy(s);
    objectAreas[t]->Position_set(p);
}

void Object::ObjectSetArea(Area *s, ObjectAreaType t)
{
    objectAreas[t]->Area_copy(s);
}

// 设置碰撞检测
void Object::ObjectSetColl(ushort w, ushort h, ObjectCollType t)
{
    objectColls[t]->Reset_test_points(w, h);
}

// 返回
Area *Object::ObjectGetArea(ObjectAreaType t) { return objectAreas[t]; }
Collision *Object::ObjectGetColl(ObjectCollType t) { return objectColls[t]; }
