
#include "GraphInterface.hpp"

GraphInterface::GraphInterface(MessageSystem *mss) : message_system(mss)
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

void GraphInterface::ReceiveFromMessageSystem()
{
    Shape *shapeLists = message_system->Send_Shapes();
    conversion_IMAGE_Area(&screen, &shapeLists[SourceScreen01]);
}

void GraphInterface::Photographed()
{
    putimage(0, 0, &screen);
}
