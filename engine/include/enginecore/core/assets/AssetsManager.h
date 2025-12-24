#pragma once
#ifndef ASSETS_ASSETSMANAGER_H_
#define ASSETS_ASSETSMANAGER_H_

#include <unordered_map>
#include <memory>
#include <string> 
#include <concepts>
#include <typeindex>
#include <exception>

#include "enginecore/interfaces/IAsset.h"
#include "enginecore/core/CoreDefines.h"
#include "enginecore/utils/StringUtils.h"

namespace CONCEPTS_NAMESPACE
{
    template<typename T>
    concept IsDerivedFromIAsset = std::derived_from<T, IAsset>;
}

class AssetsManager
{
private:
    using assets_map = std::unordered_map<std::string, std::shared_ptr<IAsset>>;
    using types_map = std::unordered_map<std::type_index, assets_map>;

public:
    AssetsManager() = default;
	~AssetsManager() = default;

public:
    static const std::shared_ptr<AssetsManager> instance() { return m_instance; }

public:
    template<CONCEPTS_NAMESPACE::IsDerivedFromIAsset T>
    std::pair<assets_map::iterator, bool> store(const std::shared_ptr<T>& asset, const std::string& name)
    {
        return m_assets[typeid(T)].insert(
            std::pair<std::string, std::shared_ptr<IAsset>>{ name, std::dynamic_pointer_cast<IAsset, T>(asset) });
    }

    template<CONCEPTS_NAMESPACE::IsDerivedFromIAsset T>
    T* get(const std::string& name) const 
    {
        const auto& mapIter = m_assets.find(typeid(T));
        if (mapIter == m_assets.end())
        {
            return nullptr;
        }
        const auto& map = mapIter->second;
        const auto& found = map.find(name);
        if (found == map.end()) 
        {
            return nullptr;
        }
        return static_cast<T*>(found->second.get());
    }

    template<CONCEPTS_NAMESPACE::IsDerivedFromIAsset T>
    std::vector<T*> get() const
    {
        std::vector<T*> result;
        const auto& mapIter = m_assets.find(typeid(T));
        if (mapIter != m_assets.end())
        {
            const auto& map = mapIter->second;
            result.reserve(map.size());
            for (const auto& pair : map)
            {
                result.push_back(static_cast<T*>(pair.second.get()));
            }
        }
        return result;
    }

    template<CONCEPTS_NAMESPACE::IsDerivedFromIAsset T>
    T& require(const std::string& name) const 
    {
        T* asset = get<T>(name);
        if (asset == nullptr) 
        {
            throw std::runtime_error(UTILS_NAMESPACE::string::quote(name) + " asset not found");
        }
        return *asset;
    }

    template<CONCEPTS_NAMESPACE::IsDerivedFromIAsset T>
    std::optional<const assets_map*> getMap() const 
    {     
        const auto& mapIter = m_assets.find(typeid(T));
        if (mapIter == m_assets.end())
        {
            return std::nullopt;
        }
        return &mapIter->second;
    }

private:
    types_map m_assets;

    static inline std::shared_ptr<AssetsManager> m_instance = std::make_shared<AssetsManager>();
};


#endif // !ASSETS_ASSETSMANAGER_H_