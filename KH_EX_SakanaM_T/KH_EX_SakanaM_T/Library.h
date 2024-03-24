
#pragma once

#include <graphics.h>
#include <string>

#include "Shape_Maker.h"

#include "Renderer.h"
#include "Animate.h"
#include "Hitbox.h"

struct static_resource_UI
{
	IMAGE char_size0_num[10];
	Renderer renderer_for_mouse;
};

struct static_resource_world
{
	Renderer renderer_for_main_A;
	Renderer renderer_for_main_B;
	Area area_for_main;

	Renderer renderer_for_wall_A;
	Renderer renderer_for_wall_B;
	Area area_for_wall;

	Renderer renderer_for_coll;
	Area area_for_coll;

	Renderer renderer_for_hurt;
	Area area_for_hurt;
};

struct static_resource_crab
{
	Animate animate_for_crab_R;
	Animate animate_for_crab_L;
	Animate animate_for_crab_dead_R;
	Animate animate_for_crab_dead_L;

	Hitbox hitbox_crab;
};

struct static_resource_fish
{
	Animate animate_for_fish_R;
	Animate animate_for_fish_L;
	Animate animate_for_fish_dead_R;
	Animate animate_for_fish_dead_L;

	Hitbox hitbox_fish;
};
struct static_resource_ball
{
	Animate animate_for_ball;
	Animate animate_for_ball_break;

	Hitbox hitbox_ball;
};

class Library
{
public:
	Library() {}

	static_resource_UI ui;
	inline void
		load_static_resource_numbers()
	{
		for (int i = 0; i < 10; i++)
		{
			loadimage(&ui.char_size0_num[i]
				, ("./KH_EX_SakanaM_T/Material/Chars/char_size0_num_"
					+ std::to_string(i)
					+ ".png").c_str());
		}

		IMAGE img;
		loadimage(&img, "./KH_EX_SakanaM_T/Material/skin_target.png");
		ui.renderer_for_mouse.Reset_skin(&img);
		ui.renderer_for_mouse.Align();
	}

	static_resource_world world;
	inline void
		load_static_resource_world()
	{
		IMAGE img;

		loadimage(&img, "./KH_EX_SakanaM_T/Material/skin_main.png", 0, 0, true);
		world.renderer_for_main_A.Reset_skin(&img);
		loadimage(&img, "./KH_EX_SakanaM_T/Material/skin_main.png", 0, 0, true);
		world.renderer_for_main_B.Reset_skin(&img);
		loadimage(&img, "./KH_EX_SakanaM_T/Material/area_main.png", 0, 0, true);
		world.area_for_main.Write(GetImageBuffer(&img), img.getwidth(), img.getheight());

		loadimage(&img, "./KH_EX_SakanaM_T/Material/skin_wall_01.png", 0, 0, true);
		world.renderer_for_wall_A.Reset_skin(&img);
		loadimage(&img, "./KH_EX_SakanaM_T/Material/skin_wall_02.png", 0, 0, true);
		world.renderer_for_wall_B.Reset_skin(&img);
		loadimage(&img, "./KH_EX_SakanaM_T/Material/area_wall_01.png", 0, 0, true);
		world.area_for_wall.Write(GetImageBuffer(&img), img.getwidth(), img.getheight());

		loadimage(&img, "./KH_EX_SakanaM_T/Material/skin_coll.png", 0, 0, true);
		world.renderer_for_coll.Reset_skin(&img);
		world.renderer_for_coll.Clear();
		loadimage(&img, "./KH_EX_SakanaM_T/Material/area_coll.png", 0, 0, true);
		world.area_for_coll.Write(GetImageBuffer(&img), img.getwidth(), img.getheight());
		world.area_for_coll.Clear();

		loadimage(&img, "./KH_EX_SakanaM_T/Material/skin_coll.png", 0, 0, true);
		world.renderer_for_hurt.Reset_skin(&img);
		world.renderer_for_hurt.Clear();
		loadimage(&img, "./KH_EX_SakanaM_T/Material/area_coll.png", 0, 0, true);
		world.area_for_hurt.Write(GetImageBuffer(&img), img.getwidth(), img.getheight());
		world.area_for_hurt.Clear();
	}

