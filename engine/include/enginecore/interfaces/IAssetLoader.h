#pragma once
#ifndef INTERFACES_IASSETLOADER_H_
#define INTERFACES_IASSETLOADER_H_

#include <string>
#include <filesystem>
#include <memory>
#include <concepts>

#include "enginecore/core/CoreDefines.h"
#include "enginecore/utils/types/Delegates.h"
#include "enginecore/core/assets/AssetsManager.h"

namespace configs
{
    struct AssetConfig {
        virtual ~AssetConfig() {
        }
    };

    struct LayoutConfig : AssetConfig {
        /*gui::GUI* gui;
        scriptenv env;

        LayoutCfg(gui::GUI* gui, scriptenv env) : gui(gui), env(std::move(env)) {
        }*/
    };

    struct SoundConfig : AssetConfig {
        bool keepPCM;

        SoundConfig(bool keepPCM) : keepPCM(keepPCM) {
        }
    };

    enum class AtlasType {
        ATLAS, SEPARATE
    };

    struct AtlasConfig : AssetConfig {
        AtlasType type;

        AtlasConfig(AtlasType type) : type(type) {
        }
    };
}

class IAssetLoader
{
public:
    IAssetLoader(AssetsManager* const manager)
        : m_manager(manager) {}
	virtual ~IAssetLoader() = default;

public:
	virtual void operator()(const std::filesystem::path& file_or_directory, const std::string& name,
        const std::shared_ptr<configs::AssetConfig>& settings) = 0;

protected:
    AssetsManager* const m_manager;
};

namespace CONCEPTS_NAMESPACE
{
    template<class T>
    concept IsDerivedFromIAssetLoader = std::derived_from<T, IAssetLoader>;
}


#endif // !INTERFACES_IASSETLOADER_H_