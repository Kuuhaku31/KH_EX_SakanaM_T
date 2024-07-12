
#pragma once

#include "Shape.hpp"

Shape::Shape() {}
Shape::Shape(const unsigned int *b, int w, int h) { Reset(b, w, h); }
Shape::~Shape() { delete[] shape_buffer; }

int Shape::Wide() const { return shape_wide; }
int Shape::High() const { return shape_high; }
int Shape::Long() const { return shape_long; }

unsigned int Shape::In_shape(int n) const
{
	return n < 0 || n >= shape_long ? 0 : shape_buffer[n];
}

unsigned int Shape::In_shape(int x, int y) const
{
	int n = y * shape_wide + x;
	return n < 0 || n >= shape_long ? 0 : shape_buffer[n];
}

void Shape::Draw_point(int n, unsigned int v)
{
	shape_buffer[n] = v;
}

void Shape::Draw_point(int x, int y, unsigned int v)
{
	int n = y * shape_wide + x;
	if (n >= 0 && n < shape_long)
	{
		shape_buffer[n] = v;
	}
}

inline int abs(int x)
{
	return x < 0 ? -x : x;
}

inline void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

void Shape::Draw_line(int x1, int y1, int x2, int y2, unsigned int v)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (dx == 0 && dy == 0)
	{
		Draw_point(x1, y1, v);
	}
	else if (dx == 0)
	{
		for (int y = y1; y <= y2; y++)
		{
			Draw_point(x1, y, v);
		}
	}
	else if (dy == 0)
	{
		for (int x = x1; x <= x2; x++)
		{
			Draw_point(x, y1, v);
		}
	}
	else
	{
		if (abs(dx) > abs(dy))
		{
			if (x1 > x2)
			{
				swap(x1, x2);
				swap(y1, y2);
			}
			for (int x = x1; x <= x2; x++)
			{
				int y = y1 + dy * (x - x1) / dx;
				Draw_point(x, y, v);
			}
		}
		else
		{
			if (y1 > y2)
			{
				swap(x1, x2);
				swap(y1, y2);
			}
			for (int y = y1; y <= y2; y++)
			{
				int x = x1 + dx * (y - y1) / dy;
				Draw_point(x, y, v);
			}
		}
	}
}

void Shape::Draw_rectangle(int, int, int, int, unsigned int)
{
	// ...
}

void Shape::Draw_circle(int centerX, int centerY, int radius, unsigned int value)
{
	for (int y = -radius; y <= radius; y++)
	{
		for (int x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
			{
				int drawX = centerX + x;
				int drawY = centerY + y;
				int p = drawY * shape_wide + drawX;
				if (p >= 0 && p < shape_long)
				{
					shape_buffer[p] = value;
				}
			}
		}
	}
}

// --------- // shape1缓存区 // shape1宽度 // shape1高度 // shape2缓存区 // shape2宽度 // shape2高度 // shape2左上角x坐标 // shape2左上角y坐标 // 计算函数 //
inline void write(unsigned int *A_b, int A_w, int A_h, unsigned int *B_b, int B_w, int B_h, int B_x, int B_y, void (*fun)(unsigned int *, unsigned int *))
{
	unsigned int *A_buffer = A_b;
	int A_wide = A_w;
	int A_high = A_h;

	unsigned int *B_buffer = B_b;
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
			fun(&A_buffer[A_n], &B_buffer[B_n]);
		}
	}
}

void Shape::Compute(const Shape *, int, int, unsigned int(const unsigned int, const unsigned int))
{
	// ...
}

void Shape::Compute(Shape *s, int x, int y, void f(unsigned int *, unsigned int *))
{
	int shape1_wide = shape_wide;
	int shape1_high = shape_high;
	int shape1_long = shape_long;
	unsigned int *shape1_buffer = shape_buffer;

	int shape2_wide = s->shape_wide;
	int shape2_high = s->shape_high;
	int shape2_long = s->shape_long;
	unsigned int *shape2_buffer = s->shape_buffer;

	write(shape1_buffer, shape1_wide, shape1_high, shape2_buffer, shape2_wide, shape2_high, x, y, f);
}

void Shape::Reset(int w, int h, unsigned int v)
{
	if (0 >= w || 0 >= h)
	{
		delete[] shape_buffer;
		shape_buffer = nullptr;
		shape_wide = 0;
		shape_high = 0;
		shape_long = 0;
	}
	else
	{
		delete[] shape_buffer;
		shape_buffer = new unsigned int[w * h];
		shape_wide = w;
		shape_high = h;
		shape_long = w * h;

		for (int i = 0; i < shape_long; i++)
		{
			shape_buffer[i] = v;
		}
	}
}

void Shape::Reset(const unsigned int *b, int w, int h)
{
	if (b || 0 >= w || 0 >= h)
	{
		delete[] shape_buffer;
		shape_buffer = nullptr;
		shape_wide = 0;
		shape_high = 0;
		shape_long = 0;
	}
	else
	{
		delete[] shape_buffer;
		shape_buffer = new unsigned int[w * h];
		shape_wide = w;
		shape_high = h;
		shape_long = w * h;

		for (int i = 0; i < shape_long; i++)
		{
			shape_buffer[i] = b[i];
		}
	}
}

void Shape::Copy_shape(Shape *s)
{
	shape_wide = s->shape_wide;
	shape_high = s->shape_high;
	shape_long = s->shape_long;
	delete[] shape_buffer;
	shape_buffer = new unsigned int[shape_long];
	for (int i = 0; i < shape_long; i++)
	{
		shape_buffer[i] = s->shape_buffer[i];
	}
}

void Shape::Clear(unsigned int v)
{
	for (int i = 0; i < shape_long; i++)
	{
		shape_buffer[i] = v;
	}
}

void Shape::Clear_shape(unsigned int t, unsigned int f)
{
	for (int i = 0; i < shape_long; i++)
	{
		if (shape_buffer[i])
		{
			shape_buffer[i] = t;
		}
		else
		{
			shape_buffer[i] = f;
		}
	}
}

void Shape::Not()
{
	for (int i = 0; i < shape_long; i++)
	{
		shape_buffer[i] = ~shape_buffer[i];
	}
}
