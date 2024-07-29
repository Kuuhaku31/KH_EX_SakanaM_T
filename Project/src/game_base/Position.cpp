
#include "base.hpp"

// 递归查找到相对于根位置坐标
int
Position::Position_root_x() const
{
    return parent_pos ? parent_pos->Position_root_x() + px : px;
}

// 递归查找到相对于根位置坐标
int
Position::Position_root_y() const
{
    return parent_pos ? parent_pos->Position_root_y() + py : py;
}

// 递归查找到相对于根位置坐标
Point
Position::Position_root_xy() const
{
    return parent_pos ? parent_pos->Position_root_xy() + *this : Point(*this);
}

void
Position::Position_x_to(int x)
{
    px += (x - Position_root_x());
}

void
Position::Position_y_to(int y)
{
    py += (y - Position_root_y());
}

void
Position::Position_xy_to(Point p)
{
    *this += (p - Position_root_xy());
}

// 如果p不为空，则将当前位置移动到p的世界位置
// 返回是否成功
bool
Position::Position_xy_to(Position* p)
{
    if(p)
    {
        Position_xy_to(p->Position_root_xy());
        return true;
    }
    else
    {
        return false;
    }
}
