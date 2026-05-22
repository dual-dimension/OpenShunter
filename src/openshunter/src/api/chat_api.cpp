#include <stdafx.h>

#include "chat_api.h"
#include <network/network_type.h>
#include <network/network.h>
#include <network/network_func.h>
#include <network/network_internal.h>

void SendChat(const char* message)
{
    if (_networking && _network_server)
    {
        NetworkServerSendChat(NETWORK_ACTION_CHAT, DESTTYPE_BROADCAST, 0, message, CLIENT_ID_SERVER);
    }
    else if (_networking)
    {
        NetworkClientSendChat(NETWORK_ACTION_CHAT, DESTTYPE_BROADCAST, 0, message);
    }
    else
    {
        NetworkTextMessage(NETWORK_ACTION_CHAT, CC_DEFAULT, false, "Mod", message);
    }
}
