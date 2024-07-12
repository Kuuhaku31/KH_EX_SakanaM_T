
#include "MessageSystem.hpp"

int MessageSystem::Send_Message_to_GameManager()
{
    std::cout << "Send Message to GameManager" << std::endl;

    if (system_message_count == 0)
    {
        std::cout << "No Message" << std::endl;
        return 0;
    }
    else
    {
        int msg = system_message_queue[system_message_count];
        system_message_queue[system_message_count] = 0;
        system_message_count--;

        std::cout << "Message Sent to GameManager:" << msg << std::endl;
        return msg;
    }
}

void MessageSystem::Receive_Message_from_GameManager(char msg)
{
    if (system_message_count >= SYSTEM_MESSAGE_MAX)
    {
        std::cout << "Message Queue Full" << std::endl;
        return;
    }
    else
    {
        system_message_count++;
        system_message_queue[system_message_count] = msg;

        std::cout << "Message Received from GameManager:" << msg << std::endl;
    }
}

void MessageSystem::Enable_Message_to_GameManager()
{
}

void MessageSystem::Disable_Message_to_GameManager()
{
}
