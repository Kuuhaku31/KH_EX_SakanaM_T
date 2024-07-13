
#include "Area.hpp"

Area::Area() : Position(), Shape() {}
Area::Area(Position *pos) : Position(pos), Shape() {}
Area::~Area() {}

int Area::Local_x(int x) const { return x - Get_x(); }
int Area::Local_y(int y) const { return y - Get_y(); }

unsigned int Area::In_area(int x, int y) const
{
	return Shape_in(Local_x(x), Local_y(y));
}

unsigned int Area::In_area(Position *pos) const
{
	return Shape_in(Local_x(pos->Get_x()), Local_y(pos->Get_y()));
}

void Area::Compute(Area *area, void f(unsigned int *, unsigned int *))
{
	int dx = area->Get_x() - Get_x();
	int dy = area->Get_y() - Get_y();
	Shape::Shape_compute(area, dx, dy, f);
}

void Area::Align() { Set_position(-shape_wide / 2, -shape_high / 2); }
void Area::Align_x() { Set_position_x(-shape_wide / 2); }
void Area::Align_y() { Set_position_y(-shape_high / 2); }
