
#include <iostream>

#include "GameManager.h"

void Fun_0()
{
	GameManager g;
	g.RUN();
}

int main()
{
	std::cout << "GAME START" << std::endl;
	Fun_0();
	std::cout << "GAME OVER!" << std::endl;
	return 0;
}
