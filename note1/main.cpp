
#include <iostream>

void Fun_0()
{
	int v;
	float a = 4.5, b = 6.9;
	v = (int)(a + b);
	printf("%d\n", v);
}

void fun(unsigned long *a, unsigned long *b)
{
	*a = *a | *b;
}

void Fun_2()
{
	bool b1[25] =
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0};

	bool b2[25] =
		{
			1, 1, 1, 1, 1,
			1, 1, 1, 1, 1,
			1, 1, 1, 1, 1,
			1, 1, 1, 1, 1,
			1, 1, 1, 1, 1};

	// Matrix::Write(b1, 5, 5, 25, b2, 5, 5, 25, 1, 1);
}

float sqrt(float number)
{
	if (number < 0)
		return -1; // 对于负数，返回-1
	if (number == 0 || number == 1)
		return number; // 0和1的平方根是它们自身
	float start = 0, end = number, ans;
	const float epsilon = 0.01; // 定义精度
	while (end - start >= epsilon)
	{
		float mid = (start + end) / 2;
		if (mid * mid == number)
		{
			return mid;
		}
		else if (mid * mid < number)
		{
			start = mid + epsilon;
			ans = mid;
		}
		else
		{
			end = mid - epsilon;
		}
	}
	return ans;
}

int main()
{
	std::cout << "GAME START" << std::endl;
	std::cout << sqrt(3);
	std::cout << "\nGAME OVER!" << std::endl;
	return 0;
}
