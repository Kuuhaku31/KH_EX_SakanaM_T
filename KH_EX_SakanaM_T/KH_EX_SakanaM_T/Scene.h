
#pragma once

#include <graphics.h>

#include "Library.h"
#include "Input.h"
#include "Camera.h"
#include "UI.h"

class Scene
{	public:
	Scene
	(
		   Library* lib
		, Input* inp
		, Camera* cam
		, UI* u
	)
		: library(lib)
		, input(inp)
		, camera(cam)
		, ui(u)
	{}

	virtual void 
	GetInput()
	{

	}

	/*virtual void 
	Update()
	{

	}*/

	virtual void 
	Rending()
	{

	}

	virtual void
	Exit()
	{

	}

protected:

	Library* library = nullptr;
	Input* input = nullptr;
	Camera* camera = nullptr;
	UI* ui = nullptr;
};