
#pragma once

#include <math.h>

#include "Position.h"

class Movement
{	public:
	Movement() {}

	void
	Update(float f)
	{
		update_drag(f);

		float xd = mov_vx * DT____;
		float yd = mov_vy * DT____;

		int xi = (int)xd;
		int yi = (int)yd;

		bufr_x += xd - xi;
		bufr_y += yd - yi;

		if (bufr_x > 1.0f)
		{
			xi++; bufr_x -= 1.0f;
		}
		else if (bufr_x < -1.0f)
		{
			xi--; bufr_x += 1.0f;
		}
		if (bufr_y > 1.0f)
		{
			yi++; bufr_y -= 1.0f;
		}
		else if (bufr_y < -1.0f)
		{
			yi--; bufr_y += 1.0f;
		}

		pos->Move(xi, yi);

		mov_vx += mov_ax * DT____;
		mov_vy += mov_ay * DT____;

		mov_ax = 0.0f;
		mov_ay = 0.0f;
	}

	float  Get_mov_m() const { return mov__m; }
	float Get_mov_vx() const { return mov_vx; }
	float Get_mov_vy() const { return mov_vy; }
	float Get_mov_ax() const { return mov_ax; }
	float Get_mov_ay() const { return mov_ay; }
	void Get_mov_v(float& vx, float& vy) const { vx = mov_vx; vy = mov_vy; }
	void Get_mov_a(float& ax, float& ay) const { ax = mov_ax; ay = mov_ay; }

	void Force(float fx, float fy)
	{
		if (mov__m <= 0) { return; }
		mov_ax += fx / mov__m; mov_ay += fy / mov__m;
	}

	void Stop() { mov_vx = mov_vy = 0.0; }
	void Stop_mov_x() { mov_vx /= 16; }
	void Stop_mov_y() { mov_vy /= 16; }
	void Reset_mov_v(float vx, float vy) { mov_vx = vx; mov_vy = vy; }

	void Set_mov_m(float m) { mov__m = m; }
	void Set_pos(Position* p) { pos = p; }

	void
	Copy_value(Movement* m)
	{
		DT____ = m->DT____; 
		mov__m = m->mov__m; 

		bufr_x = m->bufr_x; 
		bufr_y = m->bufr_y; 

		mov_vx = m->mov_vx; 
		mov_vy = m->mov_vy; 
		mov_ax = m->mov_ax; 
		mov_ay = m->mov_ay; 

		drag_u = m->drag_u; 
		drag_f = m->drag_f; 
		drag_c = m->drag_c; 
		drag_r = m->drag_r;
	}

private:
	Position* pos = nullptr;

	float DT____ = 0.1;
	float mov__m = 0;

	float bufr_x = 0;
	float bufr_y = 0;

	float mov_vx = 0;
	float mov_vy = 0;

	float mov_ax = 0;
	float mov_ay = 0;

	float drag_u = 0.0;
	float drag_f = 0.0;
	float drag_c = 0.0;
	float drag_r = 0.0;

	inline void
	update_drag(float area_drag)
	{
		if (0.0 == mov_vx && 0.0 == mov_vy) { return; }
		float v_mod = sqrt(mov_vx * mov_vx + mov_vy * mov_vy);

		float fforce_1 = drag_u;
		float fforce_2 = v_mod * v_mod * drag_c;

		if (mov__m > 0.0)
		{
			fforce_1 *= (drag_f / mov__m);
			fforce_2 *= (drag_r / mov__m);
		}
		float v_mod_ = v_mod - (fforce_1 + fforce_2) * area_drag / 10000.0;

		if (v_mod_ < 0.0)
		{
			mov_vx = 0;
			mov_vy = 0;
		}
		else
		{
			mov_vx *= v_mod_ / v_mod;
			mov_vy *= v_mod_ / v_mod;
		}
	}
};
