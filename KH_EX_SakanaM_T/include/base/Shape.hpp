
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
	int Wide() const;
	int High() const;
	int Long() const;

	// 获取形状某个点的值
	unsigned int In_shape(int) const;
	unsigned int In_shape(int, int) const;

	// 绘制圆形
	void Draw_point(int, unsigned int = OXF);
	void Draw_point(int, int, unsigned int = OXF);
	void Draw_line(int, int, int, int, unsigned int = OXF);
	void Draw_rectangle(int, int, int, int, unsigned int = OXF);
	void Draw_circle(int, int, int, unsigned int = OXF);

	// 用于两个形状的计算
	// 2、3号参数为传入Shape的相对于本Shape的左上角坐标
	// 4号参数为计算函数
	// 这个只会改变本Shape（还没写）
	void Compute(const Shape *, int, int, unsigned int(const unsigned int, const unsigned int));
	// 这个会同时改变两个Shape
	void Compute(Shape *, int, int, void(unsigned int *, unsigned int *));

	// 重新设置形状
	void Reset(int = 0, int = 0, unsigned int = 0);
	// **这个函数无法处理数组越界！**
	void Reset(const unsigned int *, int, int);
	// 复制形状
	void Copy_shape(Shape *);

	// 设置所有单位的值
	void Clear(unsigned int = 0);
	// 根据单位的值是否为0设置值
	void Clear_shape(unsigned int = OXF, unsigned int = 0);
	// 按bit位取反
	void Not();

protected:
	int shape_wide = 0;
	int shape_high = 0;
	int shape_long = 0;
	unsigned int *shape_buffer = nullptr;
};
