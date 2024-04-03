
#pragma once

#include <cmath>





//=======================================================//
namespace Toolf
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

	inline static bool
	to_unit(float* x, float* y)
	{
		float n = sqrt(*x * *x + *y * *y);
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
		  T* A_b	, int A_w	, int A_h
		, T* B_b	, int B_w	, int B_h
		, int B_x	, int B_y
		, void(*fun)(T*, T*)
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

class Point
{
public:
	Point() {}
	~Point() {}

private:

};


template <class T>
class Matrix
{	public:
	Matrix() {}
	~Matrix() { delete[] matrix_buffer; }

	T* In_matrix(int n) { return n < 0 || n >= matrix_long ? 0 : &matrix_buffer[n]; }
	T* In_matrix(int x, int y) { return In_matrix(y * matrix_wide + x); }
	T* Get_buffer()		  { return matrix_buffer; }
	int	Get_matrix_wide() { return matrix_wide; }
	int	Get_matrix_high() { return matrix_high; }
	int Get_matrix_long() { return matrix_long; }



	void
		Add_matrix(Matrix* matrix, int x, int y, bool is_neg = false)
	{
		if (is_neg)
		{
			Toolf::Write<unsigned long>
				(
					matrix_buffer
					, matrix_wide
					, matrix_high

					, matrix->matrix_buffer
					, matrix->matrix_wide
					, matrix->matrix_high

					, x
					, y

					, fun_2
				);
		}
		else
		{
			Toolf::Write<unsigned long>
				(
					matrix_buffer
					, matrix_wide
					, matrix_high

					, matrix->matrix_buffer
					, matrix->matrix_wide
					, matrix->matrix_high

					, x
					, y

					, fun_1
				);
		}
	}

	void
		Write_on(int x, int y, int wide, int high, unsigned long b)
	{
		if (x < 0) { x = 0; }
		if (y < 0) { y = 0; }
		if (x + wide > matrix_wide) { wide = matrix_wide - x; }
		if (y + high > matrix_high) { high = matrix_high - y; }

		int start = y * matrix_wide + x;
		int skip = matrix_wide - wide;

		for (int i = 0, n = start; i < wide; i++)
		{
			for (int j = 0; j < high; j++, n++)
			{
				matrix_buffer[n] = b;
			}
			n += skip;
		}
	}

	void
		Resize_matrix(int w, int h)
	{
		if (0 >= w || 0 >= h)
		{
			delete[] matrix_buffer;
			matrix_buffer = nullptr;
			matrix_wide = 0;
			matrix_high = 0;
			matrix_long = 0;
		}
		else
		{
			delete[] matrix_buffer;
			matrix_buffer = new T[w * h];
			matrix_wide = w;
			matrix_high = h;
			matrix_long = w * h;
		}
	}

	void
		Copy_matrix(Matrix* s)
	{
		matrix_wide = s->matrix_wide;
		matrix_high = s->matrix_high;
		matrix_long = s->matrix_long;
		delete[] matrix_buffer;
		matrix_buffer = new T[matrix_long];
		for (int i = 0; i < matrix_long; i++)
		{
			matrix_buffer[i] = s->matrix_buffer[i];
		}
	}

protected:

	T* matrix_buffer = nullptr;
	int matrix_wide = 0;
	int matrix_high = 0;
	int matrix_long = 0;

private:
	inline static void fun_1(unsigned long* a, unsigned long* b) { *a += *b; }
	inline static void fun_2(unsigned long* a, unsigned long* b) { *a -= *b; }
};


