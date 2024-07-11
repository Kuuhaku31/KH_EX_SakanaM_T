
#include "Shape_Maker.h"
#include "Matrix.h"

void 
Fun_0()
{
	int v;
	float a=4.5, b=6.9;
	v = (int)(a + b);
	printf("%d\n", v);
}

void
fun(unsigned long* a, unsigned long* b)
{
	*a = *a | *b;
}

void
Fun_2()
{
	IMAGE img1;
	IMAGE img2;
	// loadimage(&img1, _T("D:\\Project\\VS Code\\KH_EX_SakanaM_T\\note1\\mat\\input1.png"));
	// loadimage(&img2, _T("D:\\Project\\VS Code\\KH_EX_SakanaM_T\\note1\\mat\\input2.png"));

	loadimage(&img1, _T("..\\mat\\input1.png"));
	loadimage(&img2, _T("..\\mat\\input2.png"));

	Shape* shape1 = Shape_Maker::Make(img1, 1);
	Shape* shape2 = Shape_Maker::Make(img2, 1);

	Shape_Maker::PrintShape(shape1);
	Shape_Maker::PrintShape(shape2);

	unsigned long* buffer1 = shape1->Get_buffer();
	unsigned long* buffer2 = shape2->Get_buffer();

	int wide1 = shape1->Get_shape_wide();
	int high1 = shape1->Get_shape_high();
	int size1 = shape1->Get_shape_size();

	int wide2 = shape2->Get_shape_wide();
	int high2 = shape2->Get_shape_high();
	int size2 = shape2->Get_shape_size();

	Matrix::Write<unsigned long>(buffer1, wide1, high1, size1, buffer2, wide2, high2, size2, -1, 0, fun);

	Shape_Maker::PrintShape(shape1);
	Shape_Maker::PrintShape(shape2);

	delete shape1;
	delete shape2;
}

void
Fun_3()
{
	bool b1[25] =
	{
		 0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,0,0,0
	};

	bool b2[25] =
	{
		 1,1,1,1,1,
		 1,1,1,1,1,
		 1,1,1,1,1,
		 1,1,1,1,1,
		 1,1,1,1,1
	};

	//Matrix::Write(b1, 5, 5, 25, b2, 5, 5, 25, 1, 1);
}

int
main()
{
	std::cout << "GAME START" << std::endl;
	Fun_2();
	std::cout << "GAME OVER!" << std::endl;
	return 0;
}
