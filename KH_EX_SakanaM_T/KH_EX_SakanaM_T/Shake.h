
#pragma once

#include "Timer.h"

class Shake
{	public:
	Shake(int r, int t) : radius(r), timer(t, true, false) {}

	int 
	Get_radius_and_update() 
	{ 
		if (timer.Get_now_time())
		{
			timer.Update();
			return radius;
		}
		else
		{
			return 0;
		}
	}

private:

	const int radius;
	Timer timer;
};
