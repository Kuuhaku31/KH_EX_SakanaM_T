
// 全局消息系统
// 用于**游戏内**全局消息的发送和接收
// 不负责游戏外的消息处理接口

#include "GraphInterface.hpp"

#pragma once

#define MESSAGE_MAX 100
#define GAME_MESSAGE_MAX 100
#define SYSTEM_MESSAGE_MAX 100

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

private:
    // 消息队列
    // 不同的消息类型分别存储
    int message_count = 0;
    char message_queue[MESSAGE_MAX] = {0};

    int game_message_count = 0;
    char game_message_queue[GAME_MESSAGE_MAX] = {0};

    int system_message_count = 0;
    char system_message_queue[SYSTEM_MESSAGE_MAX] = {0};
};
