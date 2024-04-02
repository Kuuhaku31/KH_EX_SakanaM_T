
#pragma once

class Timer
{	public:
	Timer() {}
	Timer(int mt, bool rung, bool roop)
		: max_time(mt)
		, is_rung(rung)
		, is_roop(roop)
	{}

	void
	Update()
	{
		if (is_rung)
		{
			now_time--;
			lst_time++;
			if (0 > now_time)
			{
				if (is_roop)
				{
					now_time = max_time;
					lst_time = 0;
				}
				else
				{
					is_rung = false;
				}
			}
		}
	}

	int Get_now_time() { return now_time; }
	int Get_max_time() { return max_time; }
	int Get_lst_time() { return lst_time; }

	void Rstart() { now_time = max_time; }
	void Set_timer_maxt(int mt) { max_time = mt; }
	void Set_timer_rung(bool rung) { is_rung = rung; }
	void Set_timer_roop(bool roop) { is_roop = roop; }
	void Set_timer(int mt, bool rung, bool roop)
	{
		max_time = mt;
		now_time = mt;
		lst_time = 0;
		is_rung = rung;
		is_roop = roop;
	}
	void
	Set_timer(Timer* t)
	{
		max_time = t->max_time;
		now_time = t->now_time;
		lst_time = t->lst_time;
		is_rung = t->is_rung;
		is_roop = t->is_roop;
	}

	void 
	Add_time(int t) 
	{
		now_time += t; 
		if(now_time > max_time)
		{
			now_time = max_time;
		}
	}

protected:

	int max_time = 0;
	int now_time = 0;
	int lst_time = 0;

	bool is_rung = false;
	bool is_roop = false;

};
