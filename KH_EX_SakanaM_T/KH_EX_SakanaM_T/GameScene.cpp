#include "GameScene.h"

bool GameScene::Update()
{
	input->GetInput();
	if (input->enter) { return false; }

	double x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
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

	double FORCE_01 = 500;
	double FORCE_02 = 1000;

	double V_01 = 100;
	double V_02 = 10;

	if (Matrix::to_unit(&x1, &y1)) { sakana->Force(x1 * FORCE_01, y1 * FORCE_01); }
	if (Matrix::to_unit(&x2, &y2)) { ikacyann->Force(x2 * FORCE_01, y2 * FORCE_01); }
	if (Matrix::to_unit(&x3, &y3)) { camera->Move(x3 * 10, y3 * 10); }

	int mouse_w_x = input->mouse_X;
	int mouse_w_y = input->mouse_Y;
	ui_mouse->Move_to(mouse_w_x, mouse_w_y);
	camera->Get_mouse_point(&mouse_w_x, &mouse_w_y);
	mouse->Move_to(mouse_w_x, mouse_w_y);

	int camera_man_w_x = camera_man.Object::Get_x();
	int camera_man_w_y = camera_man.Object::Get_y();

	int sakana_w_x = sakana->Object::Get_x();
	int sakana_w_y = sakana->Object::Get_y();

	double x0 = sakana_w_x - camera_man_w_x;
	double y0 = sakana_w_y - camera_man_w_y;

	if (ball_num < 100 && space && input->space)
	{
		space = false;
		balls[ball_num] = sakana->Fire();
		balls[ball_num]->renderer.Reset_skin(&library->_skin_ball);
		balls[ball_num]->renderer.Align();
		balls[ball_num]->break_animate.Set_cuts(library->animate_skin_for_ball_break, library->num_of_animate_skin_for_ball_break);
		balls[ball_num]->break_animate.Set(3, false, true);

		double x = mouse_w_x - sakana_w_x;
		double y = mouse_w_y - sakana_w_y;

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

	sakana->main_hitbox.Add_hit_box_to_area();
	ikacyann->main_hitbox.Add_hit_box_to_area();

	main_world.Update_booms();

	sakana->Update();
	ikacyann->Update();
	//camera_man.Update();

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

	sakana->main_hitbox.Delete_hitbox_from_area();
	ikacyann->main_hitbox.Delete_hitbox_from_area();

	return true;
}