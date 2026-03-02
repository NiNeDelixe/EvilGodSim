#include "enginecore/core/lang/Localization.h"

void Localization::init(const std::filesystem::path &resources_root, const std::string &language)
{
    m_resources_root = resources_root;
    m_english = load(m_resources_root / "lang" / "en_en.json");
    setLanguage(language);
}

void Localization::setLanguage(const std::string &language)
{
    if (language.empty() || language == "auto")
    {
        m_current_language = "en_en";
    }
    else
    {
        m_current_language = language;
    }

    if (m_current_language == "en_en")
    {
        m_current = m_english;
        return;
    }

    m_current = load(m_resources_root / "lang" / (m_current_language + ".json"));
}

std::string Localization::tr(const std::string &key)
{
    const auto found_current = m_current.find(key);
    if (found_current != m_current.end())
    {
        return found_current->second;
    }

    const auto found_en = m_english.find(key);
    if (found_en != m_english.end())
    {
        return found_en->second;
    }

    return key;
}

std::unordered_map<std::string, std::string> Localization::load(const std::filesystem::path &file)
{
    std::unordered_map<std::string, std::string> result;

    if (!std::filesystem::exists(file))
    {
        LOG(WARNING) << "language file not found: " << file;
        return result;
    }

    std::ifstream stream(file);
    if (!stream.is_open())
    {
        LOG(WARNING) << "language file can't be opened: " << file;
        return result;
    }

    Json json = Json::parse(stream, nullptr, true, true);
    flatten("", json, result);
    return result;
}

void Localization::flatten(const std::string &prefix, const Json &json, std::unordered_map<std::string, std::string> &out)
{
    if (json.is_string())
    {
        out[prefix] = json.get<std::string>();
        return;
    }

    if (!json.is_object())
    {
        return;
    }

    for (auto it = json.begin(); it != json.end(); ++it)
    {
        const std::string next_key = prefix.empty() ? it.key() : prefix + "." + it.key();
        flatten(next_key, it.value(), out);
    }
}
