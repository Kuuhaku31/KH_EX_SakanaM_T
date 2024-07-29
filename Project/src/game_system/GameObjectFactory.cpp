
#include "GameObjectFactory.hpp"

inline GameObject *buildGameObject(MessageSystem *message_system, Zone *zone, GameObjectData *data)
{
    GameObject *go = new GameObject(message_system, zone, ZEROPOINT, data->mass, data->velocity);

    go->ObjectGetArea(skin01)->Shape_copy(data->skin);
    go->ObjectGetArea(skin01)->Area_align();
    go->ObjectGetArea(hitbox01)->Shape_copy(data->hitbox);
    go->ObjectGetArea(hitbox01)->Area_align();
    go->ObjectGetCollision(object_coll_01)->CollResetTestPoints(data->coll_test_points.px, data->coll_test_points.py);
    return go;
}

inline void initGameObjectDatas(Library *library, GameObjectData *game_object_datas)
{
    // 初始化全部GameObject数据
    // 初始化sakana他们
    game_object_datas[game_object_sakana] =
        {
            ZEROVECTOR,
            1.0f,
            library->LibMat(shape_img_skin_sakana),
            library->LibMat(shape_hitbox16),
            Point{10, 10}};
}

GameObjectFactory::GameObjectFactory(MessageSystem *mss, Library *lib) : message_system(mss), library(lib) { initGameObjectDatas(library, game_object_datas); }
GameObjectFactory::~GameObjectFactory() {}

GameObject *GameObjectFactory::CreateGameObject(Zone *z, GameObjectType t, Point p)
{
    GameObject *go = buildGameObject(message_system, z, &game_object_datas[t]);
    go->Position_move_to(p);
    return go;
}
