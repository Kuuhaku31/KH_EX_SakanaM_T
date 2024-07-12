
// Position.hpp
// 游戏对象的基本位置类

#pragma once

class Position
{
public:
	Position();
	Position(int, int);
	Position(Position *, int = 0, int = 0);
	~Position();

	// 设置位置
	void Set_position_x(int);
	void Set_position_y(int);

	void Set_position(int, int);
	void Set_position(Position *);
	void Set_position(Position *, int, int);
	void Set_position(Position *, Position *);

	int Get_dx() const;
	int Get_dy() const;
	void Get_dxy(int *, int *) const;

	int Get_x() const;
	int Get_y() const;
	void Get_xy(int *, int *) const;

	void Move_x(int);
	void Move_y(int);
	void Move(int, int);

	void Move_x_to(int);
	void Move_y_to(int);
	void Move_to(int, int);
	void Move_to(Position *);

protected:
	Position *parent_pos;
	int pos_x;
	int pos_y;
};
