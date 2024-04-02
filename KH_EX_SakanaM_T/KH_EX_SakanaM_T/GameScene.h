
#pragma once

//#include "Scene.h"

#include "Fish.h"
#include "Crab.h"
#include "Ball.h"
#include "World.h"
#include "Slideboard.h"
#include "Shake.h"

#include "Ring.h"

#include "Library.h"
#include "Input.h"
#include "Camera.h"

extern Library main_library;
extern Input main_input;
extern Camera main_camera;

class GameScene 
{	public:
	GameScene() {}
	~GameScene()
	{
		delete sakana;
		delete camera_man;

		ball_ring.Delete_all_but_this();
		crab_ring.Delete_all_but_this();
	}

	void
	Init()
	{
		Slideboard::Init_nums(main_library.ui.char_size0_num);
		World::Load_static_resource(&main_library.world);
		Fish::Load_static_resource(&main_library.fish);
		Crab::Load_static_resource(&main_library.crab);
		Ball::Load_static_resource(&main_library.ball);

		main_world.Init_world();

		sakana = new Fish(&main_world, &shake_ring);
		sakana->Move_to(spawn_point_2_x, spawn_point_2_y);

		camera_man = new Object(&main_world);
		main_camera.Set_position(camera_man);
		camera_man->Set_mov_m(100.0);
		camera_man->Set_drag(friction, friction_m, restitution, restitution_m);

		mouse.Copy_shape(&main_library.ui.renderer_for_mouse);

		sakana_wp_x.Move_to(15, 50);
		sakana_wp_x.Set_bits(4);
		sakana_wp_y.Move_to(15, 70);
		sakana_wp_y.Set_bits(4);

		frame_board.Move_to(15, 20);
		frame_board.Set_bits(3);
	}

	bool 
	Update()
	{
		main_input.GetInput();

		if (main_input.enter) { return false; }

		float x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
		if (main_input.key_W) { y1--; }
		if (main_input.key_S) { y1++; }
		if (main_input.key_A) { x1--; sakana->Face_to_L(); }
		if (main_input.key_D) { x1++; sakana->Face_to_R(); }

		if (main_input.key_I) { y2--; }
		if (main_input.key_K) { y2++; }
		if (main_input.key_J) { x2--; }
		if (main_input.key_L) { x2++; }

		if (main_input.arr_U) { y3--; }
		if (main_input.arr_D) { y3++; }
		if (main_input.arr_L) { x3--; }
		if (main_input.arr_R) { x3++; }

		if (main_input.key_F)
		{
			main_camera.Tweaks_sight(16, 9);
		}

		if (main_input.key_E)
		{
			main_camera.Tweaks_sight(-16, -9);
		}

		float FORCE_01 = 950;
		float FORCE_02 = 1000;

		float V_01 = 100;
		float V_02 = 10;

		if (Matrix::to_unit(&x1, &y1)) { sakana->Force(x1 * FORCE_01, y1 * FORCE_01); }
		if (Matrix::to_unit(&x3, &y3)) { main_camera.Move(x3 * 10, y3 * 10); }
		
		int mouse_w_x = main_input.mouse_X;
		int mouse_w_y = main_input.mouse_Y;
		main_camera.Get_mouse_point(&mouse_w_x, &mouse_w_y);
		mouse.Move_to(mouse_w_x - 10, mouse_w_y - 10);

		int sakana_w_x = sakana->Get_x();
		int sakana_w_y = sakana->Get_y();

		if (space && (main_input.space || main_input.mouse_L))//================================================================00000000000000000
		{
			space = false;

			Ball* b = sakana->Fire();

			float x = mouse_w_x - sakana_w_x;
			float y = mouse_w_y - sakana_w_y;

			if (Matrix::to_unit(&x, &y))
			{
				b->Reset_mov_v(x * V_01, y * V_01);
				b->Move(x * V_02, y * V_02);
			}
			else
			{
				b->Reset_mov_v(0, -V_01);
				b->Move(0, -V_02);
			}

			ball_ring.Add_new_node(b);

			shake_ring.Add_new_node(new Shake(2, 5));
		}
		if (!main_input.space)
		{
			space = true;
		}

		if (R && main_input.key_R)
		{
			R = false;

			Crab* c = new Crab(&main_world, &crab_ring);
			c->Move_to(sakana);
			crab_ring.Add_new_node(c);
		}
		if (!main_input.key_R)
		{
			R = true;
		}


		sakana->Update();
		crab_ring.Run_all_but_this_to_update();
		ball_ring.Run_all_but_this_to_update();

		sakana->Add_new_coll_area_manager_to_world();
		crab_ring.Run_all_but_this_to_do(&Crab::Add_new_coll_area_manager_to_world);

		main_world.Update_hurt_area();
		main_world.Update_coll_area();

		camera_man->Update();
		camera_man->Move_to(sakana_w_x, sakana_w_y);

		shake_ring.Run_all_but_this_to_update();



		//
		//
		main_camera.Clear();

		main_world.main_map.Draw_skin_01();
		main_world.wall_map.Draw_skin_01();

		crab_ring.Run_all_but_this_to_do(&Crab::Draw_skin);

		sakana->Draw_skin();

		ball_ring.Run_all_but_this_to_do(&Ball::Draw);

		main_world.wall_map.Draw_skin_02();
		main_world.fire_map.Draw_skin_01();

		main_camera.Rending_AH(&main_world.hurt_area);
		main_camera.Rending_AC(&main_world.coll_area);


		sakana->Draw_bar();
		main_camera.Rending(&mouse);

		main_camera.Photographed();
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

		putpixel(0, 0, RED);
		putpixel(1, 1, RED);
		putpixel(2, 2, RED);
		//
		//


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

	Ring<Crab> crab_ring;

	Fish* sakana = nullptr;
	Object* camera_man = nullptr;

	Renderer mouse;

	Ring<Ball> ball_ring;

	Ring<Shake> shake_ring;

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
