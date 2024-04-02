
#pragma once

#include <random>

#include "Position.h"
#include "Renderer.h"
#include "Area.h"

#include "Matrix.h"

class Camera : public Position
{	public:
	Camera() {}

	void
	New_graph(int w, int h, int l)
	{
		graph_HDC = GetImageHDC();
		graph_buffer = GetImageBuffer();

		graph_wide = w;
		graph_high = h;
		graph_long = l;
	}

	void
	Tweaks_sight(int dw, int dy)
	{
		Reset_sight(sight_wide + dw, sight_high + dy);
	}

	void
	Reset_sight(int w, int h)
	{
		if (0 < w && 0 < h)
		{
			sight.Resize(w, h);
			sight_buffer = GetImageBuffer(&sight);
			sight_HDC = GetImageHDC(&sight);

			sight_wide = w;
			sight_high = h;
			sight_long = sight_wide * sight_high;
			half_sight_wide = sight_wide / 2;
			half_sight_high = sight_high / 2;

			kx = sight_wide / 1.0 / graph_wide;
			ky = sight_high / 1.0 / graph_high;
		}
	}

	void
	Clear()
	{
		for(int i = 0; i < sight_long; i++)
		{ sight_buffer[i] = 0xff000000; }
	}

	void
	Rending(Renderer* ren)
	{
		if (ren)
		{
			Toolf::Write<unsigned long>
				(
					sight_buffer
					, sight_wide
					, sight_high

					, ren->Get_buffer()
					, ren->Get_wide()
					, ren->Get_high()

					, ren->Get_x() - Get_x() + half_sight_wide
					, ren->Get_y() - Get_y() + half_sight_high

					, mix_color
				);
		}
	}

	void
	Rending_UI(Renderer* ren)
	{
		if (ren)
		{
			Toolf::Write<unsigned long>
				(
					graph_buffer
					, graph_wide
					, graph_high

					, ren->Get_buffer()
					, ren->Get_wide()
					, ren->Get_high()

					, ren->Get_x()
					, ren->Get_y()

					, mix_color
				);
		}
	}

	void
	Rending_(Renderer* ren)
	{
		SMatrix<unsigned long> S
			(
				sight_buffer
				, sight_wide
				, sight_high

				, ren->Get_buffer()
				, ren->Get_wide()
				, ren->Get_high()

				, ren->Get_x() - Get_x() + half_sight_wide
				, ren->Get_y() - Get_y() + half_sight_high

				//, mix_color
			);

		//S.DO();
		unsigned long* a = nullptr;
		unsigned long* b = nullptr;
		if (S.Update(&a, &b))
		{
			mix_color(a, b);
		}
	}

	void
	Rending_AH(Area* area)
	{
		if (area)
		{
			Toolf::Write<unsigned long>
				(
					sight_buffer
					, sight_wide
					, sight_high

					, area->Get_buffer()
					, area->Get_shape_wide()
					, area->Get_shape_high()

					, area->Get_x() - Get_x() + half_sight_wide
					, area->Get_y() - Get_y() + half_sight_high

					, fun_add_AH
				);
		}
	}

	void
	Rending_AC(Area* area)
	{
		if (area)
		{
			Toolf::Write<unsigned long>
				(
					sight_buffer
					, sight_wide
					, sight_high

					, area->Get_buffer()
					, area->Get_shape_wide()
					, area->Get_shape_high()

					, area->Get_x() - Get_x() + half_sight_wide
					, area->Get_y() - Get_y() + half_sight_high

					, fun_add_AC
				);
		}
	}

	void
	Photographed()
	{
		std::random_device rd;  // 用于获取种子数据
		std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数
		std::uniform_int_distribution<> distr(-shake_radius, +shake_radius); // 定义分布规则

		int x = distr(gen);
		int y = distr(gen);

		StretchBlt
		(
			  graph_HDC
			, x - 16
			, y - 9
			, graph_wide + x + 32
			, graph_high + y + 18

			, sight_HDC
			, 0
			, 0
			, sight_wide
			, sight_high
			
			, SRCCOPY
		);

		shake_radius = 0;
	}

	void 
	Get_mouse_point(int* x, int* y)
	{
		*x *= kx;
		*x += Get_x() - half_sight_wide;
		*y *= ky;
		*y += Get_y() - half_sight_high;
	}

	int Get_sight_wide() { return sight_wide; }
	int Get_sight_high() { return sight_high; }

	void Add_shake(int r) { shake_radius += r; }
	void Set_shake(int r) { shake_radius = r; }
	void 
	Shake_camera()
	{
		Position::Set_position(0, 0);

		std::random_device rd;  // 用于获取种子数据
		std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数
		std::uniform_int_distribution<> distr(0, 1); // 定义分布规则

		int x = 0;
		int y = 0;
		if (distr(gen)) // 生成在min和max之间的随机整数
		{
			x = shake_radius;
		}
		else
		{
			x = -shake_radius;
		}

		if (distr(gen)) // 生成在min和max之间的随机整数
		{
			y = shake_radius;
		}
		else
		{
			y = -shake_radius;
		}

		Position::Move(x, y);
		shake_radius = 0;
	}

private:

	HDC graph_HDC = nullptr;
	unsigned long* graph_buffer = nullptr;
	int graph_wide = 0;
	int graph_high = 0;
	int graph_long = 0;

	IMAGE sight;
	HDC sight_HDC = nullptr;
	unsigned long* sight_buffer = nullptr;
	int sight_wide = 0;
	int sight_high = 0;
	int sight_long = 0;
	int half_sight_wide = 0;
	int half_sight_high = 0;

	float kx = 1.0;
	float ky = 1.0;

	int shake_radius = 0;

	static void
	fun_add_AH(unsigned long* a, unsigned long* b)
	{
		if (*b)
		{
			unsigned long d = ((*b * 0xff )/ 40000) << 24;
			mix_color(a, &d);
		}
	}

	static void
	fun_add_AC(unsigned long* a, unsigned long* b)
	{
		if (*b)
		{
			unsigned long d = ((*b * 0xff) / 800) << 24;
			unsigned long c = 0x00000000 | d;
			mix_color(a, &c);
		}
	}

	static inline void
	mix_color(unsigned long* c1, unsigned long* c2)
	{
		int a2 = (*c2 & 0xff000000) >> 24;
		if (!a2) { return; }
		int a1 = (*c1 & 0xff000000) >> 24;

		int r1 = (*c1 & 0x00ff0000) >> 16;
		int r2 = (*c2 & 0x00ff0000) >> 16;

		int g1 = (*c1 & 0x0000ff00) >> 8;
		int g2 = (*c2 & 0x0000ff00) >> 8;

		int b1 = (*c1 & 0x000000ff);
		int b2 = (*c2 & 0x000000ff);

		int a = a1 + a2;
		int r = (r1 * (0xff - a2) + r2 * a2) / 0xff;
		int g = (g1 * (0xff - a2) + g2 * a2) / 0xff;
		int b = (b1 * (0xff - a2) + b2 * a2) / 0xff;

		*c1 = (a << 24) | (r << 16) | (g << 8) | b;
	}
};
