#include "shunter.h"
#include "hooks.h"
#include "api/settings_api.h"
#include "api/chat_api.h"
#include "mod_settings/mod_settings.h"
#include <debug.h>

#if defined(_WIN32) || defined(_WIN64)
	#include <windows.h>
    static std::vector<HMODULE> mod_object_list;
    #define MOD_EXTENSION ".dll"
    #define MOD_OPEN(path)      LoadLibraryA(path)
    #define MOD_SYM(lib, name)  GetProcAddress(lib, name)
    #define MOD_CLOSE(lib)      FreeLibrary(lib)
#elif defined(__APPLE__)
	#include <dlfcn.h>
    static std::vector<void*> mod_object_list;
    #define MOD_EXTENSION ".dylib"
    #define MOD_OPEN(path)      dlopen(path, RTLD_NOW)
    #define MOD_SYM(lib, name)  dlsym(lib, name)
    #define MOD_CLOSE(lib)      dlclose(lib)
#else // Linux
	#include <dlfcn.h>
    static std::vector<void*> mod_object_list;
    #define MOD_EXTENSION ".so"
    #define MOD_OPEN(path)      dlopen(path, RTLD_NOW)
    #define MOD_SYM(lib, name)  dlsym(lib, name)
    #define MOD_CLOSE(lib)      dlclose(lib)
#endif

#include <filesystem>
#include <vector>
#include <algorithm>

static const char* MOD_LIST_PATH = "mods/";
static std::vector<ModApi> mod_apis;
static std::string current_mod_name;

static std::string NormalizeModName(const char* name)
{
    std::string result(name);
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

static void ApiRegister(ModInfo* info, const Callbacks callbacks, const Decisions decisions)
{
    current_mod_name = NormalizeModName(info->name);
    ::Register(info, callbacks, decisions);
}

static void ApiRegisterSetting(const char* name, const char* label, const char* help,
                               int32_t def, int32_t min, int32_t max,
                               bool is_bool, bool is_dropdown,
                               const char** dropdown_labels, int dropdown_count)
{
	ModSettings::RegisterSetting(current_mod_name, name, label, help, def, min, max, is_bool, is_dropdown, dropdown_labels, dropdown_count);
}

static std::vector<std::filesystem::path> GetModList();
static bool LoadMod(const char* path);
static void LoadModsFromFolder();

static std::vector<std::filesystem::path> GetModList()
{
    std::vector<std::filesystem::path> mod_list;
    std::filesystem::path mod_list_path = MOD_LIST_PATH;
    if (!std::filesystem::exists(mod_list_path))
    {
        Debug(script, 0, "Mod list not found: {}", mod_list_path.string().c_str());
        return mod_list;
    }

    for (auto const& dir_entry : std::filesystem::directory_iterator{mod_list_path}){

    	if(dir_entry.is_regular_file() && dir_entry.exists())
   			mod_list.push_back(dir_entry.path());
    }

    return mod_list;
}

static void LoadModsFromFolder()
{
	auto mod_list = GetModList();
	mod_apis.reserve(mod_list.size());
    for (const auto& mod : mod_list)
    {
    	LoadMod(mod.string().c_str());
    }
}

static bool LoadMod(const char* path)
{
	Debug(script,2, "Loading mod: '{}'", path);
	bool success = false;
	// TODO: Make handler list and remove this in the shutdown
	auto lib = MOD_OPEN(path);

    mod_object_list.push_back(lib);

	if (!lib)
	{
		Debug(script,0, "Failed to load mod: '{}'", path);
		return success;
	}

	auto register_fn = (RegisterMod)MOD_SYM(lib, "RegisterMod");
	if (!register_fn)
	{
		Debug(script,0, "Failed to register mod: '{}'", path);
		MOD_CLOSE(lib);
		return success;
	}

	// Hook up the API — stored permanently so mods can safely keep the pointer to the api data they originally passed in
	// Before: this was nuked when loading another mod
	ModApi &api = mod_apis.emplace_back();
	api.Register         = &ApiRegister;
	api.GetSettingInt    = &GetSettingInt;
	api.GetSettingBool   = &GetSettingBool;
	api.RegisterSetting  = &ApiRegisterSetting;
	api.SendChat         = &SendChat;

	// Call the register function from the mod
	register_fn(&api);

	success = true;

	return success;
}

void Shunter::Bootstrap()
{
	Debug(script, 2, "Starting bootstrap");

    ModSettings::LoadFromFile();
    LoadModsFromFolder();

    Debug(script, 2, "Bootstrap complete");
}

void Shunter::Shutdown()
{
    Debug(script, 2, "Unloading {} mods", GetModCount());
    // MOD_CLOSE(lib);
    for (auto lib : mod_object_list) {
        MOD_CLOSE(lib);
    }
}

int Shunter::GetModCount()
{
    return mod_apis.size();
}
