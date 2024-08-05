
#include "game_systems.hpp"

inline Point
getPoint(bool w, bool s, bool a, bool d, int f = 1)
{
    Point p;

    if(w) p.py -= f;
    if(s) p.py += f;
    if(a) p.px -= f;
    if(d) p.px += f;

    return p;
}

inline Vector
getVector(bool w, bool s, bool a, bool d, float f = 1.0f)
{
    Vector force_vector;

    if(w) force_vector.vy--;
    if(s) force_vector.vy++;
    if(a) force_vector.vx--;
    if(d) force_vector.vx++;

    force_vector = unit(force_vector) * f;

    return force_vector;
}


// 设置点的分布位置
inline void
setpoints(Position* p, int count, int w, int h)
{
    // 如果count不是4的倍数
    if(count % 4)
    {
        for(int i = 0; i < count; i++)
        {
            p[i] = Point{ w / 2, h / 2 };
        }
    }
    else
    {
        int side     = count / 4;
        int spaced_w = w / (side + 1);
        int spaced_h = h / (side + 1);

        Point dp = Point{ -w / 2, -h / 2 };

        for(int i = 0; i < side; i++)
        {
            p[i]            = Point{ spaced_w * (i + 1), 0 } + dp;
            p[i + side]     = Point{ w, spaced_h * (i + 1) } + dp;
            p[i + 2 * side] = Point{ w - spaced_w * (i + 1), h } + dp;
            p[i + 3 * side] = Point{ 0, h - spaced_h * (i + 1) } + dp;
        }
    }
}


// 创建一个新的鱼
// 传入一个坐标
// **记得释放内存**
inline Fish*
newFish(Position* parent, Point p, Shape* skin, Shape* hitbox, int w, int h, Area* ca, Area* da, Shape* bullet_skin, Shape* bullet_explode_range)
{
    Fish* f          = new Fish(parent, p, ca, da);
    f->movement_mass = 0.5f; // 设置质量

    Area* tem = nullptr;

    f->ObjectGetArea(&tem, fish_main_hitbox);
    tem->Shape_copy(hitbox); // 设置碰撞区域
    tem->Shape_clear(20, 0); // 设置碰撞区域
    tem->Area_align();       // 设置碰撞区域

    f->ObjectGetArea(&tem, fish_main_skin);
    tem->Shape_copy(skin); // 设置皮肤
    tem->Area_align();     // 设置皮肤

    f->ObjectGetArea(&tem, fish_bullet_skin);
    tem->Shape_copy(bullet_skin); // 设置皮肤
    tem->Area_align();            // 设置皮肤

    f->ObjectGetArea(&tem, fish_bullet_hitbox);
    tem->Shape_copy(bullet_explode_range); // 设置碰撞区域
    tem->Shape_clear(20, 0);               //
    tem->Area_align();                     // 设置碰撞区域

    setpoints(f->ObjectGetColl(), f->ObjectGetCollCount(), w, h);

    return f;
}


Game::Game(GraphInterface* gi, Library* lib)
    : graphInterface(gi)
    , library(lib)
{
    // Initialize Game...
    Say("Game Init...", WIN_COLOR_GRAY);

    // 初始化zone
    int zonetypes[3] = { zone_area_main, zone_area_wall, zone_area_relative };
    library->LibZone(&main_zone, zonetypes, 3);
    relative_area_vector = Vector{ 0.05f, 0.005f };

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

    // 初始化area_damage
    area_damage.parent_pos = &main_zone;
    area_damage.Shape_copy(library->LibMat(shape_area_main));
    area_damage.Shape_clear(1, 0);

    // 初始化camera
    main_camera.parent_pos = &main_zone;
    main_camera.Position_xy_to(Point{ 400, 200 });
    main_camera.CameraSight_size(GRAPHWIDE / 4, GRAPHHIGH / 4);
    main_camera.CameraSight_align();


    sakana  = newFish(&main_zone, Point{ 410, 225 }, library->LibMat(shape_img_skin_sakana), library->LibMat(shape_hitbox_sakana), 23, 12, &matter, &area_damage, library->LibMat(shape_img_skin_bullet), library->LibMat(shape_hitbox_ikayan));
    sayarin = newFish(&main_zone, Point{ 400, 250 }, library->LibMat(shape_img_skin_ikacyan), library->LibMat(shape_img_skin_ikacyan), 35, 35, &matter, &area_damage, library->LibMat(shape_img_skin_bullet), library->LibMat(shape_hitbox_ikayan));
    zaruto  = newFish(&main_zone, Point{ 420, 200 }, library->LibMat(shape_img_skin_sakana), library->LibMat(shape_hitbox_sakana), 20, 10, &matter, &area_damage, library->LibMat(shape_img_skin_bullet), library->LibMat(shape_hitbox_ikayan));


    // 初始化fishRing
    ring_fish.Node_add(sakana);
    ring_fish.Node_add(sayarin);
    ring_fish.Node_add(zaruto);

    Say("Game Init Success", WIN_COLOR_GRAY);
}

