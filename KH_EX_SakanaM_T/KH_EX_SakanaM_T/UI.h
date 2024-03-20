
#pragma once

#include <graphics.h>

#include "Renderer.h"

class UI
{	public:
	UI()
	{
		graph_HDC = GetImageHDC();
	}

	void
	New_graph(int w, int h, int l)
	{
		graph_wide = w;
		graph_high = h;
		graph_long = l;

		ui.Resize(graph_wide, graph_high);
		ui_buffer = GetImageBuffer(&ui);

		graph_buffer = GetImageBuffer();
	}

	void
	Clear()
	{
		for (int i = 0; i < graph_long; i++)
		{ ui_buffer[i] = 0x00000000; }
	}

	void
	Rending(Renderer* ren)
	{
		Matrix::Write<DWORD>
			(
				  ui_buffer
				, graph_wide
				, graph_high

				, ren->Get_buffer()
				, ren->Get_wide()
				, ren->Get_high()

				, ren->Get_x()
				, ren->Get_y()

				, fun_add
			);
	}

	void
	Photographed()
	{
		for (int i = 0; i < graph_long; i++)
		{
			if(ui_buffer[i] & 0xff000000)
			{ graph_buffer[i] = ui_buffer[i]; }
		}
	}

private:

	HDC graph_HDC = nullptr;
	DWORD* graph_buffer = nullptr;
	int graph_wide = 0;
	int graph_high = 0;
	int graph_long = 0;

	IMAGE ui;
	DWORD* ui_buffer = nullptr;

	static void
	fun_add(DWORD* a, DWORD* b)
	{
		DWORD c = *b;
		if (c & 0xff000000)
		{
			*a = c;
		}
	}
};
