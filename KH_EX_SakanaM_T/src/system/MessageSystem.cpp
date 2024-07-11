
#include "MessageSystem.h"

#include <iostream>

MessageSystem::MessageSystem()
{
    // Initialize the message system
    std::cout << "Message System Created" << std::endl;
}

MessageSystem::~MessageSystem()
{
    // Destroy the message system
    std::cout << "Message System Destroyed" << std::endl;
}

// 发送消息
int MessageSystem::SendMessage()
{
    if (message_count == 0)
    {
        return 0;
    }
    else
    {
        int msg = message_queue[message_count];
        message_queue[message_count] = 0;
        message_count--;
        return msg;
    }
}

// 接收消息
void MessageSystem::ReceiveMessage(int message)
{
    if (message_count >= MESSAGE_MAX)
    {
        return;
    }
    else
    {
        message_count++;
        message_queue[message_count] = message;
    }
}
