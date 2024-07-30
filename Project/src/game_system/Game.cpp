
#include "game_systems.hpp"

Game::Game(GraphInterface* gi, Library* lib)
    : graphInterface(gi)
    , library(lib)
{
    // Initialize Game...
    Say("Game Init...", WIN_COLOR_GRAY);

    library->LibZone(&main_zone);
    relative_area_vector = Vector{0.05f, 0.005f};

    main_zone.ZoneSetColor(0x880000ff, zone_area_wall);

    // 初始化areas
    world_skin.parent_pos = &main_zone;
    world_skin.Shape_copy(library->LibMat(shape_img_world_ground));

    // 初始化wallskin
    wall_skin_01.parent_pos = &main_zone;
    wall_skin_01.Shape_copy(library->LibMat(shape_img_wall_01));
    wall_skin_02.parent_pos = &main_zone;
    wall_skin_02.Shape_copy(library->LibMat(shape_img_wall_02));

    // 初始化matter
    matter.parent_pos = &main_zone;
    matter.Shape_copy(library->LibMat(shape_img_wall_01));
    matter.Shape_clear(0x00ff0000, 0);

    // 初始化camera
    main_camera.parent_pos = &main_zone;
    main_camera.Position_xy_to(Point{400, 200});
    main_camera.CameraSight_size(GRAPHWIDE / 4, GRAPHHIGH / 4);
    main_camera.CameraSight_align();

    // 工厂
    // gameObjectFactory = new GameObjectFactory(mss, library);

    sakana = new Fish();
    sakana->Position_xy_to(Point{410, 225});
    sakana->movement_mass = 0.5f;
    sakana->ObjectGetArea(fish_main_hitbox)->Shape_copy(library->LibMat(shape_hitbox16));
    sakana->ObjectGetArea(fish_main_hitbox)->Shape_clear(20, 0);
    sakana->ObjectGetArea(fish_main_hitbox)->Area_align();
    sakana->ObjectGetArea(fish_main_skin)->Shape_copy(library->LibMat(shape_img_skin_sakana));
    sakana->ObjectGetArea(fish_main_skin)->Area_align();
    sakana->ObjectGetCollision(fish_main_coll)->CollResetTestPoints(12, 18, 10);

    sayarin = new Fish();
    sayarin->Position_xy_to(Point{400, 250});
    sayarin->ObjectGetArea(fish_main_hitbox)->Shape_copy(library->LibMat(shape_img_skin_ikacyann));
    sayarin->ObjectGetArea(fish_main_hitbox)->Shape_clear(20, 0);
    sayarin->ObjectGetArea(fish_main_hitbox)->Area_align();
    sayarin->ObjectGetArea(fish_main_skin)->Shape_copy(library->LibMat(shape_img_skin_ikacyann));
    sayarin->ObjectGetArea(fish_main_skin)->Area_align();
    sayarin->ObjectGetCollision(fish_main_coll)->CollResetTestPoints(24, 28, 28);

    zaruto = new Fish();
    zaruto->Position_xy_to(Point{420, 200});
    zaruto->ObjectGetArea(fish_main_skin)->Shape_copy(library->LibMat(shape_img_skin_sakana));
    zaruto->ObjectGetArea(fish_main_skin)->Area_align();

    // 初始化fishRing
    ring_fish.Node_add(sakana);
    ring_fish.Node_add(sayarin);
    ring_fish.Node_add(zaruto);

    Say("Game Init Success", WIN_COLOR_GRAY);
}

Game::~Game()
{
    // Exit Game...

    // 释放ringfish
    ring_fish.Node_delete_all();

    Say("Game Destroyed", WIN_COLOR_GRAY);
}

inline Point
getPoint(bool w, bool s, bool a, bool d, int f = 1)
{
    Point p;

    if(w) { p.py -= f; }
    if(s) { p.py += f; }
    if(a) { p.px -= f; }
    if(d) { p.px += f; }

    return p;
}

inline Vector
getVector(bool w, bool s, bool a, bool d, float f = 1.0f)
{
    Vector force_vector;

    if(w) { force_vector.vy--; }
    if(s) { force_vector.vy++; }
    if(a) { force_vector.vx--; }
    if(d) { force_vector.vx++; }

    force_vector = unit(force_vector) * f;

    return force_vector;
}

#define ip graphInterface->input

// 只有返回值为true时才会继续运行
bool
Game::Update()
{
    bool flag = true;

    // 获取输入
    {
        ip.Input_Get_Messagelist();
        if(ip.enter)
        {
            Say("Game Exit...", WIN_COLOR_WHITE);
            flag = false;
        }

        camera_move_vector   = getPoint(ip.arr_U, ip.arr_D, ip.arr_L, ip.arr_R, 10);
        sakana_force_vector  = getVector(ip.key_W, ip.key_S, ip.key_A, ip.key_D, 20);
        sayarin_force_vector = getVector(ip.key_I, ip.key_K, ip.key_J, ip.key_L, 20);
    }

    // 更新
    {
        main_camera += camera_move_vector;
        sakana->ObjectAddForce(sakana_force_vector);
        sayarin->ObjectAddForce(sayarin_force_vector);

        sakana->movement_resistance  = relative_area_vector;
        sayarin->movement_resistance = relative_area_vector;

        sakana->FishAddHitbox(&matter);
        sayarin->FishAddHitbox(&matter);

        rending();

        sakana->ObjectGetCollision(fish_main_coll)->CollTest(&matter);
        sakana->Update();

        sayarin->ObjectGetCollision(fish_main_coll)->CollTest(&matter);
        sayarin->Update();

        sakana->FishDelHitbox(&matter);
        sayarin->FishDelHitbox(&matter);
    }

    return flag;
}

#undef ip

// 渲染
void
Game::rending()
{
    // graphInterface->ClearScreen();
    main_camera.CameraClearSight();

    main_camera.CameraRending(&world_skin);
    main_camera.CameraRending(&wall_skin_01);

    // 渲染ringfish所有对象
    Fish* temp = nullptr;
    while(temp = ring_fish.Node_next())
    {
        main_camera.CameraRending(temp->ObjectGetArea(fish_main_skin));
    }

    main_camera.CameraRending(&wall_skin_02);
    //main_camera.CameraRending(&main_zone, zone_area_wall);
    main_camera.CameraRendingMatter(&matter);

    main_camera.CameraRending(sakana->ObjectGetCollision(fish_main_coll), 0x88ff0000);
    main_camera.CameraRending(sayarin->ObjectGetCollision(fish_main_coll), 0x88ff0000);

    graphInterface->Photographed(main_camera.ObjectGetArea(0));
}
