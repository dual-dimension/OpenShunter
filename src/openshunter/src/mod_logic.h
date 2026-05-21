#include "mod_api.h"
#include "alias.h"

void Register(ModInfo* info, const Callbacks callbacks, const Decisions decisions);

namespace OpenShunter
{
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
}
