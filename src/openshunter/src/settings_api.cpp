#include "settings_api.h"
#include "mod_settings.h"
#include "../../settings_internal.h"
#include "../../settings_type.h"
#include <climits>

int64_t GetSettingInt(const char* name)
{
    std::string key(name);
    if (ModSettings::Has(key)) return ModSettings::Get(key);

    const SettingDesc* sd = GetSettingFromName(name);
    if (sd == nullptr || !sd->IsIntSetting()) return INT64_MIN;
    return static_cast<const IntSettingDesc*>(sd)->Read(&GetGameSettings());
}

bool GetSettingBool(const char* name)
{
    std::string key(name);
    if (ModSettings::Has(key)) return ModSettings::Get(key) != 0;

    const SettingDesc* sd = GetSettingFromName(name);
    if (sd == nullptr || !sd->IsIntSetting()) return false;
    return static_cast<const IntSettingDesc*>(sd)->Read(&GetGameSettings()) != 0;
}
