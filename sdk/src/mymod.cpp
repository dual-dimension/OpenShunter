#include "../include/mod_api.h"


static void OnMonthComplete(int month, int day)
{
	SendChat("Month Complete!");
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
}
