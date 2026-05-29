#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct ModSettingDef
{
	std::string full_key;      // "ModName.setting_name"
	std::string setting_name;  // "setting_name"
	std::string label;         // Display label
	std::string help;          // Help/tooltip text
	int32_t def;               // Default value
	int32_t min;               // Minimum value
	int32_t max;               // Maximum value (stored as int32_t for simplicity)
	bool is_bool;
	bool is_dropdown;
	std::vector<std::string> dropdown_labels;
};

namespace ModSettings
{
	void RegisterSetting(const char *name, const char *label, const char *help,
	                     int32_t def, int32_t min, int32_t max,
	                     bool is_bool, bool is_dropdown,
	                     const char **dropdown_labels, int dropdown_count);

	int32_t Get(const std::string &key);
	void    Set(const std::string &key, int32_t value);
	bool    Has(const std::string &key);

	const std::vector<ModSettingDef> &GetAllDefs();

	void LoadFromFile();
	void SaveToFile();
}
