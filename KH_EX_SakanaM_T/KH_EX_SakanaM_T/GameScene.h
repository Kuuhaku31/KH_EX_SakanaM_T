
#pragma once

#include "Scene.h"

#include "Character.h"
#include "Mouse.h"
#include "Ball.h"
#include "World.h"

class GameScene 
	: public Scene
{	public:
	GameScene(Library* library, Input* input, Camera* camera, UI* ui)
		: Scene(library, input, camera, ui)
		, camera_man(&main_world.main_map)
	{
		init_area();
		init_character();

		camera->Set_position(&camera_man);
		camera_man.Set_obj_m(100.0);
		camera_man.Set_drag(friction, friction_m, restitution, restitution_m);

		mouse = new Mouse(&library->_skin_target);
		ui_mouse = new Target(&library->_skin_target);

		r[0].Move_to(35, 10);
		r[1].Move_to(25, 10);
		r[2].Move_to(15, 10);

		sakana_wp_x[0].Move_to(55, 50);
		sakana_wp_x[1].Move_to(45, 50);
		sakana_wp_x[2].Move_to(35, 50);
		sakana_wp_x[3].Move_to(25, 50);
		sakana_wp_x[4].Move_to(15, 50);

		sakana_wp_y[0].Move_to(55, 70);
		sakana_wp_y[1].Move_to(45, 70);
		sakana_wp_y[2].Move_to(35, 70);
		sakana_wp_y[3].Move_to(25, 70);
		sakana_wp_y[4].Move_to(15, 70);
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

	DWORD start_time = 0;
	DWORD end___time = 0;
	DWORD delta_time = 0;
	Renderer r[3];

	Renderer sakana_wp_x[5];
	Renderer sakana_wp_y[5];

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

	inline void
	init_area()
	{
		main_world.main_map.Resize_shape(MAINWORLDWIDE, MAINWORLDHIGH);
		main_world.main_map.Clear(10000);
		main_world.wall_map.Write(GetImageBuffer(&library->_area_wall_01), MAINWORLDWIDE, MAINWORLDHIGH);
		main_world.coll_area.Resize_shape(MAINWORLDWIDE, MAINWORLDHIGH);
		main_world.coll_area.Clear();
		main_world.hurt_area.Resize_shape(MAINWORLDWIDE, MAINWORLDHIGH);
		main_world.hurt_area.Clear();

		main_world.main_map.INIT_skin(&library->_skin_main);
		main_world.wall_map.INIT_skin(&library->_skin_wall_01);
		main_world.wall_map.INIT_skin(&library->_skin_wall_02, 0, 0, 2);
		main_world.fire_map.INIT_skin();
	}

	inline void
	init_character()
	{
		sakana = new Character(&main_world);
		sakana->Set_obj_m(10.0);
		
		sakana->Object::Move_to(spawn_point_2_x, spawn_point_2_y);
		sakana->Object::Set_drag(friction, friction_m, restitution, restitution_m);
		sakana->Collision::Set(24, 18);
		sakana->Set_MAX_HP(200000);
		sakana->Heal_full();
		//sakana->Collision::Move_to(0, 4);
		sakana->bar.ren_bar.Set_position(-25, -15);
		sakana->animate_skin_R.Set_cuts(library->animate_skin_for_sakana_right, library->num_of_animate_skin_for_sakana);
		sakana->animate_skin_R.Set(30, true, true);
		sakana->animate_skin_L.Set_cuts(library->animate_skin_for_sakana_left, library->num_of_animate_skin_for_sakana);
		sakana->animate_skin_L.Set(30, true, true);
		sakana->main_hitbox.Write(GetImageBuffer(&library->_hitbox_size16), library->_hitbox_size16_wigh, library->_hitbox_size16_high);
		sakana->main_hitbox.Align();

		camera->Set_position(static_cast<Object*>(sakana));

		ikacyann = new Character(&main_world);
		ikacyann->Set_obj_m(200.0);

		ikacyann->Object::Move_to(spawn_point_1_x, spawn_point_1_y);
		ikacyann->Object::Set_drag(friction, friction_m, restitution, restitution_m);
		ikacyann->Collision::Set(24, 18);
		ikacyann->Set_MAX_HP(200000);
		ikacyann->Heal_full();
		//ikacyann->Collision::Move_to(0, 8);
		ikacyann->bar.ren_bar.Set_position(-25, -30);
		ikacyann->animate_skin_R.Set_cuts(library->animate_skin_for_ikacyann, library->num_of_animate_skin_for_ikacyann);
		ikacyann->animate_skin_R.Set(60, true, true);
		ikacyann->main_hitbox.Write(GetImageBuffer(&library->_hitbox_size16), library->_hitbox_size16_wigh, library->_hitbox_size16_high);
		ikacyann->main_hitbox.Align();
	}

	inline void
	update_screen()
	{
		camera->Clear();
			 
		camera->Rending(main_world.main_map.Get_ren(1));
			  
		camera->Rending(main_world.fire_map.Get_ren(1));
		camera->Rending(main_world.wall_map.Get_ren(1));

		camera->Rending(ikacyann->Get_skin_renderer());
		camera->Rending(sakana->Get_skin_renderer());
			  
		camera->Rending(main_world.wall_map.Get_ren(2));

		camera->Rending_A(&main_world.hurt_area);
		camera->Rending_A(&main_world.coll_area);
			
		for (int i = 0; i < ball_num; i++)
		{ camera->Rending(balls[i]->Get_renderer()); }


		camera->Rending(&ikacyann->bar.ren_bar);
		camera->Rending(&sakana->bar.ren_bar);

		camera->Rending(&mouse->ren_target);

		camera->Photographed();

		ui->Rending(&ui_mouse->ren_target);

		
		end___time = clock();
		delta_time = end___time - start_time;
		start_time = clock();

		delta_time = 1000 / delta_time;

		int n[3];
		n[0] = delta_time % 10;
		n[1] = delta_time / 10 % 10;
		n[2] = delta_time / 100;

		for (int i = 0; i < 3; i++)
		{
			r[i].Reset_skin(get_num(n[i]));
			ui->Rending(&r[i]);
		}

		int sx = sakana->Object::Get_x();
		int ssx[5];
		ssx[0] = sx % 10;
		ssx[1] = sx / 10 % 10;
		ssx[2] = sx / 100 % 10;
		ssx[3] = sx / 1000 % 10;
		ssx[4] = sx / 10000;

		for (int i = 0; i < 5; i++)
		{
			sakana_wp_x[i].Reset_skin(get_num(ssx[i]));
			ui->Rending(&sakana_wp_x[i]);
		}

		int sy = sakana->Object::Get_y();
		int ssy[5];
		ssy[0] = sy % 10;
		ssy[1] = sy / 10 % 10;
		ssy[2] = sy / 100 % 10;
		ssy[3] = sy / 1000 % 10;
		ssy[4] = sy / 10000;

		for (int i = 0; i < 5; i++)
		{
			sakana_wp_y[i].Reset_skin(get_num(ssy[i]));
			ui->Rending(&sakana_wp_y[i]);
		}
	}

	inline IMAGE* 
	get_num(int n)
	{
		IMAGE* img = nullptr;
		switch (n)
		{
		case 0: img = &library->char_size0_num_0; break;
		case 1: img = &library->char_size0_num_1; break;
		case 2: img = &library->char_size0_num_2; break;
		case 3: img = &library->char_size0_num_3; break;
		case 4: img = &library->char_size0_num_4; break;
		case 5: img = &library->char_size0_num_5; break;
		case 6: img = &library->char_size0_num_6; break;
		case 7: img = &library->char_size0_num_7; break;
		case 8: img = &library->char_size0_num_8; break;
		case 9: img = &library->char_size0_num_9; break;
		default: break;
		}
		return img;
	}
};
