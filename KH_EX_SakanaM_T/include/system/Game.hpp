
#pragma once

#include "Library.hpp"
#include "GameObjects.hpp"
#include "GraphInterface.hpp"

// 游戏类
class Game
{
public:
	Game(MessageSystem *, GraphInterface *, Library *);
	~Game();

	// 更新,需要每次循环调用
	short Update();

private:
	// ^
	MessageSystem *messageSystem;
	GraphInterface *graphInterface;
	Library *library;

	Position main_origin;
	Area main_world;

	Camera *main_camera;
	GameObject *sakana;

	Point sakana_move_vector;
	Point camera_move_vector;

	Vector sakana_force_vector;
};
