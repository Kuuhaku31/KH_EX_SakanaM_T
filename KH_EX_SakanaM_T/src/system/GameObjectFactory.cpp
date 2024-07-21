
#include "GameObjectFactory.hpp"

GameObjectFactory::GameObjectFactory(MessageSystem *mss) : message_system(mss) {}

GameObjectFactory::~GameObjectFactory() {}

GameObject *GameObjectFactory::CreateGameObject(GameObjectData *data)
{
    GameObject *go = new GameObject(message_system, data->zone, data->position, data->mass, data->velocity);
    go->ObjectSetArea(data->skin, skin01);
    go->ObjectSetArea(data->hitbox, hitbox01);
    go->ObjectGetCollision(object_coll_01)->CollResetTestPoints(data->coll_test_points.px, data->coll_test_points.py);
    return go;
}