	static_resource_crab crab;
	inline void
		load_static_resource_crab()
	{
		IMAGE img[3];
		loadimage(&img[0], "./KH_EX_SakanaM_T/Material/skin_ikacyann.png", 0, 0, true);
		loadimage(&img[1], "./KH_EX_SakanaM_T/Material/skin_sakana.png", 0, 0, true);
		loadimage(&img[2], "./KH_EX_SakanaM_T/Material/skin_target.png", 0, 0, true);
		crab.animate_for_crab_R.Set_cuts(img, 3);
		crab.animate_for_crab_R.Align_cuts();

		img[0] = Reverse_img(&img[0]);
		img[1] = Reverse_img(&img[1]);
		img[2] = Reverse_img(&img[2]);
		crab.animate_for_crab_L.Set_cuts(img, 3);
		crab.animate_for_crab_L.Align_cuts();

		loadimage(&img[0], "./KH_EX_SakanaM_T/Material/skins/skin_ball.png", 0, 0, true);
		loadimage(&img[1], "./KH_EX_SakanaM_T/Material/skins/skin_ball_break_1.png", 0, 0, true);
		loadimage(&img[2], "./KH_EX_SakanaM_T/Material/skins/skin_ball_break_2.png", 0, 0, true);
		crab.animate_for_crab_dead_R.Set_cuts(img, 3);
		crab.animate_for_crab_dead_R.Align_cuts();

		img[0] = Reverse_img(&img[0]);
		img[1] = Reverse_img(&img[1]);
		img[2] = Reverse_img(&img[2]);
		crab.animate_for_crab_dead_L.Set_cuts(img, 3);
		crab.animate_for_crab_dead_L.Align_cuts();

		loadimage(&img[0], "./KH_EX_SakanaM_T/Material/hitbox/hitbox16.png", 0, 0, true);
		crab.hitbox_crab.Write(GetImageBuffer(&img[0]), img[0].getwidth(), img[0].getheight());
		crab.hitbox_crab.Align();
	}

	static_resource_fish fish;
	inline void
		load_static_resource_fish()
	{
		IMAGE img[2];
		loadimage(&img[0], "./KH_EX_SakanaM_T/Material/skins/skin_sakana_01.png", 0, 0, true);
		loadimage(&img[1], "./KH_EX_SakanaM_T/Material/skins/skin_sakana_02.png", 0, 0, true);
		fish.animate_for_fish_R.Set_cuts(img, 2);
		fish.animate_for_fish_R.Align_cuts();

		img[0] = Reverse_img(&img[0]);
		img[1] = Reverse_img(&img[1]);
		fish.animate_for_fish_L.Set_cuts(img, 2);
		fish.animate_for_fish_L.Align_cuts();

		loadimage(&img[0], "./KH_EX_SakanaM_T/Material/skins/skin_ball.png", 0, 0, true);
		loadimage(&img[1], "./KH_EX_SakanaM_T/Material/skins/skin_ball_break_1.png", 0, 0, true);
		fish.animate_for_fish_dead_R.Set_cuts(img, 2);
		fish.animate_for_fish_dead_R.Align_cuts();

		img[0] = Reverse_img(&img[0]);
		img[1] = Reverse_img(&img[1]);
		fish.animate_for_fish_dead_L.Set_cuts(img, 2);
		fish.animate_for_fish_dead_L.Align_cuts();

		loadimage(&img[0], "./KH_EX_SakanaM_T/Material/hitbox/hitbox16.png", 0, 0, true);
		fish.hitbox_fish.Write(GetImageBuffer(&img[0]), img[0].getwidth(), img[0].getheight());
		fish.hitbox_fish.Align();
	}

