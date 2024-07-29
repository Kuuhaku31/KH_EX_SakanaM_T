
#include "base.hpp"

// 构造、析构
Position::Position() : parent_pos(nullptr), pos_x(0), pos_y(0) {}
Position::Position(int x, int y) : parent_pos(nullptr), pos_x(x), pos_y(y) {}
Position::Position(Point p) : parent_pos(nullptr), pos_x(p.px), pos_y(p.py) {}
Position::Position(Position *p, int x, int y) : parent_pos(p), pos_x(x), pos_y(y) {}
Position::Position(Position *pos, Point poi) : parent_pos(pos), pos_x(poi.px), pos_y(poi.py) {}
Position::~Position() {}

// 获取
int Position::Position_pos_x() const { return pos_x; }
int Position::Position_pos_y() const { return pos_y; }
Position *Position::Position_parent_pos() const { return parent_pos; }
int Position::Position_root_x() const { return parent_pos ? parent_pos->Position_root_x() + pos_x : pos_x; }
int Position::Position_root_y() const { return parent_pos ? parent_pos->Position_root_y() + pos_y : pos_y; }

// 设置
void Position::Position_set_x(int x) { pos_x = x; }
void Position::Position_set_y(int y) { pos_y = y; }
void Position::Position_set(int x, int y)
{
	pos_x = x;
	pos_y = y;
}

void Position::Position_set(Point p)
{
	pos_x = p.px;
	pos_y = p.py;
}

void Position::Position_set(Position *p)
{
	parent_pos = p;
}

void Position::Position_set(Position *p, int x, int y)
{
	parent_pos = p;
	pos_x = x;
	pos_y = y;
}

void Position::Position_set(Position *pos, Point poi)
{
	parent_pos = pos;
	pos_x = poi.px;
	pos_y = poi.py;
}

void Position::Position_set(Position *p1, Position *p2)
{
	parent_pos = p1;
	pos_x = p2->pos_x;
	pos_y = p2->pos_y;
}

void Position::Position_move_x(int x) { pos_x += x; }
void Position::Position_move_y(int y) { pos_y += y; }
void Position::Position_move(int dx, int dy)
{
	pos_x += dx;
	pos_y += dy;
}

void Position::Position_move(Point p)
{
	pos_x += p.px;
	pos_y += p.py;
}

void Position::Position_move_x_to(int x) { pos_x = parent_pos ? x - Position_root_x() : x; }
void Position::Position_move_y_to(int y) { pos_y = parent_pos ? y - Position_root_y() : y; }
void Position::Position_move_to(int x, int y)
{
	pos_x = parent_pos ? x - Position_root_x() : x;
	pos_y = parent_pos ? y - Position_root_y() : y;
}

void Position::Position_move_to(Point p)
{
	pos_x = parent_pos ? p.px - Position_root_x() : p.px;
	pos_y = parent_pos ? p.py - Position_root_y() : p.py;
}

void Position::Position_move_to(Position *p)
{
	if (p)
	{
		pos_x = parent_pos ? p->Position_root_x() - Position_root_x() : p->Position_root_x();
		pos_y = parent_pos ? p->Position_root_y() - Position_root_y() : p->Position_root_y();
	}
}
