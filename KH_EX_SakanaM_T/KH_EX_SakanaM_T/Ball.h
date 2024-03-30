
#pragma once

#include "struct_static.h"

#include "Camera.h"
#include "Object.h"

#include "AreaManager.h"
//#include "Boom.h"
#include "Animate.h"

#include "Ring.h"

#include "World.h"

class Ball:
	public Object
{	public:
	Ball(World* world, Camera* camera, int x, int y) : Object(world, x, y), main_camera(camera)
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
				main_world->Hurt_area_add(Explode());
			}
			return true;
		}
		else
		{
			break_animate.Update();
			if (!break_animate.is_playing)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	void del(){}

	AreaManager*
	Explode()
	{
		int r = 20;

		AreaManager* a = new AreaManager(&main_world->hurt_area);
		a->Resize_shape(r * 2 + 1, r * 2 + 1);
		a->Clear();
		a->Fill_circle(r, r, r, 2000, true);
		a->Set_position(Position::Get_x() - r, Position::Get_y() - r);

		a->Set_timer(10, true, false);

		return a;
	}

	void
	Draw()
	{
		if (is_alive)
		{
			main_camera->Rending(move__animate.Get_renderer());
		}
		else
		{
			main_camera->Rending(break_animate.Get_renderer());
		}
	}

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

	Camera* main_camera = nullptr;

	bool is_alive = true;

	Animate move__animate;
	Animate break_animate;

	static static_resource_ball static_resource;
};

