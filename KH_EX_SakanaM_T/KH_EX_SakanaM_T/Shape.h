
#pragma once

#include "Matrix.h"

class Shape
{
public:
	Shape() {}
	Shape(DWORD* b, int w, int h)
	{
		if (!b) { return; }
		shape_buffer = new DWORD[w * h];
		shape_wide = w;
		shape_high = h;
		shape_long = w * h;
		for (int i = 0; i < shape_long; i++) { shape_buffer[i] = b[i]; }
	}
	Shape(int w, int h, DWORD v = 0x00000000)
	{
		shape_buffer = new DWORD[w * h];
		shape_wide = w;
		shape_high = h;
		shape_long = w * h;
		Clear(v);
	}
	~Shape() { delete[] shape_buffer; }

	int	Get_shape_wide() const { return shape_wide; }
	int	Get_shape_high() const { return shape_high; }
	int Get_shape_long() const { return shape_long; }

	DWORD
	Is_in_shape(int n) const
	{
		return n < 0 || n >= shape_long ? 0 : shape_buffer[n];
	}

	DWORD
	Is_in_shape(int x, int y) const
	{
		return Is_in_shape(y * shape_wide + x);
	}

	DWORD*
	Get_buffer() const
	{
		return shape_buffer;
	}

	int Get_wide() const { return shape_wide; }
	int Get_high() const { return shape_high; }

	void
	Add_shape(Shape* shape, int x, int y, bool is_neg = false)
	{
		if (is_neg)
		{
			Matrix::Write<DWORD>
				(
					shape_buffer
					, shape_wide
					, shape_high

					, shape->shape_buffer
					, shape->shape_wide
					, shape->shape_high

					, x
					, y

					, fun_2
				);
		}
		else
		{
			Matrix::Write<DWORD>
				(
					shape_buffer
					, shape_wide
					, shape_high

					, shape->shape_buffer
					, shape->shape_wide
					, shape->shape_high

					, x
					, y

					, fun_1
				);
		}
	}

	void
	Zero()
	{
		delete[] shape_buffer;
		shape_buffer = nullptr;
		shape_wide = 0;
		shape_high = 0;
		shape_long = 0;
	}

	void
	Draw(int x, int y, int wide, int high, DWORD b)
	{
		if (x < 0) { x = 0; }
		if (y < 0) { y = 0; }
		if (x + wide > shape_wide) { wide = shape_wide - x; }
		if (y + high > shape_high) { high = shape_high - y; }

		int start = y * shape_wide + x;
		int skip = shape_wide - wide;

		for (int i = 0, n = start; i < wide; i++)
		{
			for (int j = 0; j < high; j++, n++)
			{
				shape_buffer[n] = b;
			}
			n += skip;
		}
	}

	void
	Write(const DWORD* b, int w, int h)
	{
		Resize_shape(w, h);
		for (int i = 0; i < shape_long; i++)
		{ shape_buffer[i] = b[i]; }
	}

	void
	Resize_shape(int w, int h)
	{
		if (0 >= w || 0 >= h)
		{
			Zero();
		}
		else
		{
			delete[] shape_buffer;
			shape_buffer = new DWORD[w * h];
			shape_wide = w;
			shape_high = h;
			shape_long = w * h;
		}
	}

	void
	Clear(DWORD b = 0)
	{
		for (int i = 0; i < shape_long; i++)
		{ shape_buffer[i] = b; }
	}

	void
	Clear_shape(DWORD b = 0xffffffff)
	{
		for (int i = 0; i < shape_long; i++)
		{ if (shape_buffer[i]) { shape_buffer[i] = b; } }
	}

	void
	Not()
	{
		for (int i = 0; i < shape_long; i++)
		{
			shape_buffer[i] = ~shape_buffer[i];
		}
	}

	void 
	Fill_circle(int centerX, int centerY, int radius, DWORD value)
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
					if(p >= 0 && p < shape_long)
					{ shape_buffer[p] = value; }
				}
			}
		}
	}

protected:

	DWORD* shape_buffer = nullptr;
	int shape_wide = 0;
	int shape_high = 0;
	int shape_long = 0;

private:
	inline static void fun_1(DWORD* a, DWORD* b) { *a += *b; }
	inline static void fun_2(DWORD* a, DWORD* b) { *a -= *b; }
};

