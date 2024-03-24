
#pragma once

#include <random>

#include "Character.h"

class Crab : public Character
{	public:
	Crab(World* world) : Character(world) 
	{
		animate_skin_L.Copy(&crab_animate_skin_R);
		animate_skin_L.Set_position(static_cast<Object*>(this));
		animate_skin_R.Copy(&crab_animate_skin_L);
		animate_skin_R.Set_position(static_cast<Object*>(this));

		main_hitbox.Copy(&crab_hitbox);
		main_hitbox.Set_position(static_cast<Object*>(this));

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
		Collision::Update(static_cast<Object*>(this), this, nullptr, &main_world->coll_area);
		Movement::Update(static_cast<Object*>(this), main_world->main_map.Is_in_area(static_cast<Object*>(this)));
		Character::Update();
	}

	void
	See(Position* pos)
	{
		if (pos)
		{
			int this_x = Position::Get_x();
			int this_y = Position::Get_y();

			int pos_x = pos->Get_x();
			int pos_y = pos->Get_y();

			float dx = pos_x - this_x;
			float dy = pos_y - this_y;
			int t = sqrt(dx * dx + dy * dy);
			if (10000 < t)
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
			if (1)
			{
				Movement::Force(dx * 50, dy * 50);
			}
		}
	}

	Crab* 
	Bron()
	{
		std::random_device rd;  // 用于获取种子数据
		std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数
		std::uniform_int_distribution<> distr(1, 10); // 定义分布规则

		btime += distr(gen); // 生成在min和max之间的随机整数

		if(btime > 1000)
		{
			btime = 0;
			return new Crab(main_world);
		}
		else
		{
			return nullptr;
		}
	}

	static Animate crab_animate_skin_R;
	static Animate crab_animate_skin_L;

	static Hitbox crab_hitbox;

private:

	int btime = 0;
};
