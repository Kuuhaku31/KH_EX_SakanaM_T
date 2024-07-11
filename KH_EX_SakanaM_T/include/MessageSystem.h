
// 全局消息系统
// 用于全局消息的发送和接收

#pragma once

#define MESSAGE_MAX 100

class MessageSystem
{
public:
    MessageSystem();
    ~MessageSystem();

    // 发送消息
    int Send_Message();

    // 接收消息
    void Receive_Message(int message);

private:
    // 消息队列
    unsigned short message_count = 0;
    int message_queue[MESSAGE_MAX] = {0};
};
