#include "mod_api.h"

ModApi* api;

void notify_month(int month, int year)
{
    if (api->GetSettingBool("chatnotifier.notifymonth"))
        api->SendChat("The month has ended!");
}

extern "C" __declspec(dllexport) void RegisterMod(ModApi* api)
{
    ::api = api;

    Callbacks callbacks{};
    callbacks.on_month_passed = notify_month;

    api->Register(new ModInfo{
        .name = "Chat Notifier",
        .version = "1.0",
        .author = "Ian"
    }, callbacks, {});

    api->RegisterSetting(
        "chatnotifier.notifymonth",
        "Notify Month End", "Send a chat message when the month had ended.",
        0,0,1,
        true, false, nullptr, 0
        );


}
