#pragma once
#ifndef MODS_MODPATHS_H_
#define MODS_MODPATHS_H_

#include <filesystem>
#include <list>
#include <string>

#include "enginecore/core/CoreDefines.h"

#include "enginecore/core/mods/ModPaths_p.h"

class ModPaths
{
public:
	DECLARE_PTR(ModPaths)
	DECLARE_WPTR(ModPaths)

public:
	ModPaths() = default;
	~ModPaths() = default;

	const std::list<std::string>& getResourceFolders() const { return d_ptr->getResourceFolders(); }
	const std::filesystem::path& getLibrary() const { return d_ptr->getLibrary(); }
	const std::filesystem::path& getResources() const { return d_ptr->getResources(); }

private:
	std::shared_ptr<ModPathsPrivate> d_ptr = std::make_shared<ModPathsPrivate>();
};


#endif // !MODS_MODPATHS_H_