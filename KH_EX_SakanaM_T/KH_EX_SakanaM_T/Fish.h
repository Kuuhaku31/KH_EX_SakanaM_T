
#pragma once

#include "Character.h"

#include "Ball.h"

class Fish : public Character
{	public:
	Fish(World* world) :Character(world) {}

	Ball* Fire() { return new Ball(main_world, pos_x, pos_y); }

	

private:

};
