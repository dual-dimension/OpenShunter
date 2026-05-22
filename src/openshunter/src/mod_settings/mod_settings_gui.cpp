#include <stdafx.h>

#include "mod_settings_gui.h"
#include "mod_settings.h"
#include <settings_gui.h>
#include <strings_func.h>
#include <gfx_func.h>
#include <window_gui.h>
#include <window_func.h>
#include <dropdown_func.h>
#include <dropdown_type.h>
#include <timer/timer.h>
#include <timer/timer_window.h>

#include <table/strings.h>

#include <safeguards.h>

enum ModSettingsWidgets : WidgetID {
	WID_MS_CAPTION,
	WID_MS_LIST,
	WID_MS_SCROLLBAR,
	WID_MS_RESET,
	WID_MS_RESIZE,
	WID_MS_DROPDOWN,
};

struct ModSettingsWindow : Window {
	Scrollbar *vscroll;
	int line_height = 0;
	int clicked_row = -1;
	bool clicked_increase = false;
	bool clicked_dropdown = false;
	bool closing_dropdown = false;

	ModSettingsWindow(WindowDesc &desc, WindowNumber) : Window(desc)
	{
		this->CreateNestedTree();
		this->vscroll = this->GetScrollbar(WID_MS_SCROLLBAR);
		this->FinishInitNested();
		this->vscroll->SetCount(ModSettings::GetAllDefs().size());
	}

	void UpdateWidgetSize(WidgetID widget, Dimension &size, [[maybe_unused]] const Dimension &padding, [[maybe_unused]] Dimension &fill, [[maybe_unused]] Dimension &resize) override
	{
		if (widget != WID_MS_LIST) return;
		this->line_height = std::max(SETTING_BUTTON_HEIGHT, GetCharacterHeight(FS_NORMAL)) + padding.height;
		resize.width = 1;
		fill.height = resize.height = this->line_height;
		size.height = 5 * this->line_height;
	}

	void DrawWidget(const Rect &r, WidgetID widget) const override
	{
		if (widget != WID_MS_LIST) return;

		const auto &defs = ModSettings::GetAllDefs();
		if (defs.empty()) {
			DrawString(r.left, r.right, r.top + (this->line_height - GetCharacterHeight(FS_NORMAL)) / 2,
			           "No mod settings registered.", TC_LIGHT_BLUE);
			return;
		}

		bool rtl = _current_text_dir == TD_RTL;
		Rect ir = r.Shrink(WidgetDimensions::scaled.frametext, RectPadding::zero);
		Rect br = ir.WithWidth(SETTING_BUTTON_WIDTH, rtl);
		Rect tr = ir.Indent(SETTING_BUTTON_WIDTH + WidgetDimensions::scaled.hsep_wide, rtl);

		int y = r.top;
		int button_y_offset = (this->line_height - SETTING_BUTTON_HEIGHT) / 2;
		int text_y_offset   = (this->line_height - GetCharacterHeight(FS_NORMAL)) / 2;

		const auto [first, last] = this->vscroll->GetVisibleRangeIterators(defs);
		for (auto it = first; it != last; ++it) {
			const ModSettingDef &def = *it;
			int32_t value = ModSettings::Get(def.full_key);
			int row = static_cast<int>(std::distance(defs.begin(), it));

			if (def.is_bool) {
				DrawBoolButton(br.left, y + button_y_offset, COLOUR_YELLOW, COLOUR_MAUVE, value != 0, true);
			} else if (def.is_dropdown) {
				DrawDropDownButton(br.left, y + button_y_offset, COLOUR_YELLOW,
				                   this->clicked_row == row && this->clicked_dropdown, true);
			} else {
				DrawArrowButtons(br.left, y + button_y_offset, COLOUR_YELLOW,
				                 (this->clicked_row == row) ? 1 + (this->clicked_increase != rtl) : 0,
				                 value > def.min, value < def.max);
			}

			// Label: "ModName - Label: value"
			std::string display = def.mod_name + " - " + def.label + ": ";
			if (def.is_bool) {
				display += value ? "On" : "Off";
			} else if (def.is_dropdown && value >= 0 && static_cast<size_t>(value) < def.dropdown_labels.size()) {
				display += def.dropdown_labels[value];
			} else {
				display += fmt::format("{}", value);
			}

			DrawString(tr.left, tr.right, y + text_y_offset, display, TC_LIGHT_BLUE);
			y += this->line_height;
		}
	}

	void OnPaint() override
	{
		if (this->closing_dropdown) {
			this->closing_dropdown = false;
			this->clicked_dropdown = false;
		}
		this->DrawWidgets();
	}

