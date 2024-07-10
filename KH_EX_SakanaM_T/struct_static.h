
#pragma once

#include "Animate.h"
#include "Hitbox.h"

struct static_resource_UI
{
	IMAGE char_size0_num[10];
	Renderer renderer_for_mouse;
};

struct static_resource_world
{
	Renderer renderer_for_main_A;
	Renderer renderer_for_main_B;
	Area area_for_main;

	Renderer renderer_for_wall_A;
	Renderer renderer_for_wall_B;
	Area area_for_wall;

	Renderer renderer_for_coll;
	Area area_for_coll;

	Renderer renderer_for_hurt;
	Area area_for_hurt;
};

struct static_resource_crab
{
	Animate animate_for_crab_R;
	Animate animate_for_crab_L;
	Animate animate_for_crab_dead_R;
	Animate animate_for_crab_dead_L;

	Hitbox hitbox_crab;
};

struct static_resource_fish
{
	Animate animate_for_fish_R;
	Animate animate_for_fish_L;
	Animate animate_for_fish_dead_R;
	Animate animate_for_fish_dead_L;

	Hitbox hitbox_fish;
};

struct static_resource_ball
{
	Animate animate_for_ball;
	Animate animate_for_ball_break;

	Hitbox hitbox_ball;
};