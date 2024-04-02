
#pragma once

#include <random>

#include "Camera.h"
#include "Timer.h"

extern Camera main_camera;

class Shake
{	public:
	Shake(int r, int t) : radius(r), now_time(t) {}

	bool
	Update() 
	{ 
		if (0 < now_time)
		{
			now_time--;

			main_camera.Add_shake(radius);

			return true;
		}
		else
		{
			return false;
		}
	}

private:

	int radius;
	int now_time;
};
