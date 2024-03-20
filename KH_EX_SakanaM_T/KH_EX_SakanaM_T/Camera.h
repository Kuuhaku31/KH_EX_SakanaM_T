
#pragma once

#include "Position.h"
#include "Renderer.h"
#include "Area.h"

#include "Matrix.h"

class Camera 
	: public Position
{	public:
	void
	New_graph(int w, int h, int l)
	{
		graph_HDC = GetImageHDC();

		graph_wide = w;
		graph_high = h;
		graph_long = l;
	}

	void
	Reset_sight(int w, int h)
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
			Matrix::Write<DWORD>
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
	Rending_(Renderer* ren)
	{
		SMatrix<DWORD> S
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
		DWORD* a = nullptr;
		DWORD* b = nullptr;
		if (S.Update(&a, &b))
		{
			mix_color(a, b);
		}
	}

	void
	Rending_A(Area* area)
	{
		Matrix::Write<DWORD>
			(
				sight_buffer
				, sight_wide
				, sight_high

				, area->Get_buffer()
				, area->Get_shape_wide()
				, area->Get_shape_high()

				, area->Get_x() - Get_x() + half_sight_wide
				, area->Get_y() - Get_y() + half_sight_high

				, fun_add_A
			);
	}

	void
	Photographed()
	{
		StretchBlt
		(
			  graph_HDC
			, 0
			, 0
			, graph_wide
			, graph_high
			, sight_HDC
			, 0
			, 0
			, sight_wide
			, sight_high
			, SRCCOPY
		);
	}

	void 
	Get_mouse_point(int* x, int* y)
	{
		*x *= kx;
		*x += Get_x() - half_sight_wide;
		*y *= ky;
		*y += Get_y() - half_sight_high;
	}

	int
	Get_sight_wide()
	{ return sight.getwidth(); }

	int
	Get_sight_high()
	{ return sight.getheight(); }

private:

	HDC graph_HDC = nullptr;
	int graph_wide = 0;
	int graph_high = 0;
	int graph_long = 0;

	IMAGE sight;
	DWORD* sight_buffer = nullptr;
	HDC sight_HDC = nullptr;
	int sight_wide = 0;
	int sight_high = 0;
	int sight_long = 0;
	int half_sight_wide = 0;
	int half_sight_high = 0;

	double kx = 1.0;
	double ky = 1.0;

	static void
	fun_add_A(DWORD* a, DWORD* b)
	{
		if (*b)
		{
			DWORD d = ((*b * 0xff )/ 20000) << 24;
			DWORD c = 0x00000000 | d;
			mix_color(a, &c);
		}
	}

	static inline void
	mix_color(DWORD* c1, DWORD* c2)
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
