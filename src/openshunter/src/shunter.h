#pragma once

#include <cstdint>
#include <dropdown_type.h>

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

    /* Movement */
    void OnVehicleEnterTile(uint32_t vehicle_id, uint8_t vehicle_type, uint8_t owner, uint32_t tile);

    /* GUI */
    void ShowModSettingsWindow();
    void DrawMenuInfo(int width, int height);

    /* UI hooks */
    void OnWindowPaint(uint16_t window_class, int left, int top, int width, int height);
    void PopulateToolbarMenu(int menu_id, DropDownList& list);
    bool HandleToolbarMenuClick(int menu_id, int item_id);

    /* Vehicle info lines */
    int  GetVehicleInfoExtraLines();
    void PaintVehicleInfoLines(uint32_t vehicle_id, int left, int& top, int right);
}
