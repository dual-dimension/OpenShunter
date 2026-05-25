#pragma once
#include "mod_api.h"

void SetupUIHooks(const UICallbacks ui);
void SetupVehicleInfoLines(int line_count, OnVehicleInfoPaintFn on_paint);
