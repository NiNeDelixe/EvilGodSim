#pragma once
#ifndef LOADERS_SHADERLOADER_H_
#define LOADERS_SHADERLOADER_H_

#include "enginecore/interfaces/IAssetLoader.h"

#include "enginecore/core/assets/shader/GLShader.h"

class ShaderLoader : public IAssetLoader
{
public:
	ShaderLoader(AssetsManager* const manager)
		: IAssetLoader(manager) { }
	~ShaderLoader() = default;

	void operator()(const std::filesystem::path& file_or_directory, const std::string& name, const std::shared_ptr<configs::AssetConfig>& settings) override 
	{
		auto shader = GLShader::createFromFile(file_or_directory.u32string() + U".vert", file_or_directory.u32string() + U".frag");
		m_manager->store(shader, name);
	}

private:

};


#endif // !LOADERS_SHADERLOADER_H_