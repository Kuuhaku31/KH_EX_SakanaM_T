
#pragma once

namespace Matrix
{
	template <class Tem>

	void 
	Write
	(
		  Tem* paper
		, int paper_wide
		, int paper_high
		, int paper_size

		, Tem* from
		, int from_wide
		, int from_high
		, int from_size

		, int from_x
		, int from_y

		, void (*fun)(Tem* a, Tem* b)
	)
	{
		Tem* skin_buffer = from;
		int skin_w = from_wide;
		int skin_h = from_high;

		Tem* sight_buffer = paper;
		int sight_w = paper_wide;
		int sight_h = paper_high;

		int w = from_wide;
		int h = from_high;

		int skin_start = 0;
		int skin_skip = 1;
		int sight_start = 0;
		int sight_skip = 1;

		int R = from_x + from_wide - paper_wide;
		int L = from_x;
		int top = from_y;
		int B = from_y + from_high - paper_high;

		if (R > 0)
		{
			w -= R;
			skin_skip += R;
		}
		if (R < 0)
		{
			sight_skip -= R;
		}
		if (L > 0)
		{
			sight_skip += L;
			sight_start += L;
		}
		if (L < 0)
		{
			w += L;
			skin_skip -= L;
			skin_start -= L;
		}
		if (B > 0)
		{
			h -= B;
		}
		if (top > 0)
		{
			sight_start += sight_w * top;
		}
		if (top < 0)
		{
			h += top;
			skin_start += skin_w * (-top);
		}

		skin_skip--;
		sight_skip--;

		for (int i = 0, skin_n = skin_start, sight_n = sight_start; i < h; i++, skin_n += skin_skip, sight_n += sight_skip)
		{
			for (int j = 0; j < w; j++, skin_n++, sight_n++)
			{
				fun(&sight_buffer[sight_n], &skin_buffer[skin_n]);
			}
		}
	}
};
