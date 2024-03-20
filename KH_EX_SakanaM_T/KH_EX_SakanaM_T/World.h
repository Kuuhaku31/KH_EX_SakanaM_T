
#pragma once

#include "Map.h"
#include "Boom.h"

const int MAINWORLDWIDE = 1600;
const int MAINWORLDHIGH = 1280;
const int MAINWORLDLONG = MAINWORLDWIDE * MAINWORLDHIGH;

class World
{	public:
	World()
		: main_map(MAINWORLDWIDE, MAINWORLDHIGH)
		, wall_map(MAINWORLDWIDE, MAINWORLDHIGH)
		, fire_map(MAINWORLDWIDE, MAINWORLDHIGH)
		, coll_area(MAINWORLDWIDE, MAINWORLDHIGH)
		, hurt_area(MAINWORLDWIDE, MAINWORLDHIGH)
	{
		for (int i = 0; i < MAX_BOOMS; i++)
		{
			booms[i] = nullptr;
		}
	}

	void
	Update_booms()
	{
		for (int i = 0; i < boom_count; i++)
		{
			if (!booms[i]->Update())
			{
				hurt_area.Add_area(booms[i], true);
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
			hurt_area.Add_area(b);
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
	
	static const int MAX_BOOMS = 100;
	Boom* booms[MAX_BOOMS] = { nullptr };
	int boom_count = 0;
};
