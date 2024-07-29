
#include "base.hpp"

Object::Object()
    : Movement(this)
{
    for(short i = 0; i < OBJECTAREASCOUNT; i++)
    {
        objectAreas[i].parent_pos = this;
    }

    for(short i = 0; i < OBJECTCOLLCOUNT; i++)
    {
        objectColls[i].parent_pos = this;
    }
}

Object::Object(Position* pos, Point poi)
    : Position{poi, pos}
    , Movement(this)
{
    for(short i = 0; i < OBJECTAREASCOUNT; i++)
    {
        objectAreas[i].parent_pos = this;
    }

    for(short i = 0; i < OBJECTCOLLCOUNT; i++)
    {
        objectColls[i].parent_pos = this;
    }
}

Object::~Object() {}

// 返回
Area*
Object::ObjectGetArea(ObjectAreaType t)
{
    return &objectAreas[t];
}

Collision*
Object::ObjectGetCollision(ObjectCollType t)
{
    return &objectColls[t];
}
