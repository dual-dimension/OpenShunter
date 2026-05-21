#include "mod_logic.h"
#include <vector>

static std::vector<OnTickFn> on_start_hooks;
static std::vector<OnTickFn> on_tick_hooks;

void Register(ModInfo* info, const Callbacks callbacks)
{
    if (callbacks.on_start) on_start_hooks.push_back(callbacks.on_start);
    if (callbacks.on_tick) on_tick_hooks.push_back(callbacks.on_tick);
}

void OpenShunter::OnStart()
{
    for (auto& hook : on_start_hooks) hook();
}

void OpenShunter::OnTick()
{
    for (auto& hook : on_tick_hooks) hook();
}
