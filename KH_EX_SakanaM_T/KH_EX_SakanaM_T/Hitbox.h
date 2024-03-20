
#pragma once

#include "World.h"

class Hitbox : public Area
{	public:
	Hitbox(World* main_world, Position* pos)
		: Area(pos)
		, main_world(main_world)
	{}

	void
	Add_hit_box_to_area()
	{
		main_world->coll_area.Add_area(this);
		x = Get_x();
		y = Get_y();
	}

	void
	Delete_hitbox_from_area()
	{
		main_world->coll_area.Add_shape(this, x, y, true);
	}

private:

	World* main_world;
	int x = 0;
	int y = 0;
};
