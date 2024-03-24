
#include "GameScene.h"

GameScene::GameScene(Library* library, Input* input, Camera* camera, UI* ui)
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

	if (-20 <= camera->Get_dy() && input->arr_U) { y3--; }
	if (+20 >= camera->Get_dy() && input->arr_D) { y3++; }
	if (-20 <= camera->Get_dx() && input->arr_L) { x3--; }
	if (+20 >= camera->Get_dx() && input->arr_R) { x3++; }

	if (input->key_F)
	{
		int w = camera->Get_sight_wide();
		int h = camera->Get_sight_high();
		camera->Reset_sight(w + 16, h + 9);
	}

	if (input->key_E)
	{
		int w = camera->Get_sight_wide();
		int h = camera->Get_sight_high();
		camera->Reset_sight(w - 16, h - 9);
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

	int camera_man_w_x = camera_man.Get_x();
	int camera_man_w_y = camera_man.Get_y();

	int sakana_w_x = sakana->Get_x();
	int sakana_w_y = sakana->Get_y();

	float x0 = sakana_w_x - camera_man_w_x;
	float y0 = sakana_w_y - camera_man_w_y;

	if (ball_num < 100 && space && input->space)
	{
		space = false;
		balls[ball_num] = sakana->Fire();
		balls[ball_num]->renderer.Reset_skin(&library->_skin_ball);
		balls[ball_num]->renderer.Align();
		balls[ball_num]->break_animate.Set_cuts(library->animate_skin_for_ball_break, library->num_of_animate_skin_for_ball_break);
		balls[ball_num]->break_animate.Set(3, false, true);

		float x = mouse_w_x - sakana_w_x;
		float y = mouse_w_y - sakana_w_y;

		if (Matrix::to_unit(&x, &y))
		{
			balls[ball_num]->Reset_obj_v(x * V_01, y * V_01);
			balls[ball_num]->Move(x * V_02, y * V_02);
		}
		else
		{
			balls[ball_num]->Reset_obj_v(0, -V_01);
		}

		ball_num++;
	}
	if (!input->space)
	{
		space = true;
	}

	if (R && input->key_R)
	{
		R = false;

		crabs[crab_count] = new Crab(&main_world);
		crabs[crab_count]->Move_to(sakana);

		crab_count++;
	}
	if (!input->key_R)
	{
		R = true;
	}

	sakana->main_hitbox.Add_hit_box_to_area(&main_world.coll_area);

	for (int i = 0; i < crab_count; i++)
	{
		crabs[i]->main_hitbox.Add_hit_box_to_area(&main_world.coll_area);
	}

	main_world.Update_booms();

	sakana->Update();

	for (int i = 0; i < crab_count; i++)
	{
		crabs[i]->Update(sakana);
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

	update_screen();

	camera_man.Move_to(sakana_w_x, sakana_w_y);

	sakana->main_hitbox.Delete_hitbox_from_area(&main_world.coll_area);
	for (int i = 0; i < crab_count; i++)
	{
		crabs[i]->main_hitbox.Delete_hitbox_from_area(&main_world.coll_area);
	}

	return true;
}

void 
GameScene::init_area()
{
	main_world.main_map.Resize_shape(MAINWORLDWIDE, MAINWORLDHIGH);
	main_world.main_map.Clear(20000);
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

void 
GameScene::init_character()
{
	sakana = new Fish(&main_world);
	sakana->Set_mov_m(10.0);

	sakana->Move_to(spawn_point_2_x, spawn_point_2_y);
	sakana->Set_drag(friction, friction_m, restitution, restitution_m);
	sakana->Collision::Set(24, 18);
	sakana->Set_MAX_HP(200000);
	sakana->Heal_full();
	//sakana->Collision::Move_to(0, 4);
	sakana->bar.ren_bar.Set_position(-25, -15);
	sakana->animate_skin_R.Set_cuts(library->animate_skin_for_sakana_right, library->num_of_animate_skin_for_sakana);
	sakana->animate_skin_R.Set(30, true, true);
	sakana->animate_skin_L.Set_cuts(library->animate_skin_for_sakana_left, library->num_of_animate_skin_for_sakana);
	sakana->animate_skin_L.Set(30, true, true);
	sakana->main_hitbox.Copy(&library->crab_hitbox);
	sakana->main_hitbox.Set_position(sakana);
	//sakana->main_hitbox.Align();

	camera->Set_position(sakana);

	//ikacyann = new Crab(&main_world);
	//ikacyann->Object::Move_to(spawn_point_1_x, spawn_point_1_y);
}

void 
GameScene::update_screen()
{
	camera->Clear();

	camera->Rending(main_world.main_map.Get_ren(1));

	camera->Rending(main_world.fire_map.Get_ren(1));
	camera->Rending(main_world.wall_map.Get_ren(1));

	
	for (int i = 0; i < crab_count; i++)
	{
		camera->Rending(crabs[i]->Get_skin_renderer());
	}


	camera->Rending(sakana->Get_skin_renderer());

	camera->Rending(main_world.wall_map.Get_ren(2));

	camera->Rending_A(&main_world.hurt_area);
	camera->Rending_A(&main_world.coll_area);

	for (int i = 0; i < ball_num; i++)
	{
		camera->Rending(balls[i]->Get_renderer());
	}


	
	for (int i = 0; i < crab_count; i++)
	{
		camera->Rending(&crabs[i]->bar.ren_bar);
	}

	camera->Rending(&sakana->bar.ren_bar);

	camera->Rending(&mouse->ren_target);

	camera->Photographed();

	ui->Rending(&ui_mouse->ren_target);

	sakana_wp_x.Set_num(sakana->Get_x());
	sakana_wp_x.Print();

	sakana_wp_y.Set_num(sakana->Get_y());
	sakana_wp_y.Print();

	end___time = clock();
	delta_time = end___time - start_time;
	start_time = clock();
	frame_board.Set_num(1000 / delta_time);
	frame_board.Print();
}
