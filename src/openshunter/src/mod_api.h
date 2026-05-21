#pragma once

#include <cstdint>

/* Menu */
using OnMenuStartFn = void(*)();
using OnMenuTickFn  = void(*)();

/* Game */
using OnGameStartFn = void(*)();
using OnGameTickFn  = void(*)();

/* Network */
using OnPlayerJoinedFn = void(*)(uint32_t client_id, const char* client_name);

/* Economy */
using OnMoneyChangedFn = void(*)(uint8_t company_id, int64_t old_money, int64_t new_money);

/* Time */
using OnDayPassedFn     = void(*)(int day, int month, int year);
using OnWeekPassedFn    = void(*)(int month, int year);
using OnMonthPassedFn   = void(*)(int month, int year);
using OnQuarterPassedFn = void(*)(int quarter, int year);
using OnYearPassedFn    = void(*)(int year);

/* Decisions - filter hooks that receive and return the engine's default result */
using AskCanTrainEnterTileFn = bool(*)(uint32_t tile, uint8_t tile_owner, uint8_t train_owner, bool default_result);

struct ModInfo
{
    const char* name;
    const char* version;
    const char* author;
};

struct Callbacks
{
    OnMenuStartFn on_menu_start;
    OnMenuTickFn  on_menu_tick;

    OnGameStartFn on_game_start;
    OnGameTickFn  on_game_tick;

    OnPlayerJoinedFn on_player_joined;
    OnMoneyChangedFn on_money_changed;

    OnDayPassedFn     on_day_passed;
    OnWeekPassedFn    on_week_passed;
    OnMonthPassedFn   on_month_passed;
    OnQuarterPassedFn on_quarter_passed;
    OnYearPassedFn    on_year_passed;
};

struct Decisions
{
    AskCanTrainEnterTileFn ask_can_train_enter_tile;
};

struct ModApi
{
    void (*Register)(ModInfo* info, const Callbacks callbacks, const Decisions decisions);

    int64_t (*GetSettingInt)(const char* name);
    bool    (*GetSettingBool)(const char* name);

    void (*RegisterSetting)(const char* name, const char* label, const char* help,
                            int32_t def, int32_t min, int32_t max,
                            bool is_bool, bool is_dropdown,
                            const char** dropdown_labels, int dropdown_count);

    void (*SendChat)(const char* message);
};


#ifndef OPENSHUNTER_MOD
extern "C"
{
    typedef void  (*RegisterMod)(ModApi* api);
}
#endif
