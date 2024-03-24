
#pragma once

#include "World.h"

#include "Position.h"
#include "Movement.h"
#include "Collision.h"
#include "Hitbox.h"


class Object 
	: public Position
	, public Movement
	, public Collision
	, public Hitbox
{	public:
	Object(World* main_world, int x = 0, int y = 0)
		: Position(x, y)
		, Movement()
		, Collision()
		, Hitbox(this)
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

protected:

	World* main_world;
};				  
