
#include "Game.hpp"

#define KEY_W graphInterface->Key_W()
#define KEY_S graphInterface->Key_S()
#define KEY_A graphInterface->Key_A()
#define KEY_D graphInterface->Key_D()

#define KEY_I graphInterface->Key_I()
#define KEY_K graphInterface->Key_K()
#define KEY_J graphInterface->Key_J()
#define KEY_L graphInterface->Key_L()

#define KEY_Q graphInterface->Key_Q()
#define KEY_E graphInterface->Key_E()
#define KEY_R graphInterface->Key_R()
#define KEY_F graphInterface->Key_F()

#define ARR_U graphInterface->Arr_U()
#define ARR_D graphInterface->Arr_D()
#define ARR_L graphInterface->Arr_L()
#define ARR_R graphInterface->Arr_R()

#define SPACE graphInterface->Space()
#define SHIFT graphInterface->Shift()
#define ESC__ graphInterface->Esc__()
#define ENTER graphInterface->Enter()

#define MOUSE_X graphInterface->Mouse_X()
#define MOUSE_Y graphInterface->Mouse_Y()
#define MOUSE_DX graphInterface->MouseDX()
#define MOUSE_DY graphInterface->MouseDY()
#define MOUSE_V graphInterface->Mouse_V()
#define MOUSE_L graphInterface->Mouse_L()
#define MOUSE_R graphInterface->Mouse_R()
#define MOUSE_M graphInterface->Mouse_M()
#define MOUSE_W graphInterface->Mouse_W()

Game::Game(MessageSystem* mss, GraphInterface* gi, Library* lib)
    : messageSystem(mss)
    , graphInterface(gi)
    , library(lib)
{
    // Initialize Game...
    library->InitMat();

    // 初始化zone
    std::string paths[20] = {
        MATPATH "/area_main.png",
        MATPATH "/area_wall.png",
        MATPATH "/area_main.png"};
    int bit[20] = {main_area, wall_area_01, relative_area_01};

    main_zone = new_ZoneMade(paths, bit, 3);
    main_zone->ZoneSetRelative(relative_area_01, Vector{7.5f, 0.0007f});
    main_zone->ZoneSetWallCollForce(wall_area_01, 100);
    main_zone->ZoneSetColor(wall_area_01, 0x880000ff);

    // 初始化areas
    main_world.Shape_copy(library->LibMat(shape_img_world_ground));
    main_world.Position_set(main_zone);

    // 初始化wallskin
    wall_skin_01.Position_set(main_zone);
    wall_skin_01.Shape_copy(library->LibMat(shape_img_wall_01));
    wall_skin_02.Position_set(main_zone);
    wall_skin_02.Shape_copy(library->LibMat(shape_img_wall_02));

    // 初始化camera
    main_camera = new Camera(messageSystem, main_zone, Point{40, 30}, GRAPHWIDE / 4, GRAPHHIGH / 4);
    main_camera->Sight_align();

    // 工厂
    gameObjectFactory = new GameObjectFactory(mss, library);

    sakana  = gameObjectFactory->CreateGameObject(main_zone, game_object_sakana, Point{410, 225});
    sayarin = gameObjectFactory->CreateGameObject(main_zone, game_object_sakana, Point{400, 250});
    zaruto  = gameObjectFactory->CreateGameObject(main_zone, game_object_sakana, Point{420, 200});

    // 初始化fishRing
    ring_fish = new Ring<GameObject>();
    ring_fish->Node_add(sakana);
    ring_fish->Node_add(sayarin);
    ring_fish->Node_add(zaruto);

    Say("Game Init Success", WIN_COLOR_GRAY);
}

inline Point
getMovement(GraphInterface* graphInterface, int w, int s, int a, int d, int f)
{
    Point move_vector;
    if(w)
    {
        move_vector.py = -f;
    }
    if(s)
    {
        move_vector.py = f;
    }
    if(a)
    {
        move_vector.px = -f;
    }
    if(d)
    {
        move_vector.px = f;
    }
    return move_vector;
}

inline Vector
getForce(GraphInterface* graphInterface, int w, int s, int a, int d, float f)
{
    Vector force_vector;
    if(w)
    {
        force_vector.vy = -1.0f;
    }
    if(s)
    {
        force_vector.vy = 1.0f;
    }
    if(a)
    {
        force_vector.vx = -1.0f;
    }
    if(d)
    {
        force_vector.vx = 1.0f;
    }

    force_vector = unit(force_vector) * f;

    return force_vector;
}

// 只有返回值为true时才会继续运行
bool
Game::Update()
{
    bool flag = true;

    // 获取输入
    {
        graphInterface->GetInput();
        if(ENTER)
        {
            Say("Game Exit...", WIN_COLOR_WHITE);
            flag = false;
        }

        camera_move_vector   = getMovement(graphInterface, ARR_U, ARR_D, ARR_L, ARR_R, 10);
        sakana_force_vector  = getForce(graphInterface, KEY_W, KEY_S, KEY_A, KEY_D, 100);
        sayarin_force_vector = getForce(graphInterface, KEY_I, KEY_K, KEY_J, KEY_L, 100);
    }

    // 更新
    {

        main_camera->Position_move(camera_move_vector);
        sakana->ObjectAddForce(sakana_force_vector);
        sayarin->ObjectAddForce(sayarin_force_vector);
        sakana->GameObjectUpdate();
        sayarin->GameObjectUpdate();
    }

    // 渲染
    {
        // graphInterface->ClearScreen();
        main_camera->Clearsight();

        main_camera->Rending(&main_world);
        main_camera->Rending(&wall_skin_01);

        // 渲染ringfish所有对象
        GameObject* temp = nullptr;
        while(temp = ring_fish->Node_next())
        {
            main_camera->RendingObject(temp, skin01);
        }

        main_camera->Rending(&wall_skin_02);
        // main_camera->RendingZone(main_zone, wall_area_01);

        main_camera->SendToMessageSystem(SourceScreen01);

        graphInterface->ReceiveFromMessageSystem();
        graphInterface->Photographed();
    }

    return flag;
}

Game::~Game()
{
    // Exit Game...

    // 释放工厂
    delete gameObjectFactory;

    // 释放Zone
    delete main_zone;

    // 释放cameras
    for(int i = 0; i < 10; i++)
    {
        if(main_camera != nullptr)
        {
            delete main_camera;
            main_camera = nullptr;
        }
    }

    // 释放ringfish
    if(ring_fish != nullptr)
    {
        delete ring_fish;
        ring_fish = nullptr;
    }

    Say("Game Destroyed", WIN_COLOR_GRAY);
}
