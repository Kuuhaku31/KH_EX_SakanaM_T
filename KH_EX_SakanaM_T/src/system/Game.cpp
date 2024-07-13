
#include "Game.hpp"

Game::Game()
{
    // Initialize the game
    std::cout << "\nGame Created";
}

Game::~Game()
{
    // Destroy the game
    std::cout << "\nGame Destroyed";
}

short Game::Init(MessageSystem *ms)
{
    // Initialize Game...
    mss = ms;

    // 设置graph输出格式
    mss->Photographed_format();
    mss->screen.Resize(800, 450);

    // 初始化camera 0
    cameras[0] = new Camera();
    cameras[0]->Shape_reset(800, 450);
    cameras[0]->Move_to(400, 225);

    // 初始化objects
    IMAGE img;
    loadimage(&img, _T("../mat/skin_sakana.png"));
    objects[0] = new Renderer();
    ((Renderer *)objects[0])->Reset_skin(&img);
    objects[0]->Move_to(400, 225);

    mss->Say("\nGame Init Success", WIN_COLOR_GRAY);
    return 0;
}

// 只有返回值为0时才会继续运行，为1时正常退出，其他情况表示运行失败
short Game::Update()
{
    short flag = 0;
    mss->ClearScreen();

    mss->input.GetInput();

    if (mss->KEY_Q)
    {
        mss->Say("You Pressed Q", WIN_COLOR_WHITE);
        cameras[0]->Rending(((Renderer *)objects[0]));

        cameras[0]->To_IMAGE(&(mss->screen));
    }
    if (mss->KEY_R)
    {
        mss->Say("You Pressed R", WIN_COLOR_WHITE);
    }
    if (mss->KEY_E)
    {
        IMAGE img;
        loadimage(&img, _T("../mat/skin_sakana.png"));
        SetWorkingImage(&mss->screen);
        putimage(0, 0, &img);
        SetWorkingImage();
    }
    if (mss->ENTER)
    {
        mss->Say("Game Exit", WIN_COLOR_WHITE);
        flag = 1;
    }

    mss->Photographed();

    return flag;
}

short Game::Exit()
{
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

    std::cout << "Game Exit Success" << std::endl;
    return 0;
}
