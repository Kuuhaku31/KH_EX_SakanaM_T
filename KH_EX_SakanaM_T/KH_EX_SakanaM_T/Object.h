
#pragma once

#include <math.h>
#include "Position.h"
#include "Area.h"

class Object : public Position
{	public:
	Object(Area* area) : Position(), drag_area(area) {};
	Object(Area* area, int x, int y) : Position(x, y), drag_area(area) {};
	
	double  Get_obj_m() const { return obj_m; }
	double Get_obj_vx() const { return obj_vx; }
	double Get_obj_vy() const { return obj_vy; }
	double Get_obj_ax() const { return obj_ax; }
	double Get_obj_ay() const { return obj_ay; }
	void Get_obj_v(double& vx, double& vy) const { vx = obj_vx; vy = obj_vy; }
	void Get_obj_a(double& ax, double& ay) const { ax = obj_ax; ay = obj_ay; }
	
	void Set_obj_m(double m) { obj_m = m; }

	void
	Set_drag(double u = 0.0, double f = 0.0, double c = 0.0, double r = 0.0)
	{
		_u = u;
		_f = f;
		_c = c;
		_r = r;
	}

	void Force(double fx, double fy) 
	{ 
		if (obj_m <= 0) { return; }
		obj_ax += fx / obj_m; obj_ay += fy / obj_m; 
	}

	void Stop() { obj_vx = obj_vy = 0.0; }
	void Stop_obj_x() { obj_vx /= 16; }
	void Stop_obj_y() { obj_vy /= 16; }
	void Reset_obj_v(double vx, double vy) { obj_vx = vx; obj_vy = vy; }

	virtual bool 
	Update()
	{
		update_drag();

		double xd = obj_vx * DT;
		double yd = obj_vy * DT;

		int xi = (int)xd;
		int yi = (int)yd;

		buffer_x += xd - xi;
		buffer_y += yd - yi;

		if (buffer_x > 1.0) { xi++; buffer_x -= 1.0; }
		else if (buffer_x < -1.0) { xi--; buffer_x += 1.0; }
		if (buffer_y > 1.0) { yi++; buffer_y -= 1.0; }
		else if (buffer_y < -1.0) { yi--; buffer_y += 1.0; }

		Position::Move(xi, yi);

		obj_vx += obj_ax * DT;
		obj_vy += obj_ay * DT;

		obj_ax = 0.0;
		obj_ay = 0.0;

		return true;
	}

protected:

	Area* drag_area = nullptr;

	double  DT = 0.1;
	double  obj_m = 0;

	double buffer_x = 0;
	double buffer_y = 0;

	double obj_vx = 0;
	double obj_vy = 0;
				  
	double obj_ax = 0;
	double obj_ay = 0;

	double _u = 0.0;
	double _f = 0.0;
	double _c = 0.0;
	double _r = 0.0;

	inline void
	update_drag()
	{
		double v_mod = sqrt(obj_vx * obj_vx + obj_vy * obj_vy);
		if (0.0 == v_mod) { return; }

		double fforce_1 = _u;
		double fforce_2 = v_mod * v_mod * _c;

		if (obj_m > 0.0)
		{
			fforce_1 *= (_f / obj_m);
			fforce_2 *= (_r / obj_m);
		}
		double v_mod_ = v_mod - (fforce_1 + fforce_2) * drag_area->Is_in_area(Get_x(), Get_y()) / 10000.0;

		if (v_mod_ < 0.0)
		{
			obj_vx = 0;
			obj_vy = 0;
		}
		else
		{
			obj_vx *= v_mod_ / v_mod;
			obj_vy *= v_mod_ / v_mod;
		}
	}
};				  
