
#pragma once

#include "Object.h"

#include "Boom.h"
#include "Animate.h"

#include "World.h"

class Ball:
	public Object
{	public:
	Ball(World* world, int x, int y, IMAGE* img = nullptr)
		: Object(world, x, y)
		, renderer(img, static_cast<Object*>(this))
		, break_animate(static_cast<Object*>(this))
	{}

	bool
	Update()
	{
		if (is_alive)
		{
			Update_mov();
			if 
			(
				main_world->wall_map.Is_in_area(static_cast<Object*>(this)) 
			 || main_world->coll_area.Is_in_area(static_cast<Object*>(this))
			)
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
		return new Boom(&main_world->hurt_area, Position::Get_x(), Position::Get_y(), 20, 10);
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

	bool is_alive = true;
};

