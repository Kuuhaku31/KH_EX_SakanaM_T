
#pragma once

#include "GameObjects.hpp"

class GameObjectFactory
{
public:
    GameObjectFactory(MessageSystem *);
    ~GameObjectFactory();

    // 创建游戏对象
    GameObject *CreateGameObject(GameObjectData *);

private:
    MessageSystem *message_system;
};
