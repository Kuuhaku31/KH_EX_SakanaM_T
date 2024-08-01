
#include "game_systems.hpp"

// 设置点的分布位置
inline void
setpoints(Position* p, int count, int w, int h)
{
    //如果count不是4的倍数
    if(count % 4)
    {
        for(int i = 0; i < count; i++)
        {
            p[i] = Point{w / 2, h / 2};
        }
    }
    else
    {
        int side     = count / 4;
        int spaced_w = w / (side + 1);
        int spaced_h = h / (side + 1);

        Point dp = Point{-w / 2, -h / 2};

        for(int i = 0; i < side; i++)
        {
            p[i]            = Point{spaced_w * (i + 1), 0} + dp;
            p[i + side]     = Point{w, spaced_h * (i + 1)} + dp;
            p[i + 2 * side] = Point{w - spaced_w * (i + 1), h} + dp;
            p[i + 3 * side] = Point{0, h - spaced_h * (i + 1)} + dp;
        }
    }
}


// 创建一个新的鱼
// 传入一个坐标
// **记得释放内存**
inline Fish*
newFish(Position* parent, Point p, Shape* skin, Shape* hitbox, int w, int h)
{
    Fish* f       = new Fish();
    f->parent_pos = parent;  // 设置父对象
    f->Position_xy_to(p);    // 设置位置
    f->movement_mass = 0.5f; // 设置质量

    Area* tem = nullptr;

    f->ObjectGetArea(&tem, fish_main_hitbox);
    tem->Shape_copy(hitbox); // 设置碰撞区域
    tem->Shape_clear(20, 0); // 设置碰撞区域
    tem->Area_align();       // 设置碰撞区域

    f->ObjectGetArea(&tem, fish_main_skin);
    tem->Shape_copy(skin); // 设置皮肤
    tem->Area_align();     // 设置皮肤

    setpoints(f->ObjectGetColl(), f->ObjectGetCollCount(), w, h);

    return f;
}


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


    sakana  = newFish(&main_zone, Point{410, 225}, library->LibMat(shape_img_skin_sakana), library->LibMat(shape_hitbox_sakana), 23, 12);
    sayarin = newFish(&main_zone, Point{400, 250}, library->LibMat(shape_img_skin_ikacyan), library->LibMat(shape_hitbox_ikayan), 35, 35);
    zaruto  = newFish(&main_zone, Point{420, 200}, library->LibMat(shape_img_skin_sakana), library->LibMat(shape_hitbox_sakana), 20, 10);


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

        sakana->ObjectCollTest(&matter);
        sakana->Update();

        sayarin->ObjectCollTest(&matter);
        sayarin->Update();

        sakana->FishDelHitbox(&matter);
        sayarin->FishDelHitbox(&matter);

        // main_camera.Position_xy_to(sayarin);
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
    Fish* temp      = nullptr;
    Area* temp_area = nullptr;
    while(temp = ring_fish.Node_next())
    {
        temp->ObjectGetArea(&temp_area, fish_main_skin);
        main_camera.CameraRending(temp_area);
    }

    main_camera.CameraRending(&wall_skin_02);
    //main_camera.CameraRending(&main_zone, zone_area_wall);
    main_camera.CameraRendingMatter(&matter);

    main_camera.CameraRending(sakana->ObjectGetColl(), sakana->ObjectGetCollCount(), 0x88ff0000);
    main_camera.CameraRending(sayarin->ObjectGetColl(), sayarin->ObjectGetCollCount(), 0x88ff0000);

    main_camera.ObjectGetArea(&temp_area, camera_sight_01);
    graphInterface->Photographed(temp_area);
}
