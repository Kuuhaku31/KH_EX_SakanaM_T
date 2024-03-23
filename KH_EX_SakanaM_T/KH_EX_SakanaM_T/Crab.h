
#pragma once

#include "Character.h"

class Crab : public Character
{	public:
	Crab(World* world) :Character(world) {};

	static inline void
	Init_skin_R(Renderer* ren, int n)
	{
		skin_R = new IMAGE[n];
		for (int i = 0; i < n; i++)
		{
			//skin_R[i]=
		}
	}

	static inline void
	Init_skin_L(Renderer* ren, int n)
	{

	}

	static inline void
	Delete_skin()
	{
		delete[] skin_R;
		delete[] skin_L;
	}

	void
	See(Position* pos)
	{
		if (pos)
		{
			int this_x = Object::Get_x();
			int this_y = Object::Get_y();

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
				Force(dx * 30, dy * 30);
			}
		}
	}

private:

	static IMAGE* skin_R;
	static IMAGE* skin_L;

};
