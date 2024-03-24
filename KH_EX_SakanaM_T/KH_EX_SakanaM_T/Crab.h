
#pragma once

#include "Character.h"

class Crab : public Character
{	public:
	Crab(World* world) : Character(world) 
	{
		animate_skin_L.Copy(&crab_animate_skin_R);
		animate_skin_L.Set_position(this);
		animate_skin_R.Copy(&crab_animate_skin_L);
		animate_skin_R.Set_position(this);

		main_hitbox.Copy(&crab_hitbox);
		main_hitbox.Set_position(this);

		Collision::Set(24, 18);
		Set_MAX_HP(200000);
		Heal_full();

		bar.ren_bar.Set_position(-25, -30);

		Set_mov_m(20.0);

		Set_drag(50, 0.1, 0.1, 0.1);
	};

	void
	Update(Position* pos)
	{
		See(pos);
		Character::Update();
	}

	void
	See(Position* pos)
	{
		if (pos)
		{
			int this_x = pos_x;
			int this_y = pos_y;

			int pos_x = pos->Get_x();
			int pos_y = pos->Get_y();

			float dx = pos_x - this_x;
			float dy = pos_y - this_y;
			int t = sqrt(dx * dx + dy * dy);
			if (300 < t)
			{
				return;
			}
			else
			{
				t /= 5;
			}

			Matrix::to_unit(&dx, &dy);
			dx *= 5.0;
			dy *= 5.0;

			int i = 0;
			bool b = true;
			for (float x = this_x, y = this_y; i < t; x += dx, y += dy, i++)
			{
				if (main_world->wall_map.Is_in_area(x, y))
				{
					b = false;
					break;
				}
			}
			if (b)
			{
				Movement::Force(dx * 50, dy * 50);
			}
		}
	}

	static Animate crab_animate_skin_R;
	static Animate crab_animate_skin_L;

	static Hitbox crab_hitbox;

private:

};
