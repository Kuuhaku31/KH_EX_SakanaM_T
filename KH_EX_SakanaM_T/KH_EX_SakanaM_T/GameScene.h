
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
	GameScene(Library* library, Input* input, Camera* camera, UI* ui);
		

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

	Crab* crabs[10000] = { nullptr };
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

	inline void update_screen();
};
