
#include "base.hpp"

Object::Object(Position *pos, Point poi, float m, Vector v) : Position(pos, poi), Movement(this, m, v)
{
    for (ushort i = 0; i < OBJECTAREASCOUNT; i++)
    {
        objectAreas[i] = new Area(this);
    }

    for (ushort i = 0; i < OBJECTCOLLCOUNT; i++)
    {
        objectColls[i] = new Collision(this);
    }
}

Object::~Object()
{
    // 释放内存
    for (ushort i = 0; i < OBJECTAREASCOUNT; i++)
    {
        delete objectAreas[i];
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

// 返回
Area *Object::ObjectGetArea(ObjectAreaType t) { return objectAreas[t]; }

Collision *Object::ObjectGetCollision(CollisionType t) { return objectColls[t]; }
