
#pragma once

#include "Target.h"

class Mouse :
	public Target
{	public:
	Mouse(IMAGE* skin = nullptr)
		: Target(skin)
	{}

};
