
#pragma once

namespace Matrix
{
	template <class T>

	void 
	Write
	(
		  T* paper
		, int paper_wide
		, int paper_high
		, int paper_size

		, T* from
		, int from_wide
		, int from_high
		, int from_size

		, int from_x
		, int from_y

		, void (*fun)(T* a, T* b)
	)
	{
		T* skin_buffer = from;
		int skin_w = from_wide;
		int skin_h = from_high;

		T* sight_buffer = paper;
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
		int T = from_y;
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
		if (T > 0)
		{
			sight_start += sight_w * T;
		}
		if (T < 0)
		{
			h += T;
			skin_start += skin_w * (-T);
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
