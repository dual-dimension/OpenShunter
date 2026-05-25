#pragma once

// Mirror of sdk/include/mod_api.h — keep in sync.

#include <cstdint>

#define SHUNTER_API extern "C" __declspec(dllimport)

/* UI */

static const uint16_t SHUNTER_WC_MAIN_WINDOW         = 0x00;
static const uint16_t SHUNTER_WC_MAIN_TOOLBAR        = 0x01;
static const uint16_t SHUNTER_WC_STATUS_BAR          = 0x02;
static const uint16_t SHUNTER_WC_SMALLMAP            = 0x08;
static const uint16_t SHUNTER_WC_SAVELOAD            = 0x0E;
static const uint16_t SHUNTER_WC_LAND_INFO           = 0x0F;

static const uint16_t SHUNTER_WC_TOWN_AUTHORITY      = 0x17;
static const uint16_t SHUNTER_WC_VEHICLE_DETAILS     = 0x18;
static const uint16_t SHUNTER_WC_VEHICLE_REFIT       = 0x19;
static const uint16_t SHUNTER_WC_VEHICLE_ORDERS      = 0x1A;
static const uint16_t SHUNTER_WC_REPLACE_VEHICLE     = 0x1B;
static const uint16_t SHUNTER_WC_VEHICLE_TIMETABLE   = 0x1C;

static const uint16_t SHUNTER_WC_NEWS_WINDOW         = 0x20;
static const uint16_t SHUNTER_WC_TOWN_DIRECTORY      = 0x21;
static const uint16_t SHUNTER_WC_SUBSIDIES_LIST      = 0x22;
static const uint16_t SHUNTER_WC_INDUSTRY_DIRECTORY  = 0x23;
static const uint16_t SHUNTER_WC_SIGN_LIST           = 0x25;

static const uint16_t SHUNTER_WC_STATION_LIST        = 0x29;
static const uint16_t SHUNTER_WC_TRAINS_LIST         = 0x2A;
static const uint16_t SHUNTER_WC_ROADVEH_LIST        = 0x2B;
static const uint16_t SHUNTER_WC_SHIPS_LIST          = 0x2C;
static const uint16_t SHUNTER_WC_AIRCRAFT_LIST       = 0x2D;

static const uint16_t SHUNTER_WC_TOWN_VIEW           = 0x2E;
static const uint16_t SHUNTER_WC_VEHICLE_VIEW        = 0x2F;
static const uint16_t SHUNTER_WC_STATION_VIEW        = 0x30;
static const uint16_t SHUNTER_WC_VEHICLE_DEPOT       = 0x31;
static const uint16_t SHUNTER_WC_INDUSTRY_VIEW       = 0x33;
static const uint16_t SHUNTER_WC_COMPANY             = 0x34;

static const uint16_t SHUNTER_WC_BUILD_VEHICLE       = 0x37;

static const uint16_t SHUNTER_WC_GRAPH_LEGEND        = 0x4B;
static const uint16_t SHUNTER_WC_FINANCES            = 0x4C;
static const uint16_t SHUNTER_WC_INCOME_GRAPH        = 0x4D;
static const uint16_t SHUNTER_WC_OPERATING_PROFIT    = 0x4E;
static const uint16_t SHUNTER_WC_DELIVERED_CARGO     = 0x4F;
static const uint16_t SHUNTER_WC_PERFORMANCE_HISTORY = 0x50;
static const uint16_t SHUNTER_WC_COMPANY_VALUE       = 0x51;
static const uint16_t SHUNTER_WC_COMPANY_LEAGUE      = 0x52;

static const int SHUNTER_MENU_MAP       = 0;
static const int SHUNTER_MENU_TOWN      = 1;
static const int SHUNTER_MENU_SUBSIDIES = 2;
static const int SHUNTER_MENU_STATIONS  = 3;
static const int SHUNTER_MENU_FINANCES  = 4;
static const int SHUNTER_MENU_COMPANIES = 5;
static const int SHUNTER_MENU_STORY     = 6;
static const int SHUNTER_MENU_GOALS     = 7;
static const int SHUNTER_MENU_GRAPHS    = 8;
static const int SHUNTER_MENU_LEAGUE    = 9;
static const int SHUNTER_MENU_INDUSTRY  = 10;
static const int SHUNTER_MENU_TRAINS    = 11;
static const int SHUNTER_MENU_ROAD      = 12;
static const int SHUNTER_MENU_SHIPS     = 13;
static const int SHUNTER_MENU_AIRCRAFT  = 14;

/* Common TextColour values (matching OpenTTD's TextColour enum) */
static const uint32_t SHUNTER_TC_RED    = 0x03;
static const uint32_t SHUNTER_TC_WHITE  = 0x0C;
static const uint32_t SHUNTER_TC_BLACK  = 0x10;
static const uint32_t SHUNTER_TC_BLUE   = 0x1A;
static const uint32_t SHUNTER_TC_GREEN  = 0x1D;
static const uint32_t SHUNTER_TC_YELLOW = 0x1E;

struct ShunterDrawContext {
    int window_width;
    int window_height;
    /* Coordinates are window-relative: (0,0) = top-left of the window. */
    void (*draw_string)(int x, int y, int max_right, const char* text, uint32_t colour);
};

/* UI - Toolbar */
using AddMenuItemFn         = void(*)(int id, const char* label);
using OnWindowPaintUIFn     = void(*)(uint16_t window_class, const ShunterDrawContext* ctx);
using OnMenuPopulateFn      = void(*)(int menu, AddMenuItemFn add_item);
using OnMenuClickFn         = void(*)(int menu, int item_id);

struct UICallbacks {
    OnWindowPaintUIFn on_window_paint;
    OnMenuPopulateFn  on_menu_populate;
    OnMenuClickFn     on_menu_click;
};

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

/* Vehicle info panel */
struct ShunterVehicleInfoContext {
    void (*add_line)(const char* text, uint32_t colour);
};
using OnVehicleInfoPaintFn = void(*)(uint32_t vehicle_id, const ShunterVehicleInfoContext* ctx);

SHUNTER_API void RegisterMod(ModInfo* info, const Callbacks callbacks, const Decisions decisions);
SHUNTER_API void RegisterUICallbacks(const UICallbacks ui);
SHUNTER_API void RegisterVehicleInfoLines(int line_count, OnVehicleInfoPaintFn on_paint);

SHUNTER_API void SendChat(const char* message);
SHUNTER_API bool IsNetworking();
SHUNTER_API bool IsServer();

/* Settings */
SHUNTER_API int  GetSettingInt(const char* name);
SHUNTER_API bool GetSettingBool(const char* name);
SHUNTER_API void RegisterSetting(const char* name, const char* label, const char* help,
                        int32_t def, int32_t min, int32_t max,
                        bool is_bool, bool is_dropdown,
                        const char** dropdown_labels, int dropdown_count);
