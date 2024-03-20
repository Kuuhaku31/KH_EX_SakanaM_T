
#pragma once

#include "Renderer.h"

class Animate : public Position
{	public:
	Animate(Position* pos) : Position(pos) {}

	void
	Restart()
	{
		cut_now = 0;
		cut_timer = 0;
	}

	void Stop() { is_playing = false; }
	void Play() { is_playing = true; }

	void
	Update()
	{
		if(!is_playing) { return; }
		if (cut_timer < cut_timer_max) { cut_timer++; }
		else
		{
			cut_timer = 0;
			cut_now++;
			if(cut_now >= cut_num)
			{
				if (is_roop) { cut_now = 0; }
				else { cut_now = cut_num - 1; is_playing = false; }
			}
		}
	}

	Renderer* 
	Get_renderer()
	{
		return &cuts[cut_now];
	}

	Renderer*
	Get_renderer(int n)
	{
		if (n >= cut_num) { n = cut_num - 1; }
		else if (n < 0) { n = 0; }
		else return &cuts[n];
	}

	void
	Set(int tm, bool b, bool b2)
	{
		cut_timer_max = tm;
		is_roop = b;
		is_playing = b2;
	}

	void
	Set_cuts(IMAGE* imgs, int n)
	{
		delete[] cuts;
		cuts = new Renderer[n];
		cut_num = n;
		for (int i = 0; i < cut_num; i++)
		{
			cuts[i].Reset_skin(&imgs[i]);
			cuts[i].Set_position(this);
		}
	}

	void
	Set_cuts(Renderer* rens, int n)
	{
		delete[] cuts;
		cuts = new Renderer[n];
		cut_num = n;
		for (int i = 0; i < cut_num; i++)
		{
			cuts[i] = rens[i];
			cuts[i].Set_position(this);
		}
	}

	void
	Set_cut(IMAGE* img, int n)
	{
		if (n < 0 || n >= cut_num) { return; }
		cuts[n].Reset_skin(img);
	}

	void
	Set_cut(IMAGE* img, int x, int y, int n)
	{
		if (n < 0 || n >= cut_num) { return; }
		cuts[n].Reset_skin(img);
		cuts[n].Set_position(x, y);
	}

	bool is_roop = false;
	bool is_playing = false;

private:

	Renderer* cuts = nullptr;

	int cut_num = 0;
	int cut_now = 0;

	int cut_timer_max = 0;
	int cut_timer = 0;
};