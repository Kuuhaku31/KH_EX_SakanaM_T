
#pragma once

#include "include_base.hpp"

#define ZEROPOINT \
	Point { 0, 0 }
#define ZEROVECTOR \
	Vector { 0.0f, 0.0f }

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

// 向量
struct Vector
{
	float vx = 0.0f;
	float vy = 0.0f;
};

// 计算模长
float moudle(Point);
float module(Vector);

// 化为单位向量
Vector unit(Point);
Vector unit(Vector);

// 数乘
Vector operator*(const Vector &, float);
Vector &operator*=(Vector &, float);

// 重载==操作符
bool operator==(const Vector &, const Vector &);
// 重载!=操作符
bool operator!=(const Vector &, const Vector &);

// 重载加法操作符
Point operator+(const Point &, const Point &);
Vector operator+(const Vector &, const Vector &);
Vector operator+(const Vector &, const Point &);
Vector operator+(const Point &, const Vector &);

// 重载+=操作符
Point &operator+=(Point &, const Point &);
Vector &operator+=(Vector &, const Vector &);
Vector &operator+=(Vector &, const Point &);
Vector &operator+=(Point &, const Vector &);

// 重载减法操作符
Point operator-(const Point &, const Point &);
Vector operator-(const Vector &, const Vector &);
Vector operator-(const Vector &, const Point &);

// 重载-=操作符
Point &operator-=(Point &, const Point &);
Vector &operator-=(Vector &, const Vector &);
Vector &operator-=(Vector &, const Point &);

// 最基础的图形类，用四个字节的数组表示一个矩阵，每个字节表示一个像素点的颜色
// **所用的宽高全部用无符号int**

class Shape
{
public:
	Shape(uint = 0, uint = 0, uint = 0);
	Shape(const uint *, uint, uint);
	~Shape(); // **记得释放内存**

	// 获取形状的宽高、缓冲区大小
	uint Shape_wide() const;
	uint Shape_high() const;
	uint Shape_long() const;
	uint *Shape_buffer();

	// 获取形状某个点的值
	uint Shape_in(uint) const;
	uint Shape_in(int, int) const;

	// 绘制圆形
	void Shape_draw_point(int, uint = OXF);
	void Shape_draw_point(int, int, uint = OXF);
	void Shape_draw_line(int, int, int, int, uint = OXF);
	void Shape_draw_rectangle(int, int, int, int, uint = OXF);
	void Shape_draw_circle(int, int, int, uint = OXF);

	// 用于两个形状的计算
	// 2、3号参数为传入Shape的相对于本Shape的左上角坐标
	// 4号参数为计算函数
	// 这个可能会同时改变两个Shape
	void Shape_compute(Shape *, int, int, void f(uint &, uint &));

	// 重新设置形状
	void Shape_reset(uint = 0, uint = 0, uint = 0);
	// **这个函数无法处理数组越界！**
	void Shape_reset(const uint *, uint, uint);
	// 复制形状
	void Shape_copy(Shape *);

	// 设置所有单位的值
	void Shape_clear(uint = 0);
	// 根据单位的值是否为0设置值
	void Shape_clear(uint, uint);
	// 按bit位取反
	void Shape_not();

protected:
	uint *shape_buffer;
	uint shape_wide;
	uint shape_high;
	uint shape_long;
};

class Area : public Position, public Shape
{
public:
	Area(Shape *);
	Area(Point = ZEROPOINT, uint = 0, uint = 0); // 坐标，宽高
	Area(Position *, Point = ZEROPOINT, uint = 0, uint = 0);
	~Area();

	// 转换到本地坐标
	int Area_local_x(int) const;
	int Area_local_y(int) const;
	Point Area_local(Point) const;

	// 给坐标获取某个点的值
	uint Area_in(int, int) const;
	uint Area_in(Point) const;
	uint Area_in(Position *) const;

	// 计算
	void Area_compute(Area *, void f(uint &, uint &));

	// 对齐
	void Area_align();
	void Area_align_x();
	void Area_align_y();

	// Copy，但是不Copy ParentPosition
	void Area_copy(Area *);
};

// 天才！！！！
// 一个Area的点有32位
// 每一位表示不同的Area
// Area[32]

#define RELATIVE_AREA_START 2
#define RELATIVE_AREA_COUNT 5

#define WALL_AREA_START 7
#define WALL_AREA_COUNT 5

#define COLL_AREA_START 12
#define COLL_AREA_COUNT 5

#define DHP_AREA_START 17
#define DHP_AREA_COUNT 5

