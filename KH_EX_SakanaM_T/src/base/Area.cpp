
#include "base.hpp"

Area::Area(Shape *s) { Shape_copy(s); }
Area::Area(Point xy, int w, int h) : Position(xy), Shape(w, h) {}
Area::Area(Position *p, Point xy, int w, int h) : Position(p), Shape(w, h) {}
Area::~Area() {}

int Area::Area_local_x(int x) const { return x - Position_root_x(); }
int Area::Area_local_y(int y) const { return y - Position_root_y(); }
Point Area::Area_local(Point p) const { return {p.px - Position_root_x(), p.py - Position_root_y()}; }

int Area::Area_in(int x, int y) const { return Shape_in(Area_local_x(x), Area_local_y(y)); }
int Area::Area_in(Point p) const { return Shape_in(Area_local_x(p.px), Area_local_y(p.py)); }
int Area::Area_in(Position *pos) const { return Shape_in(Area_local_x(pos->Position_root_x()), Area_local_y(pos->Position_root_y())); }

void Area::Area_align() { Position_set(-(int)shape_wide / 2, -(int)shape_high / 2); }
void Area::Area_align_x() { Position_set_x(-shape_wide / 2); }
void Area::Area_align_y() { Position_set_y(-shape_high / 2); }

void Area::Area_copy(Area *a)
{
    Shape_copy(a);
    Position_set(a->Position_pos_x(), a->Position_pos_y());
}
