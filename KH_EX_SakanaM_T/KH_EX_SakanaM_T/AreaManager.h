
#pragma once

#include "Area.h"
#include "Timer.h"
#include "Ring.h"

class AreaManager
	: public Area
	, public Timer
{	public:
	AreaManager(Area* a) : target_area(a) {}
	
	bool
	Update()
	{
		if (is_not_added)
		{
			is_not_added = false;
			target_area->Add_area(this);
		}
		if (0 == now_time)
		{
  			target_area->Add_area(this, true);
			return false;
		}
		Timer::Update();
		return true;
	}

private:

	bool is_not_added = true;
	Area* target_area;

};
