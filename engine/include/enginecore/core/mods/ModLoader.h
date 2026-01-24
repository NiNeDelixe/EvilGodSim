#pragma once
#ifndef MODS_MODLOADER_H_
#define MODS_MODLOADER_H_

#include <string>
#include <memory>
#include <unordered_map>
#include <filesystem>

#include <glog/logging.h>

#include "enginecore/utils/platform/SystemDetection.h"

#include "enginecore/core/mods/IGameMod.h"
#include "enginecore/core/mods/ModPaths.h"
#include "enginecore/core/EnginePaths.h"

#if defined(E_OS_WINDOWS) && defined(ENGINE_USE_WINDOWS_HEADER)
#include <windows.h>
using LibHandle = HMODULE;
#elif defined(E_OS_LINUX) || defined(E_OS_DARWIN)
#include <dlfcn.h>
using LibHandle = void*;
#else
using LibHandle = bool;
#endif

#ifdef ERROR
#undef ERROR
#endif // ERROR

class ModLoader
{
public:
	ModLoader(const EnginePaths::Ptr& mod_paths);
	~ModLoader() = default;

	bool loadMod(const std::filesystem::path& path);
	int unloadMod(const std::string& name);

private:
	std::unordered_map<std::string, std::pair<LibHandle, std::shared_ptr<IGameMod>>> loaded_mods;
	ModPaths::Ptr mod_paths;
};

#endif // !MODS_MODLOADER_H_