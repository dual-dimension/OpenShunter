#include <stdafx.h>
#include <strings_func.h>
#include <gfx_func.h>
#include <table/strings.h>
#include <format>

#include "safeguards.h"

#include "shunter.h"

void Shunter::DrawMenuInfo()
{
    int mod_count = Shunter::GetModCount();
   	int text_y = 0 - GetCharacterHeight(FS_NORMAL) * 2;

    DrawString(0, 0, text_y, std::string(GetString(STR_MISC_MODLOADER, mod_count)), TC_FROMSTRING, SA_LEFT);
}
