
#pragma once

#include "Library.hpp"
#include "GameObjectFactory.hpp"
#include "GraphInterface.hpp"

// 游戏类
class Game
{
public:
	Game(MessageSystem *, GraphInterface *, Library *);
	~Game();

	// 更新,需要每次循环调用
	bool Update();

private:
	// 基本
	MessageSystem *messageSystem;
	GraphInterface *graphInterface;
	Library *library;
	// 工厂
	GameObjectFactory *gameObjectFactory;

	// 地图
	Zone *main_zone;
	Area main_world;
	Area wall_skin_01;
	Area wall_skin_02;

	// 游戏对象
	Camera *main_camera;

	GameObject *sakana;
	GameObject *sayarin;
	GameObject *zaruto;
	Ring<GameObject> *ring_fish;

	// 移动向量
	Point camera_move_vector;
	Vector sakana_force_vector;
	Vector sayarin_force_vector;
};
