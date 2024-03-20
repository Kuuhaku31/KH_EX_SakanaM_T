
#pragma once

#include "Position.h"
#include "Renderer.h"

class Target 
	: public Position
{	public:
	Target
	(
		IMAGE* skin = nullptr

		, int x = 0
		, int y = 0
		, Position* pos = nullptr
	)
		: Position(pos, x, y)
		, ren_target(skin, this)
	{
		ren_target.Renderer::Align();
	}

	Renderer ren_target;
	
};
