
#pragma once

#include "Map.h"
#include "Boom.h"

class World
{	public:
	World(unsigned int w, unsigned int h)
		: world_wide(w)
		, world_high(h)
		, world_long(w* h)
		, main_map(w, h)
		, wall_map(w, h)
		, fire_map(w, h)
		, coll_area(w, h)
		, hurt_area(w, h)
	{}

	void 
	Update_booms()
	{
		Boom* prev_boom = nullptr;
		Boom* now_boom = booms;

		while (now_boom)
		{
			if (!now_boom->Update())
			{
				if (now_boom == booms)
				{
					booms = now_boom->next_boom;
				}
				else
				{
					prev_boom->next_boom = now_boom->next_boom;
				}

				Boom* temp_boom = now_boom;
				now_boom = now_boom->next_boom;

				delete temp_boom;
			}
			else
			{
				prev_boom = now_boom;
				now_boom = now_boom->next_boom;
			}
		}
	}


	void
	Add_new_boom(Boom* b)
	{
		if (booms)
		{
			b->next_boom = booms;
			booms = b;
		}
		else
		{
			booms = b;
		}
	}

	Map main_map;
	Map wall_map;
	Map fire_map;

	Area coll_area;
	Area hurt_area;

private:

	Boom* booms = nullptr;

	unsigned int world_wide;
	unsigned int world_high;
	unsigned int world_long;
};
