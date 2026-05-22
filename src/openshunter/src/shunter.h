#pragma once

#include <cstdint>

/* -----------------------------------------------------------------------
 * Public interface for OpenTTD core code.
 * This is the only header that should be included outside
 * of src/openshunter/src/.
 * ----------------------------------------------------------------------- */

namespace Shunter
{
    int GetModCount();

    /* Lifecycle */
    void Bootstrap();
    void Shutdown();

    /* Menu */
    void OnMenuStart();
    void OnMenuTick();

    /* Game */
    void OnGameStart();
    void OnGameTick();

    /* Network */
    void OnPlayerJoined(uint32_t client_id, const char* client_name);

    /* Economy */
    void OnMoneyChanged(uint8_t company_id, int64_t old_money, int64_t new_money);

    /* Time */
    void OnDayPassed(int day, int month, int year);
    void OnWeekPassed(int month, int year);
    void OnMonthPassed(int month, int year);
    void OnQuarterPassed(int quarter, int year);
    void OnYearPassed(int year);

    /* Decisions */
    bool AskCanTrainEnterTile(uint32_t tile, uint8_t tile_owner, uint8_t train_owner, bool default_result);

    /* GUI */
    void ShowModSettingsWindow();
    void DrawMenuInfo(int width, int height);
}
