
#pragma once

#include <random>

#include "Camera.h"
#include "Timer.h"

class Shake
{	public:
	Shake(Camera* camera, int r, int t) : camera(camera), radius(r), now_time(t) {}

	bool
	Update() 
	{ 
		if (0 < now_time)
		{
			now_time--;

			camera->Add_shake(radius);

			return true;
		}
		else
		{
			return false;
		}
	}

private:

	Camera* camera;

	int radius;
	int now_time;
};
