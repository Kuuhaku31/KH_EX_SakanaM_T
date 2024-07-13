
// 最基础的图形类，用四个字节的数组表示一个矩阵，每个字节表示一个像素点的颜色

#pragma once

#define OXF 0xffffffff

class Shape
{
public:
	Shape();
	Shape(const unsigned int *, int, int);
	~Shape(); // **记得释放内存**

	// 获取形状的宽高、缓冲区大小
	int Shape_wide() const;
	int Shape_high() const;
	int Shape_long() const;

	// 获取形状某个点的值
	unsigned int Shape_in(int) const;
	unsigned int Shape_in(int, int) const;

	// 绘制圆形
	void Shape_draw_point(int, unsigned int = OXF);
	void Shape_draw_point(int, int, unsigned int = OXF);
	void Shape_draw_line(int, int, int, int, unsigned int = OXF);
	void Shape_draw_rectangle(int, int, int, int, unsigned int = OXF);
	void Shape_draw_circle(int, int, int, unsigned int = OXF);

	// 用于两个形状的计算
	// 2、3号参数为传入Shape的相对于本Shape的左上角坐标
	// 4号参数为计算函数
	// 这个只会改变本Shape（还没写）
	void Shape_compute(const Shape *, int, int, unsigned int(const unsigned int, const unsigned int));
	// 这个会同时改变两个Shape
	void Shape_compute(Shape *, int, int, void(unsigned int *, unsigned int *));

	// 重新设置形状
	void Shape_reset(int = 0, int = 0, unsigned int = 0);
	// **这个函数无法处理数组越界！**
	void Shape_reset(const unsigned int *, int, int);
	// 复制形状
	void Shape_copy(Shape *);

	// 设置所有单位的值
	void Shape_clear(unsigned int = 0);
	// 根据单位的值是否为0设置值
	void Shape_clear(unsigned int = OXF, unsigned int = 0);
	// 按bit位取反
	void Shape_not();

protected:
	int shape_wide = 0;
	int shape_high = 0;
	int shape_long = 0;
	unsigned int *shape_buffer = nullptr;
};
