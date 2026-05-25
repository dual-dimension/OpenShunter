#include "../include/mod_api.h"
#include <cstdio>

static void OnMonthComplete(int month, int year)
{
    SendChat("Month Complete!");
}

static void OnWindowPaint(uint16_t wc, const ShunterDrawContext* ctx)
{
    if (wc != SHUNTER_WC_TRAINS_LIST) return;

    ctx->draw_string(4, 4, 300, "My Mod Active", SHUNTER_TC_RED);
}

static void OnMenuPopulate(int menu, AddMenuItemFn add)
{
    if (menu != SHUNTER_MENU_FINANCES) return;

    add(1000, "My Mod Window");
}

static void OnMenuClick(int menu, int id)
{
    if (menu != SHUNTER_MENU_FINANCES || id != 1000) return;

    // TODO: open window
}

static void OnVehicleInfo(uint32_t vehicle_id, const ShunterVehicleInfoContext* ctx)
{
    char buf[64];
    int speed = GetSettingInt("speed");
    snprintf(buf, sizeof(buf), "My Mod: vehicle %u  |  speed setting: %d", vehicle_id, speed);
    ctx->add_line(buf, SHUNTER_TC_GREEN);
}

extern "C" __declspec(dllexport) void ModEntry()
{
    static ModInfo info = { "Chat Notifier", "1.0", "Ian Henderson" };

    static Callbacks cbs = {};
    cbs.on_month_passed = OnMonthComplete;

    static Decisions dec = {};

    RegisterMod(&info, cbs, dec);

    RegisterSetting("speed", "Train Speed", "Controls train speed",
                    /*default*/ 5, /*min*/ 1, /*max*/ 10,
                    /*is_bool*/ false, /*is_dropdown*/ false,
                    /*dropdown_labels*/ nullptr, /*count*/ 0);

    RegisterUICallbacks({
        .on_window_paint  = OnWindowPaint,
        .on_menu_populate = OnMenuPopulate,
        .on_menu_click    = OnMenuClick,
    });

    RegisterVehicleInfoLines(1, OnVehicleInfo);
}
