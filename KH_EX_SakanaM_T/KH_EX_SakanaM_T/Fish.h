
#pragma once

#include "Character.h"

#include "Ball.h"

class Fish : public Character
{	public:
	Fish(World* world) :Character(world) {}

	Ball* Fire() { return new Ball(main_world, Object::Position::Get_x(), Object::Position::Get_y()); }

	void 
	Update()
	{
		Collision::Update(static_cast<Object*>(this), this, &main_world->wall_map, &main_world->coll_area);
		Movement::Update(static_cast<Object*>(this), main_world->main_map.Is_in_area(static_cast<Object*>(this)));
		Character::Update();
	}

private:

};
