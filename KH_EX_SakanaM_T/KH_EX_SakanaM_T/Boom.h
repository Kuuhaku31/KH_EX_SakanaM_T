
#pragma once

#include "Area.h"

class Boom : public Area
{	public:
	Boom(Area* area, int x, int y, int r, int t)
		: Area(r * 2 + 1, r * 2 + 1)
		, hurt_area(area)
		, time(t)
	{
		Clear();
		Fill_circle(r, r, r, 2000, true);
		Set_position(x - r, y - r);
		hurt_area->Add_area(this);
	}

	bool
	Update()
	{
		time--;
		if (time > 0)
		{
			return true;
		}
		else
		{
			hurt_area->Add_area(this, true);
			return false;
		}
	}

	Boom* next_boom = nullptr;

private:
	Area* hurt_area;

	int time;
};
