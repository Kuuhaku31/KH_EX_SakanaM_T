
// 摄像机的类
// 不负责把图像渲染到窗口上

#pragma once

#include "Area.hpp"

class Camera : public Position
{
public:
	Camera();
	Camera(int, int, uint = 0, uint = 0);
	Camera(Point, uint = 0, uint = 0);
	Camera(Position *, int = 0, int = 0, uint = 0, uint = 0);
	Camera(Position *, Point, uint = 0, uint = 0);
	~Camera();

	// 渲染
	void Rending(Area *);

	// 设置镜头参数
	void Sight_size(uint = 0, uint = 0);

private:
	// 视野
	Area sight;
};
