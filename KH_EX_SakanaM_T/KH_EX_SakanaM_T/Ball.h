
#pragma once

#include "struct_static.h"

#include "Object.h"

#include "Boom.h"
#include "Animate.h"

#include "World.h"

class Ball:
	public Object
{	public:
	Ball(World* world, int x, int y) : Object(world, x, y)
	{
		move__animate.Copy_cuts(&static_resource.animate_for_ball);
		move__animate.Copy_stat(&static_resource.animate_for_ball);
		move__animate.Set_position(static_cast<Object*>(this), &static_resource.animate_for_ball);
		break_animate.Copy_cuts(&static_resource.animate_for_ball_break);
		break_animate.Copy_stat(&static_resource.animate_for_ball_break);
		break_animate.Set_position(static_cast<Object*>(this), &static_resource.animate_for_ball_break);

		Hitbox::Copy_shape(&static_resource.hitbox_ball);
		Hitbox::Set_position(static_cast<Object*>(this), &static_resource.hitbox_ball);
	}

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
			return move__animate.Get_renderer();
		}
		else
		{
			return break_animate.Get_renderer();
		}
	}

	Animate move__animate;
	Animate break_animate;

	static void
	Load_static_resource(static_resource_ball* res)
	{
		static_resource.animate_for_ball.Copy_cuts(&res->animate_for_ball);
		static_resource.animate_for_ball.Copy_stat(&res->animate_for_ball);
		static_resource.animate_for_ball_break.Copy_cuts(&res->animate_for_ball_break);
		static_resource.animate_for_ball_break.Copy_stat(&res->animate_for_ball_break);

		static_resource.hitbox_ball.Copy_shape(&res->hitbox_ball);
		static_resource.hitbox_ball.Set_position(&res->hitbox_ball, &res->hitbox_ball);
	}

private:

	bool is_alive = true;

	static static_resource_ball static_resource;
};

