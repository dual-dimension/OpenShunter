#include "mod_logic.h"
#include <vector>
#include "../../debug.h"
#include "alias.h"
#include <string>

static std::vector<OnMenuStartFn> on_menu_start_hooks;
static std::vector<OnMenuTickFn>  on_menu_tick_hooks;
static std::vector<OnGameStartFn> on_game_start_hooks;
static std::vector<OnGameTickFn>  on_game_tick_hooks;

void Register(ModInfo* info, const Callbacks callbacks)
{
	Debug(script, 2, "Registering mod name '{}' \nVersion: '{}'\nAuthor: '{}'", std::string(info->name), std::string(info->version), std::string(info->author));

    if (callbacks.on_menu_start) on_menu_start_hooks.push_back(callbacks.on_menu_start);
    if (callbacks.on_menu_tick) on_menu_tick_hooks.push_back(callbacks.on_menu_tick);

    if (callbacks.on_game_start) on_game_start_hooks.push_back(callbacks.on_game_start);
    if (callbacks.on_game_tick) on_game_tick_hooks.push_back(callbacks.on_game_tick);
}

/* Menu */
void OpenShunter::OnMenuStart()
{
    for (auto& hook : on_menu_start_hooks) hook();
}

void OpenShunter::OnMenuTick()
{
    for (auto& hook : on_menu_tick_hooks) hook();
}

/* Game */
void OpenShunter::OnGameStart()
{
    for (auto& hook : on_game_start_hooks) hook();
}

void OpenShunter::OnGameTick()
{
    for (auto& hook : on_game_tick_hooks) hook();
}
