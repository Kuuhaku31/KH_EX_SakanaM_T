
#include "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\include\system\MessageSystem.hpp"

class ZoneFactory
{
public:
	Zone *Made(std::string *paths, int pathCount)
	{
		for (int i = 0; i < pathCount; i++)
		{
			IMAGE img;
			loadimage(&img, paths[i].c_str());

			Shape s;
			conversion_IMAGE_Area(&s, &img);
		}

		Zone *z = new Zone;

		return z;
	}
};

int main()
{
	std::cout << "GAME START" << std::endl;

	ZoneFactory zf;
	std::string paths[5] = {
		"src/zone/zone01.txt",
		"src/zone/zone02.txt",
		"src/zone/zone03.txt",
		"src/zone/zone04.txt",
		"src/zone/zone05.txt"};

	Zone *z = zf.Made(paths, 5);

	delete z;

	std::cout << "\nGAME OVER!" << std::endl;
	return 0;
}
