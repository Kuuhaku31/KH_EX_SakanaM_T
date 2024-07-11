
#include "MainGame.h"

#include "Map_Maker.h"
#include "Shape_Maker.h"

#include "Matrix.h"

void 
Fun_0()
{
	MainGame game;
	game.RUN();
}

void 
Fun_1()
{
	Shape* s = new Shape;
	Shape* d = new Shape;

	delete s;
	delete d;
}

void
Fun_2()
{
	IMAGE img;
	loadimage(&img, "./Material/area_wall_01.png");

	Shape* shape = Shape_Maker::Make(img, 1);
	Shape_Maker::PrintShape(shape);
}

void
fun(bool* a, bool* b)
{
	a = b;
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

	//Matrix::Write<bool>(b1, 5, 5, b2, 5, 5, 1, 1, fun);
}

int 
main()
{
	std::cout << "GAME START" << std::endl;
	Fun_0();
	std::cout << "GAME OVER!" << std::endl;
	return 0;
}
