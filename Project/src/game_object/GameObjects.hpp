
#pragma once

#include "base.hpp"

// 摄像机的类
// 不负责把图像渲染到窗口上
#define CAMERA_AREA_COUNT 3
enum CameraAreaType
{
    camera_sight_01,
    camera_sight_02,
    camera_sight_03,
};

class Camera : public Object
{
public:
    Camera();
    Camera(Position*, int = 0, int = 0);
    ~Camera();

    // 渲染
    void CameraRending(Area*, CameraAreaType = camera_sight_01);
    void CameraRending(Zone*, int, CameraAreaType = camera_sight_01);
    void CameraRending(Position*, int, int = 0x88ff0000, CameraAreaType = camera_sight_01);

    // 渲染质量地图
    void CameraRendingMatter(Area*, CameraAreaType = camera_sight_01);

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
class Bullet : public Object
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
class Marble : public Object
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

class Fish : public Object
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
    Area* coll_area      = nullptr; // 碰撞区域
    Area* dHP_area       = nullptr; // 血条区域
    bool  fish_alive     = true;
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
