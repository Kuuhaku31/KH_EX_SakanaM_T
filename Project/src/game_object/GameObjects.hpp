
#pragma once

#include "base.hpp"


// 天才！！！！
// 一个Area的点有32位
// 每一位表示不同的Area
// 一个Zone类可以存储32个Area信息
// main_area 为主要区域，用于判断是否在区域内
struct Zone
{
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
    GameObject()  = default;
    ~GameObject() = default;

    virtual void Update();      // 更新运动状态
    virtual void Force(Vector); // 受力


    Vector movement_buffer       = ZEROVECTOR; // 位移缓冲
    Vector movement_velocity     = ZEROVECTOR; // 速度
    Vector movement_acceleration = ZEROVECTOR; // 加速度
    Vector movement_resistance   = ZEROVECTOR; // 阻力

protected:
    Zone* zone;
    float movement_DT   = 0.1f; // 时间间隔
    float movement_mass = 1.0f; // 质量（为0时视为质量无穷大）

    Area* show_areas      = nullptr; // 皮肤
    int   show_area_count = 0;       // 皮肤的数量
    Area  area_matter;               // 物质

    Position* test_points            = nullptr; // 检测点
    int*      test_points_value      = nullptr; // 检测点的值
    int       test_points_value_main = 0;       // 主检测点的值
    int       test_point_count       = 0;       // 检测点的数量
};

// =================================================================================================
// =================================================================================================
// =================================================================================================


// 摄像机的类
// 不负责把图像渲染到窗口上
#define CAMERA_AREA_COUNT 3
enum CameraAreaType
{
    camera_sight_01,
    camera_sight_02,
    camera_sight_03,
};

class Camera : public GameObject
{
public:
    Camera();
    Camera(Position*, int = 0, int = 0);
    ~Camera();

    // 渲染
    void CameraRending(Area*, CameraAreaType = camera_sight_01);
    void CameraRending(GameObject*, CameraAreaType = camera_sight_01);
    void CameraRendingZone(int, CameraAreaType = camera_sight_01);
    void CameraRendingSelf(CameraAreaType = camera_sight_01);
    void CameraRending(Position*, int, int = 0x88ff0000, CameraAreaType = camera_sight_01);

    // 清屏
    void CameraClearSight(CameraAreaType = camera_sight_01);

    // 设置镜头参数
    void CameraSight_size(int = 0, int = 0, CameraAreaType = camera_sight_01);
    void CameraSight_size_d(int = 0, int = 0, CameraAreaType = camera_sight_01);
    void CameraSight_align(CameraAreaType = camera_sight_01);
};

#define BULLET_AREA_COUNT 3
#define BULLET_TEST_POINTS_COUNT 0
enum BulletAreaType
{
    bullet_skin,
    bullet_hitbox,
    bullet_explode_range
};

// 子弹类
class Bullet : public GameObject
{
public:
    Bullet();
    Bullet(Position*, Point, Vector, Area*);
    ~Bullet();

    void Update();

    bool BulletIsAlive() const; // 返回子弹是否存活
    void BulletKill();          // 杀死子弹

private:
    Area* explode_area = nullptr; // 爆炸影响的区域
    bool  bullet_alive = true;    // 是否存活
    bool  is_exploding = false;   // 是否计时
    int   timer        = 10;      // 爆炸计时器，爆炸持续时间，为0时爆炸结束，调用explodeDel

    void init();
    void explode();
    void explodeDel();
};

#define MARBLE_AREA_COUNT 1
#define MARBLE_TEST_POINTS_COUNT 4
enum MarbleAreaType
{
    marble_skin,
};

// 弹珠类
class Marble : public GameObject
{
public:
    Marble();
    Marble(Position*, Point, Vector);
    ~Marble();

    void Update();

    bool MarbleIsAlive() const; // 返回弹珠是否存活
    void MarbleKill();          // 杀死弹珠

private:
    bool marble_alive = true; // 是否存活
    int  marble_HP    = 100;  // 血量

    void init();
};

#define FISH_AREA_COUNT 6
#define FISH_TEST_POINTS_COUNT 12
enum FishAreaTyep
{
    fish_main_skin,
    fish_HP_bar,
    fish_power_bar,
    fish_main_hitbox,

    fish_bullet_skin,
    fish_bullet_hitbox,
    fish_bullet_explode_range
};

class Fish : public GameObject
{
public:
    Fish(Position*, Point, Area*, Area*);
    ~Fish();

    // 更新，如果鱼死亡，不更新
    void Update();
    bool FishIsAlive(); // 返回鱼是否存活
    void FishKill();    // 杀死鱼

    // 技能函数
    Bullet* FishShoot(Position*, Vector);
    Marble* FishThrow(Position*, Vector);

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
    void FishAddHitbox(Area*);
    void FishDelHitbox(Area*);


private:
    int   fish_HP_MAX    = 1000;
    int   fish_HP        = 1000;
    int   fish_power_MAX = 2000;
    int   fish_power     = 2000;
    Point hitbox_point   = ZEROPOINT; // 用于记录添加hitbox时的位置
    int   bullet_power   = 100;       // 子弹的威力

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

    void init();
};
