
#pragma once

#include "Scene.h"

#include "Fish.h"
#include "Crab.h"
#include "Mouse.h"
#include "Ball.h"
#include "World.h"
#include "Slideboard.h"

class GameScene 
	: public Scene
{	public:
	GameScene(Library* library, Input* input, Camera* camera, UI* ui)
		: Scene(library, input, camera, ui)
		, main_world(1600, 1280)
		, camera_man(&main_world.main_map)
		, frame_board(ui)
		, sakana_wp_x(ui)
		, sakana_wp_y(ui)
	{
		Slideboard::Init_nums(library->char_size0_num);
		Crab::crab_animate_skin_R.Copy(&library->animate_for_ikacyann);
		Crab::crab_animate_skin_R.Set(60, 1, 1);
		Crab::crab_animate_skin_L.Copy(&library->animate_for_ikacyann);
		Crab::crab_animate_skin_L.Set(60, 1, 1);
		Crab::crab_hitbox.Copy(&library->crab_hitbox);
		Crab::crab_hitbox.main_world = &main_world;

		init_area();
		init_character();

		camera->Set_position(&camera_man);
		camera_man.Set_obj_m(100.0);
		camera_man.Set_drag(friction, friction_m, restitution, restitution_m);

		mouse = new Mouse(&library->_skin_target);
		ui_mouse = new Target(&library->_skin_target);

		sakana_wp_x.Move_to(15, 50);
		sakana_wp_x.Set_bits(4);
		sakana_wp_y.Move_to(15, 70);
		sakana_wp_y.Set_bits(4);

		frame_board.Move_to(15, 20);
		frame_board.Set_bits(3);
	}

	~GameScene()
	{
		delete sakana;
		delete mouse;
		delete ui_mouse;

		for (int i = 0; i < ball_num; i++)
		{ delete balls[i]; }

		for (int i = 0; i < crab_count; i++)
		{
			delete crabs[i];
		}
	}

	bool Update();

private:

	unsigned long start_time = 0;
	unsigned long end___time = 0;
	unsigned long delta_time = 0;

	Slideboard frame_board;
	Slideboard sakana_wp_x;
	Slideboard sakana_wp_y;

	World main_world;

	Crab* crabs[100] = { nullptr };
	int crab_count = 0;

	Fish* sakana = nullptr;

	Object camera_man;

	Mouse* mouse = nullptr;
	Target* ui_mouse = nullptr;

	Ball* balls[100] = { nullptr };
	int ball_num = 0;

	bool space = false;
	bool R = false;

	const int MAINWORLDWIDE = 1600;
	const int MAINWORLDHIGH = 1280;
	const int MAINWORLDLONG = MAINWORLDWIDE * MAINWORLDHIGH;

	const int spawn_point_1_x = 250;
	const int spawn_point_1_y = 100;
	const int spawn_point_2_x = 400;
	const int spawn_point_2_y = 100;

	const float friction = 50.0;
	const float friction_m = 0.1;
	const float restitution = 0.1;
	const float restitution_m = 0.1;

	void init_area();
	void init_character();
	void update_screen();
};
