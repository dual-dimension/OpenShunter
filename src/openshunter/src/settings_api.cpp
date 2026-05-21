#include "settings_api.h"
#include "../../settings_internal.h"
#include "../../settings_type.h"
#include <climits>

int64_t GetSettingInt(const char* name)
{
    const SettingDesc* sd = GetSettingFromName(name);
    if (sd == nullptr || !sd->IsIntSetting()) return INT64_MIN;
    return static_cast<const IntSettingDesc*>(sd)->Read(&GetGameSettings());
}

bool GetSettingBool(const char* name)
{
    const SettingDesc* sd = GetSettingFromName(name);
    if (sd == nullptr || !sd->IsIntSetting()) return false;
    return static_cast<const IntSettingDesc*>(sd)->Read(&GetGameSettings()) != 0;
}
