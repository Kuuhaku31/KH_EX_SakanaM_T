
#include "Object.hpp"

Object::Object(MessageSystem *mss, Position *pos, Point poi, float m, Vector v) : Position(pos, poi), Movement(this, m, v), message_system(mss)
{
    main_skin = new Area(this);
    main_hit_box = new Area(this);
    main_coll = new Collision(this);
}

Object::~Object()
{
    delete main_skin;
    delete main_hit_box;
    delete main_coll;
}

// 更新

// 设置skin
void Object::SetSkin(Shape *s)
{
    main_skin->Shape_copy(s);
}

void Object::SetSkin(Shape *s, int x, int y)
{
    main_skin->Shape_copy(s);
    main_skin->Position_set(x, y);
}

void Object::SetSkin(Shape *s, Point p)
{
    main_skin->Shape_copy(s);
    main_skin->Position_set(p);
}

void Object::SetSkin(Area *a)
{
    main_skin->Area_copy(a);
}

// 设置碰撞盒
void Object::SetHitBox(Shape *s)
{
    main_hit_box->Shape_copy(s);
}

void Object::SetHitBox(Shape *s, int x, int y)
{
    main_hit_box->Shape_copy(s);
    main_hit_box->Position_set(x, y);
}

void Object::SetHitBox(Shape *s, Point p)
{
    main_hit_box->Shape_copy(s);
    main_hit_box->Position_set(p);
}

void Object::SetHitBox(Area *a)
{
    main_hit_box->Area_copy(a);
}

// 设置碰撞检测
void Object::SetColl(ushort c, ushort m)
{
    main_coll->Reset_test_points(c, m);
}
