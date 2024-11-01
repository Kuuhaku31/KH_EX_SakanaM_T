
#pragma once

#include "game_factory.hpp"


#define GRAPHWIDE 1600
#define GRAPHHIGH 900
#define GRAPHLONG 1600 * 900

#define GRAPH_X 40
#define GRAPH_Y 30

#define GAME_NAME "Sakana"

struct Input
{
    ExMessage msg;

    // 按键状态
    bool key_W = false;
    bool key_S = false;
    bool key_A = false;
    bool key_D = false;

    bool key_I = false;
    bool key_K = false;
    bool key_J = false;
    bool key_L = false;

    bool key_Q = false;
    bool key_E = false;
    bool key_R = false;
    bool key_F = false;

    bool arr_U = false;
    bool arr_D = false;
    bool arr_L = false;
    bool arr_R = false;

    bool space = false;
    bool shift = false;
    bool esc__ = false;
    bool enter = false;

    // 鼠标状态
    int  mouse_X = 0;
    int  mouse_Y = 0;
    bool mouse_L = false;
    bool mouse_R = false;
    bool mouse_M = false;
    int  mouse_W = 0;

    // 拉取一个消息
    // 返回值为 false 表示没有消息
    bool Input_Peekmessage();

    // 获取输入队列中的所有消息
    void Input_Get_Messagelist();
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
    Game(GraphInterface*, GameFactory*, Library*);
    ~Game();

    // 更新,需要每次循环调用，返回false表示游戏结束
    bool Update();

private:
    // 游戏
    bool is_game_continue = true;

    GraphInterface* graphInterface;
    GameFactory*    gameFactory;
    Library*        library;

    // 工厂
    // GameObjectFactory* gameObjectFactory;

    // 地图
    Zone main_zone;
    enum gameZoneType
    {
        zone_area_main     = 0,
        zone_area_wall     = 1,
        zone_area_relative = 2,
        zone_end           = 31
    };
    Vector relative_area_vector;

    Area world_skin;
    Area wall_skin_01;
    Area wall_skin_02;

    // 游戏对象
    Camera main_camera;

    Fish*        sakana;
    Fish*        sayarin;
    Fish*        zaruto;
    Ring<Fish>   ring_fish;
    Ring<Bullet> ring_bullet;
    // Ring<Marble> ring_marble;

    // 移动向量
    Point  camera_move_vector;
    Vector sakana_force_vector;
    Vector sayarin_force_vector;

    void getInput();
    void rending();
    void update01();
    void update02();
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
    GameFactory*    gf   = nullptr;
    Library*        lib  = nullptr;

    void init();
    void exit();
};
