#pragma once
#ifndef LOADERS_ATLASLOADER_H_
#define LOADERS_ATLASLOADER_H_

#include "enginecore/interfaces/IAssetLoader.h"

#include "enginecore/core/assets/texture/Atlas.h"
#include "enginecore/core/assets/texture/GLTexture.h"
#include "enginecore/core/assets/loaders/AutoRegisterLoader.h"

class AtlasLoader : public IAssetLoader, public AutoRegisterLoader<AssetType::ATLAS, AtlasLoader>
{
public:
	AtlasLoader(AssetsManager* const manager)
		: IAssetLoader(manager) { }
	~AtlasLoader() = default;

	virtual void operator()(const std::filesystem::path& file_or_directory, const std::string& name,
		const std::shared_ptr<configs::AssetConfig>& settings) override
	{
        auto atlasConfig = std::dynamic_pointer_cast<configs::AtlasConfig>(settings);
        if (atlasConfig && atlasConfig->type == configs::AtlasType::SEPARATE) 
        {
            /*for (const auto& file : paths.listdir(file_or_directory))
            {
                loader->add(
                    AssetType::TEXTURE,
                    file_or_directory / file.stem(),
                    name / file.stem()
                );
            }*/
        }
        auto builder = Atlas::builder();
        for (const auto& file : paths.listdir(file_or_directory)) 
        {
            if (!appendAtlas(builder, file)) 
                continue;
        }
        std::set<std::string> names = builder->getNames();
        std::shared_ptr<Atlas> atlas = builder->build<GLTexture>(2);

        m_manager->template store<Atlas>(atlas, name);
        //for (const auto& file : names) {
        //    load_animation(assets, paths, name, file_or_directory, file, atlas);
        //}
	}

private:
    bool appendAtlas(const std::shared_ptr<Atlas::Builder>& builder, const std::filesystem::path& path)
    {
        std::string name = path.stem().string();
        // skip duplicates
        if (builder->has(name))
        {
            return false;
        }
        std::shared_ptr<ImageData> data = ImageData::createFromFile(path);
        builder->addTexture(name, std::move(data));
        return true;
    }

private:

};


#endif // !LOADERS_ATLASLOADER_H_