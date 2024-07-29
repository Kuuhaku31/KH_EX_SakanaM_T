
#pragma once

#include "include_base.hpp"

// 数对（点）
struct Point
{
    int px = 0;
    int py = 0;
};

#define ZEROPOINT (Point{0, 0})

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
};

// 向量
struct Vector
{
    float vx = 0.0f;
    float vy = 0.0f;
};

#define ZEROVECTOR (Vector{0.0f, 0.0f})

float  moudle(Point);  // 计算模长
float  module(Vector); //
Vector unit(Point);    // 化为单位向量
Vector unit(Vector);   //

// 重载操作符
Vector  operator*(const Vector&, float);          // 数乘
Vector& operator*=(Vector&, float);               //
bool    operator==(const Vector&, const Vector&); //
bool    operator!=(const Vector&, const Vector&); //
Point   operator+(const Point&, const Point&);    // 重载加法操作符
Vector  operator+(const Vector&, const Vector&);  //
Vector  operator+(const Vector&, const Point&);   //
Vector  operator+(const Point&, const Vector&);   //
Point&  operator+=(Point&, const Point&);         // 重载+=操作符
Vector& operator+=(Vector&, const Vector&);       //
Vector& operator+=(Vector&, const Point&);        //
Point   operator-(const Point&, const Point&);    // 重载减法操作符
Vector  operator-(const Vector&, const Vector&);  //
Vector  operator-(const Vector&, const Point&);   //
Vector  operator-(const Point&, const Vector&);   //
Point&  operator-=(Point&, const Point&);         // 重载-=操作符
Vector& operator-=(Vector&, const Vector&);       //
Vector& operator-=(Vector&, const Point&);        //

//限制器模板函数
// 如果value不在范围内，则调整并返回false
template<int MIN, int MAX>
inline bool
Limit(int& value)
{
    if(value < MIN)
    {
        value = MIN;
        return false;
    }
    if(value > MAX)
    {
        value = MAX;
        return false;
    }
    return true;
}
bool Limit(int& value, int min, int max);
bool Limit(float& value, float min, float max);
bool Limit(Point& value, Point min, Point max);
bool Limit(Vector& value, Vector min, Vector max);


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

    // 绘制圆形
    void Shape_draw_point(int, int = OXF);
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

// 数组长度为6用来储存输出
inline void transformat(int*);

// action为一个表达式，用来操作两个Shape的对应点
#define M0M2(s1, s2, x, y, action) \
    { \
        int m[6] = {s1->Shape_wide(), s1->Shape_high(), s2->Shape_wide(), s2->Shape_high(), x, y}; \
        transformat(m); \
        int* b1 = s1->Shape_buffer(); \
        int* b2 = s2->Shape_buffer(); \
        for(int i = 0; i < m[5]; i++) \
        { \
            for(int j = 0; j < m[4]; j++) \
            { \
                int& a = b1[m[0]]; \
                int& b = b2[m[2]]; \
                action; \
                m[0]++; \
                m[2]++; \
            } \
            m[0] += m[1]; \
            m[2] += m[3]; \
        } \
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

    // 对齐
    void Area_align();
    void Area_align_x();
    void Area_align_y();
};

#define AREA_COMPUTE(a1, a2, action) M0M2(a1, a2, a2->Position_root_x() - a1->Position_root_x(), a2->Position_root_y() - a1->Position_root_y(), action);

// 天才！！！！
// 一个Area的点有32位
// 每一位表示不同的Area
//
// 一个Zone类可以存储32个Area信息
// main_area 为主要区域，用于判断是否在区域内
class Zone : public Area
{
public:
    Zone();
    Zone(int, int);
    Zone(Shape*);
    ~Zone();

    int   Zone_color(int) const; // 获取某个area的颜色
    void* Zone_data(int) const;  // 获取某个area的数据

    // 第一个参数为area的编号，第二个参数为颜色
    void Zone_color(int, int);  // 设置某个area的颜色
    void Zone_data(int, void*); // 设置某个area的数据

private:
    // 32个area对应的颜色
    int colors[32] = {0};
    // 32个任意指针指向Area对应的数据
    void* data[32] = {nullptr};
};

