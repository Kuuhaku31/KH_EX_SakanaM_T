
#pragma once

#include <graphics.h>

#include "Renderer.h"

#include "Matrix.h"

class Bar
{	public:
	Bar
	(
	 	  int* vm
		, int* vn

		, Position* pos = nullptr
		, int x = 0
		, int y = 0
	)
		: ren_bar(nullptr, pos, x, y)
		, max_value(vm)
		, now_value(vn)
	{
		int bar_w = 52;
		int bar_h = 6;
		IMAGE img = IMAGE(bar_w, bar_h);
		ren_bar.Reset_skin(&img);
		fill(DARKGRAY, 0, 0, bar_w, bar_h);
		fill(LIGHTGRAY, 1, 1, 50, 4);
	}

	void
	Update()
	{
		fill(LIGHTGRAY, 1, 1, 50, 4);
		fill(BLACK, 1, 1, *now_value * 50 / *max_value, 4);
	}

	Renderer ren_bar;

private:
	
	int* max_value;
	int* now_value;

	void
	fill(int color, int x, int y, int w, int h)
	{
		DWORD fill_color = color | 0xff000000;

		int p_s = w * h;
		DWORD* p = new DWORD[p_s];
		for (int i = 0; i < p_s; i++)
		{ p[i] = fill_color; }

		Matrix::Write
		(
			  ren_bar.Get_buffer()
			, ren_bar.Get_wide()
			, ren_bar.Get_high()
			
			, p
			, w
			, h
			
			, x
			, y
			, fun
		);

		delete[] p;
	}

	static void
	fun(DWORD* a, DWORD* b)
	{ *a = *b; }
};
