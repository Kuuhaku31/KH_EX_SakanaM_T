
#pragma once

#include "struct_static.h"

#include "Camera.h"
#include "Map.h"
//#include "Boom.h"
#include "Ring.h"
#include "AreaManager.h"

class World
{	public:
	World() {}

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

	/*void 
	Update_booms()
	{
		Ring<Boom>* lst_boom = nullptr;
		Ring<Boom>* now_boom = booms.Get_next();
		while (now_boom != &booms)
		{
			lst_boom = now_boom;
			now_boom = now_boom->Get_next();
			if (!lst_boom->Get_data()->Update())
			{
				lst_boom->Out_and_delete_this();
			}
		}
	}*/

	void
	Hurt_area_add(AreaManager* a)
	{
		hurt_areas.Add_new_node(a);
	}

	void
	Coll_area_add(AreaManager* a)
	{
		coll_areas.Add_new_node(a);
	}

	void
	Update_hurt_area()
	{
		hurt_areas.Run_all_but_this_to_update();
	}

	void
	Update_coll_area()
	{
		coll_areas.Run_all_but_this_to_update();
	}


	/*void
	Add_new_boom(Boom* b)
	{
		booms.Add_new_node(b);
	}*/

	void
	Add_new_hitbox(Hitbox* h)
	{
		hitboxes.Add_new_node(h);
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

	Ring<Hitbox> hitboxes;

	Ring<AreaManager> hurt_areas;
	Ring<AreaManager> coll_areas;

	static static_resource_world static_resource;
};
