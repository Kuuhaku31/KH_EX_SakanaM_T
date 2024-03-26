
#pragma once

#include "struct_static.h"

#include "Character.h"

#include "Ball.h"

class Fish : public Character
{	public:
	Fish(World* world, Camera* camera) : Character(world, camera)
	{
		animate_skin_R.Copy_cuts(&static_resource.animate_for_fish_R);
		animate_skin_R.Copy_stat(&static_resource.animate_for_fish_R);
		animate_skin_R.Set_position(static_cast<Object*>(this), &static_resource.animate_for_fish_R);
		animate_skin_L.Copy_cuts(&static_resource.animate_for_fish_L);
		animate_skin_L.Copy_stat(&static_resource.animate_for_fish_L);
		animate_skin_L.Set_position(static_cast<Object*>(this), &static_resource.animate_for_fish_L);

		Hitbox::Copy_shape(&static_resource.hitbox_fish);
		Hitbox::Set_position(static_cast<Object*>(this), &static_resource.hitbox_fish);

		Collision::Set(24, 18);
		Set_MAX_HP(200000);
		Heal_full();

		bar.ren_bar.Set_position(-25, -30);

		Set_mov_m(10.0);

		Set_drag(50, 0.1, 0.1, 0.1);
	}

	Ball* Fire() { return new Ball(main_world, main_camera, Object::Position::Get_x(), Object::Position::Get_y()); }

	void 
	Update()
	{
		Collision::Update(static_cast<Object*>(this), this, &main_world->wall_map, &main_world->coll_area);
		Movement::Update(static_cast<Object*>(this), main_world->main_map.Is_in_area(static_cast<Object*>(this)));
		Character::Update();
	}

	static void
	Load_static_resource(static_resource_fish* res)
	{
		static_resource.animate_for_fish_R.Copy_cuts(&res->animate_for_fish_R);
		static_resource.animate_for_fish_R.Copy_stat(&res->animate_for_fish_R);
		static_resource.animate_for_fish_L.Copy_cuts(&res->animate_for_fish_L);
		static_resource.animate_for_fish_L.Copy_stat(&res->animate_for_fish_L);
		static_resource.animate_for_fish_dead_R.Copy_cuts(&res->animate_for_fish_dead_R);
		static_resource.animate_for_fish_dead_R.Copy_stat(&res->animate_for_fish_dead_R);
		static_resource.animate_for_fish_dead_L.Copy_cuts(&res->animate_for_fish_dead_L);
		static_resource.animate_for_fish_dead_L.Copy_stat(&res->animate_for_fish_dead_L);
		static_resource.hitbox_fish.Copy_shape(&res->hitbox_fish);
		static_resource.hitbox_fish.Set_position(&res->hitbox_fish, &res->hitbox_fish);
	}

private:

	static static_resource_fish static_resource;

};
