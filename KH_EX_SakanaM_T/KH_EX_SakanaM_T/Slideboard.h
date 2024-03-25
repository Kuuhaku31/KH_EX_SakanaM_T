
#pragma once

#include "UI.h"
#include "Camera.h"
#include "Renderer.h"

class Slideboard : public Position
{	public:
	Slideboard(Camera* u, Position* pos = nullptr, int x = 0, int y = 0)
		: Position(pos, x, y)
		, ui(u)
	{}
	~Slideboard() { delete[] bits; }

	static void
	Init_nums(IMAGE* imgs)
	{
		for (int i = 0; i < 10; i++)
		{
			char_size0_num[i] = imgs[i]; 
		}
	}
	
	void
	Set_bits(int n)
	{
		delete[] bits;
		bits = new Renderer[n];

		bit_count = n;

		for (int i = 0; i < bit_count; i++)
		{
			bits[i].Reset_skin(&char_size0_num[0]);
			bits[i].Set_position(this, i * 10, 0);
		}
	}

	void
	Set_num(int n = 0)
	{
		for (int i = bit_count - 1; i >= 0; i--)
		{
			bits[i].Reset_skin(&char_size0_num[n % 10]);
			n /= 10;
		}
	}

	void
	Print()
	{
		for (int i = 0; i < bit_count; i++)
		{
			ui->Rending_UI(&bits[i]);
		}
	}
	
private:

	Camera* ui;

	Renderer* bits = nullptr;
	int bit_count = 0;

	static IMAGE char_size0_num[10];
};
