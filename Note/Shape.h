
#pragma once

class Shape
{
public:
	Shape(int w, int h, unsigned long b = 0)
		: shape_wide(w)
		, shape_high(h)
		, shape_size(w * h)
	{
		shape_buffer = new unsigned long[shape_size];
		Clear(b); 
	}
	~Shape() { delete[] shape_buffer; }

	int	Get_shape_wide() const { return shape_wide; }
	int	Get_shape_high() const { return shape_high; }
	int Get_shape_size() const { return shape_size; }

	bool
	Is_in_shape
	(int n) const
	{ return n < 0 || n >= shape_size ? false : shape_buffer[n]; }

	bool
	Is_in_shape
	(int x, int y) const
	{ return Is_in_shape(y * shape_wide + x); }

	unsigned long*
	Get_buffer() const
	{ return shape_buffer; }

	void
	Draw
	(int x, int y, int wide, int high, unsigned long b)
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
	Clear(unsigned long b = 0)
	{
		for (int i = 0; i < shape_size; i++)
		{ shape_buffer[i] = b; }
	}

	void
	Not()
	{
		for (int i = 0; i < shape_size; i++)
		{ shape_buffer[i] = ~shape_buffer[i]; }
	}

	void
	Write(const unsigned long* input, int input_long)
	{
		for (int i = 0; i < input_long; i++)
		{ shape_buffer[i] = input[i] == 0 ? 0 : 0xffffff; }
	}

protected:
	unsigned long* shape_buffer;
	const int shape_wide;
	const int shape_high;
	const int shape_size;
};

