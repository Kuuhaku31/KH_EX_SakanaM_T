
#include "GraphInterface.hpp"

// 用于在控制台打印消息
// 第二个参数表示消息的颜色
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

// 实现IMAGE类和Shape类的互相转化
void conversion_IMAGE_Area(IMAGE *img, Shape *area)
{
    uint w = area->Shape_wide();
    uint h = area->Shape_high();
    uint l = area->Shape_long();
    uint *areab = area->Shape_buffer();

    img->Resize(w, h);
    DWORD *imgb = GetImageBuffer(img);

    for (uint i = 0; i < l; i++)
    {
        imgb[i] = areab[i];
    }
};

void conversion_IMAGE_Area(Shape *area, IMAGE *img)
{
    uint w = img->getwidth();
    uint h = img->getheight();
    area->Shape_reset(w, h);
    uint l = area->Shape_long();
    uint *areab = area->Shape_buffer();

    DWORD *imgb = GetImageBuffer(img);

    for (uint i = 0; i < l; i++)
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

// 清屏
void clearGraph()
{
    SetWorkingImage();
    setbkcolor(BLACK);
    cleardevice();
}

GraphInterface::GraphInterface()
{
    // 初始化窗口，设置参数
    graph_HWND = initgraph(GRAPHWIDE, GRAPHHIGH, 1);
    SetWindowPos(graph_HWND, nullptr, GRAPH_X, GRAPH_Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    SetWindowText(graph_HWND, _T(GAME_NAME));

    graph_HDC = GetImageHDC();
    graph_buffer = (uint *)GetImageBuffer();
    graph_wide = GRAPHWIDE;
    graph_high = GRAPHHIGH;
    graph_long = GRAPHLONG;

    graph_half_wide = GRAPHWIDE / 2;
    graph_half_high = GRAPHHIGH / 2;

    screen.Resize(graph_wide, graph_high);
}

GraphInterface::~GraphInterface()
{
    // 退出窗口
    closegraph();
}

void GraphInterface::ClearScreen()
{
    SetWorkingImage(&screen);
    setbkcolor(0);
    cleardevice();
    SetWorkingImage();
}

void GraphInterface::Photographed()
{
    putimage(0, 0, &screen);
}

void GraphInterface::Receive(Camera *camera)
{
    conversion_IMAGE_Area(&screen, &camera->sight);
}
