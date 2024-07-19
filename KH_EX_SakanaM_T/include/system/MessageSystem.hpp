
// 全局消息系统
// 用于**游戏内**全局消息的发送和接收
// 不负责游戏外的消息处理接口
#pragma once

#include "base.hpp"
#include <graphics.h>

#define GAME_RATE 60
#define RATE_SLEEP 1000 / GAME_RATE

#define GRAPHWIDE 1600
#define GRAPHHIGH 900
#define GRAPHLONG 1600 * 900

#define GRAPH_X 40
#define GRAPH_Y 30

#define GAME_NAME "Sakana"

// 消息队列的最大长度
#define MESSAGE_MAX 100
#define GAME_MESSAGE_MAX 100
#define SYSTEM_MESSAGE_MAX 100

#define SHAPE_QUEUE_MAX 100

// 用于在控制台打印消息
// 第二个参数表示消息的颜色
void Say(std::string str, int txtCode = OXF, int bakcgroudCode = 0);
// 实现IMAGE类和Shape类的互相转化
void conversion_IMAGE_Area(IMAGE *img, Shape *area);
void conversion_IMAGE_Area(Shape *area, IMAGE *img);
void get_resources(Shape *shape, std::string path);
void clearGraph();

enum ShapeType
{
    SourceScreen01,
    SourceScreen02,
    SourceScreen03,

    UIScreen01,
    UIScreen02,
    UIScreen03,
    UIScreen04,
    UIScreen05,

    SHapeNULL01,
    SHapeNULL02,
};

class MessageSystem
{
public:
    MessageSystem();
    ~MessageSystem();

    // 初始化和退出
    short Init();
    short Exit();

    // 发送消息
    int Send_Message();
    int Send_Message_to_Game();
    int Send_Message_to_GameManager();

    // 接收消息
    void Receive_Message(char);
    void Receive_Message_from_Game(char);
    void Receive_Message_from_GameManager(char);

    // 启用、停用消息队列
    // 先不写
    void Enable_Message();
    void Enable_Message_to_Game();
    void Enable_Message_to_GameManager();

    void Disable_Message();
    void Disable_Message_to_Game();
    void Disable_Message_to_GameManager();

    // 游戏画面
    Shape *Send_Shapes(ShapeType);
    void Receive_Shapes(Shape *, ShapeType);

private:
    // 消息队列
    // 不同的消息类型分别存储
    int message_count = 0;
    char message_queue[MESSAGE_MAX] = {0};

    int game_message_count = 0;
    char game_message_queue[GAME_MESSAGE_MAX] = {0};

    int system_message_count = 0;
    char system_message_queue[SYSTEM_MESSAGE_MAX] = {0};

    // 需要处理的图像指针列表
    Shape *shape_queue[SHAPE_QUEUE_MAX];
};
