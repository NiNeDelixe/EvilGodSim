#pragma once
#ifndef LOADERS_GLTEXTURELOADER_H_
#define LOADERS_GLTEXTURELOADER_H_

#include "enginecore/interfaces/IAssetLoader.h"

#include "enginecore/core/assets/loaders/AutoRegisterLoader.h"

#include "enginecore/core/assets/texture/GLTexture.h"

class GLTextureLoader : public IAssetLoader, public AutoRegisterLoader<AssetType::TEXTURE, GLTextureLoader>
{
public:
	GLTextureLoader(AssetsManager* const manager)
		: IAssetLoader(manager) {}
	~GLTextureLoader() = default;

	virtual void operator()(const std::filesystem::path& file_or_directory, const std::string& name,
		const std::shared_ptr<configs::AssetConfig>& settings) override
	{
		std::shared_ptr<Texture> texture = Texture::template createFromFile<GLTexture>(file_or_directory);
		m_manager->template store<Texture>(texture, name);
	}

private:
	
};


#endif // !LOADERS_GLTEXTURELOADER_H_