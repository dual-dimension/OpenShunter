#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #define MOD_EXTENSION ".dll"
    #define MOD_OPEN(path)      LoadLibrary(path)
    #define MOD_SYM(lib, name)  GetProcAddress(lib, name)
    #define MOD_CLOSE(lib)      FreeLibrary(lib)
#elif defined(__APPLE__)
    #define MOD_EXTENSION ".dylib"
    #define MOD_OPEN(path)      dlopen(path, RTLD_NOW)
    #define MOD_SYM(lib, name)  dlsym(lib, name)
    #define MOD_CLOSE(lib)      dlclose(lib)
#else // Linux
    #define MOD_EXTENSION ".so"
    #define MOD_OPEN(path)      dlopen(path, RTLD_NOW)
    #define MOD_SYM(lib, name)  dlsym(lib, name)
    #define MOD_CLOSE(lib)      dlclose(lib)
#endif

namespace OpenShunter
{
    void Bootstrap();
    void Shutdown();
    bool LoadMod(const char* path);
}
