#include "mod_api.h"
#include "alias.h"

void Register(ModInfo* info, const Callbacks callbacks);

namespace OpenShunter
{
    void OnMenuStart();
    void OnMenuTick();

    void OnGameStart();
    void OnGameTick();
}
