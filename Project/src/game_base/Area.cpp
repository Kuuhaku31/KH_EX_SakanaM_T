
#include "base.hpp"

Area::Area()
{}

Area::Area(Shape* s)
{
    Shape_copy(s);
}

Area::Area(Point xy, int w, int h)
    : Position{xy}
    , Shape(w, h)
{}

Area::Area(Position* p, Point xy, int w, int h)
    : Position{xy, p}
    , Shape(w, h)
{}

Area::~Area()
{}

int
Area::Area_local_x(int x) const
{
    return x - Position_root_x();
}

int
Area::Area_local_y(int y) const
{
    return y - Position_root_y();
}

Point
Area::Area_local_xy(Point p) const
{
    return Point{p.px - Position_root_x(), p.py - Position_root_y()};
}

int
Area::Area_in(Point p) const
{
    return Shape_in(Area_local_xy(p));
}

int
Area::Area_in(Position* pos) const
{
    return Shape_in(Area_local_xy(pos->Position_root_xy()));
}

bool
Area::Area_in(Point p, int b) const
{
    return Shape_in(Area_local_xy(p), b);
}

bool
Area::Area_in(Position* pos, int b) const
{
    return Shape_in(Area_local_xy(pos->Position_root_xy()), b);
}

bool
Area::Area_in_addr(int** addr, Point p)
{
    return Shape_in_addr(addr, Area_local_xy(p));
}

bool
Area::Area_in_addr(int** addr, Position* pos)
{
    return Shape_in_addr(addr, Area_local_xy(pos->Position_root_xy()));
}

void
Area::Area_align()
{
    px = -shape_wide / 2;
    py = -shape_high / 2;
}

void
Area::Area_align_x()
{
    px = -shape_wide / 2;
}

void
Area::Area_align_y()
{
    py = -shape_high / 2;
}
