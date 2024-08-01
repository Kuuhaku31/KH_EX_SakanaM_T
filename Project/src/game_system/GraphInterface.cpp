
#include "game_systems.hpp"

void
GraphInterface::NewGraph(int w, int h, int x, int y, char* name)
{
    // 初始化窗口，设置参数
    graph_HWND = initgraph(w, h, 1);
    SetWindowPos(graph_HWND, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    SetWindowText(graph_HWND, name);

    // 全屏
    // SetWindowLong(graph_HWND, GWL_STYLE, GetWindowLong(graph_HWND, GWL_STYLE) - WS_CAPTION);
    // SetWindowPos(graph_HWND, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);

    graph_HDC    = GetImageHDC();
    graph_buffer = (int*)GetImageBuffer();
    graph_wide   = w;
    graph_high   = h;
    graph_long   = x * y;

    graph_half_wide = w / 2;
    graph_half_high = h / 2;

    // 输出参数
    output_p1 = {0, 0};
    output_p2 = {w, h};

    output_wide = output_p2.px - output_p1.px;
    output_high = output_p2.py - output_p1.py;
}

void
GraphInterface::CloseGraph()
{
    closegraph();
}

void
GraphInterface::ClearScreen()
{
    setbkcolor(0);
    cleardevice();
    SetWorkingImage();
}

void
GraphInterface::Photographed(Shape* shape)
{
    IMAGE img;
    conversion_IMAGE_Area(&img, shape);

    StretchBlt(
        graph_HDC,
        output_p1.px,
        output_p1.py,
        output_wide,
        output_high,

        GetImageHDC(&img),
        0,
        0,
        img.getwidth(),
        img.getheight(),

        SRCCOPY);
}

Point
GraphInterface::MousePointInSight(int w, int h)
{
    // (mouse_x - output_x1)/target_x = output_wide/sight_wide
    return Point{(input.mouse_X - output_p1.px) * w / output_wide, (input.mouse_Y - output_p1.py) * h / output_high};
}
