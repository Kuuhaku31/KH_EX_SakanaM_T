
#pragma once

#include "Shape.h"
#include "Position.h"

#include "Matrix.h"

class Area
	: public Position
	, public Shape
{	public:
	Area(Position* pos = nullptr) : Position(pos) {}
	Area(int w, int h, Position* pos = nullptr)
		: Position(pos)
		, Shape(w, h)
	{}

	unsigned long
	Is_in_area(int x, int y, bool is_use_local = false) const
	{
		if (!is_use_local) { x -= Get_x(); y -= Get_y(); }
		return Is_in_shape(x, y);
	}

	void
	Add_area(Area* area, bool is_neg = false)
	{
		Add_shape(area, area->Get_x() - Get_x(), area->Get_y() - Get_y(), is_neg);
	}

	void Align() { Set_position(-shape_wide / 2, -shape_high / 2); }
	void Align_x() { Set_position_x(-shape_wide / 2); }
	void Align_y() { Set_position_y(-shape_high / 2); }

	void
	Fill_circle(int centerX, int centerY, int radius, unsigned long value, bool is_use_local = false)
	{
		if (!is_use_local) { centerX -= Get_x(); centerY -= Get_y(); }
		Shape::Fill_circle(centerX, centerY, radius, value);
	}

private:
};
