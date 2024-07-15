
#include "Area.hpp"

Area::Area() : Position(), Shape() {}
Area::Area(int x, int y, uint w, uint h) : Position(x, y), Shape(w, h) {}
Area::Area(Point xy, uint w, uint h) : Position(xy), Shape(w, h) {}
Area::Area(Position *p) : Position(p), Shape() {}
Area::Area(Position *p, int x, int y, uint w, uint h) : Position(p, x, y), Shape(w, h) {}
Area::Area(Position *p, Point xy, uint w, uint h) : Position(p), Shape(w, h) {}
Area::~Area() {}

int Area::Area_local_x(int x) const { return x - Position_root_x(); }
int Area::Area_local_y(int y) const { return y - Position_root_y(); }
Point Area::Area_local(Point p) const { return {p.px - Position_root_x(), p.py - Position_root_y()}; }

uint Area::Area_in(int x, int y) const { return Shape_in(Area_local_x(x), Area_local_y(y)); }
uint Area::Area_in(Point p) const { return Shape_in(Area_local_x(p.px), Area_local_y(p.py)); }
uint Area::Area_in(Position *pos) const { return Shape_in(Area_local_x(pos->Position_root_x()), Area_local_y(pos->Position_root_y())); }

void Area::Area_compute(Area *area, void f(uint &, uint &)) { Shape::Shape_compute(area, area->Position_root_x() - Position_root_x(), area->Position_root_y() - Position_root_y(), f); }

void Area::Area_align() { Position_set(-(int)shape_wide / 2, -(int)shape_high / 2); }
void Area::Area_align_x() { Position_set_x(-shape_wide / 2); }
void Area::Area_align_y() { Position_set_y(-shape_high / 2); }

void Area::Area_copy(Area *a)
{
    Shape_copy(a);
    Position_set(a->Position_pos_x(), a->Position_pos_y());
}
