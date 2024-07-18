
#include "base.hpp"

Shape::Shape(uint w, uint h, uint v)
{
	if (0 >= w || 0 >= h)
	{
		shape_buffer = nullptr;
		shape_wide = 0;
		shape_high = 0;
		shape_long = 0;
	}
	else
	{
		shape_buffer = new uint[w * h];
		shape_wide = w;
		shape_high = h;
		shape_long = w * h;

		for (int i = 0; i < shape_long; i++)
		{
			shape_buffer[i] = v;
		}
	}
}

Shape::Shape(const uint *b, uint w, uint h)
{
	if (!b || 0 >= w || 0 >= h)
	{
		shape_buffer = nullptr;
		shape_wide = 0;
		shape_high = 0;
		shape_long = 0;
	}
	else
	{
		shape_buffer = new uint[w * h];
		shape_wide = w;
		shape_high = h;
		shape_long = w * h;

		for (int i = 0; i < shape_long; i++)
		{
			shape_buffer[i] = b[i];
		}
	}
}

Shape::~Shape()
{
	if (shape_buffer)
	{
		delete[] shape_buffer;
	}
}

uint Shape::Shape_wide() const { return shape_wide; }
uint Shape::Shape_high() const { return shape_high; }
uint Shape::Shape_long() const { return shape_long; }
uint *Shape::Shape_buffer() { return shape_buffer; }

uint Shape::Shape_in(uint n) const
{
	return n < 0 || n >= shape_long ? 0 : shape_buffer[n];
}

uint Shape::Shape_in(int x, int y) const
{
	if (x >= 0 && x < shape_wide && y >= 0 && y < shape_high)
	{
		return shape_buffer[y * shape_wide + x];
	}
	else
	{
		return 0;
	}
}

void Shape::Shape_draw_point(int n, uint v)
{
	if (n >= 0 && n < shape_long)
	{
		shape_buffer[n] = v;
	}
}

void Shape::Shape_draw_point(int x, int y, uint v)
{
	if (x >= 0 && x < shape_wide && y >= 0 && y < shape_high)
	{
		shape_buffer[y * shape_wide + x] = v;
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

void Shape::Shape_draw_line(int x1, int y1, int x2, int y2, uint v)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (dx == 0 && dy == 0)
	{
		Shape_draw_point(x1, y1, v);
	}
	else if (dx == 0)
	{
		for (int y = y1; y <= y2; y++)
		{
			Shape_draw_point(x1, y, v);
		}
	}
	else if (dy == 0)
	{
		for (int x = x1; x <= x2; x++)
		{
			Shape_draw_point(x, y1, v);
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
				Shape_draw_point(x, y, v);
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
				Shape_draw_point(x, y, v);
			}
		}
	}
}

void Shape::Shape_draw_rectangle(int, int, int, int, uint)
{
	// ...
}

void Shape::Shape_draw_circle(int centerX, int centerY, int radius, uint value)
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
}

void Shape::Shape_compute(Shape *s, int x, int y, void f(uint &, uint &))
{
	int shape1_wide = shape_wide;
	int shape1_high = shape_high;
	int shape1_long = shape_long;
	uint *shape1_buffer = shape_buffer;

	int shape2_wide = s->shape_wide;
	int shape2_high = s->shape_high;
	int shape2_long = s->shape_long;
	uint *shape2_buffer = s->shape_buffer;

	write(shape1_buffer, shape1_wide, shape1_high, shape2_buffer, shape2_wide, shape2_high, x, y, f);
}

void Shape::Shape_reset(uint w, uint h, uint v)
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
		shape_buffer = new uint[w * h];
		shape_wide = w;
		shape_high = h;
		shape_long = w * h;

		for (int i = 0; i < shape_long; i++)
		{
			shape_buffer[i] = v;
		}
	}
}

void Shape::Shape_reset(const uint *b, uint w, uint h)
{
	if (!b || 0 >= w || 0 >= h)
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
		shape_buffer = new uint[w * h];
		shape_wide = w;
		shape_high = h;
		shape_long = w * h;

		for (int i = 0; i < shape_long; i++)
		{
			shape_buffer[i] = b[i];
		}
	}
}

void Shape::Shape_copy(Shape *s)
{
	shape_wide = s->shape_wide;
	shape_high = s->shape_high;
	shape_long = s->shape_long;
	delete[] shape_buffer;
	shape_buffer = new uint[shape_long];
	for (int i = 0; i < shape_long; i++)
	{
		shape_buffer[i] = s->shape_buffer[i];
	}
}

void Shape::Shape_clear(uint v)
{
	for (int i = 0; i < shape_long; i++)
	{
		shape_buffer[i] = v;
	}
}

void Shape::Shape_clear(uint t, uint f)
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

void Shape::Shape_not()
{
	for (int i = 0; i < shape_long; i++)
	{
		shape_buffer[i] = ~shape_buffer[i];
	}
}
