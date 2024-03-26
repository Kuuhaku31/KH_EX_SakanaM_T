
#pragma once

#include "Camera.h"
#include "Area.h"
#include "Renderer.h"		 

class Map : public Area
{	public: friend class World;
	Map(Camera* camera) : Area(), main_camera(camera) {}

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

	void Draw_skin_01() { main_camera->Rending(&ren_skin_01); }
	void Draw_skin_02() { main_camera->Rending(&ren_skin_02); }
	void Draw_skin_03() { main_camera->Rending(&ren_skin_03); }

private:

	Camera* main_camera = nullptr;

	Renderer ren_skin_01;
	Renderer ren_skin_02;
	Renderer ren_skin_03;
};
