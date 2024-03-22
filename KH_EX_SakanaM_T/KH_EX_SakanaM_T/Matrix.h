
#pragma once

#include <cmath>

template <class T>
class SMatrix
{	public:
	SMatrix
	(
		T* A_b
		, int A_w
		, int A_h

		, T* B_b
		, int B_w
		, int B_h

		, int B_x
		, int B_y

		//, void (*fun_)(T* a, T* b)
	)
	{
		A_buffer = A_b;
		int A_wide = A_w;
		int A_high = A_h;

		B_buffer = B_b;
		int B_wide = B_w;
		int B_high = B_h;

		wide = B_w;
		high = B_h;

		int B_start = 0;
		B_skip = 1;
		int A_start = 0;
		A_skip = 1;

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

		A_n = A_start;
		B_n = B_start;

		//fun = fun_;
	}

	bool
	Update_1(T** a, T** b)
	{
		if (w < wide)
		{
			*a = &A_buffer[A_n];
			*b = &B_buffer[B_n];
			w++;
			A_n++;
			B_n++;
			return true;
		}
		else
		{
			w = 0;
			return false;
		}
	}

	bool
	Update(T** a, T** b)
	{
		//std::
	}

	bool
	Update_(T** a, T** b)
	{
		while (true) 
		{
			if (h < high) 
			{
				int w = 0;
				while (true) 
				{
					if (w < wide) 
					{
						*a = &A_buffer[A_n];
						*b = &B_buffer[B_n];

						B_n++;
						A_n++;
						w++;
					}
					else 
					{
						break;
					}
				}
				B_n += B_skip;
				A_n += A_skip;
				h++;
			}
			else 
			{
				break;
			}
		}
	}

	void
	DO()
	{
		for (int i = 0; i < high; i++, B_n += B_skip, A_n += A_skip)
		{
			for (int j = 0; j < wide; j++, B_n++, A_n++)
			{
				fun(&A_buffer[A_n], &B_buffer[B_n]);
			}
		}
	}

private:
	T* A_buffer;
	T* B_buffer;

	int w = 0;
	int h = 0;

	int wide;
	int high;

	int A_skip;
	int B_skip;

	int A_n;
	int B_n;

	//void (*fun)(T* a, T* b);
};

namespace Matrix
{
	inline static float 
	Q_rsqrt(float number)
	{
		long i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *(long*)&y;									// evil floating point bit level hacking  
		i = 0x5f3759df - (i >> 1);						// what the fuck?  
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y));			// 1st iteration  
		// y = y * ( threehalfs - ( x2 * y * y ) );		// 2nd iteration, this can be removed  

		return y;
	}

	inline static float 
	sqrt_newton(float n)
	{
		float x = n;
		float threshold = 0.01;

		float v = x * x - n;
		//while (0 > v ? -v : v > threshold)
		while (std::abs(x * x - n) > threshold)
		{
			x = (x + n / x) / 2;
		}

		return x;
	}

	inline static bool
	to_unit(float* x, float* y)
	{
		float n = sqrt_newton(*x * *x + *y * *y);
		if (n == 0) 
		{
			return false;
		}
		else
		{
			*x /= n;
			*y /= n;
			return true;
		}
	}

	template <class T> inline void  
	Write
	(
		  T* A_b
		, int A_w
		, int A_h

		, T* B_b
		, int B_w
		, int B_h

		, int B_x
		, int B_y

		, void (*fun)(T* a, T* b)
	)
	{
		T* A_buffer = A_b;
		int A_wide = A_w;
		int A_high = A_h;

		T* B_buffer = B_b;
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
			{ fun(&A_buffer[A_n], &B_buffer[B_n]); }
		}
	}

	template <class T> inline void
		Write_
		(
			T* paper
			, int paper_wide
			, int paper_high
			, int paper_size

			, T* from
			, int from_wide
			, int from_high
			, int from_size

			, int from_x
			, int from_y

			, void (*fun)(T* a, T* b)
		)
	{
		T* write_from_buffer = from;
		int write_from_w = from_wide;
		int write_from_h = from_high;

		T* write_to_buffer = paper;
		int write_to_w = paper_wide;
		int write_to_h = paper_high;

		int w = from_wide;
		int h = from_high;

		int write_from_start = 0;
		int write_from_skip = 1;
		int write_to_start = 0;
		int write_to_skip = 1;

		int R = from_x + from_wide - paper_wide;
		int L = from_x;
		int T = from_y;
		int B = from_y + from_high - paper_high;

		if (R > 0)
		{
			w -= R;
			write_from_skip += R;
		}
		if (R < 0)
		{
			write_to_skip -= R;
		}
		if (L > 0)
		{
			write_to_skip += L;
			write_to_start += L;
		}
		if (L < 0)
		{
			w += L;
			write_from_skip -= L;
			write_from_start -= L;
		}
		if (B > 0)
		{
			h -= B;
		}
		if (T > 0)
		{
			write_to_start += write_to_w * T;
		}
		if (T < 0)
		{
			h += T;
			write_from_start += write_from_w * (-T);
		}

		write_from_skip--;
		write_to_skip--;

		for (int i = 0, write_from_n = write_from_start, write_to_n = write_to_start; i < h; i++, write_from_n += write_from_skip, write_to_n += write_to_skip)
		{
			for (int j = 0; j < w; j++, write_from_n++, write_to_n++)
			{
				fun(&write_to_buffer[write_to_n], &write_from_buffer[write_from_n]);
			}
		}
	}
	
};
