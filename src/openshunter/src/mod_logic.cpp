#include "mod_logic.h"
#include <vector>
#include "../../debug.h"
#include <string>

static std::vector<OnTickFn> on_start_hooks;
static std::vector<OnTickFn> on_tick_hooks;

void Register(ModInfo* info, const Callbacks callbacks)
{
	Debug(script, 2, "Registering mod name '{}' \nVersion: '{}'\nAuthor: '{}'", std::string(info->name), std::string(info->version), std::string(info->author));
    if (callbacks.on_start) on_start_hooks.push_back(callbacks.on_start);
    if (callbacks.on_tick) on_tick_hooks.push_back(callbacks.on_tick);
}

void OpenShunter::OnStart()
{
    Debug(script, 2, "OnStart called");
    for (auto& hook : on_start_hooks) hook();
}

void OpenShunter::OnTick()
{
    Debug(script, 2, "OnTick called");
    for (auto& hook : on_tick_hooks) hook();
}
