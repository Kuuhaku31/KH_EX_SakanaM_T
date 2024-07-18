
#include <iostream>

#define uint unsigned int

#define M0M2(m, action)                 \
	transformat(m);                     \
	for (uint i = 0; i < m[5]; i++)     \
	{                                   \
		for (uint j = 0; j < m[4]; j++) \
		{                               \
			action;                     \
			m[0]++;                     \
			m[2]++;                     \
		}                               \
		m[0] += m[1];                   \
		m[2] += m[3];                   \
	}

// --------- // shape1缓存区 // shape1宽度 // shape1高度 // shape2缓存区 // shape2宽度 // shape2高度 // shape2左上角x坐标 // shape2左上角y坐标 // 计算函数 //
inline void write(uint *A_b, int A_w, int A_h, uint *B_b, int B_w, int B_h, int B_x, int B_y, void fun(uint &, uint &))
{
	uint *A_buffer = A_b;
	int A_wide = A_w;
	int A_high = A_h;

	uint *B_buffer = B_b;
	int B_wide = B_w;
	int B_high = B_h;

	int wide = B_w;
	int high = B_h;

	int B_start = 0;
	int B_skip = 1;
	int A_start = 0;
	int A_skip = 1;

	int R = B_x + B_wide - A_wide;
	int L = B_x;
	int T = B_y;
	int B = B_y + B_high - A_high;

	if (R > 0)
	{
		wide -= R;
		B_skip += R;
	}
	if (R < 0)
	{
		A_skip -= R;
	}
	if (L > 0)
	{
		A_skip += L;
		A_start += L;
	}
	if (L < 0)
	{
		wide += L;
		B_skip -= L;
		B_start -= L;
	}
	if (B > 0)
	{
		high -= B;
	}
	if (T > 0)
	{
		A_start += A_w * T;
	}
	if (T < 0)
	{
		high += T;
		B_start += B_w * (-T);
	}

	A_skip--;
	B_skip--;

	for (int i = 0, B_n = B_start, A_n = A_start; i < high; i++, B_n += B_skip, A_n += A_skip)
	{
		for (int j = 0; j < wide; j++, B_n++, A_n++)
		{
			fun(A_buffer[A_n], B_buffer[B_n]);
		}
	}

	// for (uint i = 0; i < high; i++)
	// {
	// 	for (uint j = 0; j < wide; j++)
	// 	{
	// 		// action;
	// 		A_n++;
	// 		B_n++;
	// 	}
	// 	A_n += A_skip;
	// 	B_n += B_skip;
	// }
}

inline void transformat(int *m) // 长度为6
{
	/*
	56 0 0 1 8 -2

	A的宽度0
	A的高度1
	B的宽度2
	B的高度3
	B的左上角相对于A的左上角的x坐标4
	B的左上角相对于A的左上角的y坐标5

		||
		\/

	A的起始点
	A的间隔
	B的起始点
	B的间隔
	宽度
	次数
	*/

	int A_start = 0;
	int A_skip = 0;
	int B_start = 0;
	int B_skip = 0;

	int wide = m[2];
	int high = m[3];

	int R = m[4] + m[2] - m[0];
	int L = m[4];
	int T = m[5];
	int B = m[5] + m[3] - m[1];

	if (R > 0)
	{
		wide -= R;
		B_skip += R;
	}
	if (R < 0)
	{
		A_skip -= R;
	}
	if (L > 0)
	{
		A_skip += L;
		A_start += L;
	}
	if (L < 0)
	{
		wide += L;
		B_skip -= L;
		B_start -= L;
	}
	if (B > 0)
	{
		high -= B;
	}
	if (T > 0)
	{
		A_start += m[0] * T;
	}
	if (T < 0)
	{
		high += T;
		B_start -= m[2] * T;
	}

	m[0] = A_start;
	m[1] = A_skip;
	m[2] = B_start;
	m[3] = B_skip;
	m[4] = wide;
	m[5] = high;
}

inline void printM(uint *m, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			std::cout << m[i * w + j] << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	std::cout << "GAME START\n"
			  << std::endl;

	int m1_w = 8;
	int m1_h = 5;
	uint m1[40] = {
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0};

	int m2_w = 9;
	int m2_h = 6;
	uint m2[54] = {
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1};

	printM(m1, m1_w, m1_h);
	std::cout << std::endl;
	printM(m2, m2_w, m2_h);

	int m[6] = {m1_w, m1_h, m2_w, m2_h, 0, 7};

	// M0M2(m, );

	transformat(m);

	for (int i = 0; i < 6; i++)
	{
		std::cout << m[i] << " ";
	}

	for (int i = 0; i < m[5]; i++)
	{
		for (int j = 0; j < m[4]; j++)
		{
			m1[m[0]] = m1[m[0]] + m2[m[2]];
			m[0]++;
			m[2]++;
		}
		m[0] += m[1];
		m[2] += m[3];
	}

	// write(m1, m1_w, m1_h, m2, m2_w, m2_h, 0, 7, [](uint &a, uint &b)
	// 	  { a = a + b; });

	std::cout << std::endl;
	printM(m1, m1_w, m1_h);

	std::cout << "\nGAME OVER!" << std::endl;
	return 0;
}