	static_resource_ball ball;
	inline void
		load_static_resource_ball()
	{
		IMAGE img[3];

		loadimage(&img[0], "./KH_EX_SakanaM_T/Material/skins/skin_ball.png", 0, 0, true);
		loadimage(&img[1], "./KH_EX_SakanaM_T/Material/skins/skin_ball.png", 0, 0, true);
		loadimage(&img[2], "./KH_EX_SakanaM_T/Material/skins/skin_ball.png", 0, 0, true);
		ball.animate_for_ball.Set_cuts(img, 3);
		ball.animate_for_ball.Align_cuts();

		loadimage(&img[0], "./KH_EX_SakanaM_T/Material/skins/skin_ball.png", 0, 0, true);
		loadimage(&img[1], "./KH_EX_SakanaM_T/Material/skins/skin_ball_break_1.png", 0, 0, true);
		loadimage(&img[2], "./KH_EX_SakanaM_T/Material/skins/skin_ball_break_2.png", 0, 0, true);
		ball.animate_for_ball_break.Set_cuts(img, 3);
		ball.animate_for_ball_break.Align_cuts();

		loadimage(&img[0], "./KH_EX_SakanaM_T/Material/hitbox/hitbox8.png", 0, 0, true);
		ball.hitbox_ball.Write(GetImageBuffer(&img[0]), img[0].getwidth(), img[0].getheight());
		ball.hitbox_ball.Align();
	}

	std::string _path_area_main = "./KH_EX_SakanaM_T/Material/area_main.png";
	IMAGE _area_main;
	std::string _path_skin_main = "./KH_EX_SakanaM_T/Material/skin_main.png";
	IMAGE _skin_main;
	Renderer ren_main_map;
	void init_ren_main_map()
	{

	}

	std::string _path_skin_wall_01 = "./KH_EX_SakanaM_T/Material/skin_wall_01.png";
	IMAGE _skin_wall_01;
	std::string _path_skin_wall_02 = "./KH_EX_SakanaM_T/Material/skin_wall_02.png";
	IMAGE _skin_wall_02;
	std::string _path_area_wall_01 = "./KH_EX_SakanaM_T/Material/area_wall_01.png";
	IMAGE _area_wall_01;

	std::string _path_skin_ikacyann = "./KH_EX_SakanaM_T/Material/skin_ikacyann.png";
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

	IMAGE char_size0_num[10];

	std::string path_char_size0_num = "./KH_EX_SakanaM_T/Material/Chars/char_size0_num_";
	std::string _png = ".png";

	inline void
		init_nums()
	{
		for (int i = 0; i < 10; i++)
		{
			loadimage(&char_size0_num[i], (path_char_size0_num + std::to_string(i) + _png).c_str());
		}
	}

	//====================================================================================================
	//====================================================================================================

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



		loadimage(&_coll_size32, _path_coll_size32.c_str());
		loadimage(&_coll_size64, _path_coll_size64.c_str());


		init_nums();
		Init_animate_skin_for_sakana();
		Init_animate_skin_for_ikacyann();
		Init_animate_skin_for_ball_break();

		init_crab_hitbox();
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

		animate_for_ikacyann.Set_cuts(animate_skin_for_ikacyann, num_of_animate_skin_for_ikacyann);
		animate_for_ikacyann.Set(60, 1, 1);
	}
	Animate animate_for_ikacyann;

	static const int num_of_animate_skin_for_ball_break = 2;
	Renderer animate_skin_for_ball_break[num_of_animate_skin_for_ikacyann];
	void Init_animate_skin_for_ball_break()
	{
		animate_skin_for_ball_break[0].Reset_skin(&_skin_ball_break_1);
		animate_skin_for_ball_break[0].Align();
		animate_skin_for_ball_break[1].Reset_skin(&_skin_ball_break_2);
		animate_skin_for_ball_break[1].Align();
	}

	Hitbox crab_hitbox;
	void init_crab_hitbox()
	{

		IMAGE img;
		loadimage(&img, "./KH_EX_SakanaM_T/Material/hitbox/hitbox16.png");
		crab_hitbox.Write(GetImageBuffer(&img), img.getwidth(), img.getheight());
		crab_hitbox.Align();
	}

	static inline IMAGE
		Reverse_img(IMAGE* img)
	{
		unsigned long* input_buffer = GetImageBuffer(img);
		int wigh = img->getwidth();
		int high = img->getheight();

		IMAGE output(wigh, high);
		unsigned long* output_buffer = GetImageBuffer(&output);

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
