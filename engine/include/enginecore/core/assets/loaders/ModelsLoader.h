#pragma once
#ifndef LOADERS_MODELSLOADER_H_
#define LOADERS_MODELSLOADER_H_

#include "enginecore/core/CoreDefines.h"

#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glog/logging.h>

#include "enginecore/interfaces/IAssetLoader.h"

#include "enginecore/core/assets/loaders/AutoRegisterLoader.h"
#include "enginecore/core/graphics/render/Model.h"

class ModelsLoader : public IAssetLoader, public AutoRegisterLoader<AssetType::MODEL, ModelsLoader>
{
public:
	ModelsLoader(AssetsManager* const manager)
		: IAssetLoader(manager) {}
	~ModelsLoader() = default;

	void operator()(const std::filesystem::path& file_or_directory, const std::string& name,
		const std::shared_ptr<configs::AssetConfig>& settings) override;

	std::shared_ptr<Model> processScene(const aiScene* scene);
	std::shared_ptr<Mesh<DefaultAtributes>> processMesh(aiMesh* mesh);
	std::vector<float> extractVertexData(aiMesh* mesh);
	std::vector<uint32_t> extractIndexData(aiMesh* mesh);

private:

};


#endif // !LOADERS_MODELSLOADER_H_