
// 摄像机的类
// 不负责把图像渲染到窗口上

#pragma once

#include "Object.hpp"

class Camera : public Object
{
public:
	Camera(MessageSystem *, Position *p = nullptr, Point = ZEROPOINT, uint = 0, uint = 0);
	~Camera();

	// 渲染
	void Rending(Area *);
	void RendingObject(Object *);

	// 清屏
	void Clearsight();

	// 设置镜头参数
	void Sight_size(uint = 0, uint = 0);
	void Sight_align(bool = true);

	// 把当前画面发送给MessageSystem
	void SendToMessageSystem(ShapeType);

private:
	// 视野
	Area *sight;
};
