
#include "MessageSystem.hpp"

int MessageSystem::Send_Message_to_Game()
{
    if (game_message_count == 0)
    {
        return 0;
    }
    else
    {
        int msg = game_message_queue[game_message_count];
        game_message_queue[game_message_count] = 0;
        game_message_count--;

        return msg;
    }
}

void MessageSystem::Receive_Message_from_Game(char msg)
{
    if (game_message_count >= GAME_MESSAGE_MAX)
    {
        return;
    }
    else
    {
        game_message_count++;
        game_message_queue[game_message_count] = msg;

    }
}

void MessageSystem::Enable_Message_to_Game()
{
}

void MessageSystem::Disable_Message_to_Game()
{
}
