
#include "GameScene.h"

GameScene::GameScene(Library* library, Input* input, Camera* camera)
	: Scene(library, input, camera)
	, main_world()
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

	mouse = new Mouse();
	mouse->ren_target.Copy_shape(&library->ui.renderer_for_mouse);
	mouse->ren_target.Align();
	ui_mouse = new Target();
	ui_mouse->ren_target.Copy_shape(&library->ui.renderer_for_mouse);
	ui_mouse->ren_target.Align();

	sakana_wp_x.Move_to(15, 50);
	sakana_wp_x.Set_bits(4);
	sakana_wp_y.Move_to(15, 70);
	sakana_wp_y.Set_bits(4);

	frame_board.Move_to(15, 20);
	frame_board.Set_bits(3);
}

bool
GameScene::Update()
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

	float FORCE_01 = 500;
	float FORCE_02 = 1000;

	float V_01 = 100;
	float V_02 = 10;

	if (Matrix::to_unit(&x1, &y1)) { sakana->Movement::Force(x1 * FORCE_01, y1 * FORCE_01); }
  //if (Matrix::to_unit(&x2, &y2)) { ikacyann->Force(x2 * FORCE_01, y2 * FORCE_01); }
	if (Matrix::to_unit(&x3, &y3)) { camera->Move(x3 * 10, y3 * 10); }

	int mouse_w_x = input->mouse_X;
	int mouse_w_y = input->mouse_Y;
	ui_mouse->Move_to(mouse_w_x, mouse_w_y);
	camera->Get_mouse_point(&mouse_w_x, &mouse_w_y);
	mouse->Move_to(mouse_w_x, mouse_w_y);

	int camera_man_w_x = camera_man.Position::Get_x();
	int camera_man_w_y = camera_man.Position::Get_y();

	int sakana_w_x = sakana->Object::Position::Get_x();
	int sakana_w_y = sakana->Object::Position::Get_y();

	float x0 = sakana_w_x - camera_man_w_x;
	float y0 = sakana_w_y - camera_man_w_y;

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
		}

		ball_num++;
	}
	if (!input->space)
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

	for (int i = 0; i < crab_count; i++)
	{
		Crab* c = crabs[i]->Bron();
		if (100 > crab_count && c)
		{
			crabs[crab_count] = new Crab(&main_world, camera);
			crabs[crab_count]->Object::Position::Move_to(static_cast<Object*>(crabs[i]));
			crabs[crab_count]->Object::Position::Move(0, 10);
			crab_count++;
		}
		else
		{
			delete c;
		}
	}

	sakana->Add_hit_box_to_area(&main_world.coll_area);

	for (int i = 0; i < crab_count; i++)
	{
		crabs[i]->Add_hit_box_to_area(&main_world.coll_area);
	}

	main_world.Update_booms();

	sakana->Update();

	for (int i = 0; i < crab_count; i++)
	{
		crabs[i]->Update(static_cast<Object*>(sakana));
	}

	camera_man.Update();

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

	camera_man.Position::Move_to(sakana_w_x, sakana_w_y);

	//
	//
	camera->Clear();

	camera->Rending(main_world.main_map.Get_ren(1));
	camera->Rending(main_world.wall_map.Get_ren(1));

	for (int i = 0; i < crab_count; i++)
	{
		crabs[i]->Draw_skin();
	}

	//camera->Rending(sakana->Get_skin_renderer());
	sakana->Draw_skin();

	camera->Rending_A(&main_world.hurt_area);
	camera->Rending_A(&main_world.coll_area);

	for (int i = 0; i < ball_num; i++)
	{
		balls[i]->Draw();
	}

	camera->Rending(main_world.wall_map.Get_ren(2));
	camera->Rending(main_world.fire_map.Get_ren(1));

	for (int i = 0; i < crab_count; i++) 
	{
		crabs[i]->Draw_bar();
	}
	sakana->Draw_bar();
	camera->Rending(&mouse->ren_target);

	camera->Photographed();

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

	sakana->Delete_hitbox_from_area(&main_world.coll_area);
	for (int i = 0; i < crab_count; i++)
	{
		crabs[i]->Delete_hitbox_from_area(&main_world.coll_area);
	}
	for (int i = 0; i < crab_count; i++)
	{
		if (0 >= crabs[i]->GetHP())
		{
			delete crabs[i];
			crabs[i] = crabs[crab_count - 1];
			crabs[crab_count - 1] = nullptr;
			crab_count--;
		}
	}

	return true;
}
