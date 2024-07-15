
// Movement.hpp
// Movement类
// 用于指导物体的运动

#pragma once

#include "Vector.hpp"

// 阻力参数
struct drag_data
{
	// 阻力参数
	float drag_u = 0.0;
	float drag_f = 0.0;
	float drag_c = 0.0;
	float drag_r = 0.0;

	float area_drag = 0.0;
};

class Movement
{
public:
	Movement(Position *);
	Movement(Position *, float = 0.0f, Vector = ZEROVECTOR);
	~Movement();

	// 更新运动状态
	void Update(drag_data);

	// 更改物体的运动参数
	void ResetDT(float = 0.1f);
	void ResetMass(float = 0.0f);

	void ResetVelocity(Vector = ZEROVECTOR);
	void ResetVelocity_x(float = 0.0f);
	void ResetVelocity_y(float = 0.0f);
	void AddVelocity(Vector);

	void ResetAcceleration(Vector = ZEROVECTOR);
	void ResetAcceleration_x(float = 0.0f);
	void ResetAcceleration_y(float = 0.0f);
	void AddAcceleration(Vector);

	void AddForce(Vector);

	// 获取物体的运动参数
	float GetDT();
	float GetMass();
	Vector GetVelocity();
	Vector GetAcceleration();

private:
	friend class Collision;
	// 附着的Position类
	Position *position;

	float DT;	  // 时间间隔
	float mass;	  // 质量
	Vector buf_p; // 位置缓冲
	Vector mov_v; // 速度
	Vector mov_a; // 加速度
};
