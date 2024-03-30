
#pragma once

#include "Area.h"
#include "Ring.h"

class Hitbox : public Area
{	public:
	Hitbox() : Area() {}

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

	void Bind_node(Ring<Hitbox>* r) { node = r; }

private:

	Ring<Hitbox>* node = nullptr;

	int x = 0;
	int y = 0;
};
