
#pragma once

#include "World.h"

class Hitbox : public Area
{	public:
	Hitbox(World* main_world = nullptr, Position* pos = nullptr)
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

	void
	Copy(Hitbox* h)
	{
		main_world = h->main_world;
		x = h->x;
		y = h->y;
		Area::Copy(h);
	}

	World* main_world;
private:

	
	int x = 0;
	int y = 0;
};
