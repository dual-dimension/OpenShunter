#include "mod_settings.h"
#include "../../../ini_type.h"
#include "../../../fileio_func.h"
#include "../../../debug.h"

#include <algorithm>
#include <set>

static std::vector<ModSettingDef> all_defs;
static std::unordered_map<std::string, int32_t> values;

static const std::string CONFIG_FILENAME = "openshunter_mods.cfg";

void ModSettings::RegisterSetting(const std::string &mod_name, const char *name, const char *label, const char *help,
                                  int32_t def, int32_t min, int32_t max,
                                  bool is_bool, bool is_dropdown,
                                  const char **dropdown_labels, int dropdown_count)
{
	ModSettingDef d;
	d.setting_name = name;
	d.mod_name = mod_name;
	d.full_key = mod_name + "." + name;
	d.label = label;
	d.help = help;
	d.def = def;
	d.min = min;
	d.max = max;
	d.is_bool = is_bool;
	d.is_dropdown = is_dropdown;

	if (dropdown_labels != nullptr) {
		for (int i = 0; i < dropdown_count; i++) {
			d.dropdown_labels.push_back(dropdown_labels[i]);
		}
	}

	all_defs.push_back(std::move(d));

	// Only set default if not already loaded from file
	if (values.find(all_defs.back().full_key) == values.end()) {
		values[all_defs.back().full_key] = def;
	}

	Debug(script, 2, "Registered mod setting '{}'", all_defs.back().full_key);
}

int32_t ModSettings::Get(const std::string &key)
{
	auto it = values.find(key);
	if (it != values.end()) return it->second;
	return 0;
}

void ModSettings::Set(const std::string &key, int32_t value)
{
	values[key] = value;
	SaveToFile();
}

bool ModSettings::Has(const std::string &key)
{
	return values.find(key) != values.end();
}

const std::vector<ModSettingDef> &ModSettings::GetAllDefs()
{
	return all_defs;
}

std::vector<std::string> ModSettings::GetModNames()
{
	std::set<std::string> names;
	for (const auto &d : all_defs) {
		names.insert(d.mod_name);
	}
	return {names.begin(), names.end()};
}

std::vector<const ModSettingDef*> ModSettings::GetSettingsForMod(const std::string &mod_name)
{
	std::vector<const ModSettingDef*> result;
	for (const auto &d : all_defs) {
		if (d.mod_name == mod_name) result.push_back(&d);
	}
	return result;
}

void ModSettings::LoadFromFile()
{
	std::string path = FioFindDirectory(Subdirectory::Base) + CONFIG_FILENAME;
	if (!FileExists(path)) {
		Debug(script, 2, "No mod settings file found, using defaults");
		return;
	}

	IniFile ini;
	ini.LoadFromDisk(path, Subdirectory::None);

	for (const auto &group : ini.groups) {
		for (const auto &item : group.items) {
			std::string key = group.name + "." + item.name;
			if (item.value.has_value()) {
				try {
					values[key] = std::stoi(*item.value);
				} catch (...) {
					Debug(script, 0, "Failed to parse mod setting value for '{}'", key);
				}
			}
		}
	}

	Debug(script, 2, "Loaded mod settings from '{}'", path);
}

void ModSettings::SaveToFile()
{
	IniFile ini;

	for (const auto &d : all_defs) {
		IniGroup &group = ini.GetOrCreateGroup(d.mod_name);
		IniItem &item = group.GetOrCreateItem(d.setting_name);
		item.SetValue(std::to_string(values[d.full_key]));
	}

	std::string path = FioFindDirectory(Subdirectory::Base) + CONFIG_FILENAME;
	ini.SaveToDisk(path);

	Debug(script, 2, "Saved mod settings to '{}'", path);
}
