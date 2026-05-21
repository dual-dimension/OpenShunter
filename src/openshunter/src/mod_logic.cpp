#include "mod_logic.h"
#include "../../debug.h"
#include <string>
#include <vector>

static std::vector<OnMenuStartFn> on_menu_start_hooks;
static std::vector<OnMenuTickFn>  on_menu_tick_hooks;
static std::vector<OnGameStartFn> on_game_start_hooks;
static std::vector<OnGameTickFn>  on_game_tick_hooks;

static std::vector<OnPlayerJoinedFn> on_player_joined_hooks;
static std::vector<OnMoneyChangedFn> on_money_changed_hooks;

static std::vector<AskCanTrainEnterTileFn> ask_can_train_enter_tile_hooks;

static std::vector<OnDayPassedFn>     on_day_passed_hooks;
static std::vector<OnWeekPassedFn>    on_week_passed_hooks;
static std::vector<OnMonthPassedFn>   on_month_passed_hooks;
static std::vector<OnQuarterPassedFn> on_quarter_passed_hooks;
static std::vector<OnYearPassedFn>    on_year_passed_hooks;

void Register(ModInfo* info, const Callbacks callbacks, const Decisions decisions)
{
	Debug(script, 2, "Registering mod name '{}' \nVersion: '{}'\nAuthor: '{}'", std::string(info->name), std::string(info->version), std::string(info->author));

    if (callbacks.on_menu_start) on_menu_start_hooks.push_back(callbacks.on_menu_start);
    if (callbacks.on_menu_tick) on_menu_tick_hooks.push_back(callbacks.on_menu_tick);

    if (callbacks.on_game_start) on_game_start_hooks.push_back(callbacks.on_game_start);
    if (callbacks.on_game_tick) on_game_tick_hooks.push_back(callbacks.on_game_tick);

    if (callbacks.on_player_joined) on_player_joined_hooks.push_back(callbacks.on_player_joined);
    if (callbacks.on_money_changed) on_money_changed_hooks.push_back(callbacks.on_money_changed);

    if (callbacks.on_day_passed)     on_day_passed_hooks.push_back(callbacks.on_day_passed);
    if (callbacks.on_week_passed)    on_week_passed_hooks.push_back(callbacks.on_week_passed);
    if (callbacks.on_month_passed)   on_month_passed_hooks.push_back(callbacks.on_month_passed);
    if (callbacks.on_quarter_passed) on_quarter_passed_hooks.push_back(callbacks.on_quarter_passed);
    if (callbacks.on_year_passed)    on_year_passed_hooks.push_back(callbacks.on_year_passed);

    if (decisions.ask_can_train_enter_tile) ask_can_train_enter_tile_hooks.push_back(decisions.ask_can_train_enter_tile);
}

/* Decisions */
bool OpenShunter::AskCanTrainEnterTile(uint32_t tile, uint8_t tile_owner, uint8_t train_owner, bool default_result)
{
    bool result = default_result;
    for (auto& hook : ask_can_train_enter_tile_hooks)
        result = hook(tile, tile_owner, train_owner, result);
    return result;
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

/* Network */
void OpenShunter::OnPlayerJoined(uint32_t client_id, const char* client_name)
{
    for (auto& hook : on_player_joined_hooks) hook(client_id, client_name);
}

/* Economy */

void OpenShunter::OnMoneyChanged(uint8_t company_id, int64_t old_money, int64_t new_money)
{
    for (auto& hook : on_money_changed_hooks) hook(company_id, old_money, new_money);
}

/* Time */

void OpenShunter::OnDayPassed(int day, int month, int year)
{
    for (auto& hook : on_day_passed_hooks) hook(day, month, year);
}

void OpenShunter::OnWeekPassed(int month, int year)
{
    for (auto& hook : on_week_passed_hooks) hook(month, year);
}

void OpenShunter::OnMonthPassed(int month, int year)
{
    for (auto& hook : on_month_passed_hooks) hook(month, year);
}

void OpenShunter::OnQuarterPassed(int quarter, int year)
{
    for (auto& hook : on_quarter_passed_hooks) hook(quarter, year);
}

void OpenShunter::OnYearPassed(int year)
{
    for (auto& hook : on_year_passed_hooks) hook(year);
}
