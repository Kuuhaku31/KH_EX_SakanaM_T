
#pragma once

#include <graphics.h>

#include "Area.hpp"

class Renderer : public Area
{
public:
	Renderer();
	~Renderer();

	void Reset_skin(IMAGE * = nullptr);
};
