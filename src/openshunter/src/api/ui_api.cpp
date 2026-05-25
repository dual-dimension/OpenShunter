#include "ui_api.h"
#include "../shunter.h"
#include <dropdown_type.h>
#include <dropdown_func.h>
#include <gfx_func.h>
#include <vector>

static std::vector<UICallbacks> ui_callbacks;

struct VehicleInfoEntry {
    int line_count;
    OnVehicleInfoPaintFn on_paint;
};
static std::vector<VehicleInfoEntry> vehicle_info_entries;

static int  g_veh_left  = 0;
static int  g_veh_right = 0;
static int* g_veh_top   = nullptr;

static void VehicleInfoDrawLineImpl(const char* text, uint32_t colour)
{
    if (!g_veh_top) return;
    DrawString(g_veh_left, g_veh_right, *g_veh_top, std::string_view(text), (TextColour)colour);
    *g_veh_top += GetCharacterHeight(FS_NORMAL);
}

void SetupVehicleInfoLines(int line_count, OnVehicleInfoPaintFn on_paint)
{
    vehicle_info_entries.push_back({line_count, on_paint});
}

int Shunter::GetVehicleInfoExtraLines()
{
    int total = 0;
    for (auto& e : vehicle_info_entries) total += e.line_count;
    return total;
}

void Shunter::PaintVehicleInfoLines(uint32_t vehicle_id, int left, int& top, int right)
{
    if (vehicle_info_entries.empty()) return;
    ShunterVehicleInfoContext ctx { &VehicleInfoDrawLineImpl };
    g_veh_left = left; g_veh_right = right; g_veh_top = &top;
    for (auto& e : vehicle_info_entries)
        if (e.on_paint) e.on_paint(vehicle_id, &ctx);
    g_veh_top = nullptr;
}

void SetupUIHooks(const UICallbacks ui)
{
    ui_callbacks.push_back(ui);
}


static void ShunterDrawStringImpl(int x, int y, int max_right, const char* text, uint32_t colour)
{
    DrawString(x, max_right, y, std::string_view(text), (TextColour)colour);
}


static DropDownList* g_current_dropdown = nullptr;

static void AddModMenuItemImpl(int id, const char* label)
{
    if (g_current_dropdown)
        g_current_dropdown->push_back(MakeDropDownListStringItem(std::string(label), id));
}

void Shunter::OnWindowPaint(uint16_t window_class, int left, int top, int width, int height)
{
    if (ui_callbacks.empty()) return;
    ShunterDrawContext ctx { width, height, &ShunterDrawStringImpl };
    for (auto& cb : ui_callbacks)
        if (cb.on_window_paint) cb.on_window_paint(window_class, &ctx);
}

void Shunter::PopulateToolbarMenu(int menu_id, DropDownList& list)
{
    if (ui_callbacks.empty()) return;
    g_current_dropdown = &list;
    for (auto& cb : ui_callbacks)
        if (cb.on_menu_populate) cb.on_menu_populate(menu_id, AddModMenuItemImpl);
    g_current_dropdown = nullptr;
}

bool Shunter::HandleToolbarMenuClick(int menu_id, int item_id)
{
    if (item_id < 1000) return false;
    for (auto& cb : ui_callbacks)
        if (cb.on_menu_click) cb.on_menu_click(menu_id, item_id);
    return true;
}
