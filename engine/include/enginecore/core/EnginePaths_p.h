#pragma once
#ifndef CORE_ENGINE_P_H_
#define CORE_ENGINE_P_H_

#include <filesystem>
#include <vector>
#include <unordered_map>
#include <string>
#include <optional>

struct PathsRoot
{
	std::string name;
	std::filesystem::path path;

	PathsRoot(std::string name, std::filesystem::path path)
		: name(std::move(name)), path(std::move(path)) {
	}
};

class EnginePathsPrivate
{
public:
	EnginePathsPrivate()
	{
	}

	~EnginePathsPrivate()
	{
	}

public:
	const std::vector<PathsRoot>& roots() const { return this->m_roots; }
	const std::filesystem::path& resources() const { return this->resources_folder; }

private:
	std::filesystem::path user_files_folder = ".";
	std::filesystem::path resources_folder = "resources";
	std::filesystem::path mods_folder = "mods";
	std::optional<std::filesystem::path> scripts_folder;
	std::vector<std::string> content_entry_points;
	std::vector<std::string> mounted;
	std::vector<PathsRoot> m_roots;
};


#endif // !CORE_ENGINE_P_H_