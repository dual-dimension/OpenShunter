#include "mod_api.h"
#include "openshunter/src/api/chat_api.h"
#include "openshunter/src/api/networking_api.h"
#include "openshunter/src/hooks.h"
#include "ui_api.h"
#include "../mod_settings/mod_settings.h"
#include <string>

static std::string g_current_mod_name;

void RegisterMod(ModInfo* info, const Callbacks callbacks, const Decisions decisions)
{
	g_current_mod_name = info->name;
	SetupHooks(info, callbacks, decisions);
}

void RegisterUICallbacks(const UICallbacks ui)
{
	::SetupUIHooks(ui);
}

void RegisterVehicleInfoLines(int line_count, OnVehicleInfoPaintFn on_paint)
{
	::SetupVehicleInfoLines(line_count, on_paint);
}

void SendChat(const char *message)
{
	API::SendChat(message);
}

bool IsNetworking()
{
	return API::IsNetworking();
}

bool IsServer()
{
	return API::IsServer();
}

/* Settings */
void RegisterSetting(const char *name, const char *label, const char *help,
                                  int32_t def, int32_t min, int32_t max,
                                  bool is_bool, bool is_dropdown,
                                  const char **dropdown_labels, int dropdown_count)
{
	std::string full_key = g_current_mod_name + "." + name;
	ModSettings::RegisterSetting(full_key.c_str(), label, help, def, min, max, is_bool, is_dropdown, dropdown_labels, dropdown_count);
}

bool GetSettingBool(const char *name)
{
	return (bool)ModSettings::Get(name);
}

int GetSettingInt(const char *name)
{
	return (int)ModSettings::Get(name);
}
