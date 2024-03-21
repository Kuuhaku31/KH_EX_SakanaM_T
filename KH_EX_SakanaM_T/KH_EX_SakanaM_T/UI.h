
#pragma once

#include <graphics.h>

#include "Renderer.h"

class UI
{	public:
	~UI() { delete[] ui_buffer; }

	void
	New_graph(int w, int h, int l)
	{
		graph_buffer = GetImageBuffer();
		graph_wide = w;
		graph_high = h;
		graph_long = l;

		delete[] ui_buffer;
		ui_buffer = new unsigned long[w * h];
	}

	void
	Rending(Renderer* ren)
	{
		Matrix::Write<unsigned long>
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

	void
	Photographed_()
	{
		for(int i = 0; i < graph_long; i++)
		{
			mix_color(&graph_buffer[i], &ui_buffer[i]);
		}
		for (int i = 0; i < graph_long; i++)
		{
			ui_buffer[i] = 0;
		}
	}

private:

	unsigned long* graph_buffer = nullptr;
	int graph_wide = 0;
	int graph_high = 0;
	int graph_long = 0;

	unsigned long* ui_buffer = nullptr;

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
