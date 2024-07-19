
#include "MessageSystem.hpp"

void Say(std::string str, int txtCode, int bakcgroudCode)
{
    // 设置控制台文字颜色
    int code = txtCode + (bakcgroudCode << 4);
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleOutput, code);
    std::cout << std::endl
              << str;
    SetConsoleTextAttribute(hConsoleOutput, WIN_COLOR_WHITE);
}

void conversion_IMAGE_Area(IMAGE *img, Shape *area)
{
    int w = area->Shape_wide();
    int h = area->Shape_high();
    int l = area->Shape_long();
    int *areab = area->Shape_buffer();

    img->Resize(w, h);
    DWORD *imgb = GetImageBuffer(img);

    for (int i = 0; i < l; i++)
    {
        imgb[i] = areab[i];
    }
};

void conversion_IMAGE_Area(Shape *area, IMAGE *img)
{
    int w = img->getwidth();
    int h = img->getheight();
    area->Shape_reset(w, h);
    int l = area->Shape_long();
    int *areab = area->Shape_buffer();

    DWORD *imgb = GetImageBuffer(img);

    for (int i = 0; i < l; i++)
    {
        areab[i] = imgb[i];
    }
};

void get_resources(Shape *shape, std::string path)
{
    IMAGE img;
    loadimage(&img, path.c_str());
    conversion_IMAGE_Area(shape, &img);
}

void clearGraph()
{
    SetWorkingImage();
    setbkcolor(BLACK);
    cleardevice();
}

// MessageSystem
int MessageSystem::Send_Message_to_GameManager()
{

    if (system_message_count == 0)
    {
        return 0;
    }
    else
    {
        int msg = system_message_queue[system_message_count];
        system_message_queue[system_message_count] = 0;
        system_message_count--;

        return msg;
    }
}

void MessageSystem::Receive_Message_from_GameManager(char msg)
{
    if (system_message_count >= SYSTEM_MESSAGE_MAX)
    {
        return;
    }
    else
    {
        system_message_count++;
        system_message_queue[system_message_count] = msg;
    }
}

void MessageSystem::Enable_Message_to_GameManager()
{
}

void MessageSystem::Disable_Message_to_GameManager()
{
}

Shape *MessageSystem::Send_Shapes(ShapeType t)
{
    return shape_queue[t];
}

void MessageSystem::Receive_Shapes(Shape *shape, ShapeType i)
{
    shape_queue[i] = shape;
}
