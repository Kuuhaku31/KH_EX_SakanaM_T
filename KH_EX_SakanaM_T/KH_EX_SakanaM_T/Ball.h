
#pragma once

#include "Object.h"

#include "Boom.h"
#include "Animate.h"

#include "World.h"

class Ball:
	public Object
{	public:
	Ball(World* world, int x, int y, IMAGE* img = nullptr)
		: Object(&world->main_map, x, y)
		, main_world(world)
		, renderer(img, this)
		, break_animate(this)
	{}

	bool
	Update()
	{
		if (is_alive)
		{
			Object::Update();
			if (main_world->wall_map.Is_in_area(pos_x, pos_y) || main_world->coll_area.Is_in_area(pos_x, pos_y))
			{
				is_alive = false;
				main_world->Add_new_boom(Explode());
			}
			return true;
		}
		else
		{
			break_animate.Update();
			return break_animate.is_playing;
		}
	}

	Boom*
	Explode()
	{
		return new Boom(pos_x, pos_y, 20, 10);
	}

	Renderer*
	Get_renderer()
	{
		if (is_alive)
		{
			return &renderer;
		}
		else
		{
			return break_animate.Get_renderer();
		}
	}

	Renderer renderer;

	Animate break_animate;

private:

	World* main_world;

	bool is_alive = true;
};

