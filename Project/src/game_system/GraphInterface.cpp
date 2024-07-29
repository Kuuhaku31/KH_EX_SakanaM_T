
#include "GraphInterface.hpp"

GraphInterface::GraphInterface(MessageSystem *mss) : message_system(mss)
{
    // 初始化窗口，设置参数
    graph_HWND = initgraph(GRAPHWIDE, GRAPHHIGH, 1);
    SetWindowPos(graph_HWND, nullptr, GRAPH_X, GRAPH_Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    SetWindowText(graph_HWND, _T(GAME_NAME));

    graph_HDC = GetImageHDC();
    graph_buffer = (int *)GetImageBuffer();
    graph_wide = GRAPHWIDE;
    graph_high = GRAPHHIGH;
    graph_long = GRAPHLONG;

    graph_half_wide = GRAPHWIDE / 2;
    graph_half_high = GRAPHHIGH / 2;

    screen.Resize(graph_wide, graph_high);

    // 输出参数
    output_x1 = 0;
    output_y1 = 0;
    output_x2 = GRAPHWIDE;
    output_y2 = GRAPHHIGH;

    output_wide = output_x2 - output_x1;
    output_high = output_y2 - output_y1;
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
    conversion_IMAGE_Area(&screen, message_system->Send_Shapes(SourceScreen01));
}

void GraphInterface::Photographed()
{
    // putimage(0, 0, &screen);
    StretchBlt(
        graph_HDC,
        0,         // output_x1,
        0,         // output_y1,
        GRAPHWIDE, // output_x2,
        GRAPHHIGH, // output_y2,

        GetImageHDC(&screen),
        0,
        0,
        screen.getwidth(),
        screen.getheight(),

        SRCCOPY);
}

// int Camera::Mouse_X(int x)
// {
//     return x * kx + Get_x() - shape_wide / 2;
// }

// int Camera::Mouse_Y(int y)
// {
//     return y * ky + Get_y() - shape_high / 2;
// }
