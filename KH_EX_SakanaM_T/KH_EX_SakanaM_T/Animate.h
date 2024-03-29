
#pragma once

#include "Renderer.h"

#include "Timer.h"

class Animate : public Position
{	public:
	Animate(Position* pos = nullptr) : Position(pos) {}
	~Animate() { delete[] cuts; }

	void
	Restart()
	{
		cut_now = 0;
		timer_sec.Rstart();
	}

	void Stop() { is_playing = false; }
	void Play() { is_playing = true; }

	void
	Update()
	{
		if(is_playing)
		{
			timer_sec.Update();
			if (!timer_sec.Get_now_time())
			{
				cut_now++;
				if (cut_now >= cut_num)
				{
					if (is_roop) { cut_now = 0; }
					else { cut_now = cut_num - 1; is_playing = false; }
				}
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
		timer_sec.Set_timer_maxt(tm);
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
			cuts[i].Copy_shape(&rens[i]);
			cuts[i].Set_position(this, &rens[i]);
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

	void
	Align_cuts()
	{
		for (int i = 0; i < cut_num; i++)
		{
			cuts[i].Align();
		}
	}

	void
	Copy_cuts(Animate* a)
	{
		cut_num = a->cut_num;
		cut_now = 0;
		timer_sec.Rstart();

		delete[] cuts;
		cuts = new Renderer[cut_num];
		for (int i = 0; i < cut_num; i++)
		{
			cuts[i].Copy_shape(&a->cuts[i]);
			cuts[i].Set_position(this, &a->cuts[i]);
		}
	}

	void
	Copy_stat(Animate* a)
	{
		is_roop = a->is_roop;
		is_playing = a->is_playing;

		timer_sec.Set_timer(&a->timer_sec);
		timer_sec.Set_timer_rung(1);
		timer_sec.Set_timer_roop(1);
	}

	bool is_roop = false;
	bool is_playing = false;

private:

	Renderer* cuts = nullptr;

	Timer timer_sec;

	int cut_num = 0;
	int cut_now = 0;
};
