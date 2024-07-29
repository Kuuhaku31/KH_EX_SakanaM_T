
#include "base.hpp"


bool
Limit(int& value, int min, int max)
{
    if(value < min)
    {
        value = min;
        return false;
    }
    if(value > max)
    {
        value = max;
        return false;
    }
    return true;
}

bool
Limit(Point& value, Point min, Point max)
{
    if(!Limit(min.px, 0, max.px) || !Limit(min.py, 0, max.py))
    {
        return false;
    }
    if(!Limit(value.px, min.px, max.px) || !Limit(value.py, min.py, max.py))
    {
        return false;
    }
    return true;
}

bool
Limit(float& value, float min, float max)
{
    if(value < min)
    {
        value = min;
        return false;
    }
    if(value > max)
    {
        value = max;
        return false;
    }
    return true;
}

bool
Limit(Vector& value, Vector min, Vector max)
{
    if(!Limit(min.vx, 0, max.vx) || !Limit(min.vy, 0, max.vy))
    {
        return false;
    }
    if(!Limit(value.vx, min.vx, max.vx) || !Limit(value.vy, min.vy, max.vy))
    {
        return false;
    }
    return true;
}

inline void
transformat(int* m) // 长度为6
{
    /*
	A的宽度
	A的高度
	B的宽度
	B的高度
	B的左上角相对于A的左上角的x坐标
	B的左上角相对于A的左上角的y坐标

		||
		\/

	A的起始点
	A的间隔
	B的起始点
	B的间隔
	宽度
	次数
	*/

    int A_start = 0;
    int A_skip  = 0;
    int B_start = 0;
    int B_skip  = 0;

    int wide = m[2];
    int high = m[3];

    int R = m[4] + m[2] - m[0];
    int L = m[4];
    int T = m[5];
    int B = m[5] + m[3] - m[1];

    if(R > 0)
    {
        wide -= R;
        B_skip += R;
    }
    if(R < 0)
    {
        A_skip -= R;
    }
    if(L > 0)
    {
        A_skip += L;
        A_start += L;
    }
    if(L < 0)
    {
        wide += L;
        B_skip -= L;
        B_start -= L;
    }
    if(B > 0)
    {
        high -= B;
    }
    if(T > 0)
    {
        A_start += m[0] * T;
    }
    if(T < 0)
    {
        high += T;
        B_start -= m[2] * T;
    }

    m[0] = A_start;
    m[1] = A_skip;
    m[2] = B_start;
    m[3] = B_skip;
    m[4] = wide;
    m[5] = high;
}
