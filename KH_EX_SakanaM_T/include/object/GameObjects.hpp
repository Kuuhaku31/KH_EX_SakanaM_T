
#pragma once

#include "MessageSystem.hpp"

class GameObject : public Object
{
public:
	GameObject(MessageSystem *, Zone *, Point = ZEROPOINT, float = 0.0f, Vector = ZEROVECTOR);
	~GameObject();

	// 更新
	void GameObjectUpdate();

protected:
	MessageSystem *message_system;
};

// 摄像机的类
// 不负责把图像渲染到窗口上

class Camera : public GameObject
{
public:
	Camera(MessageSystem *, Zone *p, Point = ZEROPOINT, uint = 0, uint = 0);
	~Camera();

	// 渲染
	void Rending(Area *);
	void RendingObject(Object *, ObjectAreaType = skin01);
	void RendingZone(Zone *, ZoneAreaType = main_area);

	// 清屏
	void Clearsight();

	// 设置镜头参数
	void Sight_size(uint = 0, uint = 0);
	void Sight_align(bool = true);

	// 把当前画面发送给MessageSystem
	void SendToMessageSystem(ShapeType);
};
