
#include "MessageSystem.hpp"

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

short MessageSystem::Init()
{
    return 0;
}

short MessageSystem::Exit()
{
    return 0;
}

void MessageSystem::Say(std::string str, int txtCode, int bakcgroudCode)
{
    // 设置控制台文字颜色
    int code = txtCode + (bakcgroudCode << 4);
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleOutput, code);
    std::cout << std::endl
              << str;
    SetConsoleTextAttribute(hConsoleOutput, WIN_COLOR_WHITE);
}

// 发送消息
int MessageSystem::Send_Message()
{
    if (message_count == 0)
    {
        Say("No Message", WIN_COLOR_YELLOW);
        return 0;
    }
    else
    {
        int msg = message_queue[message_count];
        message_queue[message_count] = 0;
        message_count--;

        Say("Message Sent:" + std::to_string(msg), WIN_COLOR_GRAY);
        return msg;
    }
}

// 接收消息
void MessageSystem::Receive_Message(char message)
{
    if (message_count >= MESSAGE_MAX)
    {
        Say("Message Queue Full", WIN_COLOR_YELLOW);
        return;
    }
    else
    {
        message_count++;
        message_queue[message_count] = message;

        Say("Message Received:" + std::to_string(message), WIN_COLOR_GRAY);
    }
}

void MessageSystem::Enable_Message()
{
}

void MessageSystem::Disable_Message()
{
}
