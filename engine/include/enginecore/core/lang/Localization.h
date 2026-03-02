#pragma once
#ifndef LANG_LOCALIZATION_H_
#define LANG_LOCALIZATION_H_

#include "enginecore/core/CoreDefines.h"

#include <filesystem>
#include <string>
#include <unordered_map>
#include <fstream>

#include <glog/logging.h>

#include "enginecore/utils/types/JsonDefines.h"

class Localization
{
public:
    static void init(const std::filesystem::path& resources_root, const std::string& language);
    static void setLanguage(const std::string& language);

    static std::string tr(const std::string& key);

private:
    static std::unordered_map<std::string, std::string> load(const std::filesystem::path& file);
    static void flatten(const std::string& prefix, const Json& json, std::unordered_map<std::string, std::string>& out);

private:
    static inline std::filesystem::path m_resources_root = "resources";
    static inline std::string m_current_language = "en_en";
    static inline std::unordered_map<std::string, std::string> m_english{};
    static inline std::unordered_map<std::string, std::string> m_current{};
};


#endif // LANG_LOCALIZATION_H_
