
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
int MessageSystem::Send_Message()
{
    if (message_count == 0)
    {
        std::cout << "No Message" << std::endl;
        return 0;
    }
    else
    {
        int msg = message_queue[message_count];
        message_queue[message_count] = 0;
        message_count--;

        std::cout << "Message Sent:" << msg << std::endl;
        return msg;
    }
}

// 接收消息
void MessageSystem::Receive_Message(int message)
{
    if (message_count >= MESSAGE_MAX)
    {
        std::cout << "Message Queue Full" << std::endl;
        return;
    }
    else
    {
        message_count++;
        message_queue[message_count] = message;

        std::cout << "Message Received:" << message << std::endl;
    }
}
