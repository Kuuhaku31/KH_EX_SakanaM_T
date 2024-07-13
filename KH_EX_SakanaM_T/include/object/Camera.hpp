
// 用于处理摄像机的类
// 不负责把图像渲染到窗口上（去找MessageSystem）
// 负责处理摄像机的位置，视野大小，摄像机震动等

#pragma once

#include "Renderer.hpp"

class Camera : public Area
{
public:
	Camera();
	~Camera();

	// 调整视野大小
	void Tweaks_sight(int dw, int dh);

	void Rending(Renderer *ren);

	int Mouse_X(int x);
	int Mouse_Y(int y);

private:
	// 视野缩放系数
	float kx = 1.0;
	float ky = 1.0;
};
