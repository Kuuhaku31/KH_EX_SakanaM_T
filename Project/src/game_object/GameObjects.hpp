
#pragma once

#include "base.hpp"


// 天才！！！！
// 一个Area的点有32位
// 每一位表示不同的Area
// 一个Zone类可以存储32个Area信息
// main_area 为主要区域，用于判断是否在区域内
class Zone : public Position
{
public:
    Zone();
    ~Zone();

    Area zone_data;
    Area zone_matter;
    Area zone_damage;

    int zone_data_colors[32] = { 0 };

    void ZoneSetArea(Area*, int); // 设置某个area的区域
};

// 碰撞检测
// 用于检测角色是否与墙体或其他角色发生碰撞
// 有12个检测点，分别在角色的四个角和四个边的中点
// 当角色的检测点与墙体或其他角色的检测点重合时，认为发生碰撞
/*

(0,0)------(w/4,0)-----(w/2,0)-----(3w/4,0)-----(w,0)
  |           |           |           |           |
  |           |           |           |           |
(0,h/4)----(w/4,h/4)---(w/2,h/4)---(3w/4,h/4)---(w,h/4)
  |           |           |           |           |
  |           |           |           |           |
(0,h/2)----(w/4,h/2)---(w/2,h/2)---(3w/4,h/2)---(w,h/2)
  |           |           |           |           |
  |           |           |           |           |
(0,3h/4)--(w/4,3h/4)--(w/2,3h/4)--(3w/4,3h/4)--(w,3h/4)
  |           |           |           |           |
  |           |           |           |           |
(0,h)------(w/4,h)-----(w/2,h)-----(3w/4,h)-----(w,h)

*/


// 有若干个个检测点，分别在角色的四个角和四个边的中点
// 用于指导物体的运动
// 位置参数：坐标、速度、加速度
// 阻力参数：摩擦力、空气阻力
// Frictional resistance, air resistance、
// 直接用Vector表示
class GameObject : public Position
{
    friend class GameFactory;
    friend class Camera;

public:
    GameObject(Zone*);
    ~GameObject();

    virtual void Update();      // 更新运动状态
    virtual void Force(Vector); // 受力

    bool GameObjectIsAlive() const; // 返回物体是否存活

    Vector movement_buffer       = ZEROVECTOR; // 位移缓冲
    Vector movement_velocity     = ZEROVECTOR; // 速度
    Vector movement_acceleration = ZEROVECTOR; // 加速度
    Vector movement_resistance   = ZEROVECTOR; // 阻力

protected:
    bool  is_alive      = true;    // 是否存活
    Zone* zone          = nullptr; // 所在区域
    float movement_DT   = 0.1f;    // 时间间隔
    float movement_mass = 1.0f;    // 质量（为0时视为质量无穷大）
    Area  area_matter;             // 物质区域

    Position* test_points            = nullptr; // 检测点
    int*      test_points_value      = nullptr; // 检测点的值
    int       test_points_value_main = 0;       // 主检测点的值
    int       test_point_count       = 0;       // 检测点的数量

    Timer          animation_timer; // 动画计时器
    Point          animation_point; // 动画位置
    AnimationList* animation_list;  // 动画列表


    virtual void free();            // 释放内存，析构函数调用
    virtual void updateTimer();     // 更新计时器
    virtual void updateMovement();  // 更新运动状态
    virtual void updateTestValue(); // 更新检测点的值
};

// =================================================================================================
// =================================================================================================
// =================================================================================================

// 摄像机的渲染方式枚举
enum CameraRendingType
{
    camera_rending_default, // 默认
    camera_rending_fill,    // 填充
    camera_rending_line,    // 线框
    camera_rending_point,   // 点

    camera_rending_zone_data,   // 区域数据
    camera_rending_zone_matter, // 区域物质
    camera_rending_zone_damage, // 区域伤害
};

// 摄像机的类
// 不负责把图像渲染到窗口上
class Camera : public Position
{
public:
    Camera();
    Camera(Position*, int = 0, int = 0);
    ~Camera();

    // 渲染
    void CameraRending(Area*, CameraRendingType = camera_rending_default);
    void CameraRending(GameObject*, CameraRendingType = camera_rending_default);
    void CameraRending(Zone*, CameraRendingType = camera_rending_default);
    void CameraRending(Position*, int, int = 0x88ff0000, CameraRendingType = camera_rending_default);

    // 清屏
    void CameraClearSight();

    // 设置镜头参数
    void CameraSight_size(int = 0, int = 0);
    void CameraSight_size_d(int = 0, int = 0);
    void CameraSight_align();

    Area camera_sight;
};


// 子弹类
class Bullet : public GameObject
{
    friend class GameFactory;

public:
    Bullet(Zone*);
    ~Bullet();

    virtual void Update();

protected:
    Timer explode_timer;     // 爆炸倒计时
    Timer explode_timer_del; // 爆炸持续时间计时器

    Area explode_area; // 爆炸范围

    bool is_exploding = false; // 是否爆炸

    virtual void explode();
    virtual void explodeDel();
};


// #define MARBLE_AREA_COUNT 1
// #define MARBLE_TEST_POINTS_COUNT 4
// enum MarbleAreaType
// {
//     marble_skin,
// };

// // 弹珠类
// class Marble : public GameObject
// {
// public:
//     Marble();
//     Marble(Position*, Point, Vector);
//     ~Marble();

//     void Update();

//     bool MarbleIsAlive() const; // 返回弹珠是否存活
//     void MarbleKill();          // 杀死弹珠

// private:
//     bool marble_alive = true; // 是否存活
//     int  marble_HP    = 100;  // 血量

//     void init();
// };

#define FISH_TEST_POINTS_COUNT 12
class Fish : public GameObject
{
public:
    Fish(Zone*);
    ~Fish();

    // 更新，如果鱼死亡，不更新
    virtual void Update();

    // 获取
    int FishGetHP();
    int FishGetPower();

    // 重置血量、能量
    void FishSetHP(int);
    void FishSetPower(int);

    // 增减
    void FishSetHP_d(int);
    void FishSetPower_d(int);

    // 给matter添加、删除hitbox
    void FishMatterAdd();
    void FishMatterDel();


protected:
    int   fish_HP_MAX    = 1000;
    int   fish_HP        = 1000;
    int   fish_power_MAX = 2000;
    int   fish_power     = 2000;
    Point hitbox_point   = ZEROPOINT; // 用于记录添加hitbox时的位置
    bool  is_add_matter  = false;     // 是否添加matters

    enum FishCollType
    {
        fish_test_point_top_start   = 0,
        fish_test_point_top_end     = 2,
        fish_test_point_right_start = 3,
        fish_test_point_right_end   = 5,
        fish_test_point_down_start  = 6,
        fish_test_point_down_end    = 8,
        fish_test_point_left_start  = 9,
        fish_test_point_left_end    = 11,
    };
};
