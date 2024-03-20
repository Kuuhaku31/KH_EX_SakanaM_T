
#pragma once

#include <graphics.h>
#include <string>

#include "Shape_Maker.h"

#include "Renderer.h"

class Library
{	public:

	std::string _path_area_main = "./KH_EX_SakanaM_T/Material/area_main.png";
	IMAGE _area_main;
	std::string _path_skin_main = "./KH_EX_SakanaM_T/Material/skin_main.png";
	IMAGE _skin_main;

	std::string _path_skin_wall_01 = "./KH_EX_SakanaM_T/Material/skin_wall_01.png";
	IMAGE _skin_wall_01;
	std::string _path_skin_wall_02 = "./KH_EX_SakanaM_T/Material/skin_wall_02.png";
	IMAGE _skin_wall_02;
	std::string _path_area_wall_01 = "./KH_EX_SakanaM_T/Material/area_wall_01.png";
	IMAGE _area_wall_01;

	std::string _path_skin_ikacyann= "./KH_EX_SakanaM_T/Material/skin_ikacyann.png";
	IMAGE _skin_ikacyann;
	std::string _path_skin_sakana = "./KH_EX_SakanaM_T/Material/skin_sakana.png";
	IMAGE _skin_sakana;

	std::string _path_skin_saskana_01 = "./KH_EX_SakanaM_T/Material/skins/skin_sakana_01.png";
	IMAGE _skin_sakana_right_01;
	std::string _path_skin_saskana_02 = "./KH_EX_SakanaM_T/Material/skins/skin_sakana_02.png";
	IMAGE _skin_sakana_right_02;
	IMAGE _skin_sakana_left_01;
	IMAGE _skin_sakana_left_02;

	std::string _path_skin_target = "./KH_EX_SakanaM_T/Material/skin_target.png";
	IMAGE _skin_target;

	std::string _path_skin_ball = "./KH_EX_SakanaM_T/Material/skins/skin_ball.png";
	IMAGE _skin_ball;
	std::string _path_skin_ball_break_1 = "./KH_EX_SakanaM_T/Material/skins/skin_ball_break_1.png";
	IMAGE _skin_ball_break_1;
	std::string _path_skin_ball_break_2 = "./KH_EX_SakanaM_T/Material/skins/skin_ball_break_2.png";
	IMAGE _skin_ball_break_2;

	std::string _path_unit_skin_wall_01 = "./KH_EX_SakanaM_T/Material/Map/unit_skin_wall_01.png";
	IMAGE _unit_skin_wall_01;
	std::string _path_unit_skin_wall_02 = "./KH_EX_SakanaM_T/Material/Map/unit_skin_wall_02.png";
	IMAGE _unit_skin_wall_02;
	std::string _path_unit_area_wall_01 = "./KH_EX_SakanaM_T/Material/Map/unit_area_wall_01.png";
	IMAGE _unit_area_wall_01;

	//====================================================================================================
	//====================================================================================================

	std::string _path_hitbox_size16 = "./KH_EX_SakanaM_T/Material/hitbox/hitbox16.png";
	IMAGE _hitbox_size16;
	int _hitbox_size16_wigh;
	int _hitbox_size16_high;
	int _hitbox_size16_long;

	std::string _path_coll_size32 = "./KH_EX_SakanaM_T/Material/collision/size32.png";
	IMAGE _coll_size32;
	std::string _path_coll_size64 = "./KH_EX_SakanaM_T/Material/collision/size64.png";
	IMAGE _coll_size64;

	IMAGE bar_01;
	IMAGE bar_02;
	IMAGE bar_03;