// 从低位到高位
enum ZoneAreaType
{
	/*01*/ main_area, // main_area 为主要区域，用于判断是否在区域内
	/*02*/ relative_area_01,
	/*03*/ relative_area_02,
	/*04*/ relative_area_03,
	/*05*/ relative_area_04,
	/*06*/ relative_area_05,
	/*07*/ wall_area_01,
	/*08*/ wall_area_02,
	/*09*/ wall_area_03,
	/*10*/ wall_area_04,
	/*11*/ wall_area_05,
	/*12*/ coll_area_01,
	/*13*/ coll_area_02,
	/*14*/ coll_area_03,
	/*15*/ coll_area_04,
	/*16*/ coll_area_05,
	/*17*/ DHP_area_01,
	/*18*/ DHP_area_02,
	/*19*/ DHP_area_03,
	/*20*/ DHP_area_04,
	/*21*/ DHP_area_05,
	/*22*/ area_22,
	/*23*/ area_23,
	/*24*/ area_24,
	/*25*/ area_25,
	/*26*/ area_26,
	/*27*/ area_27,
	/*28*/ area_28,
	/*29*/ area_29,
	/*30*/ area_30,
	/*31*/ area_31,
	/*32*/ area_32
};

// 一个Zone类可以存储32个Area信息

class Zone : public Area
{
public:
	Zone(uint = 0, uint = 0);
	Zone(Shape *);
	~Zone();

	// 获取、设置
	Vector ZoneGetRelative(ZoneAreaType);
	float ZoneGetWallCollForce(ZoneAreaType);
	float ZoneGetCollForce(ZoneAreaType);
	int ZoneGetDHP(ZoneAreaType);

	void ZoneSetRelative(ZoneAreaType, Vector);
	void ZoneSetWallCollForce(ZoneAreaType, float);
	void ZoneSetCollForce(ZoneAreaType, float);
	void ZoneSetDHP(ZoneAreaType, int);

private:
	// 阻力参数：摩擦力、空气阻力float表示
	Vector relatives[RELATIVE_AREA_COUNT] = {ZEROVECTOR, ZEROVECTOR, ZEROVECTOR, ZEROVECTOR, ZEROVECTOR};

	// 墙体参数：是否碰撞、碰撞方向
	float wall_coll_force[WALL_AREA_COUNT] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

	// 碰撞参数：碰撞力、碰撞方向
	float coll_force[COLL_AREA_COUNT] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

	// 血量增减
	int dHP[DHP_AREA_COUNT] = {0, 0, 0, 0, 0};
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
	Movement(Position *);
	Movement(Position *, float, Vector = ZEROVECTOR);
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
	float MovementDT();
	float MovementMass();
	Vector MovementVelocity();
	Vector MovementAcceleration();

private:
	friend class Collision;
	// 附着的Position类
	Position *position;

	float DT;	  // 时间间隔
	float mass;	  // 质量
	Vector buf_p; // 位置缓冲
	Vector mov_v; // 速度
	Vector mov_a; // 加速度
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

#define OBJECTAREASMAX 10

class Object : public Position, public Movement
{
public:
	Object(Position *, Point = ZEROPOINT, float = 0.0f, Vector = ZEROVECTOR);
	~Object();

	// 设置skin、碰撞盒
	void ObjectSetArea(Shape *, Point, ObjectAreaType);
	void ObjectSetArea(Area *, ObjectAreaType);

	// 返回skin、碰撞盒
	Area *ObjectGetArea(ObjectAreaType);

protected:
	// 皮肤、碰撞盒
	Area *objectAreas[OBJECTAREASMAX];
};

// 碰撞检测类
// 用于检测角色是否与墙体或其他角色发生碰撞
// 有8个检测点，分别在角色的四个角和四个边的中点
// 当角色的检测点与墙体或其他角色的检测点重合时，认为发生碰撞
/*
 (-w,-h)----------(0,-h)----------(w,-h)
	|               |               |
	|               |               |
 (-w,0)-----------(0,0)-----------(w,0)
	|               |               |
	|               |               |
 (-w,h)-----------(0,h)-----------(w,h)
*/

#define TESTPOINTCOUNT 8

class Collision : public Position
{
public:
	Collision(ushort, ushort);
	~Collision();

	// 检测碰撞、更新test_points_value、向Movement发出指令
	void CollUpdate(Position *, Area *, uint *);

	// 重置检测点的坐标
	void CollResetTestPoints(ushort, ushort);

private:
	// 	检测点
	Position test_points[8];
};
