
#pragma once

#include "World.h"

#include "Position.h"
#include "Movement.h"
#include "Collision.h"
#include "Hitbox.h"
#include "AreaManager.h"

class Object 
	: public Position
	, public Movement
	, public Collision
{	public:
	Object(World* main_world, int x = 0, int y = 0)
		: Position(x, y)
		, Movement()
		, Collision()
		, main_hit_box(this)
		, main_world(main_world)
	{}

	void
	Update()
	{
		Collision::Update(this, this, &main_world->wall_map, &main_world->coll_area);
		Movement::Update(this, main_world->main_map.Is_in_area(this));
	}

	void 
	Update_col()
	{
		Collision::Update(this, this, &main_world->wall_map, &main_world->coll_area);
	}

	void
	Update_mov()
	{
		Movement::Update(this, main_world->main_map.Is_in_area(this));
	}

	void
	Add_new_coll_area_manager_to_world()
	{
		AreaManager* a = new AreaManager(&main_world->coll_area);
		a->Copy_shape(&main_hit_box);
		a->Set_position(main_hit_box.Get_x(), main_hit_box.Get_y());
		a->Set_timer(1, true, false);
		main_world->Coll_area_add(a);
	}

protected:

	World* main_world;
	Area main_hit_box;
};				  
