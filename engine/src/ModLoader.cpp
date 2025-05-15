#include "enginecore/core/mods/ModLoader.h"

bool ModLoader::loadMod(const std::filesystem::path& path)
{
    LOG(INFO) << "Load mod:" << path.filename();

    std::filesystem::path lib_path = path;

    lib_path = lib_path.generic_u32string() +
#ifdef E_OS_WINDOWS
    U".dll";
#elif defined(E_OS_LINUX) || defined(E_OS_DARWIN)
    U".o";
#endif

    if (!std::filesystem::exists(lib_path))
    {
        LOG(ERROR) << "Mod library dont found:" << lib_path;
        return false;
    }

    LibHandle handle =
#ifdef E_OS_WINDOWS
        LoadLibraryW(lib_path.generic_wstring().c_str());
#elif defined(E_OS_LINUX) || defined(E_OS_DARWIN)
        dlopen(lib_path.generic_string().c_str(), RTLD_LAZY);
#endif

    if (!handle) 
    {
        LOG(ERROR) << "Failed to load mod:" << lib_path;
        return false;
    }
    
    using CreateModFunc = IGameMod* (*)();
    CreateModFunc createMod =
#ifdef E_OS_WINDOWS
    (CreateModFunc)GetProcAddress(handle, "IGameMod::init");
#elif defined(E_OS_LINUX) || defined(E_OS_DARWIN)
    (CreateModFunc)dlsym(handle, "IGameMod::init");
#endif

    if (!createMod) 
    {
        LOG(ERROR) << "Mod must have createMod function:" << lib_path;
        return false;
    }

    std::shared_ptr<IGameMod> mod = std::shared_ptr<IGameMod>(createMod());
    if (!mod) 
    {
        LOG(ERROR) << "Mod creation failed:" << lib_path;
        return false;
    }

    mod->onLoad();
    loaded_mods[mod->getName()] = { handle, mod };

    return true;
}

int ModLoader::unloadMod(const std::string& name)
{
#ifdef E_OS_WINDOWS
    return ~(FreeLibrary(loaded_mods[name].first));
#elif defined(E_OS_LINUX) || defined(E_OS_DARWIN)
    return dlclose(loaded_mods[name].first);
#endif

    loaded_mods.erase(name);
}
