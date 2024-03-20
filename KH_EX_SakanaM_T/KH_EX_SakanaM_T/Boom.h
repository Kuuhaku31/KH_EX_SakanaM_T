
#pragma once

#include "Area.h"

class Boom : public Area
{	public:
	Boom(int x, int y, int r, int t) 
		: Area(r * 2 + 1, r * 2 + 1)
		, time(t)
	{
		Clear();
		Fill_circle(r, r, r, 2000, true);
		Set_position(x - r, y - r);
	}

	bool
	Update()
	{
		time--;
		return time > 0 ? true : false;
	}

private:

	int time;
};
