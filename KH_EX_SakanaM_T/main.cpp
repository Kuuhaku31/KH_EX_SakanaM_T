
#include <iostream>

#include "GameManager.hpp"

void Fun_0()
{
	GameManager g;
	g.RUN();
}

int main()
{
	std::cout << "\nGAME START" << std::endl;
	Fun_0();
	std::cout << "\nGAME OVER!" << std::endl;
	return 0;
}
