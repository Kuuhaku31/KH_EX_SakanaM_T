
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
	)
		: library(lib)
		, input(inp)
		, camera(cam)
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
};