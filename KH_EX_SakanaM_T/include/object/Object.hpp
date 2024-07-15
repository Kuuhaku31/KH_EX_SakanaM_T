
//

#pragma once

#include "Collision.hpp"

#include "MessageSystem.hpp"

class Object : public Position, public Movement
{
	// 为了让Camera能够访问Object的私有成员
	friend class Camera;

public:
	Object(MessageSystem *, Position *p = nullptr, Point = ZEROPOINT, float = 0.0f, Vector = ZEROVECTOR);
	~Object();

	// 更新
	// 传入参数说明：
	// 1、Area指针数组
	// 2、Area指针数组的长度
	// 3、阻力参数
	void Update(Area **, ushort, drag_data);

	// 设置skin
	void SetSkin(Shape *);
	void SetSkin(Shape *, int, int);
	void SetSkin(Shape *, Point);
	void SetSkin(IMAGE *, int, int); // **未实现**
	void SetSkin(IMAGE *, Point);	 // **未实现**
	void SetSkin(Area *);

	// 设置碰撞盒
	void SetHitBox(Shape *);
	void SetHitBox(Shape *, int, int);
	void SetHitBox(Shape *, Point);
	void SetHitBox(IMAGE *, int, int); // **未实现**
	void SetHitBox(IMAGE *, Point);	   // **未实现**
	void SetHitBox(Area *);

	// 设置碰撞检测
	void SetColl(ushort, ushort);

protected:
	// MessageSystem
	MessageSystem *message_system;
	// 发送消息给MessageSystem
	short send_message();

	//  皮肤、碰撞盒、碰撞检测
	Area *main_skin;
	Area *main_hit_box;
	Collision *main_coll;
};
