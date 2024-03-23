
#pragma once

#include "Area.h"
#include "Renderer.h"		 

class Map :
    public Area
{   public:
	Map(int w = 0, int h = 0) : Area(w, h) {}

	void 
	INIT_skin
	(
		IMAGE* skin = nullptr
		, int skin_x = 0
		, int skin_y = 0
		, int n = 1
	)
	{
		Renderer* ren = nullptr;

		switch (n)
		{
		case 1: ren = &ren_skin_01; break;
		case 2: ren = &ren_skin_02; break;
		case 3: ren = &ren_skin_03; break;
		}

		ren->Reset_skin(skin);
		ren->Set_position(this, skin_x, skin_y);
	}

	Renderer*
	Get_ren(int n)
	{
		switch (n)
		{
		case 1: return &ren_skin_01;
		case 2: return &ren_skin_02;
		case 3: return &ren_skin_03;
		}
	}


private:

	Renderer ren_skin_01;
	Renderer ren_skin_02;
	Renderer ren_skin_03;

};
