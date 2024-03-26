
#pragma once

#include <random>

#include "struct_static.h"

#include "Character.h"

class Crab : public Character
{	public:
	Crab(World* world, Camera* camera) : Character(world, camera)
	{
		animate_skin_R.Copy_cuts(&static_resource.animate_for_crab_R);
		animate_skin_R.Copy_stat(&static_resource.animate_for_crab_R);
		animate_skin_R.Set_position(static_cast<Object*>(this), &static_resource.animate_for_crab_R);
		animate_skin_L.Copy_cuts(&static_resource.animate_for_crab_L);
		animate_skin_L.Copy_stat(&static_resource.animate_for_crab_L);
		animate_skin_L.Set_position(static_cast<Object*>(this), &static_resource.animate_for_crab_L);

		Hitbox::Copy_shape(&static_resource.hitbox_crab);
		Hitbox::Set_position(static_cast<Object*>(this), &static_resource.hitbox_crab);

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
		bool l = 1;
		l = Collision::Update(static_cast<Object*>(this), this, &main_world->wall_map, &main_world->coll_area);
		if (!l) { Dead(); return; }
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
			if (100 < t)
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

	Crab* 
	Bron()
	{
		std::random_device rd;  // 用于获取种子数据
		std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数
		std::uniform_int_distribution<> distr(1, 100); // 定义分布规则

		btime += distr(gen); // 生成在min和max之间的随机整数

		if(btime > 10000)
		{
			btime = 0;
			return new Crab(main_world, main_camera);
		}
		else
		{
			return nullptr;
		}
	}

	static void
	Load_static_resource(static_resource_crab* res)
	{
		static_resource.animate_for_crab_R.Copy_cuts(&res->animate_for_crab_R);
		static_resource.animate_for_crab_R.Copy_stat(&res->animate_for_crab_R);
		static_resource.animate_for_crab_L.Copy_cuts(&res->animate_for_crab_L);
		static_resource.animate_for_crab_L.Copy_stat(&res->animate_for_crab_L);
		static_resource.animate_for_crab_dead_R.Copy_cuts(&res->animate_for_crab_dead_R);
		static_resource.animate_for_crab_dead_R.Copy_stat(&res->animate_for_crab_dead_R);
		static_resource.animate_for_crab_dead_L.Copy_cuts(&res->animate_for_crab_dead_L);
		static_resource.animate_for_crab_dead_L.Copy_stat(&res->animate_for_crab_dead_L);
		static_resource.hitbox_crab.Copy_shape(&res->hitbox_crab);
		static_resource.hitbox_crab.Set_position(&res->hitbox_crab, &res->hitbox_crab);
	}

private:

	int btime = 0;

	static static_resource_crab static_resource;
};
