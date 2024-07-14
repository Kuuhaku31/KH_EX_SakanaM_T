
// 最基础的图形类，用四个字节的数组表示一个矩阵，每个字节表示一个像素点的颜色
// **所用的宽高全部用无符号int**

#pragma once

#define uint unsigned int
#define ushort unsigned short

#define OXF 0xffffffff

class Shape
{
public:
	Shape();
	Shape(uint, uint);
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
	void Shape_reset(uint = 0, uint = 0, uint = OXF);
	// **这个函数无法处理数组越界！**
	void Shape_reset(const uint *, uint, uint);
	// 复制形状
	void Shape_copy(Shape *);

	// 设置所有单位的值
	void Shape_clear(uint = 0);
	// 根据单位的值是否为0设置值
	void Shape_clear(uint = OXF, uint = 0);
	// 按bit位取反
	void Shape_not();

protected:
	uint *shape_buffer;
	uint shape_wide;
	uint shape_high;
	uint shape_long;
};
