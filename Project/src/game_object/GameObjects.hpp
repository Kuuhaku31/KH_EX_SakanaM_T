
#pragma once

#include "base.hpp"

struct GameObjectData
{
    // 速度
    Vector velocity;
    // 质量
    float mass;

    // 皮肤
    Shape* skin;
    // 碰撞箱
    Shape* hitbox;
    // 碰撞检测参数
    Point coll_test_points;
};

class GameObject : public Object
{
public:
    GameObject(Zone*, Point = ZEROPOINT);
    ~GameObject();

    // 更新
    // 返回值为0时表示需要摧毁这个对象
    bool
    GameObjectUpdate();

    Zone*
    GameObjectZoneGet();

protected:
    Zone* zone;
};

// 摄像机的类
// 不负责把图像渲染到窗口上

class Camera : public GameObject
{
public:
    Camera(MessageSystem*, Zone*, Point = ZEROPOINT, int = 0, int = 0);
    ~Camera();

    // 渲染
    void
    Rending(Area*);
    void
    RendingObject(Object*, ObjectAreaType = skin01);
    void
    RendingZone(Zone*, ZoneAreaType = main_area);

    // 清屏
    void
    Clearsight();

    // 设置镜头参数
    void
    Sight_size(int = 0, int = 0);
    void
    Sight_align(bool = true);

    // 把当前画面发送给MessageSystem
    void SendToMessageSystem(ShapeType);
};

struct FishData
{
};

class Fish : public GameObject
{
public:
    Fish(MessageSystem*, Zone*);
    ~Fish();

    bool
    FishUpdate();

    // 获取
    int
    FishGetHP();
    int
    FishGetPower();

    // 重置血量、能量
    void
    FishSetHP(int);
    void
    FishSetPower(int);

    // 增减
    void
    FishSetHP_d(int);
    void
    FishSetPower_d(int);

private:
    int fish_HP_MAX;
    int fish_HP;
    int fish_power_MAX;
    int fish_power;
};
