
#pragma once

#include <random>

#include "Matrix.h"

#include "Object.h"

class AI
{	public:
	AI(Object* obj) :obj(obj) {}

	void
	Update(bool b)
	{
		if (b)
		{
			fx = getRandomNumber();
			fy = getRandomNumber();
		}
		if (Matrix::to_unit(&fx, &fy))
		{
			obj->Force(fx * 100, fy * 100);
		}
	}


private:

	Object* obj;

	float fx = 0;
	float fy = 0;

	int
	getRandomNumber(int min = -1000, int max = +1000)
	{
		std::random_device rd;  // 用于获取种子数据
		std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数
		std::uniform_int_distribution<> distr(min, max); // 定义分布规则

		return distr(gen); // 生成在min和max之间的随机整数
	}
};
