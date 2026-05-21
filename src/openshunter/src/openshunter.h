#pragma once
#include "mod_logic.h"
#include <filesystem>
#include <vector>


#if defined(_WIN32) || defined(_WIN64)
	#include <windows.h>
    #define MOD_EXTENSION ".dll"
    #define MOD_OPEN(path)      LoadLibraryA(path)
    #define MOD_SYM(lib, name)  GetProcAddress(lib, name)
    #define MOD_CLOSE(lib)      FreeLibrary(lib)
#elif defined(__APPLE__)
	#include <dlfcn.h>
    #define MOD_EXTENSION ".dylib"
    #define MOD_OPEN(path)      dlopen(path, RTLD_NOW)
    #define MOD_SYM(lib, name)  dlsym(lib, name)
    #define MOD_CLOSE(lib)      dlclose(lib)
#else // Linux
	#include <dlfcn.h>
    #define MOD_EXTENSION ".so"
    #define MOD_OPEN(path)      dlopen(path, RTLD_NOW)
    #define MOD_SYM(lib, name)  dlsym(lib, name)
    #define MOD_CLOSE(lib)      dlclose(lib)
#endif

static const char* MOD_LIST_PATH = "mods/";

#include "mod_logic.h"

namespace OpenShunter
{
    void Bootstrap();
    void Shutdown();
    std::vector<std::filesystem::path> GetModList();
    void LoadModsFromFolder();
    bool LoadMod(const char* path);
}
