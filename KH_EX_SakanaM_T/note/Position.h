
#pragma once

class Position
{	public:
	Position()
		: parent_pos(nullptr)
		, pos_x(0)
		, pos_y(0)
	{}

	Position(int x, int y)
		: parent_pos(nullptr)
		, pos_x(x)
		, pos_y(y)
	{}

	Position(Position* pos, int x = 0, int y = 0)
		: parent_pos(pos)
		, pos_x(x)
		, pos_y(y)
	{}

	void Set_position_x(int x) { pos_x = x; }
	void Set_position_y(int y) { pos_y = y; }

	void
	Set_position(int x, int y)
	{
		pos_x = x;
		pos_y = y;
	}

	void
	Set_position(Position* pos)
	{
		parent_pos = pos;
	}

	void
	Set_position(Position* pos, int x, int y)
	{
		parent_pos = pos;
		pos_x = x;
		pos_y = y;
	}

	void
	Set_position(Position* pos1, Position* pos2)
	{
		parent_pos = pos1;
		pos_x = pos2->pos_x;
		pos_y = pos2->pos_y;
	}

	int Get_dx() const { return pos_x; }
	int Get_dy() const { return pos_y; }
	void Get_dxy(int* dx, int* dy) const { *dx = pos_x; *dy = pos_y; }

	int Get_x() const { return parent_pos ? parent_pos->Get_x() + pos_x : pos_x; }
	int Get_y() const { return parent_pos ? parent_pos->Get_y() + pos_y : pos_y; }
	void Get_xy(int* x, int* y) const { *x = Get_x(); *y = Get_y(); }

	void Move_x(int x) { pos_x += x; }
	void Move_y(int y) { pos_y += y; }
	void Move(int dx, int dy)
	{
		pos_x += dx; 
		pos_y += dy; 
	}

	void Move_x_to(int x) { pos_x = parent_pos ? x - Get_x() : x; }
	void Move_y_to(int y) { pos_y = parent_pos ? y - Get_y() : y; }
	void Move_to(int x, int y) 
	{
		pos_x = parent_pos ? x - Get_x() : x;
		pos_y = parent_pos ? y - Get_y() : y;
	}
	void Move_to(Position* pos)
	{
		if (pos)
		{
			pos_x = parent_pos ? pos->Get_x() - Get_x() : pos->Get_x();
			pos_y = parent_pos ? pos->Get_y() - Get_y() : pos->Get_y();
		}
	}

protected:

	Position* parent_pos;
	int pos_x;
	int pos_y;
};