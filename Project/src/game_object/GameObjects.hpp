
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
    void CameraRending(Zone*, int, int);

    // 清屏
    void CameraClearSight(int = 0);

    // 设置镜头参数
    void CameraSight_size(int = 0, int = 0, int = 0);
    void CameraSight_size_d(int = 0, int = 0, int = 0);
    void CameraSight_align(int = 0);
};

enum FishAreaTyep
{
    main_skin,
    HP_bar,
    power_bar,
    main_hitbox
};

enum FishCollType
{
    main_coll
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

    bool fish_alive = true;

private:
    int fish_HP_MAX    = 1000;
    int fish_HP        = 1000;
    int fish_power_MAX = 2000;
    int fish_power     = 2000;
};