	void
	Init()
	{
		loadimage(&_area_main, _path_area_main.c_str());
		loadimage(&_skin_main, _path_skin_main.c_str());
		loadimage(&_skin_wall_01, _path_skin_wall_01.c_str());
		loadimage(&_skin_wall_02, _path_skin_wall_02.c_str());
		loadimage(&_area_wall_01, _path_area_wall_01.c_str());
		loadimage(&_skin_ikacyann, _path_skin_ikacyann.c_str());
		loadimage(&_skin_sakana, _path_skin_sakana.c_str());

		loadimage(&_skin_sakana_right_01, _path_skin_saskana_01.c_str());
		loadimage(&_skin_sakana_right_02, _path_skin_saskana_02.c_str());
		_skin_sakana_left_01 = Reverse_img(&_skin_sakana_right_01);
		_skin_sakana_left_02 = Reverse_img(&_skin_sakana_right_02);

		loadimage(&_skin_target, _path_skin_target.c_str());

		loadimage(&_skin_ball, _path_skin_ball.c_str());
		loadimage(&_skin_ball_break_1, _path_skin_ball_break_1.c_str());
		loadimage(&_skin_ball_break_2, _path_skin_ball_break_2.c_str());

		loadimage(&_unit_skin_wall_01, _path_unit_skin_wall_01.c_str());
		loadimage(&_unit_skin_wall_02, _path_unit_skin_wall_02.c_str());
		loadimage(&_unit_area_wall_01, _path_unit_area_wall_01.c_str());

		loadimage(&_hitbox_size16, _path_hitbox_size16.c_str());
		_hitbox_size16_wigh = _hitbox_size16.getwidth();
		_hitbox_size16_high = _hitbox_size16.getheight();
		_hitbox_size16_long = _hitbox_size16_wigh * _hitbox_size16_high;

		loadimage(&_coll_size32, _path_coll_size32.c_str());
		loadimage(&_coll_size64, _path_coll_size64.c_str());

		/*loadimage(&bar_01, "./KH_EX_SakanaM_T/Material/bar_01.png");
		loadimage(&bar_02, "./KH_EX_SakanaM_T/Material/bar_02.png");
		loadimage(&bar_03, "./KH_EX_SakanaM_T/Material/bar_03.png");*/

		//Shape_Maker maker;
		//main = maker.Make(_area_main, 320);
		//wall = maker.Make(_area_wall_01, 32);
		////fire = maker.Make(_area_main);

		//coll_size16 = maker.Make(_coll_size16);
		//coll_size32 = maker.Make(_coll_size32);
		//coll_size64 = maker.Make(_coll_size64);

		Init_animate_skin_for_sakana();
		Init_animate_skin_for_ikacyann();
		Init_animate_skin_for_ball_break();
	}

	void
	Delete()
	{
	
	}

	static const int num_of_animate_skin_for_sakana = 2;
	Renderer animate_skin_for_sakana_right[num_of_animate_skin_for_sakana];
	Renderer animate_skin_for_sakana_left[num_of_animate_skin_for_sakana];
	void Init_animate_skin_for_sakana()
	{
		animate_skin_for_sakana_right[0].Reset_skin(&_skin_sakana_right_01);
		animate_skin_for_sakana_right[0].Align();
		animate_skin_for_sakana_right[1].Reset_skin(&_skin_sakana_right_02);
		animate_skin_for_sakana_right[1].Align();

		animate_skin_for_sakana_left[0].Reset_skin(&_skin_sakana_left_01);
		animate_skin_for_sakana_left[0].Align();
		animate_skin_for_sakana_left[1].Reset_skin(&_skin_sakana_left_02);
		animate_skin_for_sakana_left[1].Align();
	}

	static const int num_of_animate_skin_for_ikacyann = 2;
	Renderer animate_skin_for_ikacyann[num_of_animate_skin_for_ikacyann];
	void Init_animate_skin_for_ikacyann()
	{
		animate_skin_for_ikacyann[0].Reset_skin(&_skin_ikacyann);
		animate_skin_for_ikacyann[0].Align();
		animate_skin_for_ikacyann[1].Reset_skin(&_skin_sakana);
		animate_skin_for_ikacyann[1].Align();
	}

	static const int num_of_animate_skin_for_ball_break = 2;
	Renderer animate_skin_for_ball_break[num_of_animate_skin_for_ikacyann];
	void Init_animate_skin_for_ball_break()
	{
		animate_skin_for_ball_break[0].Reset_skin(&_skin_ball_break_1);
		animate_skin_for_ball_break[0].Align();
		animate_skin_for_ball_break[1].Reset_skin(&_skin_ball_break_2);
		animate_skin_for_ball_break[1].Align();
	}

	IMAGE
	Reverse_img(IMAGE* img)
	{
		DWORD* input_buffer = GetImageBuffer(img);
		int wigh = img->getwidth();
		int high = img->getheight();

		IMAGE output(wigh, high);
		DWORD* output_buffer = GetImageBuffer(&output);

		for (int i = 0; i < high; i++)
		{
			for (int j = 0; j < wigh; j++)
			{
				output_buffer[i * wigh + j] = input_buffer[i * wigh + (wigh - j - 1)];
			}
		}

		return output;
	}
};
