#pragma once
#ifndef MODS_MODPATHS_P_H_
#define MODS_MODPATHS_P_H_

#include <filesystem>
#include <list>
#include <string>

class ModPathsPrivate
{
public:
	ModPathsPrivate() = default;
	~ModPathsPrivate() = default;

public:
	const std::list<std::string>& getResourceFolders() const { return this->resource_folders; }
	const std::filesystem::path& getLibrary() const { return this->library; }
	const std::filesystem::path& getResources() const { return this->resources; }

private:
	std::filesystem::path resources = "res";
	std::filesystem::path library = ".";

	std::list<std::string> resource_folders;
};


#endif // !MODS_MODPATHS_P_H_