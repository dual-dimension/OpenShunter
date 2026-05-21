#include "openshunter.h"
#include "mod_api.h"
#include "mod_logic.h"
#include "../../openttd/src/debug.h"
#include <string>
#include <filesystem>
#include <vector>

std::vector<std::filesystem::path> OpenShunter::GetModList()
{
    std::vector<std::filesystem::path> mod_list;
    std::filesystem::path mod_list_path = MOD_LIST_PATH;
    if (!std::filesystem::exists(mod_list_path))
    {
        Debug("GetModList", 0, "Mod list not found: %s", mod_list_path.string().c_str());
        return mod_list;
    }

    for (auto const& dir_entry : std::filesystem::directory_iterator{mod_list_path}){

    	if(dir_entry.is_regular_file() && dir_entry.exists())
   			mod_list.push_back(dir_entry.path());
    }

    return mod_list;
}

void OpenShunter::LoadModsFromFolder()
{
	auto mod_list = GetModList();
    for (const auto& mod : mod_list)
    {
    	LoadMod(mod.string().c_str());
    }
}

bool OpenShunter::LoadMod(const char* path)
{
	Debug("LoadMod",2, "Starting loading mod: %s", path);
	bool success = false;
	auto lib = MOD_OPEN(path);
	if (!lib)
	{
		Debug("LoadMod",0, "Failed to load mod: %s", path);
		return success;
	}

	auto register_fn = MOD_SYM(lib, "RegisterMod");
	if (!register_fn)
	{
		Debug("LoadMod",0, "Failed to register mod: %s", path);
		MOD_CLOSE(lib);
		return success;
	}

	ModApi api {};

	api.Register = &Register;

	MOD_CLOSE(lib);
	success = true;

	return success;
}

void OpenShunter::Bootstrap()
{
	Debug("Bootstrap", 2, "Starting bootstrap");
    // find mods
    // load em
    // check success?
    // allow boot
    LoadModsFromFolder();

    Debug("Bootstrap", 2, "Bootstrap complete");
}

void OpenShunter::Shutdown()
{

}
