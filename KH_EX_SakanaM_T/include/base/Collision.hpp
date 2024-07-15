
// 碰撞检测类
// 用于检测角色是否与墙体或其他角色发生碰撞
// 有8个检测点，分别在角色的四个角和四个边的中点
// 当角色的检测点与墙体或其他角色的检测点重合时，认为发生碰撞
/*
(-w/2,-h/2)------(0,-h/2)-------(w/2,-h/2)
	|               |               |
	|               |               |
(-w/2,0)----------(0,0)-----------(w/2,0)
	|               |               |
	|               |               |
(-w/2,h/2)-------(0,h/2)---------(w/2,h/2)
*/

#pragma once

#include "Movement.hpp"
#include "Area.hpp"

#define COLLFORCE 1000.0f

class Collision : public Position
{
public:
	Collision(Movement *);
	Collision(Movement *, ushort, ushort);
	~Collision();

	// 检测碰撞、更新test_points_value、向Movement发出指令
	void CollUpdate(Area *);

	// 重置检测点的坐标
	void Reset_test_points(ushort, ushort);

	// 获取检测点的值
	uint Get_test_points_value(short i);

private:
	// Movement
	Movement *movement;

	// 	检测点
	Position test_points[8];
	uint test_points_value[8] = {0};
};
