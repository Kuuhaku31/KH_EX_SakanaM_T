
#pragma once

#include "Library.hpp"
#include "MessageSystem.hpp"
#include "Camera.hpp"

class Game
{
public:
	Game(GraphInterface *, MessageSystem *);
	~Game();

	// 更新,需要每次循环调用
	short Update();

private:
	GraphInterface *graphInterface;
	MessageSystem *messageSystem;

	Position main_world;

	Camera *cameras[10];
	Position *objects[10];
	Area *areas[10];
};
