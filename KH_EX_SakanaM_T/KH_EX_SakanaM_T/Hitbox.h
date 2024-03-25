
#pragma once

#include "Area.h"

class Hitbox : public Area
{	public:
	Hitbox(Position* pos = nullptr) : Area(pos) {}

	void
	Add_hit_box_to_area(Area* area)
	{
		area->Add_area(this);
		x = Get_x();
		y = Get_y();
	}

	void
	Delete_hitbox_from_area(Area* area)
	{
		area->Add_shape(this, x, y, true);
	}

private:

	int x = 0;
	int y = 0;
};
