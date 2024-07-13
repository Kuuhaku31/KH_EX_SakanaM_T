
#pragma once

#include <graphics.h>

#include "Area.hpp"

class Renderer : public Area
{
public:
	Renderer();
	~Renderer();

	// 重置皮肤
	void Reset_skin(IMAGE * = nullptr);

	// 映射到IMAGE
	void To_IMAGE(IMAGE *);
};
