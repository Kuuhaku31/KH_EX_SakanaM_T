
#include "Game.hpp"

Game::Game(GraphInterface *gi, MessageSystem *mss)
{
    // Initialize Game...
    graphInterface = gi;
    messageSystem = mss;

    // 初始化camera 0
    cameras[0] = new Camera(&main_world);
    cameras[0]->Sight_size(800, 450);
    cameras[0]->Position_move_to(400, 225);

    // 初始化areas
    IMAGE img;
    loadimage(&img, _T("../mat/skin_sakana.png"));
    areas[0] = new Area(&main_world);
    conversion_IMAGE_Area(areas[0], &img);
    areas[0]->Position_move_to(400, 225);

    Say("\nGame Init Success", WIN_COLOR_GRAY);
    Say("Game Created", WIN_COLOR_GRAY);
}

// 只有返回值为0时才会继续运行，为1时正常退出，其他情况表示运行失败
short Game::Update()
{
    short flag = 0;

    // if (mss->KEY_Q)
    // {
    //     mss->Say("You Pressed Q", WIN_COLOR_WHITE);
    //     cameras[0]->Rending(areas[0]);

    //     cameras[0]->To_IMAGE(&(mss->screen));
    // }
    // if (mss->KEY_R)
    // {
    //     mss->Say("You Pressed R", WIN_COLOR_WHITE);
    // }
    // if (mss->KEY_E)
    // {
    //     IMAGE img;
    //     loadimage(&img, _T("../mat/skin_sakana.png"));
    //     SetWorkingImage(&mss->screen);
    //     putimage(0, 0, &img);
    //     SetWorkingImage();
    // }
    // if (mss->ENTER)
    // {
    //     mss->Say("Game Exit", WIN_COLOR_WHITE);
    //     flag = 1;
    // }

    // mss->Photographed();

    return flag;
}

Game::~Game()
{
    // Destroy the game
    // Exit the game
    std::cout << "Game Exit" << std::endl;

    // Exit Game...

    // 释放cameras
    for (int i = 0; i < 10; i++)
    {
        if (cameras[i] != nullptr)
        {
            delete cameras[i];
            cameras[i] = nullptr;
        }
    }

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
