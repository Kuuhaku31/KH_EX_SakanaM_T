
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


#define FISH_AREA_COUNT 4
enum FishAreaTyep
{
    fish_main_skin,
    fish_HP_bar,
    fish_power_bar,
    fish_main_hitbox
};

#define FISH_TEST_POINTS_COUNT 12

class Fish : public Object
{
public:
    Fish();
    Fish(Position*, Point);
    ~Fish();

    void Update();

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

    bool fish_alive = true;

private:
    int fish_HP_MAX    = 1000;
    int fish_HP        = 1000;
    int fish_power_MAX = 2000;
    int fish_power     = 2000;

    Point hitbox_point;

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


#define BULLET_AREA_COUNT 3
enum BulletAreaType
{
    bullet_skin,
    bullet_hitbox,
    bullet_explode_range
};

#define BULLET_TEST_POINTS_COUNT 0

// 子弹类
class Bullet : public Object
{
public:
    Bullet();
    Bullet(Position*, Point, Vector, Area*);
    ~Bullet();

    void Update();

    int  BulletGetPower();
    void BulletSetPower(int);
    void BulletSetPower_d(int);

    bool bullet_alive = true;

    void BulletExplode();
    void BulletExplodeDel();

private:
    bool is_timer = false;
    int  timer    = 10;

    Area* explode_area = nullptr;

    void init();
};