Game::~Game()
{
    // Exit Game...

    // 释放ring
    ring_fish.Node_delete_all();
    ring_bullet.Node_delete_all();

    Say("Game Destroyed", WIN_COLOR_GRAY);
}

// 只有返回值为true时才会继续运行
bool
Game::Update()
{
    getInput();
    update01();
    rending();
    update02();
    return is_game_continue;
}

// 渲染
void
Game::rending()
{
    // graphInterface->ClearScreen();
    main_camera.CameraClearSight();

    main_camera.CameraRending(&world_skin);
    main_camera.CameraRending(&wall_skin_01);

    Area* temp_area = nullptr;

    // 渲染ringfish所有对象
    Fish* temp = nullptr;
    while(temp = ring_fish.Node_next())
    {
        temp->ObjectGetArea(&temp_area, fish_main_skin);
        main_camera.CameraRending(temp_area);

        temp->ObjectGetArea(&temp_area, fish_HP_bar);
        main_camera.CameraRending(temp_area);

        // temp->ObjectGetArea(&temp_area, fish_power_bar);
        // main_camera.CameraRending(temp_area);
    }

    // 渲染ringbullet所有对象
    Bullet* temp_bullet = nullptr;
    while(temp_bullet = ring_bullet.Node_next())
    {
        temp_bullet->ObjectGetArea(&temp_area, bullet_skin);
        main_camera.CameraRending(temp_area);
    }

    main_camera.CameraRending(&wall_skin_02);
    // main_camera.CameraRending(&main_zone, zone_area_wall);
    // main_camera.CameraRendingMatter(&matter);
    // main_camera.CameraRendingMatter(&area_damage);

    // main_camera.CameraRending(sakana->ObjectGetColl(), sakana->ObjectGetCollCount(), 0x88ff0000);
    // main_camera.CameraRending(sayarin->ObjectGetColl(), sayarin->ObjectGetCollCount(), 0x88ff0000);

    main_camera.ObjectGetArea(&temp_area, camera_sight_01);
    graphInterface->Photographed(temp_area);
}

#define ip graphInterface->input

void
Game::getInput()
{
    ip.Input_Get_Messagelist();
    if(ip.enter)
    {
        Say("Game Exit...", WIN_COLOR_WHITE);
        is_game_continue = false;
    }

    camera_move_vector   = getPoint(ip.arr_U, ip.arr_D, ip.arr_L, ip.arr_R, 10);
    sakana_force_vector  = getVector(ip.key_W, ip.key_S, ip.key_A, ip.key_D, 20);
    sayarin_force_vector = getVector(ip.key_I, ip.key_K, ip.key_J, ip.key_L, 20);
}

void
Game::update01()
{
    main_camera += camera_move_vector;
    sakana->ObjectAddForce(sakana_force_vector);
    sayarin->ObjectAddForce(sayarin_force_vector);

    sakana->movement_resistance  = relative_area_vector;
    sayarin->movement_resistance = relative_area_vector;

    sakana->FishAddHitbox(&matter);
    sayarin->FishAddHitbox(&matter);

    // 当按下空格键时，鱼发射子弹
    if(ip.space)
    {
        Vector  v = unit(zaruto->Position_root_xy() - sakana->Position_root_xy());
        Bullet* b = sakana->FishShoot(&main_zone, v);
        ring_bullet.Node_add(b);
    }

    // 移动鼠标追踪zaruto
    Area* tem = nullptr;
    main_camera.ObjectGetArea(&tem, camera_sight_01);
    Point p = graphInterface->MousePointInSight(tem->Shape_wide(), tem->Shape_high());
    p += tem->Position_root_xy();
    zaruto->Position_xy_to(p);
}

void
Game::update02()
{
    sakana->Update();
    sayarin->Update();

    // 更新ringbullet所有对象
    Bullet* temp_bullet = nullptr;
    while(temp_bullet = ring_bullet.Node_next())
    {
        if(temp_bullet->BulletIsAlive())
        {
            temp_bullet->ObjectCollTest(&matter);
            temp_bullet->Update();
        }
        else
        {
            ring_bullet.Node_delete();
        }
    }

    sakana->FishDelHitbox(&matter);
    sayarin->FishDelHitbox(&matter);

    // main_camera.Position_xy_to(sayarin);
}

#undef ip
