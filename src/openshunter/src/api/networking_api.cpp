#include "networking_api.h"

#include <network/network_type.h>
#include <network/network.h>
#include <network/network_func.h>
#include <network/network_internal.h>

bool API::IsNetworking()
{
	return _networking;
}

bool API::IsServer()
{
	return _network_server;
}
