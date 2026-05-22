#include <stdafx.h>
#include <strings_func.h>
#include <gfx_func.h>
#include <table/strings.h>
#include <format>

#include "safeguards.h"

#include "shunter.h"

void Shunter::DrawMenuInfo(int width, int height)
{
    int mod_count = Shunter::GetModCount();
    int text_y = height - GetCharacterHeight(FS_NORMAL);
    DrawString(0, width - 1, text_y, GetString(STR_MISC_MODLOADER, mod_count), TC_FROMSTRING, SA_LEFT);
}
