#include "openshunter.h"
#include "mod_api.h"
#include "mod_logic.h"
#include "../../debug.h"
#include <string>
#include <filesystem>
#include <vector>

std::vector<std::filesystem::path> OpenShunter::GetModList()
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
	Debug(script,2, "Starting loading mod: '{}'", path);
	bool success = false;
	// TODO: Make handler list and remove this in the shutdown
	auto lib = MOD_OPEN(path);
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

	// Hook up the API and call the register function from the mod
	ModApi api {};

	api.Register = &::Register;

	// Call the register function from the mod
	register_fn(&api);

	success = true;

	return success;
}

void OpenShunter::Bootstrap()
{
	Debug(script, 2, "Starting bootstrap");

    LoadModsFromFolder();

    Debug(script, 2, "Bootstrap complete");
}

void OpenShunter::Shutdown()
{
    // MOD_CLOSE(lib);
}
