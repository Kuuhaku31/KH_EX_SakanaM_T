
#pragma once

#include "Map.h"
#include "Boom.h"

//const int MAINWORLDWIDE = 1600;
//const int MAINWORLDHIGH = 1280;
//const int MAINWORLDLONG = MAINWORLDWIDE * MAINWORLDHIGH;

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
		for (int i = 0; i < boom_count; i++)
		{
			if (!booms[i]->Update())
			{
				boom_count--;
				delete booms[i];
				booms[i] = booms[boom_count];
				booms[boom_count] = nullptr;
			}
		}
	}

	void
	Add_new_boom(Boom* b)
	{
		if (boom_count < MAX_BOOMS)
		{
			booms[boom_count] = b;
			boom_count++;
		}
		else
		{
			delete b;
		}
	}

	Map main_map;
	Map wall_map;
	Map fire_map;

	Area coll_area;
	Area hurt_area;

private:
	
	static const unsigned int MAX_BOOMS = 100;
	Boom* booms[MAX_BOOMS] = { nullptr };
	int boom_count = 0;

	unsigned int world_wide;
	unsigned int world_high;
	unsigned int world_long;
};
