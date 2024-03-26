
#pragma once

#include "Scene.h"

#include "Fish.h"
#include "Crab.h"
#include "Ball.h"
#include "World.h"
#include "Slideboard.h"

class GameScene 
	: public Scene
{	public:
	GameScene(Library* library, Input* input, Camera* camera)
		: Scene(library, input, camera)
		, main_world(camera)
		, camera_man(&main_world)
		, frame_board(camera)
		, sakana_wp_x(camera)
		, sakana_wp_y(camera)
	{
		Slideboard::Init_nums(library->ui.char_size0_num);
		World::Load_static_resource(&library->world);
		Fish::Load_static_resource(&library->fish);
		Crab::Load_static_resource(&library->crab);
		Ball::Load_static_resource(&library->ball);

		main_world.Init_world();

		sakana = new Fish(&main_world, camera);
		sakana->Object::Position::Move_to(spawn_point_2_x, spawn_point_2_y);

		camera->Set_position(&camera_man);
		camera_man.Set_mov_m(100.0);
		camera_man.Set_drag(friction, friction_m, restitution, restitution_m);

		mouse.Copy_shape(&library->ui.renderer_for_mouse);

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

		for (int i = 0; i < ball_num; i++)
		{ delete balls[i]; }

		for (int i = 0; i < crab_count; i++)
		{
			delete crabs[i];
		}
	}

	bool 
	Update()
	{
		input->GetInput();

		if (input->enter) { return false; }

		float x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
		if (input->key_W) { y1--; }
		if (input->key_S) { y1++; }
		if (input->key_A) { x1--; sakana->Face_to_L(); }
		if (input->key_D) { x1++; sakana->Face_to_R(); }

		if (input->key_I) { y2--; }
		if (input->key_K) { y2++; }
		if (input->key_J) { x2--; }
		if (input->key_L) { x2++; }

		if (input->arr_U) { y3--; }
		if (input->arr_D) { y3++; }
		if (input->arr_L) { x3--; }
		if (input->arr_R) { x3++; }

		if (input->key_F)
		{
			camera->Tweaks_sight(16, 9);
		}

		if (input->key_E)
		{
			camera->Tweaks_sight(-16, -9);
		}

		float FORCE_01 = 950;
		float FORCE_02 = 1000;

		float V_01 = 100;
		float V_02 = 10;

		if (Matrix::to_unit(&x1, &y1)) { sakana->Movement::Force(x1 * FORCE_01, y1 * FORCE_01); }
		if (Matrix::to_unit(&x3, &y3)) { camera->Move(x3 * 10, y3 * 10); }

		int mouse_w_x = input->mouse_X;
		int mouse_w_y = input->mouse_Y;
		camera->Get_mouse_point(&mouse_w_x, &mouse_w_y);
		mouse.Move_to(mouse_w_x - 10, mouse_w_y - 10);

		int sakana_w_x = sakana->Position::Get_x();
		int sakana_w_y = sakana->Position::Get_y();

		if (ball_num < 100 && space && (input->space || input->mouse_L))
		{
			space = false;
			balls[ball_num] = sakana->Fire();

			float x = mouse_w_x - sakana_w_x;
			float y = mouse_w_y - sakana_w_y;

			if (Matrix::to_unit(&x, &y))
			{
				balls[ball_num]->Reset_mov_v(x * V_01, y * V_01);
				balls[ball_num]->Position::Move(x * V_02, y * V_02);
			}
			else
			{
				balls[ball_num]->Reset_mov_v(0, -V_01);
				balls[ball_num]->Position::Move(0, -V_02); balls[ball_num]->Position::Move(x * V_02, y * V_02);
			}

			ball_num++;
		}
		if (input->space)
		{
			space = true;
		}

		if (100 > crab_count && R && input->key_R)
		{
			R = false;

			crabs[crab_count] = new Crab(&main_world, camera);
			crabs[crab_count]->Object::Position::Move_to(static_cast<Object*>(sakana));

			crab_count++;
		}
		if (!input->key_R)
		{
			R = true;
		}

		main_world.Update_booms();

		sakana->Add_coll();
		for (int i = 0; i < crab_count; i++)
		{
			crabs[i]->Add_coll();
		}

		sakana->Update();
		for (int i = 0; i < crab_count; i++)
		{
			crabs[i]->Update(static_cast<Object*>(sakana));

			Crab* c = crabs[i]->Bron();
			if (10000 > crab_count && c)
			{
				crabs[crab_count] = new Crab(&main_world, camera);
				crabs[crab_count]->Object::Position::Move_to(static_cast<Object*>(crabs[i]));
				crabs[crab_count]->Object::Position::Move(-10, 10);
				crabs[crab_count]->Add_coll();
				crab_count++;
			}
			else
			{
				delete c;
			}

			if (0 >= crabs[i]->GetHP())
			{
				crabs[i]->Del_coll();
				delete crabs[i];
				crabs[i] = crabs[crab_count - 1];
				crabs[crab_count - 1] = nullptr;
				crab_count--;
			}
		}

		for (int i = 0; i < ball_num; i++)
		{
			if (!balls[i]->Update())
			{
				ball_num--;
				delete balls[i];
				balls[i] = balls[ball_num];
				balls[ball_num] = nullptr;
			}
		}

		camera_man.Update();
		camera_man.Position::Move_to(sakana_w_x, sakana_w_y);

		//
		//
		camera->Clear();

		main_world.main_map.Draw_skin_01();
		main_world.wall_map.Draw_skin_01();

		for (int i = 0; i < crab_count; i++)
		{
			crabs[i]->Draw_skin();
		}

		sakana->Draw_skin();

		for (int i = 0; i < ball_num; i++)
		{
			balls[i]->Draw();
		}

		main_world.wall_map.Draw_skin_02();
		main_world.fire_map.Draw_skin_01();

		camera->Rending_A(&main_world.hurt_area);
		//camera->Rending_AC(&main_world.coll_area);

		for (int i = 0; i < crab_count; i++)
		{
			//crabs[i]->Draw_bar();
		}

		sakana->Draw_bar();
		camera->Rending(&mouse);

		camera->Photographed();

		//
		//
		sakana_wp_x.Set_num(sakana->Object::Position::Get_x());
		sakana_wp_x.Print();

		sakana_wp_y.Set_num(sakana->Object::Position::Get_y());
		sakana_wp_y.Print();

		end___time = clock();
		delta_time = end___time - start_time;
		start_time = clock();
		frame_board.Set_num(1000 / delta_time);
		frame_board.Print();
		//
		//
		//

		sakana->Del_coll();
		for (int i = 0; i < crab_count; i++)
		{
			crabs[i]->Del_coll();
		}

		putpixel(0, 0, RED);
		putpixel(1, 1, RED);
		putpixel(2, 2, RED);

		return true;
	}


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

	Renderer mouse;

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
};
