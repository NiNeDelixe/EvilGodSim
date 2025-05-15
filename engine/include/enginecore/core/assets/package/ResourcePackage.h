#pragma once
#ifndef PACKAGES_RESOURCEPACKAGE_H_
#define PACKAGES_RESOURCEPACKAGE_H_

#include <string>
#include <vector>
#include <filesystem>

enum class DependencyLevel 
{
    required,  // dependency must be installed
    optional,  // dependency will be installed if found
    weak,      // only affects packs order
};

/// @brief Content-pack that should be installed earlier the dependent
struct DependencyPack 
{
    DependencyLevel level;
    std::string id;
};

class ResourcePackage
{
public:
	ResourcePackage() = default;
	~ResourcePackage() = default;

public:
    static inline const std::string PACKAGE_FILENAME = "package.json";
    static inline const std::string CONTENT_FILENAME = "content.json";
    static inline const std::filesystem::path BLOCKS_FOLDER = "blocks";
    static inline const std::filesystem::path ITEMS_FOLDER = "items";
    static inline const std::filesystem::path ENTITIES_FOLDER = "entities";
    static inline const std::filesystem::path GENERATORS_FOLDER = "generators";
    static const std::vector<std::string> RESERVED_NAMES;

private:
    std::string m_id = "none";
    std::string m_title = "untitled";
    std::string m_version = "0.0";
    std::string m_creator = "";
    std::string m_description = "no description";
    std::filesystem::path m_folder;
    std::filesystem::path m_path;
    std::vector<DependencyPack> m_dependencies;
    std::string m_source = "";
};


#endif // !PACKAGES_RESOURCEPACKAGE_H_