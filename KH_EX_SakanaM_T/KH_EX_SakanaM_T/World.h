
#pragma once

#include "struct_static.h"

#include "Camera.h"
#include "Map.h"
#include "Boom.h"

class World
{	public:
	World(Camera* camera)
		: main_map(camera)
		, wall_map(camera)
		, fire_map(camera)
	{}

	void
	Init_world()
	{
		main_map.Copy_shape(&static_resource.area_for_main);
		main_map.ren_skin_01.Copy_shape(&static_resource.renderer_for_main_A);
		main_map.ren_skin_02.Copy_shape(&static_resource.renderer_for_main_B);

		wall_map.Copy_shape(&static_resource.area_for_wall);
		wall_map.ren_skin_01.Copy_shape(&static_resource.renderer_for_wall_A);
		wall_map.ren_skin_02.Copy_shape(&static_resource.renderer_for_wall_B);

		coll_area.Copy_shape(&static_resource.area_for_coll);
		//coll_area.ren_skin_01.Copy_shape(&static_resource.renderer_for_wall_A);

		hurt_area.Copy_shape(&static_resource.area_for_hurt);
	}

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

	static void
	Load_static_resource(static_resource_world* res)
	{
		static_resource.renderer_for_main_A.Copy_shape(&res->renderer_for_main_A);
		static_resource.renderer_for_main_B.Copy_shape(&res->renderer_for_main_B);
		static_resource.area_for_main.Copy_shape(&res->area_for_main);

		static_resource.renderer_for_wall_A.Copy_shape(&res->renderer_for_wall_A);
		static_resource.renderer_for_wall_B.Copy_shape(&res->renderer_for_wall_B);
		static_resource.area_for_wall.Copy_shape(&res->area_for_wall);

		static_resource.renderer_for_coll.Copy_shape(&res->renderer_for_coll);
		static_resource.area_for_coll.Copy_shape(&res->area_for_coll);

		static_resource.renderer_for_hurt.Copy_shape(&res->renderer_for_hurt);
		static_resource.area_for_hurt.Copy_shape(&res->area_for_hurt);
	}

private:

	Boom* booms = nullptr;

	static static_resource_world static_resource;
};
