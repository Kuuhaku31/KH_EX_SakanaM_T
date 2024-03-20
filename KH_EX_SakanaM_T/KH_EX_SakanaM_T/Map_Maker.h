
#pragma once

#include "Library.h"

class Map_Maker
{	public:

	void Make()
	{
		loadimage(&_input, "./Material/Map/input.png");

		Library lib;
		lib.Init();

		_unit_skin = lib._unit_skin_wall_02;

		_unit_wide = _unit_skin.getwidth();
		_unit_high = _unit_skin.getheight();

		_map_wide = _input.getwidth() * _unit_block_wide;
		_map_high = _input.getheight() * _unit_block_high;

		_map.Resize(_map_wide, _map_high);
		SetWorkingImage(&_map);
		setfillcolor(GREEN);
		fillrectangle(-1, -1, _map_wide, _map_high);
		
		SetWorkingImage(&_input);
		int x = 0;
		for (int i = 0; i < _map_wide; i += _unit_block_wide)
		{
			int y = 0;
			for (int j = -9; j < _map_high; j += _unit_block_high)
			{
				if (getpixel(x, y) != 0x000000)
				{
					Draw(i, j);
				}
				y++;
			}
			x++;
		}
		
		saveimage("./Material/Map/output_a.png", &_map);
	}

private:
	BLENDFUNCTION _bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	BLENDFUNCTION _bf_b = { AC_SRC_OVER, 0, 255, AC_SRC_OVER };

	IMAGE _input;

	IMAGE _unit_skin;
	int _unit_wide;
	int _unit_high;
	int _unit_block_wide = 32;
	int _unit_block_high = 32;

	IMAGE _map;
	int _map_wide;
	int _map_high;

	void
	Draw(const int& x, const int& y)
	{
		GdiAlphaBlend
		(
			GetImageHDC(&_map)
			, x
			, y
			, _unit_wide
			, _unit_high
			, GetImageHDC(&_unit_skin)
			, 0
			, 0
			, _unit_wide
			, _unit_high
			, _bf
		);
	}
};
