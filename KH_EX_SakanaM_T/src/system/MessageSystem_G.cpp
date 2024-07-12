
#include "MessageSystem.hpp"

int MessageSystem::Send_Message_to_Game()
{
    if (game_message_count == 0)
    {
        std::cout << "No Message" << std::endl;
        return 0;
    }
    else
    {
        int msg = game_message_queue[game_message_count];
        game_message_queue[game_message_count] = 0;
        game_message_count--;

        std::cout << "Message Sent to Game:" << msg << std::endl;
        return msg;
    }
}

void MessageSystem::Receive_Message_from_Game(char msg)
{
    if (game_message_count >= GAME_MESSAGE_MAX)
    {
        std::cout << "Message Queue Full" << std::endl;
        return;
    }
    else
    {
        game_message_count++;
        game_message_queue[game_message_count] = msg;

        std::cout << "Message Received from Game:" << msg << std::endl;
    }
}

void MessageSystem::Enable_Message_to_Game()
{
}

void MessageSystem::Disable_Message_to_Game()
{
}
