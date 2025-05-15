#pragma once
#ifndef CORE_ENGINEPATHS_H_
#define CORE_ENGINEPATHS_H_

#include <filesystem>
#include <vector>
#include <unordered_map>
#include <string>
#include <optional>

#include "enginecore/core/CoreDefines.h"

#include "enginecore/core/EnginePaths_p.h"

struct PathsRoots;

class EnginePaths
{
private:
    DECLARE_PRIVATE(EnginePaths);

public:
    DECLARE_PTR(EnginePaths);

public:
	EnginePaths() = default;
	~EnginePaths() = default;

public:
    std::list<std::filesystem::path> listDirectory(const std::string_view& folder_name);
    std::list<std::filesystem::path> listResources();

private:
    std::shared_ptr<EnginePathsPrivate> d_ptr = std::make_shared<EnginePathsPrivate>();
};


#endif // !CORE_ENGINEPATHS_H_