
#include "base.hpp"

Object::Object(Position *pos, Point poi, float m, Vector v) : Position(pos, poi), Movement(this, m, v)
{
    for (short i = 0; i < OBJECTAREASCOUNT; i++)
    {
        objectAreas[i].Position_set(this);
    }

    for (short i = 0; i < OBJECTCOLLCOUNT; i++)
    {
        objectColls[i].Position_set(this);
    }
}

Object::~Object() {}

void Object::ObjectSetArea(Shape *s, Point p, ObjectAreaType t)
{
    objectAreas[t].Shape_copy(s);
    objectAreas[t].Position_set(p);
}

void Object::ObjectSetArea(Area *s, ObjectAreaType t)
{
    objectAreas[t].Area_copy(s);
}

// 返回
Area *Object::ObjectGetArea(ObjectAreaType t) { return &objectAreas[t]; }

Collision *Object::ObjectGetCollision(CollisionType t) { return &objectColls[t]; }
