
#pragma once

#include "Character.h"

#include "Ball.h"

class Fish : public Character
{	public:
	Fish(World* world) :Character(world) {}

	Ball* Fire() { return new Ball(main_world, pos_x, pos_y); }

	void 
	Update()
	{
		Collision::Update(this, this, &main_world->wall_map, &main_world->coll_area);
		Movement::Update(this, main_world->main_map.Is_in_area(pos_x, pos_y));
		Character::Update();
	}

private:

};
