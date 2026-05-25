#include "mod_api.h"

static void OnGameTick()
{
    int speed = GetSettingInt("MyMod.speed");
    (void)speed;
}

extern "C" __declspec(dllexport) void ModEntry()
{
    static ModInfo info = { "MyMod", "1.0", "YourName" };

    static Callbacks cbs = {};
    cbs.on_game_tick = OnGameTick;

    static Decisions dec = {};

    RegisterMod(&info, cbs, dec);

    RegisterSetting("speed", "Train Speed", "Controls train speed",
                    /*default*/ 5, /*min*/ 1, /*max*/ 10,
                    /*is_bool*/ false, /*is_dropdown*/ false,
                    /*dropdown_labels*/ nullptr, /*count*/ 0);
}
