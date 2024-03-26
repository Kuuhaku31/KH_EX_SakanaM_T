
#pragma once

#include <iostream>
#include <graphics.h>

#include "Shape.h"

class Shape_Maker
{
public:

	static void
	Write(Shape* shape, IMAGE* input, int k = 1)
	{
		unsigned long* input_buffer = GetImageBuffer(input);
		int input_long = input->getwidth() * input->getheight();

		unsigned long* shape_buffer = shape->Get_buffer();
		int shape_long = shape->Get_shape_long();

		for (int i = 0, p = 0; i < input_long; i++)
		{
			if (input_buffer[i] != 0x000000)
			{
				for (int j = 0; j < k; j++, p++)
				{
					if (p >= shape_long) { return; }
					shape_buffer[p] = 0xffffff;
				}
			}
		}
	}

	static Shape*
		Make(IMAGE& input, int k = 1)
	{
		int input_wide = input.getwidth();
		int input_high = input.getheight();

		Shape* output = nullptr;//new Shape(input_wide * k, input_high * k);

		SetWorkingImage(&input);
		for (int i = 0, x = 0; i < input_wide; i++, x += k)
		{
			for (int j = 0, y = 0; j < input_high; j++, y += k)
			{
				if (getpixel(i, j) != 0x000000)
				{
					output->Draw(x, y, k, k, 0xffffffff);
				}
			}
		}
		SetWorkingImage();
		return output;
	}

	static void
		PrintShape(const Shape* shape)
	{
		int wide = shape->Get_shape_wide();
		int high = shape->Get_shape_high();
		for (int i = 0, n = 0; i < high; i++)
		{
			for (int j = 0; j < wide; j++, n++)
			{
				if (shape->Shape::Is_in_shape(n))
				{
					std::cout << "¡ö ";
				}
				else
				{
					std::cout << "¡õ ";
				}
			}
			std::cout << std::endl;
		}
		std::cout << "END" << std::endl;
	}
};
