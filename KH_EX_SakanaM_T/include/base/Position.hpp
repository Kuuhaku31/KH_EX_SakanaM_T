
#pragma once

// 数对（点）
struct Point
{
	int px = 0;
	int py = 0;
};

// 游戏对象的基本位置类
class Position
{
public:
	// 构造、析构函数
	Position();
	Position(int, int);
	Position(Point);
	Position(Position *, int = 0, int = 0);
	Position(Position *, Point);
	~Position();

	// 获取信息
	int Position_pos_x() const;
	int Position_pos_y() const;
	Position *Position_parent_pos() const;

	// 递归查找到相对于根位置坐标
	int Position_root_x() const;
	int Position_root_y() const;

	// 设置
	// 直接设置
	void Position_set_x(int);
	void Position_set_y(int);
	void Position_set(int, int);
	void Position_set(Point);
	void Position_set(Position *);
	void Position_set(Position *, int, int);
	void Position_set(Position *, Point);
	void Position_set(Position *, Position *);

	// 移动
	void Position_move_x(int);
	void Position_move_y(int);
	void Position_move(int, int);
	void Position_move(Point);

	void Position_move_x_to(int);
	void Position_move_y_to(int);
	void Position_move_to(int, int);
	void Position_move_to(Point);
	void Position_move_to(Position *);

protected:
	Position *parent_pos;
	int pos_x;
	int pos_y;
};
