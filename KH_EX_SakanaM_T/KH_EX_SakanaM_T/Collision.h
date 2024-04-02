
#pragma once

#include "Position.h"
#include "Movement.h"
#include "Area.h"

class Collision
{	public:
	Collision() {}

	bool
	Update(Position* pos, Movement* mov, Area* wall_area, Area* coll_area)
	{
		update_test_points(pos);
		return test_area(pos, mov, wall_area, coll_area);
	}

	void
	Set(int coll_wide, int coll_high)
	{
		int half_wide = coll_wide / 2;
		int half_high = coll_high / 2;
		int quarter_wide = coll_wide / 4;
		int quarter_high = coll_high / 4;

		_tp_01_dx = -quarter_wide;
		_tp_01_dy = -half_high;

		_tp_02_dx = 0;
		_tp_02_dy = -half_high;

		_tp_03_dx = +quarter_wide;
		_tp_03_dy = -half_high;

		_tp_04_dx = +half_wide;
		_tp_04_dy = -quarter_high;

		_tp_05_dx = +half_wide;
		_tp_05_dy = 0;

		_tp_06_dx = +half_wide;
		_tp_06_dy = +quarter_high;

		_tp_07_dx = +quarter_wide;
		_tp_07_dy = +half_high;

		_tp_08_dx = 0;
		_tp_08_dy = +half_high;

		_tp_09_dx = -quarter_wide;
		_tp_09_dy = +half_high;

		_tp_10_dx = -half_wide;
		_tp_10_dy = +quarter_high;

		_tp_11_dx = -half_wide;
		_tp_11_dy = 0;

		_tp_12_dx = -half_wide;
		_tp_12_dy = -quarter_high;
	}

private:

	int _tp_01_dx = 0;
	int _tp_01_dy = 0;
				  
	int _tp_02_dx = 0;
	int _tp_02_dy = 0;
				
	int _tp_03_dx = 0;
	int _tp_03_dy = 0;
				 
	int _tp_04_dx = 0;
	int _tp_04_dy = 0;
				 
	int _tp_05_dx = 0;
	int _tp_05_dy = 0;
				
	int _tp_06_dx = 0;
	int _tp_06_dy = 0;
				
	int _tp_07_dx = 0;
	int _tp_07_dy = 0;
				
	int _tp_08_dx = 0;
	int _tp_08_dy = 0;
				 
	int _tp_09_dx = 0;
	int _tp_09_dy = 0;
				
	int _tp_10_dx = 0;
	int _tp_10_dy = 0;
				 
	int _tp_11_dx = 0;
	int _tp_11_dy = 0;
				
	int _tp_12_dx = 0;
	int _tp_12_dy = 0;

	int test_point_01_x = 0;
	int test_point_01_y = 0;

	int test_point_02_x = 0;
	int test_point_02_y = 0;

	int test_point_03_x = 0;
	int test_point_03_y = 0;

	int test_point_04_x = 0;
	int test_point_04_y = 0;

	int test_point_05_x = 0;
	int test_point_05_y = 0;

	int test_point_06_x = 0;
	int test_point_06_y = 0;

	int test_point_07_x = 0;
	int test_point_07_y = 0;

	int test_point_08_x = 0;
	int test_point_08_y = 0;

	int test_point_09_x = 0;
	int test_point_09_y = 0;

	int test_point_10_x = 0;
	int test_point_10_y = 0;

	int test_point_11_x = 0;
	int test_point_11_y = 0;

	int test_point_12_x = 0;
	int test_point_12_y = 0;

	inline void
	update_test_points(Position* pos)
	{
		int x = pos->Get_x();
		int y = pos->Get_y();

		test_point_01_x = x + _tp_01_dx;
		test_point_01_y = y + _tp_01_dy;

		test_point_02_x = x + _tp_02_dx;
		test_point_02_y = y + _tp_02_dy;

		test_point_03_x = x + _tp_03_dx;
		test_point_03_y = y + _tp_03_dy;

		test_point_04_x = x + _tp_04_dx;
		test_point_04_y = y + _tp_04_dy;

		test_point_05_x = x + _tp_05_dx;
		test_point_05_y = y + _tp_05_dy;

		test_point_06_x = x + _tp_06_dx;
		test_point_06_y = y + _tp_06_dy;

		test_point_07_x = x + _tp_07_dx;
		test_point_07_y = y + _tp_07_dy;

		test_point_08_x = x + _tp_08_dx;
		test_point_08_y = y + _tp_08_dy;

		test_point_09_x = x + _tp_09_dx;
		test_point_09_y = y + _tp_09_dy;

		test_point_10_x = x + _tp_10_dx;
		test_point_10_y = y + _tp_10_dy;

		test_point_11_x = x + _tp_11_dx;
		test_point_11_y = y + _tp_11_dy;

		test_point_12_x = x + _tp_12_dx;
		test_point_12_y = y + _tp_12_dy;
	}

