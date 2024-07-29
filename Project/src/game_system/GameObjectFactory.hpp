
#pragma once

#define GAME_OBJECT_TYPE_MAX 100

#include "Library.hpp"
#include "GameObjects.hpp"

enum GameObjectType
{
    game_object,
    game_object_sakana,
};

inline GameObject *buildGameObject(MessageSystem *, Zone *, GameObjectData *);
inline void initGameObjectDatas(Library *, GameObjectData *);

class GameObjectFactory
{
public:
    GameObjectFactory(MessageSystem *, Library *);
    ~GameObjectFactory();

    // 创建游戏对象
    GameObject *CreateGameObject(Zone *, GameObjectType, Point);

private:
    MessageSystem *message_system;
    Library *library;
    GameObjectData game_object_datas[GAME_OBJECT_TYPE_MAX];
};
