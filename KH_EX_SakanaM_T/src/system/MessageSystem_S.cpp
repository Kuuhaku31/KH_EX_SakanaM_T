
#include "MessageSystem.hpp"

int MessageSystem::Send_Message_to_GameManager()
{

    if (system_message_count == 0)
    {
        return 0;
    }
    else
    {
        int msg = system_message_queue[system_message_count];
        system_message_queue[system_message_count] = 0;
        system_message_count--;

        return msg;
    }
}

void MessageSystem::Receive_Message_from_GameManager(char msg)
{
    if (system_message_count >= SYSTEM_MESSAGE_MAX)
    {
        return;
    }
    else
    {
        system_message_count++;
        system_message_queue[system_message_count] = msg;
    }
}

void MessageSystem::Enable_Message_to_GameManager()
{
}

void MessageSystem::Disable_Message_to_GameManager()
{
}
