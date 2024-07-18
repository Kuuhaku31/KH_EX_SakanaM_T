
#pragma once

#include "MessageSystem.hpp"

class GameObject : public Object
{
public:
	GameObject(MessageSystem *, Zone *, Point = ZEROPOINT, float = 0.0f, Vector = ZEROVECTOR);
	~GameObject();

	// 更新
	// 返回值为0时表示需要摧毁这个对象
	char GameObjectUpdate();

protected:
	MessageSystem *message_system;
	Zone *zone;
};

// 摄像机的类
// 不负责把图像渲染到窗口上

class Camera : public GameObject
{
public:
	Camera(MessageSystem *, Zone *, Point = ZEROPOINT, int = 0, int = 0);
	~Camera();

	// 渲染
	void Rending(Area *);
	void RendingObject(Object *, ObjectAreaType = skin01);
	void RendingZone(Zone *, ZoneAreaType = main_area);

	// 清屏
	void Clearsight();

	// 设置镜头参数
	void Sight_size(int = 0, int = 0);
	void Sight_align(bool = true);

	// 把当前画面发送给MessageSystem
	void SendToMessageSystem(ShapeType);
};
