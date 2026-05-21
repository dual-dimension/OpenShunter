#include "chat_api.h"
#include <network/network.h>
#include <network/network_func.h>
#include <network/network_internal.h>

void SendChat(const char* message)
{
    if (_networking && _network_server)
    {
        NetworkServerSendChat(NetworkAction::ChatBroadcast, NetworkChatDestinationType::Broadcast, 0, message, CLIENT_ID_SERVER);
    }
    else if (_networking)
    {
        NetworkClientSendChat(NetworkAction::ChatBroadcast, NetworkChatDestinationType::Broadcast, 0, message);
    }
    else
    {
        NetworkTextMessage(NetworkAction::ChatBroadcast, CC_DEFAULT, false, "Mod", message);
    }
}
