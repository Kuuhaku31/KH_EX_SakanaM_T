
#pragma once

#include "World.h"
#include "Camera.h"

#include "Object.h"

#include "Bar.h"
#include "Animate.h"
#include "Ball.h"

class Character : public Object
{	public:
	Character(World* world,Camera*camera)
		: Object(world)
		, main_camera(camera)
		, bar(&MAX_HP, &HP, static_cast<Object*>(this))
		, animate_skin_R(static_cast<Object*>(this))
		, animate_skin_L(static_cast<Object*>(this))
	{}

	int GetHP() const { return HP; }

	void Set_MAX_HP(int h) { MAX_HP = h; }

	void Face_to_R() { facing_right = true; }
	void Face_to_L() { facing_right = false; }

	void Heal(int h) { HP += h; }
	void Hurt(int d) { HP -= d; }
	void Heal_full() { HP = MAX_HP; }

	void
	Dead()
	{
		HP = 0;
	}

	bool
	Update()
	{
		HP -= main_world->hurt_area.Is_in_area(static_cast<Object*>(this));

		if (HP < 0) { HP = 0; }
		//if (HP >= 0 && HP < MAX_HP) { HP += 1000; }
		if (HP > MAX_HP) { HP = MAX_HP; }

		bar.Update();
		animate_skin_R.Update();
		animate_skin_L.Update();

		return is_alive;
	}

	void
	Draw_skin()
	{
		if (facing_right)
		{
			main_camera->Rending(animate_skin_R.Get_renderer()); 
		}
		else
		{ 
			main_camera->Rending(animate_skin_L.Get_renderer()); 
		}
	}

	void
	Draw_bar()
	{
		main_camera->Rending(&bar.ren_bar);
	}

	void
	Add_coll()
	{
		Add_hit_box_to_area(&main_world->coll_area);
	}

	void
	Del_coll()
	{
		Delete_hitbox_from_area(&main_world->coll_area);
	}

protected:

	Camera* main_camera = nullptr;
	
	bool is_alive = true;
	int MAX_HP = 1;
	int HP = 1;

	bool facing_right = true;

	Bar bar;
	Animate animate_skin_R;
	Animate animate_skin_L;
};
