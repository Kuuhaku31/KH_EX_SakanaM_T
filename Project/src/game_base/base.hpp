
#pragma once

#include "include_base.hpp"


// 游戏对象的基本位置类
struct Position : public Point
{
    // 父位置
    Position* parent_pos = nullptr;

    // 递归查找到相对于根位置坐标
    int   Position_root_x() const;
    int   Position_root_y() const;
    Point Position_root_xy() const;

    // 移动到...
    void Position_x_to(int);
    void Position_y_to(int);
    void Position_xy_to(Point);
    bool Position_xy_to(Position*);

    Point&
    operator=(const Point& p)
    {
        px = p.px;
        py = p.py;
        return *this;
    }
};

// 重载操作符，计算两个位置的差
inline Point
operator-(const Position& p1, const Position& p2)
{
    return p1.Position_root_xy() - p2.Position_root_xy();
}


static void
default_action_add(int& a, int& b, int v)
{
    a += b;
}

static void
default_action_sub(int& a, int& b, int v)
{
    a -= b;
}

// 最基础的图形类，用四个字节的数组表示一个矩阵，每个字节表示一个像素点的颜色
// **所用的宽高全部用无符号int**
class Shape
{
public:
    Shape(int = 0, int = 0, int = 0);
    Shape(const int*, int, int);
    ~Shape(); // **记得释放内存**

    // 获取形状的宽高、缓冲区大小
    int  Shape_wide() const;
    int  Shape_high() const;
    int  Shape_long() const;
    int* Shape_buffer();

    // 获取形状某个点的值
    int  Shape_in(int) const;
    int  Shape_in(Point) const;
    bool Shape_in(int, int) const;   // 获取某个bit位的值，第三个参数为0-31
    bool Shape_in(Point, int) const; // 获取某个bit位的值，第三个参数为0-31

    // 合并两个形状
    void Shape_merge(Shape*, Point = ZEROPOINT, void (*action)(int&, int&, int) = default_action_add, int = 0);

    // 获取某个点的地址
    bool Shape_in_addr(int**, int);
    bool Shape_in_addr(int**, Point);

    // 绘制圆形
    void Shape_draw_point(int, int, int = OXF);
    void Shape_draw_line(int, int, int, int, int = OXF);
    void Shape_draw_rectangle(int, int, int, int, int = OXF);
    void Shape_draw_circle(int, int, int, int = OXF);

    // 重新设置形状
    void Shape_reset(int = 0, int = 0, int = 0);
    // **这个函数无法处理数组越界！**
    void Shape_reset(const int*, int, int);
    // 复制形状
    void Shape_copy(Shape*);

    // 设置所有单位的值
    void Shape_clear(int = 0);
    // 根据单位的值是否为0设置值
    void Shape_clear(int, int);
    // 按bit位取反
    void Shape_not();

protected:
    int* shape_buffer;
    int  shape_wide;
    int  shape_high;
    int  shape_long;
};


// action为一个表达式，用来操作两个Shape的对应点
#define M0M2(s1, s2, x, y, action)                                                                   \
    {                                                                                                \
        int m[6] = { s1->Shape_wide(), s1->Shape_high(), s2->Shape_wide(), s2->Shape_high(), x, y }; \
        transformat(m);                                                                              \
        int* b1 = s1->Shape_buffer();                                                                \
        int* b2 = s2->Shape_buffer();                                                                \
        for(int i = 0; i < m[5]; i++)                                                                \
        {                                                                                            \
            for(int j = 0; j < m[4]; j++)                                                            \
            {                                                                                        \
                int& a = b1[m[0]];                                                                   \
                int& b = b2[m[2]];                                                                   \
                action;                                                                              \
                m[0]++;                                                                              \
                m[2]++;                                                                              \
            }                                                                                        \
            m[0] += m[1];                                                                            \
            m[2] += m[3];                                                                            \
        }                                                                                            \
    }
//

// Area 类，Point 表示形状最左上角的坐标
class Area : public Position, public Shape
{
public:
    Area();
    Area(Shape*);
    Area(Point, int = 0, int = 0); // 坐标，宽高
    Area(Position*, Point = ZEROPOINT, int = 0, int = 0);
    ~Area();

    // 转换到本地坐标
    int   Area_local_x(int) const;
    int   Area_local_y(int) const;
    Point Area_local_xy(Point) const;

    // 给坐标，获取某个点的值
    int Area_in(Point) const;
    int Area_in(Position*) const;

    // 给坐标，获取某个位的值
    bool Area_in(Point, int) const;
    bool Area_in(Position*, int) const;

    bool Area_in_addr(int**, Point);
    bool Area_in_addr(int**, Position*);

    // 对齐
    void Area_align();
    void Area_align_x();
    void Area_align_y();

    // 重载运算符
    Area& operator+=(Area&);
    Area& operator-=(Area&);
    void  Area_merge(Area*, void (*action)(int&, int&, int) = default_action_add, int = 0);
};

#define AREA_COMPUTE(a1, a2, action) M0M2(a1, a2, a2->Position_root_x() - a1->Position_root_x(), a2->Position_root_y() - a1->Position_root_y(), action);

// =================================================================================================
// =================================================================================================
// =================================================================================================

class Timer
{
public:
    Timer(int = 0);

    void Timer_start();       // 开始计时
    void Timer_stop();        // 停止计时
    void Timer_reset();       // 重置计时
    void Timer_update();      // 更新计时
    void Timer_setLoop(bool); // 设置循环
    void Timer_setTime(int);  // 设置时间

    int Timer_getTime(); // 获取时间

private:
    bool is_timing = false; // 是否正在计时
    bool is_loop   = false; // 是否循环
    int  time      = 0;     // 时间
    int  time_max  = 0;     // 最大时间
};

class AnimationList
{
    friend class Library;

public:
    AnimationList() = default;
    ~AnimationList();

    Shape* AnimationList_getFrame(int);   // 获取帧
    int    AnimationList_getFrameCount(); // 获取帧数

private:
    Shape* frames      = nullptr; // 帧数组
    int    frame_count = 0;       // 帧数

    void free(); // 释放内存
};