	inline bool
		test_area(Position* pos, Movement* mov, Area* wall_area, Area* coll_area)
	{
		float F_1 = 200;
		float F_2 = 1000;

		float force_x = 0.0;
		float force_y = 0.0;

		int move_x = 0;
		int move_y = 0;

		int w = 0;
		if (wall_area)
		{
			if
				(
					wall_area->Is_in_area(test_point_01_x, test_point_01_y)
					|| wall_area->Is_in_area(test_point_02_x, test_point_02_y)
					|| wall_area->Is_in_area(test_point_03_x, test_point_03_y)
					)
			{
				force_y += F_2;
				move_y += 1;
				w++;
			}

			if
				(
					wall_area->Is_in_area(test_point_04_x, test_point_04_y)
					|| wall_area->Is_in_area(test_point_05_x, test_point_05_y)
					|| wall_area->Is_in_area(test_point_06_x, test_point_06_y)
					)
			{
				force_x -= F_2;
				move_x -= 1;
				w++;
			}

			if
				(
					wall_area->Is_in_area(test_point_07_x, test_point_07_y)
					|| wall_area->Is_in_area(test_point_08_x, test_point_08_y)
					|| wall_area->Is_in_area(test_point_09_x, test_point_09_y)
					)
			{
				force_y -= F_2;
				move_y -= 1;
				w++;
			}

			if
				(
					wall_area->Is_in_area(test_point_10_x, test_point_10_y)
					|| wall_area->Is_in_area(test_point_11_x, test_point_11_y)
					|| wall_area->Is_in_area(test_point_12_x, test_point_12_y)
					)
			{
				force_x += F_2;
				move_x += 1;
				w++;
			}

			if (4 <= w) { return 0; }
		}

		int a = coll_area->Is_in_area(test_point_01_x, test_point_01_y) + coll_area->Is_in_area(test_point_02_x, test_point_02_y) + coll_area->Is_in_area(test_point_03_x, test_point_03_y);
		int b1 = coll_area->Is_in_area(test_point_04_x, test_point_04_y) + coll_area->Is_in_area(test_point_05_x, test_point_05_y) + coll_area->Is_in_area(test_point_06_x, test_point_06_y);
		int c = coll_area->Is_in_area(test_point_07_x, test_point_07_y) + coll_area->Is_in_area(test_point_08_x, test_point_08_y) + coll_area->Is_in_area(test_point_09_x, test_point_09_y);
		int d = coll_area->Is_in_area(test_point_10_x, test_point_10_y) + coll_area->Is_in_area(test_point_11_x, test_point_11_y) + coll_area->Is_in_area(test_point_12_x, test_point_12_y);

		if (1500 <= a + b1 + c + d) { return 0; }

		force_y += a;
		force_x -=b1;
		force_y -=c;
		force_x +=d;

		/*if
		(
			   coll_area->Is_in_area(test_point_01_x, test_point_01_y)
			|| coll_area->Is_in_area(test_point_02_x, test_point_02_y)
			|| coll_area->Is_in_area(test_point_03_x, test_point_03_y)
		)
		{
			force_y += F_1;
		}

		if
		(
			   coll_area->Is_in_area(test_point_04_x, test_point_04_y)
			|| coll_area->Is_in_area(test_point_05_x, test_point_05_y)
			|| coll_area->Is_in_area(test_point_06_x, test_point_06_y)
		)
		{
			force_x -= F_1;
		}

		if
		(
			   coll_area->Is_in_area(test_point_07_x, test_point_07_y)
			|| coll_area->Is_in_area(test_point_08_x, test_point_08_y)
			|| coll_area->Is_in_area(test_point_09_x, test_point_09_y)
		)
		{
			force_y -= F_1;
		}

		if
		(
			   coll_area->Is_in_area(test_point_10_x, test_point_10_y)
			|| coll_area->Is_in_area(test_point_11_x, test_point_11_y)
			|| coll_area->Is_in_area(test_point_12_x, test_point_12_y)
		)
		{
			force_x += F_1;
		}*/

		bool b = false;

		if (move_x) { mov->Stop_mov_x(); b = 1; }
		if (move_y) { mov->Stop_mov_y(); b = 1; }

		mov->Force(force_x, force_y);
		pos->Move(move_x, move_y);

		return 1;
	}
};
