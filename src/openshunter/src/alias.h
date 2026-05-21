#pragma once

#include <cstdint>

/* Menu */
using OnMenuStartFn = void(*)();
using OnMenuTickFn  = void(*)();

/* Game */
using OnGameStartFn = void(*)();
using OnGameTickFn  = void(*)();

/* Network */
using OnPlayerJoinedFn = void(*)(uint32_t client_id, const char* client_name);

/* Economy */
using OnMoneyChangedFn = void(*)(uint8_t company_id, int64_t old_money, int64_t new_money);

/* Time */
using OnDayPassedFn     = void(*)(int day, int month, int year);
using OnWeekPassedFn    = void(*)(int month, int year);
using OnMonthPassedFn   = void(*)(int month, int year);
using OnQuarterPassedFn = void(*)(int quarter, int year);
using OnYearPassedFn    = void(*)(int year);

/* Decisions - filter hooks that receive and return the engine's default result */
using AskCanTrainEnterTileFn = bool(*)(uint32_t tile, uint8_t tile_owner, uint8_t train_owner, bool default_result);
