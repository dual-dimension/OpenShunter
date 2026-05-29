#pragma once

#include <cstdint>

namespace API
{
	int64_t GetSettingInt(const char* name);
	bool    GetSettingBool(const char* name);
}
