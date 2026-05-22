#include "mod_api.h"

extern "C" __declspec(dllexport) void RegisterMod(ModApi* api)
{
    api->Register(new ModInfo{
        .name = "Settings Test",
        .version = "1.0",
        .author = "Ian"
    }, {}, {});

    api->RegisterSetting(
        "test.setting",
        "Test Setting", "A Very Nice Test Setting!",
        0,0,1,
        true, false, nullptr, 0
        );
}
