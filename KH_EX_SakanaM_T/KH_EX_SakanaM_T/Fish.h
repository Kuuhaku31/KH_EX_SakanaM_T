
#pragma once

#include "Character.h"

#include "Ball.h"

class Fish : public Character
{	public:

	Ball* Fire_water_ball() { return new Ball(main_world, Object::pos_x, Object::pos_y); }

private:

};
