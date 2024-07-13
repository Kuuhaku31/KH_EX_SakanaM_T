
#pragma once

#include <graphics.h>

#include "Shape.hpp"
#include "Position.hpp"

class Area : public Position, public Shape
{
public:
	Area();
	Area(Position *);
	~Area();

	int Local_x(int) const;
	int Local_y(int) const;

	unsigned int In_area(int, int) const;
	unsigned int In_area(Position *) const;
	void Compute(Area *, void(unsigned int *, unsigned int *));

	void Align();
	void Align_x();
	void Align_y();

	// 重置皮肤
	void Reset_skin(IMAGE * = nullptr);
	// 映射到IMAGE
	void To_IMAGE(IMAGE *);
};
