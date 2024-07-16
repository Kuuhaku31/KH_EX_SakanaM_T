
//
// Library.h
//
// 管理所有静态资源
//
//

#pragma once

#include "MessageSystem.hpp"

// #include "Shape_Maker.h"

// #include "struct_static.h"

class Library
{
public:
	Library() = default;
	~Library() = default;

	// 初始化所有静态资源
	// 开发中……
	short
	Init()
	{
		// load_static_resource_ui();
		// load_static_resource_world();
		// load_static_resource_crab();
		// load_static_resource_fish();
		// load_static_resource_ball();

		return 0;
	}

	/*
		static_resource_UI ui;
		static_resource_world world;
		static_resource_crab crab;
		static_resource_fish fish;
		static_resource_ball ball;

	private:
		inline void
		load_static_resource_ui()
		{
			for (int i = 0; i < 10; i++)
			{
				loadimage(&ui.char_size0_num[i], ("./KH_EX_SakanaM_T/Material/Chars/char_size0_num_" + std::to_string(i) + ".png").c_str());
			}

			IMAGE img;
			loadimage(&img, "./KH_EX_SakanaM_T/Material/skin_target.png");
			ui.renderer_for_mouse.Reset_skin(&img);
			ui.renderer_for_mouse.Align();
		}

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
			world.area_for_main.Clear_shape(20000);

			loadimage(&img, "./KH_EX_SakanaM_T/Material/skin_wall_01.png", 0, 0, true);
			world.renderer_for_wall_A.Reset_skin(&img);
			loadimage(&img, "./KH_EX_SakanaM_T/Material/skin_wall_02.png", 0, 0, true);
			world.renderer_for_wall_B.Reset_skin(&img);
			loadimage(&img, "./KH_EX_SakanaM_T/Material/area_wall_01.png", 0, 0, true);
			world.area_for_wall.Write(GetImageBuffer(&img), img.getwidth(), img.getheight());
			world.area_for_wall.Clear_shape(0xffffffff);

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

		inline void
		load_static_resource_crab()
		{
			IMAGE img[3];
			loadimage(&img[0], "./KH_EX_SakanaM_T/Material/skin_ikacyann.png", 0, 0, true);
			loadimage(&img[1], "./KH_EX_SakanaM_T/Material/skin_sakana.png", 0, 0, true);
			loadimage(&img[2], "./KH_EX_SakanaM_T/Material/skin_target.png", 0, 0, true);
			crab.animate_for_crab_R.Set_cuts(img, 3);
			crab.animate_for_crab_R.Align_cuts();
			crab.animate_for_crab_R.Set(20, 1, 1);

			img[0] = reverse_img(&img[0]);
			img[1] = reverse_img(&img[1]);
			img[2] = reverse_img(&img[2]);
			crab.animate_for_crab_L.Set_cuts(img, 3);
			crab.animate_for_crab_L.Align_cuts();
			crab.animate_for_crab_L.Set(60, 1, 1);

			loadimage(&img[0], "./KH_EX_SakanaM_T/Material/skins/skin_ball.png", 0, 0, true);
			loadimage(&img[1], "./KH_EX_SakanaM_T/Material/skins/skin_ball_break_1.png", 0, 0, true);
			loadimage(&img[2], "./KH_EX_SakanaM_T/Material/skins/skin_ball_break_2.png", 0, 0, true);
			crab.animate_for_crab_dead_R.Set_cuts(img, 3);
			crab.animate_for_crab_dead_R.Align_cuts();
			crab.animate_for_crab_dead_R.Set(60, 1, 1);

			img[0] = reverse_img(&img[0]);
			img[1] = reverse_img(&img[1]);
			img[2] = reverse_img(&img[2]);
			crab.animate_for_crab_dead_L.Set_cuts(img, 3);
			crab.animate_for_crab_dead_L.Align_cuts();
			crab.animate_for_crab_dead_L.Set(60, 1, 1);

			loadimage(&img[0], "./KH_EX_SakanaM_T/Material/hitbox/hitbox16.png", 0, 0, true);
			crab.hitbox_crab.Write(GetImageBuffer(&img[0]), img[0].getwidth(), img[0].getheight());
			crab.hitbox_crab.Clear_shape(100);
			crab.hitbox_crab.Align();
		}

		inline void
		load_static_resource_fish()
		{
			IMAGE img[2];
			loadimage(&img[0], "./KH_EX_SakanaM_T/Material/skins/skin_sakana_01.png", 0, 0, true);
			loadimage(&img[1], "./KH_EX_SakanaM_T/Material/skins/skin_sakana_02.png", 0, 0, true);
			fish.animate_for_fish_R.Set_cuts(img, 2);
			fish.animate_for_fish_R.Align_cuts();
			fish.animate_for_fish_R.Set(60, 1, 1);

			img[0] = reverse_img(&img[0]);
			img[1] = reverse_img(&img[1]);
			fish.animate_for_fish_L.Set_cuts(img, 2);
			fish.animate_for_fish_L.Align_cuts();
			fish.animate_for_fish_L.Set(60, 1, 1);

			loadimage(&img[0], "./KH_EX_SakanaM_T/Material/skins/skin_ball.png", 0, 0, true);
			loadimage(&img[1], "./KH_EX_SakanaM_T/Material/skins/skin_ball_break_1.png", 0, 0, true);
			fish.animate_for_fish_dead_R.Set_cuts(img, 2);
			fish.animate_for_fish_dead_R.Align_cuts();
			fish.animate_for_fish_dead_R.Set(60, 1, 1);

			img[0] = reverse_img(&img[0]);
			img[1] = reverse_img(&img[1]);
			fish.animate_for_fish_dead_L.Set_cuts(img, 2);
			fish.animate_for_fish_dead_L.Align_cuts();
			fish.animate_for_fish_dead_L.Set(60, 1, 1);

			loadimage(&img[0], "./KH_EX_SakanaM_T/Material/hitbox/hitbox16.png", 0, 0, true);
			fish.hitbox_fish.Write(GetImageBuffer(&img[0]), img[0].getwidth(), img[0].getheight());
			fish.hitbox_fish.Clear_shape(100);
			fish.hitbox_fish.Align();
		}

		inline void
		load_static_resource_ball()
		{
			IMAGE img[3];

			loadimage(&img[0], "./KH_EX_SakanaM_T/Material/skins/skin_ball.png", 0, 0, true);
			loadimage(&img[1], "./KH_EX_SakanaM_T/Material/skins/skin_ball.png", 0, 0, true);
			loadimage(&img[2], "./KH_EX_SakanaM_T/Material/skins/skin_ball.png", 0, 0, true);
			ball.animate_for_ball.Set_cuts(img, 3);
			ball.animate_for_ball.Align_cuts();
			ball.animate_for_ball.Set(60, 1, 1);

			loadimage(&img[0], "./KH_EX_SakanaM_T/Material/skins/skin_ball.png", 0, 0, true);
			loadimage(&img[1], "./KH_EX_SakanaM_T/Material/skins/skin_ball_break_1.png", 0, 0, true);
			loadimage(&img[2], "./KH_EX_SakanaM_T/Material/skins/skin_ball_break_2.png", 0, 0, true);
			ball.animate_for_ball_break.Set_cuts(img, 3);
			ball.animate_for_ball_break.Align_cuts();
			ball.animate_for_ball_break.Set(3, 0, 1);

			loadimage(&img[0], "./KH_EX_SakanaM_T/Material/hitbox/hitbox8.png", 0, 0, true);
			ball.hitbox_ball.Write(GetImageBuffer(&img[0]), img[0].getwidth(), img[0].getheight());
			ball.hitbox_ball.Align();
		}

		static inline IMAGE
		reverse_img(IMAGE *img)
		{
			unsigned long *input_buffer = GetImageBuffer(img);
			int wigh = img->getwidth();
			int high = img->getheight();

			IMAGE output(wigh, high);
			unsigned long *output_buffer = GetImageBuffer(&output);

			for (int i = 0; i < high; i++)
			{
				for (int j = 0; j < wigh; j++)
				{
					output_buffer[i * wigh + j] = input_buffer[i * wigh + (wigh - j - 1)];
				}
			}

			return output;
		}

	*/
};