// =================================================================================================
// =================================================================================================
// =================================================================================================

// Movement.hpp
// Movement类
// 用于指导物体的运动

// 阻力参数：摩擦力、空气阻力
// Frictional resistance, air resistance、
// 直接用Vector表示

class Movement
{
public:
    Movement(Position*);
    ~Movement();

    // 更新运动状态
    void MovementUpdate(Vector = ZEROVECTOR);

    // 更改物体的运动参数
    void MovementResetDT(float = 0.1f);
    void MovementResetMass(float = 0.0f);

    void MovementResetVelocity(Vector = ZEROVECTOR);
    void MovementResetVelocity_x(float = 0.0f);
    void MovementResetVelocity_y(float = 0.0f);
    void MovementAddVelocity(Vector);

    void MovementResetAcceleration(Vector = ZEROVECTOR);
    void MovementResetAcceleration_x(float = 0.0f);
    void MovementResetAcceleration_y(float = 0.0f);
    void MovementAddAcceleration(Vector);

    void MovementAddForce(Vector);

    // 获取物体的运动参数
    float  MovementDT();
    float  MovementMass();
    Vector MovementVelocity();
    Vector MovementAcceleration();

protected:
    // 附着的Position类
    Position* position;

    float  DT;    // 时间间隔
    float  mass;  // 质量（为0时视为质量无穷大）
    Vector buf_p; // 位置缓冲
    Vector mov_v; // 速度
    Vector mov_a; // 加速度
};

// 碰撞检测类
// 用于检测角色是否与墙体或其他角色发生碰撞
// 有12个检测点，分别在角色的四个角和四个边的中点
// 当角色的检测点与墙体或其他角色的检测点重合时，认为发生碰撞
/*

(0,0)------(w/4,0)-----(w/2,0)-----(3w/4,0)-----(w,0)
  |           |           |           |           |
  |           |           |           |           |
(0,h/4)----(w/4,h/4)---(w/2,h/4)---(3w/4,h/4)---(w,h/4)
  |           |           |           |           |
  |           |           |           |           |
(0,h/2)----(w/4,h/2)---(w/2,h/2)---(3w/4,h/2)---(w,h/2)
  |           |           |           |           |
  |           |           |           |           |
(0,3h/4)--(w/4,3h/4)--(w/2,3h/4)--(3w/4,3h/4)--(w,3h/4)
  |           |           |           |           |
  |           |           |           |           |
(0,h)------(w/4,h)-----(w/2,h)-----(3w/4,h)-----(w,h)

*/

#define TESTPOINTCOUNT 12

class Collision : public Position
{
public:
    Collision(Position* p = nullptr, int = 0, int = 0);
    ~Collision();

    // 检测碰撞
    void CollTest(Area*);

    // 获取检测点的值
    int CollTestPointValue(int) const;

    // 重置检测点的坐标
    void CollResetTestPoints(int, int);

private:
    // 检测点以及检测点的值
    Position test_points[TESTPOINTCOUNT];
    int      test_points_value[TESTPOINTCOUNT];
};

// 可能用到的类型
enum ObjectAreaType
{
    skin01,
    skin02,
    widget01,
    widget02,
    widget03,
    hitbox01,
    hitbox02,
    hitbox03,
    NULL01,
    NULL02
};

enum ObjectCollType
{
    object_coll_01,
    object_coll_02,
    object_coll_03,
    object_coll_04,
    object_coll_05
};

#define OBJECTAREASCOUNT 10
#define OBJECTCOLLCOUNT 5

class Object : public Position, public Movement
{
public:
    Object();
    Object(Position*, Point = ZEROPOINT);
    ~Object();

    // 返回area、碰撞检测
    Area*      ObjectGetArea(ObjectAreaType);
    Collision* ObjectGetCollision(ObjectCollType);

protected:
    // 皮肤、碰撞检测
    Area      objectAreas[OBJECTAREASCOUNT];
    Collision objectColls[OBJECTCOLLCOUNT];
};

// =================================================================================================
// =================================================================================================
// =================================================================================================