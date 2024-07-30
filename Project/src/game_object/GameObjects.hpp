
#pragma once

#include "base.hpp"

// 摄像机的类
// 不负责把图像渲染到窗口上

class Camera : public Object
{
public:
    Camera();
    Camera(Position*, int = 0, int = 0);
    ~Camera();

    // 渲染
    void CameraRending(Area*, int = 0);
    void CameraRending(Zone*, ZoneAreaType, int = 0);
    void CameraRending(Collision*, unsigned int = 0x88ff0000, int = 0);

    // 渲染质量地图
    void CameraRendingMatter(Area*, int = 0);

    // 清屏
    void CameraClearSight(int = 0);

    // 设置镜头参数
    void CameraSight_size(int = 0, int = 0, int = 0);
    void CameraSight_size_d(int = 0, int = 0, int = 0);
    void CameraSight_align(int = 0);
};

enum FishAreaTyep
{
    fish_main_skin,
    fish_HP_bar,
    fish_power_bar,
    fish_main_hitbox
};

enum FishCollType
{
    fish_main_coll
};

class Fish : public Object
{
public:
    Fish();
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
};
