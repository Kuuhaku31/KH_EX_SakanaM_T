
#include "Game.hpp"

Game::Game(MessageSystem *mss, GraphInterface *gi, Library *lib) : messageSystem(mss), graphInterface(gi), library(lib)
{
    // Initialize Game...

    // 初始化camera
    main_camera = new Camera(messageSystem, &main_origin, Point{40, 30}, GRAPHWIDE, GRAPHHIGH);
    main_camera->Sight_align();

    // 初始化areas
    IMAGE img;
    loadimage(&img, _T("../mat/area_main.png"));
    conversion_IMAGE_Area(&main_world, &img);
    main_world.Position_set(&main_origin, 0, 0);

    loadimage(&img, _T("../mat/skin_sakana.png"), 0, 0, true);
    areas[0] = new Area(&main_origin);
    conversion_IMAGE_Area(areas[0], &img);
    areas[0]->Position_move_to(400, 225);

    Say("\nGame Init Success", WIN_COLOR_GRAY);
    Say("Game Created", WIN_COLOR_GRAY);
}

inline Point
getMovement(GraphInterface *graphInterface, int w, int s, int a, int d)
{
    Point move_vector;
    if (w)
    {
        move_vector.py = -1;
    }
    if (s)
    {
        move_vector.py = 1;
    }
    if (a)
    {
        move_vector.px = -1;
    }
    if (d)
    {
        move_vector.px = 1;
    }
    return move_vector;
}

// 只有返回值为0时才会继续运行，为1时正常退出，其他情况表示运行失败
short Game::Update()
{
    graphInterface->GetInput();
    short flag = 0;
    if (ENTER)
    {
        Say("Game Exit", WIN_COLOR_WHITE);
        flag = 1;
    }

    graphInterface->ClearScreen();
    main_camera->Clearsight();
    main_camera->Rending(&main_world);

    sakana_move_vector = getMovement(graphInterface, KEY_W, KEY_S, KEY_A, KEY_D);
    camera_move_vector = getMovement(graphInterface, ARR_U, ARR_D, ARR_L, ARR_R);

    main_camera->Position_move(camera_move_vector);
    areas[0]->Position_move(sakana_move_vector);

    main_camera->Rending(areas[0]);

    main_camera->SendToMessageSystem(SourceScreen01);

    graphInterface->ReceiveFromMessageSystem();
    graphInterface->Photographed();

    return flag;
}

Game::~Game()
{
    // Destroy the game
    // Exit the game
    std::cout << "Game Exit" << std::endl;

    // Exit Game...

    // 释放cameras
    // for (int i = 0; i < 10; i++)
    // {
    //     if (cameras[i] != nullptr)
    //     {
    //         delete cameras[i];
    //         cameras[i] = nullptr;
    //     }
    // }

    // 释放objects
    for (int i = 0; i < 10; i++)
    {
        if (objects[i] != nullptr)
        {
            delete objects[i];
            objects[i] = nullptr;
        }
    }

    // 释放areas
    for (int i = 0; i < 10; i++)
    {
        if (areas[i] != nullptr)
        {
            delete areas[i];
            areas[i] = nullptr;
        }
    }

    std::cout << "Game Exit Success" << std::endl;
    Say("Game Destroyed", WIN_COLOR_GRAY);
}
