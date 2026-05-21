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
    OnStartFn on_start;
    OnTickFn on_tick;
};

struct ModApi
{
    void (*Register)(ModInfo* info, const Callbacks callbacks);
};


extern "C"
{
    typedef void  (*RegisterMod)(ModApi* api);
}
