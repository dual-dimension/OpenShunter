#pragma once

#include "alias.h"

struct ModInfo
{
    const char* name;
    const char* version;
    const char* author;
};

struct Callbacks
{
    OnMenuStartFn on_menu_start;
    OnMenuTickFn  on_menu_tick;

    OnGameStartFn on_game_start;
    OnGameTickFn  on_game_tick;
};

struct ModApi
{
    void (*Register)(ModInfo* info, const Callbacks callbacks);
};


extern "C"
{
    typedef void  (*RegisterMod)(ModApi* api);
}
