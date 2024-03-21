
#pragma once

#include <graphics.h>

#include "Position.h"
#include "Shape.h"

class Renderer
	: public Position
	, public Shape
{	public:
	Renderer(IMAGE* img = nullptr, Position* pos = nullptr, int x = 0, int y = 0)
		: Position(pos, x, y)
		, Shape()
	{ Reset_skin(img); }

	void
	Reset_skin(IMAGE* img = nullptr)
	{
		if (img) { Write(GetImageBuffer(img), img->getwidth(), img->getheight()); }
		else { Zero(); }
	}

	void Align() { Set_position(-shape_wide >> 1, -shape_high >> 1); }
	void Align_x() { Set_position_x(-shape_wide >> 1); }
	void Align_y() { Set_position_y(-shape_high >> 1); }

private:

};
