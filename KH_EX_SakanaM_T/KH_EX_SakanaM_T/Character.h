
#pragma once

#include "Object.h"

#include "World.h"

#include "AI.h"
#include "Collision.h"
#include "Bar.h"
#include "Animate.h"
#include "Hitbox.h"

#include "Ball.h"

class Character
	: public Object
	, public Collision 
{	public:
	Character
	(
		  World* world
	)
		: Object(&world->main_map)
		, Collision(static_cast<Object*>(this), &world->wall_map, &world->coll_area)

		, main_world(world)

		, main_hitbox(world, static_cast<Object*>(this))

		, bar(&MAX_HP, &HP, static_cast<Object*>(this))
		, animate_skin_R(static_cast<Object*>(this))
		, animate_skin_L(static_cast<Object*>(this))

		//, ai(this)
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
		is_alive = false;
	}

	Ball* Fire() { return new Ball(main_world, Object::pos_x, Object::pos_y); }

	bool
	Update()
	{
		bool b = Collision::Update();
		//ai.Update(b);
		Object::Update();

		HP -= main_world->hurt_area.Is_in_area(Object::pos_x, Object::pos_y);

		if (HP < 0) { HP = 0; }
		if (HP >= 0 && HP < MAX_HP) { HP += 1000; }
		if (HP > MAX_HP) { HP = MAX_HP; }

		bar.Update();
		animate_skin_R.Update();
		animate_skin_L.Update();

		return is_alive;
	}

	Renderer*
	Get_skin_renderer()
	{
		if (facing_right) { return animate_skin_R.Get_renderer(); }
		else { return animate_skin_L.Get_renderer(); }
	}

	Bar bar;
	Animate animate_skin_R;
	Animate animate_skin_L;

	Hitbox main_hitbox;

protected:
	//AI ai;

	World* main_world;

	bool is_alive = true;
	int MAX_HP = 1;
	int HP = 1;

	bool facing_right = true;
};
