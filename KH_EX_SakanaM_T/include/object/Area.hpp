
#pragma once

#include "Position.hpp"
#include "Shape.hpp"

class Area : public Position, public Shape
{
public:
	Area();
	Area(int, int, uint = 0, uint = 0);
	Area(Point, uint = 0, uint = 0); // 坐标，宽高
	Area(Position *);
	Area(Position *, int, int, uint = 0, uint = 0);
	Area(Position *, Point, uint = 0, uint = 0);
	~Area();

	// 转换到本地坐标
	int Area_local_x(int) const;
	int Area_local_y(int) const;
	Point Area_local(Point) const;

	// 给坐标获取某个点的值
	uint Area_in(int, int) const;
	uint Area_in(Point) const;
	uint Area_in(Position *) const;

	// 计算
	void Area_compute(Area *, void f(uint &, uint &));

	// 对齐
	void Area_align();
	void Area_align_x();
	void Area_align_y();
};
