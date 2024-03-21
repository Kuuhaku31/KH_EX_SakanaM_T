
#pragma once

#include "Scene.h"

#include "Character.h"
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
		init_area();
		init_character();

		camera->Set_position(&camera_man);
		camera_man.Set_obj_m(100.0);
		camera_man.Set_drag(friction, friction_m, restitution, restitution_m);

		mouse = new Mouse(&library->_skin_target);
		ui_mouse = new Target(&library->_skin_target);

		Slideboard::Init_nums(library->char_size0_num);

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
		delete ikacyann;
		delete mouse;
		delete ui_mouse;

		for (int i = 0; i < ball_num; i++)
		{ delete balls[i]; }
	}

	bool Update();

	
	void
	Exit()
	{
		delete sakana;
		delete ikacyann;
		delete mouse;

		for (int i = 0; i < ball_num; i++)
		{ delete balls[i]; }
	}

private:

	unsigned long start_time = 0;
	unsigned long end___time = 0;
	unsigned long delta_time = 0;

	Slideboard frame_board;
	Slideboard sakana_wp_x;
	Slideboard sakana_wp_y;

	World main_world;

	Character* ikacyann = nullptr;
	Character* sakana = nullptr;

	Object camera_man;

	Mouse* mouse = nullptr;
	Target* ui_mouse = nullptr;

	Ball* balls[100] = { nullptr };
	int ball_num = 0;

	bool space = false;

	const int MAINWORLDWIDE = 1600;
	const int MAINWORLDHIGH = 1280;
	const int MAINWORLDLONG = MAINWORLDWIDE * MAINWORLDHIGH;

	const int spawn_point_1_x = 250;
	const int spawn_point_1_y = 100;
	const int spawn_point_2_x = 400;
	const int spawn_point_2_y = 100;

	const double friction = 50.0;
	const double friction_m = 0.1;
	const double restitution = 0.1;
	const double restitution_m = 0.1;

	void init_area();
	void init_character();
	void update_screen();
};