	void OnClick([[maybe_unused]] Point pt, WidgetID widget, [[maybe_unused]] int click_count) override
	{
		if (widget != WID_MS_LIST) return;

		const auto &defs = ModSettings::GetAllDefs();
		auto it = this->vscroll->GetScrolledItemFromWidget(defs, pt.y, this, widget);
		if (it == defs.end()) return;

		const ModSettingDef &def = *it;
		int row = static_cast<int>(std::distance(defs.begin(), it));
		int32_t value = ModSettings::Get(def.full_key);

		if (this->clicked_row != row) {
			this->CloseChildWindows(WC_DROPDOWN_MENU);
			this->clicked_row = row;
			this->clicked_dropdown = false;
		}

		Rect r = this->GetWidget<NWidgetBase>(widget)->GetCurrentRect().Shrink(WidgetDimensions::scaled.frametext, RectPadding::zero);
		int x = pt.x - r.left;
		if (_current_text_dir == TD_RTL) x = r.Width() - 1 - x;

		if (IsInsideMM(x, 0, SETTING_BUTTON_WIDTH)) {
			if (def.is_bool) {
				ModSettings::Set(def.full_key, value ? 0 : 1);
			} else if (def.is_dropdown) {
				if (this->clicked_dropdown) {
					this->CloseChildWindows(WC_DROPDOWN_MENU);
					this->clicked_dropdown = false;
					this->closing_dropdown = false;
				} else {
					int rel_y = (pt.y - r.top) % this->line_height;
					Rect wi_rect;
					wi_rect.left   = pt.x - (_current_text_dir == TD_RTL ? SETTING_BUTTON_WIDTH - 1 - x : x);
					wi_rect.right  = wi_rect.left + SETTING_BUTTON_WIDTH - 1;
					wi_rect.top    = pt.y - rel_y + (this->line_height - SETTING_BUTTON_HEIGHT) / 2;
					wi_rect.bottom = wi_rect.top + SETTING_BUTTON_HEIGHT - 1;

					if (pt.y >= wi_rect.top && pt.y <= wi_rect.bottom) {
						this->clicked_dropdown = true;
						DropDownList list;
						for (size_t i = 0; i < def.dropdown_labels.size(); i++) {
							list.push_back(MakeDropDownListStringItem(std::string(def.dropdown_labels[i]), static_cast<int>(i)));
						}
						ShowDropDownListAt(this, std::move(list), value, WID_MS_DROPDOWN, wi_rect, COLOUR_ORANGE);
					}
				}
			} else {
				int32_t new_val = value;
				if (x >= SETTING_BUTTON_WIDTH / 2) {
					new_val = std::min(new_val + 1, def.max);
					this->clicked_increase = true;
				} else {
					new_val = std::max(new_val - 1, def.min);
					this->clicked_increase = false;
				}
				if (new_val != value) {
					ModSettings::Set(def.full_key, new_val);
					this->unclick_timeout.Reset();
				}
			}
		}
		this->SetDirty();
	}

	void OnDropdownSelect(WidgetID widget, int index, int) override
	{
		if (widget != WID_MS_DROPDOWN) return;
		if (this->clicked_row < 0) return;
		const auto &defs = ModSettings::GetAllDefs();
		if (static_cast<size_t>(this->clicked_row) >= defs.size()) return;
		ModSettings::Set(defs[this->clicked_row].full_key, index);
		this->SetDirty();
	}

	void OnDropdownClose(Point, WidgetID widget, int, int, bool) override
	{
		if (widget != WID_MS_DROPDOWN) return;
		this->closing_dropdown = true;
		this->SetDirty();
	}

	void OnResize() override
	{
		this->vscroll->SetCapacityFromWidget(this, WID_MS_LIST);
	}

	TimeoutTimer<TimerWindow> unclick_timeout = {std::chrono::milliseconds(150), [this]() {
		this->clicked_row = -1;
		this->SetDirty();
	}};
};

static constexpr std::initializer_list<NWidgetPart> _mod_settings_widgets = {
	NWidget(NWID_HORIZONTAL),
		NWidget(WWT_CLOSEBOX, COLOUR_MAUVE),
		NWidget(WWT_CAPTION, COLOUR_MAUVE, WID_MS_CAPTION), SetStringTip(STR_NEWGRF_SETTINGS_CAPTION),
		NWidget(WWT_DEFSIZEBOX, COLOUR_MAUVE),
	EndContainer(),
	NWidget(NWID_HORIZONTAL),
		NWidget(WWT_MATRIX, COLOUR_MAUVE, WID_MS_LIST), SetMinimalSize(300, 150), SetFill(1, 1), SetResize(1, 1), SetMatrixDataTip(1, 0), SetScrollbar(WID_MS_SCROLLBAR),
		NWidget(NWID_VSCROLLBAR, COLOUR_MAUVE, WID_MS_SCROLLBAR),
	EndContainer(),
	NWidget(NWID_HORIZONTAL),
		NWidget(WWT_PUSHTXTBTN, COLOUR_MAUVE, WID_MS_RESET), SetStringTip(STR_AI_SETTINGS_RESET), SetFill(1, 0), SetResize(1, 0),
		NWidget(WWT_RESIZEBOX, COLOUR_MAUVE, WID_MS_RESIZE),
	EndContainer(),
};

static WindowDesc _mod_settings_desc(
	WDP_CENTER, "mod_settings", 400, 200,
	SHUNTER_MOD_SETTINGS, WC_NONE, {},
	_mod_settings_widgets
);

void Shunter::ShowModSettingsWindow()
{
	AllocateWindowDescFront<ModSettingsWindow>(_mod_settings_desc, 0);
}
