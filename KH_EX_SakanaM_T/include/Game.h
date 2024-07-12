
#pragma once

#include "MessageSystem.h"

class Game
{
public:
	Game();
	~Game();

	// 初始化
	short Init(MessageSystem *);

	// 更新,需要每次循环调用
	short Update();

	// 退出
	short Exit();

private:
	MessageSystem *mss = nullptr;
};
