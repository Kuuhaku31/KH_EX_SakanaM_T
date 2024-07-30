
#pragma once

#include "GameObjects.hpp"
#include "Input.hpp"
#include "ring.hpp"

#define GRAPHWIDE 1600
#define GRAPHHIGH 900
#define GRAPHLONG 1600 * 900

#define GRAPH_X 40
#define GRAPH_Y 30

#define GAME_NAME "Sakana"

// 用于在控制台打印消息
inline void
Say(std::string str, int txtCode = WIN_COLOR_WHITE, int bakcgroudCode = KHCOLOR_BLACK)
{
    // 设置控制台文字颜色
    int    code           = txtCode + (bakcgroudCode << 4);
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleOutput, code);
    std::cout << std::endl
              << str;
    SetConsoleTextAttribute(hConsoleOutput, WIN_COLOR_WHITE);
}

// 实现IMAGE类和Shape类的互相转化
inline void
conversion_IMAGE_Area(IMAGE* img, Shape* area)
{
    int           w     = area->Shape_wide();
    int           h     = area->Shape_high();
    int           l     = area->Shape_long();
    unsigned int* areab = area->Shape_buffer();

    img->Resize(w, h);
    DWORD* imgb = GetImageBuffer(img);

    for(int i = 0; i < l; i++)
    {
        imgb[i] = areab[i];
    }
};

inline void
conversion_IMAGE_Area(Shape* area, IMAGE* img)
{
    int w = img->getwidth();
    int h = img->getheight();
    area->Shape_reset(w, h);
    int           l     = area->Shape_long();
    unsigned int* areab = area->Shape_buffer();

    DWORD* imgb = GetImageBuffer(img);

    for(int i = 0; i < l; i++)
    {
        areab[i] = imgb[i];
    }
};


// mat路径
#define MATPATH "D:/Project/VS Code/KH_EX_SakanaM_T/mat/"
#define MATMAX 1000

// 制作Zone，返回是否成功
// 传入Zone指针，图片路径数组，位数组，图片数量
bool madeZone(Zone*, std::string*, ZoneAreaType*, int);

// 根据地址导入图片，返回是否成功
bool loadshape(Shape*, std::string);

enum LibraryMatType
{
    shape_area_main,
    shape_area_wall,

    shape_img_world_ground,
    shape_img_wall_01,
    shape_img_wall_02,

    shape_img_skin_sakana,
    shape_img_skin_ikacyann,

    shape_hitbox16
};

class Library
{
public:
    Library();
    ~Library();

    // 获取Zone
    void LibZone(Zone*);

    // 初始化所有静态资源
    void InitMat();

    // 获取资源
    Shape* LibMat(LibraryMatType);

private:
    std::string lib_mat_path[MATMAX];
    Shape       lib_mat[MATMAX];
};


class GraphInterface
{
public:
    void NewGraph(int, int, int, int, char*); // 初始化窗口，宽高，位置
    void CloseGraph();                        // 关闭窗口
    void ClearScreen();                       // 清屏
    void Photographed(Shape*);                // 输出图像
    void Photographed_format();               // 设置输出格式，先不写

    // 获取鼠标在sight坐标系中的位置, 传入视野视野宽高
    Point MousePointInSight(int, int);

    Input input;

private:
    // 窗口信息
    HWND graph_HWND;
    HDC  graph_HDC;
    int* graph_buffer;
    int  graph_wide;
    int  graph_high;
    int  graph_long;

    int graph_half_wide;
    int graph_half_high;

    // 窗口输出参数
    Point output_p1;
    Point output_p2;

    int output_wide;
    int output_high;
};


// 游戏类，进行游戏的核心逻辑
class Game
{
public:
    Game(GraphInterface*, Library*);
    ~Game();

    // 更新,需要每次循环调用
    // 返回false表示游戏结束
    // 返回true表示游戏继续
    bool Update();

private:
    // 游戏
    GraphInterface* graphInterface;
    Library*        library;

    // 工厂
    // GameObjectFactory* gameObjectFactory;

    // 地图
    Zone   main_zone;
    Vector relative_area_vector;
    Area   matter;

    Area world_skin;
    Area wall_skin_01;
    Area wall_skin_02;

    // 游戏对象
    Camera main_camera;

    Fish*      sakana;
    Fish*      sayarin;
    Fish*      zaruto;
    Ring<Fish> ring_fish;

    // 移动向量
    Point  camera_move_vector;
    Vector sakana_force_vector;
    Vector sayarin_force_vector;

    void rending();
};


// 引入库
class GameManager
{
public:
    // 返回值：0正常退出，1初始化失败，2运行失败，3退出失败
    int RUN();

private:
    Game*           game = nullptr;
    GraphInterface* gi   = nullptr;
    Library*        lib  = nullptr;

    void init();
    void exit();
};
