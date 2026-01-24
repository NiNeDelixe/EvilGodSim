#include "enginecore/core/mods/ModLoader.h"

bool ModLoader::loadMod(const std::filesystem::path& path)
{
    LOG(INFO) << "Load mod:" << path.filename();

    std::filesystem::path lib_path = path;

    lib_path = lib_path.generic_u32string() +
#if defined(E_OS_WINDOWS)
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
#if defined(E_OS_WINDOWS) && defined(ENGINE_USE_WINDOWS_HEADER)
        LoadLibraryW(lib_path.generic_wstring().c_str());
#elif defined(E_OS_LINUX) || defined(E_OS_DARWIN)
        dlopen(lib_path.generic_string().c_str(), RTLD_LAZY);
#else
        LibHandle();
#endif

    if (!handle) 
    {
        LOG(ERROR) << "Failed to load mod:" << lib_path;
        return false;
    }
    
    using CreateModFunc = IGameMod* (*)();
    CreateModFunc createMod =
#if defined(E_OS_WINDOWS) && defined(ENGINE_USE_WINDOWS_HEADER)
    (CreateModFunc)GetProcAddress(handle, "IGameMod::init");
#elif defined(E_OS_LINUX) || defined(E_OS_DARWIN)
    (CreateModFunc)dlsym(handle, "IGameMod::init");
#else
    CreateModFunc();
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
    int err =
#if defined(E_OS_WINDOWS) && defined(ENGINE_USE_WINDOWS_HEADER)
    ~(FreeLibrary(loaded_mods[name].first));
#elif defined(E_OS_LINUX) || defined(E_OS_DARWIN)
    dlclose(loaded_mods[name].first);
#else
    -1; //MODS NOT SUPPORTED
#endif

    loaded_mods.erase(name);

    return err;
}
